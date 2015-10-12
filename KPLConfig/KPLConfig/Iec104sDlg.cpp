// Iec104sDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "Iec104sDlg.h"


#define IDM_PRINT1 WM_USER + 420

// диалоговое окно CIec104sDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CIec104sDlg, CDialog)

CIec104sDlg::CIec104sDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIec104sDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("Процесс №%d: IEC 870-5-104 (SLAVE)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
	m_byProcType = 8;

}

CIec104sDlg::~CIec104sDlg()
{
}

void CIec104sDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CIec104sDlg, CDialog)
	ON_WM_SIZE()	
	ON_WM_GETMINMAXINFO()		
	ON_COMMAND(IDM_PRINT1, OnPrint)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
END_MESSAGE_MAP()

afx_msg void CIec104sDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	
	
	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CIec104sDlg::OnPrint(void)
{
	m_Grid.Print();
}

// обработчики сообщений CIec104sDlg
void CIec104sDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
BOOL CIec104sDlg::ProcessSave(void)
{
	CString str;
		
	m_Iec104s.ADRESS_IP = m_Grid.GetItemText(1,1);
	
	str = m_Grid.GetItemText(2,1);
	m_Iec104s.GLOBAL_ASDU = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_Iec104s.UST_CONNECT_t0 = atoi(str);

	str = m_Grid.GetItemText(4,1);
	m_Iec104s.TEST_APDU_t1 = atoi(str);

	str = m_Grid.GetItemText(5,1);
	m_Iec104s.CONFIRM_t2 = atoi(str);

	str = m_Grid.GetItemText(6,1);
	m_Iec104s.SEND_TEST_t3 = atoi(str);

	str = m_Grid.GetItemText(7,1);
	m_Iec104s.MAX_DELTA_K = atoi(str);

	str = m_Grid.GetItemText(8,1);
	m_Iec104s.CONFIRM_AFTER_W = atoi(str);

	/*str = m_Grid.GetItemText(9,1);
	if((atoi(str)<0)||(atoi(str)>12000))
	{
		AfxMessageBox("Таймаут сообщений от клиента  0..12000!");
		return FALSE;
	}
	m_Iec104s.BIGTIME = atoi(str);*/

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<0)||(atoi(str)>180))
	{
		AfxMessageBox("Время ожидания входного пакета данных в квантах 0..255!");
		return FALSE;
	}
	m_Iec104s.SMOLLTIME = atoi(str);

	str = m_Grid.GetItemText(10,1);
	m_Iec104s.PORT = atoi(str);

	str = m_Grid.GetItemText(11,1);
	if(atoi(str)>1000000)
	{
		AfxMessageBox("Глубина файлового архива 0..1000000 инф. объектов!");
		return FALSE;
	}
	m_Iec104s.SIZE_OBJECT_ARH = atoi(str);

	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 12)
	{
		m_Iec104s.RES_ADRESS_IP = m_Grid.GetItemText(12,1);			
	}
	

	return TRUE;
}
void CIec104sDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CIec104sDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnCancel();
}

BOOL CIec104sDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Процесс №%d: IEC 870-5-104 (SLAVE)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(12);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
	
	CString str;
	m_Grid.SetItemText(1,0,"IP адрес клиента");
	str.Format("%s",m_Iec104s.ADRESS_IP);
	m_Grid.SetItemText(1,1,str);
	//m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));	

	m_Grid.SetItemText(2,0,"Адрес ASDU");
	str.Format("%d",m_Iec104s.GLOBAL_ASDU);
	m_Grid.SetItemText(2,1,str);
	m_Grid.SetCellType(2,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(3,0,"Таймаут t0");
	str.Format("%d",m_Iec104s.UST_CONNECT_t0);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"Таймаут t1");
	str.Format("%d",m_Iec104s.TEST_APDU_t1);
	m_Grid.SetItemText(4,1,str);
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(5,0,"Таймаут t2");
	str.Format("%d",m_Iec104s.CONFIRM_t2);
	m_Grid.SetItemText(5,1,str);
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(6,0,"Таймаут t3");
	str.Format("%d",m_Iec104s.SEND_TEST_t3);
	m_Grid.SetItemText(6,1,str);
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(7,0,"Число K");
	str.Format("%d",m_Iec104s.MAX_DELTA_K);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(8,0,"Число W");
	str.Format("%d",m_Iec104s.CONFIRM_AFTER_W);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(9,0,"Время ожидания входного пакета в квантах(1квант = 10 мс.)");
	str.Format("%d",m_Iec104s.SMOLLTIME);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));
	
	if(m_byProcType == 8)
	{
		m_Grid.SetItemText(10,0,"Порт");
		str.Format("%d",m_Iec104s.PORT);
		m_Grid.SetItemText(10,1,str);
		m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));
	}
	else
	{		
		m_Grid.SetItemText(10,0,"Порт");
		m_Grid.SetItemText(10,1,"2404");
		m_Grid.SetItemState(10, 1, GVIS_READONLY);
	}
	m_Grid.SetItemText(11,0,"Глубина файлового архива (инф. объектов)");
	str.Format("%d",m_Iec104s.SIZE_OBJECT_ARH);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellNumeric));
	
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 12)
	{
		int index = m_Grid.InsertRow(NULL);
		m_Grid.SetItemText(index,0,"IP адрес резервного сервера");
		str.Format("%s",m_Iec104s.RES_ADRESS_IP);
		m_Grid.SetItemText(index,1,str);			
	}

	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,280);
	m_Grid.Refresh();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CIec104sDlg::OnSize(UINT nType, int cx, int cy)
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
		m_Grid.MoveWindow(2*dx, 30, r.right - r.left - 2*dx, r.bottom - r.top - 70 - dx*2, TRUE);		
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
BOOL CIec104sDlg::PreTranslateMessage(MSG* pMsg)
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
