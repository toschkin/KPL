// GPIOmDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "GPIOmDlg.h"

#include "TuConfigTUDlg.h"


#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_PRINT1	WM_USER + 420

// диалоговое окно CIec101mDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);

// диалоговое окно CGPIOmDlg

IMPLEMENT_DYNAMIC(CGPIOmDlg, CDialog)

CGPIOmDlg::CGPIOmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGPIOmDlg::IDD, pParent)
	, m_bService(FALSE)
	, m_bButtonsEnable(FALSE)
{
	nProcNum=0;
	strTitle.Format("Процесс №%d: GPIO",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);	
}

CGPIOmDlg::~CGPIOmDlg()
{
}

void CGPIOmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bService);
	DDX_Control(pDX, IDC_GRID, m_Grid);	
	DDX_Check(pDX, IDC_CHECK2, m_bButtonsEnable);
	DDX_Control(pDX, IDC_EDIT1, m_edtDrebezgButton);
	DDX_Control(pDX, IDC_EDIT10, m_edtDrebezgTS);
	DDX_Control(pDX, IDC_CHECK2, m_chkButtonsEnable);
}


BEGIN_MESSAGE_MAP(CGPIOmDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)	
	ON_COMMAND(IDM_DEL, OnDel)
	ON_WM_GETMINMAXINFO()		
	//ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)	
	ON_COMMAND(IDM_PRINT1, OnPrint1)	
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
END_MESSAGE_MAP()


// обработчики сообщений CGPIOmDlg
afx_msg void CGPIOmDlg::OnPrint1(void)
{
	m_Grid.Print();
}
void CGPIOmDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}

