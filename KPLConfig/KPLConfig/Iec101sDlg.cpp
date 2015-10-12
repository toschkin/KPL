// Iec101sDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "Iec101sDlg.h"

#define IDM_PRINT1 WM_USER + 420

// ���������� ���� CIec101sDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CIec101sDlg, CDialog)

CIec101sDlg::CIec101sDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIec101sDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("������� �%d: IEC 870-5-101 (SLAVE)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);

}

CIec101sDlg::~CIec101sDlg()
{
}

void CIec101sDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);	
}


BEGIN_MESSAGE_MAP(CIec101sDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()	
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit1)	
	ON_COMMAND(IDM_PRINT1, OnPrint)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
END_MESSAGE_MAP()

afx_msg void CIec101sDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "������...");	
	
	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CIec101sDlg::OnPrint(void)
{
	m_Grid.Print();
}
afx_msg void CIec101sDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//��������� �����
	//m_Grid.AutoSize();
	m_Grid.Refresh();
}

// ����������� ��������� CIec101sDlg
void CIec101sDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
BOOL CIec101sDlg::ProcessSave(void)
{
	CString str;
		
	str = m_Grid.GetItemText(1,1);
	if((atoi(str)<=0)||(atoi(str)>255))
	{
		AfxMessageBox("������� ����� ���-����!");
		return FALSE;
	}
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.IsPortDuplicated(atoi(str)-1,nProcNum))
	{
		AfxMessageBox("������ ���-���� ����� ��� ������ ������!");
		return FALSE;
	}

	m_Iec101s.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_Iec101s.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_Iec101s.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(4,1);
	if(str == "NONE")
		m_Iec101s.PARITY = 0;
	if(str == "EVEN")
		m_Iec101s.PARITY = 1;
	if(str == "ODD")
		m_Iec101s.PARITY = 2;

	str = m_Grid.GetItemText(5,1);
	if(str == "���")
		m_Iec101s.FLOWCONTROLL = 0;
	if(str == "����������")
		m_Iec101s.FLOWCONTROLL = 1;
	if(str == "�����������")
		m_Iec101s.FLOWCONTROLL = 2;

	str = m_Grid.GetItemText(6,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("������� �������� �������� ��������� 1..3000!");
		return FALSE;
	}
	m_Iec101s.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("����� ����� ������� � ������� 1..3000!");
		return FALSE;
	}
	m_Iec101s.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(8,1);	
	m_Iec101s.ADRESS_LINK = atoi(str);

	str = m_Grid.GetItemText(9,1);
	m_Iec101s.SIZE_LINK = atoi(str);

	str = m_Grid.GetItemText(10,1);
	m_Iec101s.SIZE_COFT = atoi(str);

	str = m_Grid.GetItemText(11,1);
	m_Iec101s.SIZE_ASDU = atoi(str);

	str = m_Grid.GetItemText(12,1);
	m_Iec101s.SIZE_IOA = atoi(str);

	str = m_Grid.GetItemText(13,1);	
	m_Iec101s.GLOBAL_ASDU = atoi(str);

	m_Iec101s.AMOUNTBYTE = 8;

	str = m_Grid.GetItemText(14,1);	
	m_Iec101s.CHECK_BAD_CHANEL = atoi(str);

	str = m_Grid.GetItemText(15,1);	
	if((atoi(str)<=0)||(atoi(str)>255))
	{
		AfxMessageBox("������� ����� ��������� ���-����!");
		return FALSE;
	}	
	m_Iec101s.RES_PORT = atoi(str)-1;

	str = m_Grid.GetItemText(16,1);		
	if(atoi(str)>1000000)
	{
		AfxMessageBox("������� ��������� ������ 0..1000000 ���. ��������!");
		return FALSE;
	}
	m_Iec101s.SIZE_OBJECT_ARH = atoi(str);

	return TRUE;
}
void CIec101sDlg::OnOK()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CIec101sDlg::OnCancel()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

	CDialog::OnCancel();
}

