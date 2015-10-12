// MapboardDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "MapboardDlg.h"
#include "LampDlg.h"

#define IDM_PRINT1 WM_USER + 420

// ���������� ���� CIec101sDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);

// ���������� ���� CMapboardDlg

IMPLEMENT_DYNAMIC(CMapboardDlg, CDialog)

CMapboardDlg::CMapboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapboardDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("������� �%d: ����� �� ��",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
}

CMapboardDlg::~CMapboardDlg()
{
}

void CMapboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);	
}


BEGIN_MESSAGE_MAP(CMapboardDlg, CDialog)		
	ON_COMMAND(IDM_PRINT1, OnPrint)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapboardDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapboardDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// ����������� ��������� CMapboardDlg
afx_msg void CMapboardDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CMapboardDlg::OnPrint(void)
{
	m_Grid.Print();
}
void CMapboardDlg::OnOK()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

BOOL CMapboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	

	strTitle.Format("������� �%d: ����� �� ��",nProcNum);
	this->SetWindowTextA(strTitle);		
	
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
	str.Format("%d",m_Mapboard.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"��������, ���");
	str.Format("%d",m_Mapboard.BAUDRATE);
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
	
	m_Grid.SetItemText(3,0,"���������� ��� � �����");
	str.Format("%d",m_Mapboard.AMOUNTBYTE);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"���������� �������� ���");
	str.Format("%d",m_Mapboard.STOPBITS);
	m_Grid.SetItemText(4,1,str);
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	
	m_Grid.SetItemText(5,0,"�������� ��������");	
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
	aOptions.Add("NONE");
	aOptions.Add("EVEN");
	aOptions.Add("ODD");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_Mapboard.PARITY!=1)&&(m_Mapboard.PARITY!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_Mapboard.PARITY==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_Mapboard.PARITY==2)
		m_Grid.SetItemText(5,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(6,0,"�������� ������");	
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(6, 1);
	aOptions.Add("���");
	aOptions.Add("����������");
	aOptions.Add("�����������");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_Mapboard.CONTROLPOTOK!=1)&&(m_Mapboard.CONTROLPOTOK!=2))
		m_Grid.SetItemText(6,1,aOptions[0]);
	if(m_Mapboard.CONTROLPOTOK==1)
		m_Grid.SetItemText(6,1,aOptions[1]);
	if(m_Mapboard.CONTROLPOTOK==2)
		m_Grid.SetItemText(6,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(7,0,"������� �������� �������� ��������� (1����� = 10 ��.)");
	str.Format("%d",m_Mapboard.WAITRESP);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(8,0,"����� ����� ������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Mapboard.BYTETIME);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));
							
	m_Grid.SetItemText(9,0,"�������� ����� ��������� � �������(1 ����� = 10��.)");
	str.Format("%d",m_Mapboard.NEXTMESSAGE);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(10,0,"���������� ������ ��� ��������� \"���������������\"");
	str.Format("%d",m_Mapboard.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.SetItemText(11,0,"���������� ������� ����");
	str.Format("%d",m_Mapboard.NUMBER_BUTS);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellNumeric));
		
	m_Grid.SetItemText(12,0,"���������� ������� ����");
	str.Format("%d",m_Mapboard.NUMBER_BUI);
	m_Grid.SetItemText(12,1,str);
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(13,0,"��������� ����� ������ ����(1..254)");
	str.Format("%d",m_Mapboard.START_ADDRESS_BUTS);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(14,0,"��������� ����� ������ ����(1..254)");
	str.Format("%d",m_Mapboard.START_ADDRESS_BUI);
	m_Grid.SetItemText(14,1,str);
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(15,0,"����� ���������������� ��� ������� ����(�.)");
	str.Format("%d",m_Mapboard.TIMER_AUTO_KVIT_TS);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(16,0,"����� ���������������� ��� ������� ����(�.)");
	str.Format("%d",m_Mapboard.TIMER_AUTO_KVIT_TI);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,100);	
	m_Grid.Refresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
