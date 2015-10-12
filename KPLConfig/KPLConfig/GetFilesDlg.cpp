// GetFilesDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "GetFilesDlg.h"
#include "FileManip.h"
// диалоговое окно CGetFilesDlg

IMPLEMENT_DYNAMIC(CGetFilesDlg, CDialog)

CGetFilesDlg::CGetFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetFilesDlg::IDD, pParent)
{
	m_byTypeDlg = TYPE_ALARM;
	m_pFtpConn = NULL;
}

CGetFilesDlg::~CGetFilesDlg()
{
	
}

void CGetFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRIDDISK, m_GridDisk);
	DDX_Control(pDX, IDC_GRIDKPL, m_GridKPL);	
}


BEGIN_MESSAGE_MAP(CGetFilesDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetFilesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGetFilesDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_GRIDDISK, OnGridDblClick)
	ON_BN_CLICKED(IDC_BUTTON3, &CGetFilesDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

void CGetFilesDlg::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	if((pItem->iRow < 1)||(pItem->iColumn != 0))
		return;

	CString strCmd;

	if(m_byTypeDlg == TYPE_ALARM)
		strCmd.Format("%s",m_strAlarmPath+"\\"+m_GridDisk.GetItemText(pItem->iRow,pItem->iColumn));				
	if(m_byTypeDlg == TYPE_LOG)
		strCmd.Format("%s",m_strLogPath+"\\"+m_GridDisk.GetItemText(pItem->iRow,pItem->iColumn));				
					
	HINSTANCE ret = ShellExecute( NULL,
				NULL,
				"notepad.exe",
				strCmd.GetBuffer(),
				NULL,
				SW_SHOWNORMAL);
}

void  CGetFilesDlg::UpdateDiskGrid(void)
{	
	m_GridDisk.DeleteNonFixedRows();

	CFileFind finder;
	BOOL bWorking = FALSE;
	if(m_byTypeDlg == TYPE_ALARM)
		bWorking = finder.FindFile(m_strAlarmPath+"\\*.log");				
	if(m_byTypeDlg == TYPE_LOG)
		bWorking = finder.FindFile(m_strLogPath+"\\*.log");				

	int nFilesCount = 0;
	while (bWorking)
	{					
		bWorking = finder.FindNextFile();
		
		CString str = finder.GetFileName();					
		int nIndex = m_GridDisk.InsertRow(NULL);
		m_GridDisk.SetItemText(nIndex,0,str);
		CTime tm;
		finder.GetCreationTime(tm);
		m_GridDisk.SetItemText(nIndex,1,tm.Format("%d.%m.%Y %H:%M:%S"));
		finder.GetLastWriteTime(tm);
		m_GridDisk.SetItemText(nIndex,2,tm.Format("%d.%m.%Y %H:%M:%S"));
		str.Format("%.2f",finder.GetLength()/1024.0);		
		m_GridDisk.SetItemText(nIndex,3,str);
	}		
	m_GridDisk.AutoSize();
	m_GridDisk.Refresh();
}

void CGetFilesDlg::UpdateKPLGrid(void)
{
	m_GridKPL.DeleteNonFixedRows();

	CWaitCursor wait;
	m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
	m_WaitDlg.SetText("Подключение к КПЛ...");
	

	CFtpFileFind finder(m_pFtpConn);

	BOOL bWorking = FALSE;
	if(m_byTypeDlg == TYPE_ALARM)
		bWorking = finder.FindFile(m_strFtpAlarm+"/*.log");				
	if(m_byTypeDlg == TYPE_LOG)
		bWorking = finder.FindFile(m_strFtpLog+"/*.log");				

	int nFilesCount = 0;
	while (bWorking)
	{					
		bWorking = finder.FindNextFile();
		
		CString str = finder.GetFileName();			
		int nIndex = m_GridKPL.InsertRow(NULL);
		m_GridKPL.SetItemText(nIndex,0,str);
		CTime tm;
		finder.GetCreationTime(tm);
		m_GridKPL.SetItemText(nIndex,1,tm.Format("%d.%m.%Y %H:%M:%S"));
		finder.GetLastWriteTime(tm);
		m_GridKPL.SetItemText(nIndex,2,tm.Format("%d.%m.%Y %H:%M:%S"));		
		str.Format("%.2f",finder.GetLength()/1024.0);		
		m_GridKPL.SetItemText(nIndex,3,str);
	}		
	m_WaitDlg.ShowWindow(SW_HIDE);
	m_GridKPL.AutoSize();
	m_GridKPL.Refresh();
}
// обработчики сообщений CGetFilesDlg