BOOL CIec101sDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������
	strTitle.Format("������� �%d: IEC 870-5-101 (SLAVE)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(17);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"��������");
	m_Grid.SetItemText(0,1,"��������");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-����");
	str.Format("%d",m_Iec101s.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"��������, ���");
	str.Format("%d",m_Iec101s.BAUDRATE);
	m_Grid.SetItemText(2,1,str);
	m_Grid.SetCellType(2,1, RUNTIME_CLASS(CGridCellCombo));
	CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(2, 1);
	aOptions.Add("50");
	aOptions.Add("75");
	aOptions.Add("110");
	aOptions.Add("134");
	aOptions.Add("150");
	aOptions.Add("200");
	aOptions.Add("300");
	aOptions.Add("600");
	aOptions.Add("1200");
	aOptions.Add("2400");
	aOptions.Add("4800");
	aOptions.Add("9600");
	aOptions.Add("19200");
	aOptions.Add("38400");
	aOptions.Add("57600");
	aOptions.Add("115200");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	
	m_Grid.SetItemText(3,0,"���������� �������� ���");
	str.Format("%d",m_Iec101s.STOPBITS);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(3, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	
	m_Grid.SetItemText(4,0,"�������� ��������");	
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	aOptions.Add("NONE");
	aOptions.Add("EVEN");
	aOptions.Add("ODD");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_Iec101s.PARITY!=1)&&(m_Iec101s.PARITY!=2))
		m_Grid.SetItemText(4,1,aOptions[0]);
	if(m_Iec101s.PARITY==1)
		m_Grid.SetItemText(4,1,aOptions[1]);
	if(m_Iec101s.PARITY==2)
		m_Grid.SetItemText(4,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(5,0,"�������� ������");	
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
	aOptions.Add("���");
	aOptions.Add("����������");
	aOptions.Add("�����������");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_Iec101s.FLOWCONTROLL!=1)&&(m_Iec101s.FLOWCONTROLL!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_Iec101s.FLOWCONTROLL==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_Iec101s.FLOWCONTROLL==2)
		m_Grid.SetItemText(5,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(6,0,"������� �������� �������� ��������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec101s.WAITRESP);
	m_Grid.SetItemText(6,1,str);
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(7,0,"����� ����� ������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec101s.BYTETIME);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(8,0,"�������� ���� LINK ADDRESS");
	str.Format("%d",m_Iec101s.ADRESS_LINK);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(9,0,"������ ���� LINK ADDRESS, ����");
	str.Format("%d",m_Iec101s.SIZE_LINK);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(9, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();

	m_Grid.SetItemText(10,0,"������ ���� CAUSE OF TRANSMISSION, ����");
	str.Format("%d",m_Iec101s.SIZE_COFT);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(10, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();

	m_Grid.SetItemText(11,0,"������ ���� ASDU ADDRESS, ����");
	str.Format("%d",m_Iec101s.SIZE_ASDU);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(11, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();

	m_Grid.SetItemText(12,0,"������ ���� INF. OBJECT ADDRESS, ����");
	str.Format("%d",m_Iec101s.SIZE_IOA);
	m_Grid.SetItemText(12,1,str);
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(12, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	aOptions.Add("3");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();

	m_Grid.SetItemText(13,0,"����� ASDU");
	str.Format("%d",m_Iec101s.GLOBAL_ASDU);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(14,0,"���-�� ��������� �������� ��� �������� �� ���.����");
	str.Format("%d",m_Iec101s.CHECK_BAD_CHANEL);
	m_Grid.SetItemText(14,1,str);
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(15,0,"��������� ����");
	str.Format("%d",m_Iec101s.RES_PORT+1);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(16,0,"������� ��������� ������ (���. ��������)");
	str.Format("%d",m_Iec101s.SIZE_OBJECT_ARH);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));


	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,100);
	m_Grid.Refresh();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
void CIec101sDlg::OnSize(UINT nType, int cx, int cy)
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
		m_Grid.MoveWindow(2*dx, 30, r.right - r.left - 4*dx, r.bottom - r.top - 70 - dx*2, TRUE);		
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
	// TODO: �������� ���� ��� ����������� ���������
}
BOOL CIec101sDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
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