BOOL CMapboardDlg::ProcessSave(void)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
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

	m_Mapboard.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_Mapboard.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_Mapboard.AMOUNTBYTE = atoi(str);
	if((m_Mapboard.AMOUNTBYTE > 8)||(m_Mapboard.AMOUNTBYTE < 5))
	{
		AfxMessageBox("���������� ��� � ����� 5..8!");
		return FALSE;	
	}
	str = m_Grid.GetItemText(4,1);
	m_Mapboard.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(5,1);
	if(str == "NONE")
		m_Mapboard.PARITY = 0;
	if(str == "EVEN")
		m_Mapboard.PARITY = 1;
	if(str == "ODD")
		m_Mapboard.PARITY = 2;

	str = m_Grid.GetItemText(6,1);
	if(str == "���")
		m_Mapboard.CONTROLPOTOK = 0;
	if(str == "����������")
		m_Mapboard.CONTROLPOTOK = 1;
	if(str == "�����������")
		m_Mapboard.CONTROLPOTOK = 2;

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("������� ������ ������������ � ������� 1..3000!");
		return FALSE;
	}
	m_Mapboard.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("����� ����� ������� � ������� 1..3000!");
		return FALSE;
	}
	m_Mapboard.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("�������� ����� ��������� � ������������� 1..3000!");
		return FALSE;
	}
	m_Mapboard.NEXTMESSAGE = atoi(str);
	
	str = m_Grid.GetItemText(10,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		AfxMessageBox("���������� ������ ��� ��������� \"���������������\" 0..50!");
		return FALSE;
	}
	m_Mapboard.NUMBER_NO_ANSWER = atoi(str);

	str = m_Grid.GetItemText(11,1);
	if((atoi(str)<0)||(atoi(str)>255))
	{
		AfxMessageBox("���������� ������� ���� 0..255!");
		return FALSE;
	}
	m_Mapboard.NUMBER_BUTS = atoi(str);

	str = m_Grid.GetItemText(12,1);
	if((atoi(str)<0)||(atoi(str)>255))
	{
		AfxMessageBox("���������� ������� ���� 0..255!");
		return FALSE;
	}
	m_Mapboard.NUMBER_BUI = atoi(str);

	str = m_Grid.GetItemText(13,1);
	if((atoi(str)<1)||(atoi(str)>254))
	{
		AfxMessageBox("C�������� ����� ������ ���� 1..254!");
		return FALSE;
	}
	m_Mapboard.START_ADDRESS_BUTS = atoi(str);

	str = m_Grid.GetItemText(14,1);
	if((atoi(str)<1)||(atoi(str)>254))
	{
		AfxMessageBox("C�������� ����� ������ ���� 1..254!");
		return FALSE;
	}
	m_Mapboard.START_ADDRESS_BUI = atoi(str);

	str = m_Grid.GetItemText(15,1);	
	m_Mapboard.TIMER_AUTO_KVIT_TS = atoi(str);

	str = m_Grid.GetItemText(16,1);	
	m_Mapboard.TIMER_AUTO_KVIT_TI = atoi(str);
	
	return TRUE;
}
BOOL CMapboardDlg::PreTranslateMessage(MSG* pMsg)
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
void CMapboardDlg::OnBnClickedButton1()
{
	// TODO: �������� ���� ��� ����������� �����������
	CLampDlg dlg;
	dlg.m_byTypeInd = IND_TS;
	dlg.m_Mapboard = m_Mapboard;
	if(dlg.DoModal()==IDOK)
	{
		m_Mapboard = dlg.m_Mapboard;
	}
}

void CMapboardDlg::OnBnClickedButton4()
{
	CLampDlg dlg;
	dlg.m_byTypeInd = IND_TI;
	dlg.m_Mapboard = m_Mapboard;
	if(dlg.DoModal()==IDOK)
	{
		m_Mapboard = dlg.m_Mapboard;
	}
}