BOOL CGetFilesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_WaitDlg.Create(IDD_WAITDIALOG,this);
	// TODO:  Добавить дополнительную инициализацию
	
	m_GridDisk.SetColumnCount(4);	
	m_GridDisk.SetRowCount(1);
	m_GridDisk.SetFixedRowCount(1);
	
	if(m_byTypeDlg == TYPE_ALARM)
		m_GridDisk.SetItemText(0,0,"Журнал событий");
	if(m_byTypeDlg == TYPE_LOG)
		m_GridDisk.SetItemText(0,0,"Журнал обмена данными");

	m_GridDisk.SetItemText(0,1,"Создан");
	m_GridDisk.SetItemText(0,2,"Изменен");
	m_GridDisk.SetItemText(0,3,"Размер(кБ)");
	m_GridDisk.EnableSelection(0);	
	m_GridDisk.SetEditable(FALSE);
	
	m_GridKPL.SetColumnCount(4);	
	m_GridKPL.SetRowCount(1);
	m_GridKPL.SetFixedRowCount(1);
	
	if(m_byTypeDlg == TYPE_ALARM)
		m_GridKPL.SetItemText(0,0,"Журнал событий");
	if(m_byTypeDlg == TYPE_LOG)
		m_GridKPL.SetItemText(0,0,"Журнал обмена данными");

	m_GridKPL.SetItemText(0,1,"Создан");
	m_GridKPL.SetItemText(0,2,"Изменен");
	m_GridKPL.SetItemText(0,3,"Размер(кБ)");
	m_GridKPL.EnableSelection(TRUE);
	m_GridKPL.SetListMode();
	m_GridKPL.SetEditable(FALSE);
	
	UpdateDiskGrid();

	UpdateKPLGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CGetFilesDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnOK();
}
//Считать
void CGetFilesDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString strFtpDir,strDiskDir;
	if(m_byTypeDlg == TYPE_ALARM)
	{
		strFtpDir = m_strFtpAlarm+"/";				
		strDiskDir = m_strAlarmPath+"\\";
	}
	if(m_byTypeDlg == TYPE_LOG)
	{
		strFtpDir = m_strFtpLog+"/";				
		strDiskDir = m_strLogPath+"\\";
	}
	CWaitCursor wait;
	m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
	m_WaitDlg.SetText("Подключение к КПЛ...");

	int nFilesCount = 0;
	int nSelCount = 0;
	for(int row = 1; row < m_GridKPL.GetRowCount(); row++)
	{
		if(m_GridKPL.GetItemState(row,0) & GVIS_SELECTED)
		{
			nSelCount++;
			CString sFile = m_GridKPL.GetItemText(row,0);
			m_WaitDlg.SetText("Загрузка файла: "+sFile);
			if(!m_pFtpConn->GetFile(strFtpDir+sFile,strDiskDir+sFile,FALSE))
			{
				m_WaitDlg.ShowWindow(SW_HIDE);
				AfxMessageBox("Ошибка при загрузке файла:\r\n"+sFile);
				UpdateDiskGrid();
				UpdateKPLGrid();
				return;
			}		
			nFilesCount++;
		}
	}
	m_WaitDlg.ShowWindow(SW_HIDE);
	if(nSelCount == 0)
	{
		AfxMessageBox("Не выбрано ни одного файла!");
	}
	if(nFilesCount > 0)
	{
		AfxMessageBox("Файлы успешно считаны.",MB_ICONINFORMATION);
		UpdateDiskGrid();
		UpdateKPLGrid();	
	}
}
//Обновить
void CGetFilesDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateKPLGrid();
}

void CGetFilesDlg::OnBnClickedButton3()
{
	CString strFtpDir,strDiskDir;
	if(m_byTypeDlg == TYPE_ALARM)
	{		
		strDiskDir = m_strAlarmPath+"\\";
	}
	if(m_byTypeDlg == TYPE_LOG)
	{		
		strDiskDir = m_strLogPath+"\\";
	}
	// TODO: добавьте свой код обработчика уведомлений
	CFileManip::DelTree(strDiskDir+"*.*");
	UpdateDiskGrid();
}

BOOL CGetFilesDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	if( pMsg->message == WM_KEYDOWN )
    {
        if(pMsg->wParam == VK_RETURN
            || pMsg->wParam == VK_ESCAPE )
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return TRUE;                    // DO NOT process further
        }
    }	
	return CDialog::PreTranslateMessage(pMsg);
}