BOOL CGPIOmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	strTitle.Format("Процесс №%d: GPIO",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);	
	
	m_bService = m_GPIOm.SERVICE;
	
	if(m_GPIOm.m_nVersion > 15)
	{
		m_bButtonsEnable = m_GPIOm.BUTTONS_ENABLE;

		CString str;
		str.Format("%d",m_GPIOm.BUTTONS_DELAY);
		m_edtDrebezgButton.SetWindowText(str);

		str.Format("%d",m_GPIOm.TS_DELAY);
		m_edtDrebezgTS.SetWindowText(str);
	}
	else
	{
		m_chkButtonsEnable.EnableWindow(FALSE);
		m_edtDrebezgButton.EnableWindow(FALSE);
		m_edtDrebezgTS.EnableWindow(FALSE);
	}
	UpdateData(FALSE);

	m_Grid.SetColumnCount(3);
	m_Grid.SetFixedRowCount(1);		
	m_Grid.EnableTitleTips(0);
	m_Grid.SetItemText(0,0,"Комментарий");
	m_Grid.SetItemText(0,1,"Канал порта ввода GPIO");
	m_Grid.SetItemText(0,2,"Нач. адрес в ПМЗ канала");
	
	UpdateDataGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CGPIOmDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	
	if(ProcessSave()==FALSE)
		return;
	

	CDialog::OnOK();
}
void CGPIOmDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	long nCentery = (long)(cy / 2);
	long nCenter = (long)(cx / 2);

	int dx = 5;
	//m_Grid.GetClientRect
	if (IsWindow(m_Grid.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_Grid.MoveWindow(2*dx, 100, r.right - r.left - 4*dx, r.bottom - r.top - 70 - dx*2, TRUE);		
	}

	CWnd* pWnd = this->GetDlgItem(IDOK);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter - 100 , cy - 26, 79, 23);
	}
	pWnd = this->GetDlgItem(IDCANCEL);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter + 20, cy - 26, 79, 23);
	}

	Invalidate(FALSE);
	// TODO: добавьте свой код обработчика сообщений
}
BOOL CGPIOmDlg::PreTranslateMessage(MSG* pMsg)
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
afx_msg void CGPIOmDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить канал");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить канал");	
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
BOOL CGPIOmDlg::ProcessSave(void)
{
	for(int row = 1; row < m_Grid.GetRowCount(); row++)
	{
		for(int col = 0; col < m_Grid.GetColumnCount(); col++)
		{
			m_Grid.SetItemBkColour(row,col,RGB(255,255,255));
		}
	}	
	m_Grid.Refresh();

	UpdateData(TRUE);

	m_GPIOm.SERVICE = m_bService;

	if(m_GPIOm.m_nVersion > 15)
	{
		m_GPIOm.BUTTONS_ENABLE = m_bButtonsEnable;
		CString str;		
		m_edtDrebezgButton.GetWindowText(str);
		m_GPIOm.BUTTONS_DELAY = atoi(str);		
		m_edtDrebezgTS.GetWindowText(str);
		m_GPIOm.TS_DELAY = atoi(str);
	}

	m_GPIOm.m_IndividualStructureGPIOArray.RemoveAll();
	
	int nTotalAmount=0;
	CString str;

	for(int i = 1; i < m_Grid.GetRowCount(); i++)
	{
		IndividualStructureGPIO is101;	
		int nCol=0;

		is101.strCOMMENT = m_Grid.GetItemText(i,nCol++);

		str = m_Grid.GetItemText(i,nCol++);
		is101.CHANNEL_NUM = atoi(str);
		if((is101.CHANNEL_NUM>7)||(is101.CHANNEL_NUM<=0))
		{
			AfxMessageBox("Номер канала порта ввода GPIO: 0..7!");
			return FALSE;
		}
		
		str = m_Grid.GetItemText(i,nCol++);
		is101.ADDRESS_PMZ = atoi(str);
		
		nTotalAmount++;

		if((is101.ADDRESS_PMZ < m_nStartPMZAddr)
			||(is101.ADDRESS_PMZ > m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("Адрес ПМЗ в строке %d выходит за пределы карты памяти ПРОЦЕССА: %d..%d!",i,m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			for(int col = 0; col < m_Grid.GetColumnCount(); col++)
			{
				m_Grid.SetItemBkColour(i,col,RGB(255,128,255));
			}
			m_Grid.EnsureVisible(i,0);
			m_Grid.Refresh();
		}
		m_GPIOm.m_IndividualStructureGPIOArray.Add(is101);		

	}

	if(nTotalAmount > m_nEndPMZAddr+1)
	{
		str.Format("%d > %d !",nTotalAmount,m_nEndPMZAddr+1);
		AfxMessageBox("Суммарное кол-во инф. объектов больше выделенного количества для данного процесса:"+str);
		//return FALSE;
	}

	for(int i = 0; i < m_GPIOm.m_IndividualStructureGPIOArray.GetSize();i++)
	{
		for(int j = 0; j < m_GPIOm.m_IndividualStructureGPIOArray.GetSize();j++)
		{
			if((IsIntersect(m_GPIOm.m_IndividualStructureGPIOArray[i].ADDRESS_PMZ,
							m_GPIOm.m_IndividualStructureGPIOArray[i].ADDRESS_PMZ,
							m_GPIOm.m_IndividualStructureGPIOArray[j].ADDRESS_PMZ,
							m_GPIOm.m_IndividualStructureGPIOArray[j].ADDRESS_PMZ))
							&&(i!=j))
			{
				str.Format("%d на %d !\r\n(строки подсвечены розовым цветом)",j+1,i+1);
				AfxMessageBox("Наложение наборов инф.объектов:"+str);
				for(int col = 0; col < m_Grid.GetColumnCount(); col++)
				{
					m_Grid.SetItemBkColour(j+1,col,RGB(255,128,128));
					m_Grid.SetItemBkColour(i+1,col,RGB(255,128,128));
				}
				m_Grid.EnsureVisible(i+1,0);
				m_Grid.Refresh();
				return FALSE;
			}
		}
	}
	
	return TRUE;
}
void CGPIOmDlg::UpdateDataGrid(void)
{
	CString str;
	m_Grid.DeleteNonFixedRows();
	for(int i = 0; i < m_GPIOm.m_IndividualStructureGPIOArray.GetSize(); i++)
	{
		int nIndex = m_Grid.InsertRow(NULL);
		int nCol = 0;
		
		m_Grid.SetItemText(nIndex,nCol,m_GPIOm.m_IndividualStructureGPIOArray[i].strCOMMENT);
		nCol++;

		str.Format("%d",m_GPIOm.m_IndividualStructureGPIOArray[i].CHANNEL_NUM);
		m_Grid.SetItemText(nIndex,nCol,str);
		m_Grid.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_GPIOm.m_IndividualStructureGPIOArray[i].ADDRESS_PMZ);
		m_Grid.SetItemText(nIndex,nCol,str);
		m_Grid.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

	}
	m_Grid.AutoSize();
	m_Grid.Refresh();
}
afx_msg void CGPIOmDlg::OnAdd()
{
	CCellID cell = m_Grid.GetFocusCell();

	ProcessSave();

	IndividualStructureGPIO is101;
	if((cell.row > 0)&&(m_GPIOm.m_IndividualStructureGPIOArray.GetCount() > 1))
	{									
		m_GPIOm.m_IndividualStructureGPIOArray.InsertAt(cell.row,is101);		
		UpdateDataGrid();		
		return;
	}
	if((cell.row == m_GPIOm.m_IndividualStructureGPIOArray.GetCount())
		||(cell.row == -1))
	{									
		m_GPIOm.m_IndividualStructureGPIOArray.Add(is101);												
		UpdateDataGrid();		
		return;
	}	
	
}
afx_msg void CGPIOmDlg::OnDel()
{
	if(m_Grid.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID SelectedCell;
	CWordArray arGrigIndexes;	

	for(int m = 1; m < m_Grid.GetRowCount(); m++)
	{
		SelectedCell.row=m;
		SelectedCell.col=0;
		BOOL bRowSelected = FALSE;
		for(int s = 1; s < m_Grid.GetColumnCount(); s++)
		{
			if(m_Grid.GetItemState(SelectedCell.row,s) & GVIS_SELECTED)
			{
				bRowSelected=TRUE;
				break;
			}
		}
		if(bRowSelected)
		{			
			arGrigIndexes.Add(SelectedCell.row);								
		}
	}
	for(int j = 0; j < arGrigIndexes.GetSize();j++)
	{				
		m_Grid.DeleteRow(arGrigIndexes[j]);				
		m_GPIOm.m_IndividualStructureGPIOArray.RemoveAt(arGrigIndexes[j]-1);				
		for(int v = j+1; v < arGrigIndexes.GetSize();v++)
		{
			arGrigIndexes[v]--;
		}
	}
	if(arGrigIndexes.GetSize()>0)
	{
		UpdateDataGrid();		
	}	
}