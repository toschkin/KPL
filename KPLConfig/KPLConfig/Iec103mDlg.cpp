// Iec103mDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "Iec103mDlg.h"
#include "TuConfigTUDlg.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401

#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
#define IDM_PRINT3 WM_USER + 422

// ���������� ���� CIec103mDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CIec103mDlg, CDialog)

CIec103mDlg::CIec103mDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIec103mDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("������� �%d: IEC 870-5-103 (MASTER)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);

}

CIec103mDlg::~CIec103mDlg()
{
}

void CIec103mDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridData);	
	DDX_Control(pDX, IDC_GRID3, m_GridKP);	
}


BEGIN_MESSAGE_MAP(CIec103mDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_WM_GETMINMAXINFO()	
	ON_BN_CLICKED(IDC_BUTTON1, &CIec103mDlg::OnBnClickedButton1)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit1)
	ON_BN_CLICKED(IDCANCEL2, &CIec103mDlg::OnBnClickedCancel2)
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)
	ON_COMMAND(IDM_PRINT3, OnPrint3)
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid1)
	ON_NOTIFY(NM_RCLICK, IDC_GRID3, OnRClickGrid3)
END_MESSAGE_MAP()

afx_msg void CIec103mDlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CIec103mDlg::OnPrint2(void)
{
	m_GridData.Print();
}

afx_msg void CIec103mDlg::OnPrint3(void)
{
	m_GridKP.Print();
}


// ����������� ��������� CIec103mDlg
void CIec103mDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
BOOL CIec103mDlg::ProcessSave(void)
{
	for(int row = 1; row < m_GridData.GetRowCount(); row++)
	{
		for(int col = 0; col < m_GridData.GetColumnCount(); col++)
		{
			m_GridData.SetItemBkColour(row,col,RGB(255,255,255));
		}
	}	
	m_GridData.Refresh();


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

	m_Iec103m.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_Iec103m.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_Iec103m.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(4,1);
	if(str == "NONE")
		m_Iec103m.PARITY = 0;
	if(str == "EVEN")
		m_Iec103m.PARITY = 1;
	if(str == "ODD")
		m_Iec103m.PARITY = 2;

	str = m_Grid.GetItemText(5,1);
	if(str == "���")
		m_Iec103m.FLOWCONTROLL = 0;
	if(str == "����������")
		m_Iec103m.FLOWCONTROLL = 1;
	if(str == "�����������")
		m_Iec103m.FLOWCONTROLL = 2;

	str = m_Grid.GetItemText(6,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("������� ������ ������������ � ������� 1..3000!");
		return FALSE;
	}
	m_Iec103m.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("����� ����� ������� � ������� 1..3000!");
		return FALSE;
	}
	m_Iec103m.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("�������� ����� ��������� � ������� 1..3000!");
		return FALSE;
	}
	m_Iec103m.NEXTMESSAGE = atoi(str);

	str = m_Grid.GetItemText(9,1);
	m_Iec103m.SIZE_LINK = 1;//atoi(str);

	str = m_Grid.GetItemText(10,1);
	m_Iec103m.SIZE_COFT = 1;//atoi(str);

	str = m_Grid.GetItemText(11,1);
	m_Iec103m.SIZE_ASDU = 1;//atoi(str);

	str = m_Grid.GetItemText(12,1);
	m_Iec103m.SIZE_IOA = 2;//atoi(str);

	str = m_Grid.GetItemText(13,1);
	if((atoi(str)<0)||(atoi(str)>4320))
	{
		AfxMessageBox("������ ��� ������ ���������� ������: 0 - ���, 1..4320 ���.!");
		return FALSE;
	}
	m_Iec103m.PERIOD_C_IC_NA_1 = atoi(str);

	str = m_Grid.GetItemText(14,1);
	if((atoi(str)<0)||(atoi(str)>4320))
	{
		AfxMessageBox("������ ��� ������������� �������: 0 - ���, 1..4320 ���.!");
		return FALSE;
	}
	m_Iec103m.PERIOD_C_CS_NA_1 = atoi(str);
	
	str = m_Grid.GetItemText(15,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		AfxMessageBox("���������� ������ ��� ��������� \"���������������\" 0..50!");
		return FALSE;
	}
	m_Iec103m.NUMBER_NO_ANSWER = atoi(str);

	str = m_Grid.GetItemText(16,1);
	if((atoi(str)<m_nStartPMZAddr)||(atoi(str)>m_nEndPMZAddr))
	{
		CString tmp;
		tmp.Format("������ ������� ������ � ����� ������ �� ������ %d..%d!",m_nStartPMZAddr,m_nEndPMZAddr);
		AfxMessageBox(tmp);
		//return FALSE;
	}
	m_Iec103m.ADRES_BADCHANEL = atoi(str);

	str = m_Grid.GetItemText(17,1);
	if((atoi(str)<=0)||(atoi(str)>50))
	{
		AfxMessageBox("���������� ���������, ������������ � ������� ������ 1..50!");
		return FALSE;
	}
	m_Iec103m.NUMBER_OF_DEVICES = atoi(str);
	
	m_Iec103m.AMOUNTBYTE = 8;

	str = m_Grid.GetItemText(18,1);
	if((atoi(str)<=0)||(atoi(str)>120))
	{
		AfxMessageBox("����� �� ������������� ������� �� 1..120 c!");
		return FALSE;
	}
	m_Iec103m.TIME_TU_EXPIRE = atoi(str);

	
	m_Iec103m.m_IndividualStructure103Array.RemoveAll();
	int nTotalAmount=0;

	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		IndividualStructure103 is103;
		int nCol=0;

		is103.strCOMMENT = m_GridData.GetItemText(i,nCol++);

		str = m_GridData.GetItemText(i,nCol++ );
										
		if(str == arrMain_Set_ObjectTypes[0])
		{
			is103.TYPE_ID = TYPE103_1;			
		}
		else if(str == arrMain_Set_ObjectTypes[1])
		{
			is103.TYPE_ID = TYPE103_2;
		}
		else if(str == arrMain_Set_ObjectTypes[2])
		{
			is103.TYPE_ID = TYPE103_3;
		}
		else if(str == arrMain_Set_ObjectTypes[3])
		{
			is103.TYPE_ID = TYPE103_4;
		}
		else if(str == arrMain_Set_ObjectTypes[4])
		{
			is103.TYPE_ID = TYPE103_9;
		}
		else if(str == arrMain_Set_ObjectTypes[5])
		{
			is103.TYPE_ID = TYPE103_10;
		}		
		else
		{
			AfxMessageBox("�������� ��� ���. ��������!");
			return FALSE;
		}		

		is103.TYPE_ID_C_IC_NA_1 = 0;
		is103.NUM_BYTE = 0;
		is103.NUM_BYTE_C_IC_NA_1 = 0;
		is103.POZITION_OF_QUALITY_FLAG = 0;						

		str = m_GridData.GetItemText(i,nCol++);
		is103.LINK_ADDRESS = atoi(str);
		if((m_Iec103m.SIZE_LINK == 1)&&((is103.LINK_ADDRESS>255)||(is103.LINK_ADDRESS<=0)))
		{
			AfxMessageBox("Link Address: 1..255!");
			return FALSE;
		}		

		//str = m_GridData.GetItemText(i,2);
		//is103.ORIGINATOR_ADDRESS = atoi(str);				
		
		str = m_GridData.GetItemText(i,nCol++);
		is103.COMMON_ADDRESS_ASDU = atoi(str);
		if((m_Iec103m.SIZE_ASDU == 1)&&((is103.COMMON_ADDRESS_ASDU>255)||(is103.COMMON_ADDRESS_ASDU<0)))
		{
			AfxMessageBox("ASDU Address: 0..255!");
			return FALSE;
		}	
	
		BYTE FUN=0;
		BYTE INF=0;
		str = m_GridData.GetItemText(i,nCol++);
		if((atoi(str) > 255)||(atoi(str) < 0))
		{
			AfxMessageBox("FUN: 0..255!");
			return FALSE;
		}	
		FUN = (BYTE)atoi(str);
		str = m_GridData.GetItemText(i,nCol++);
		if((atoi(str) > 255)||(atoi(str) < 0))
		{
			AfxMessageBox("INF: 0..255!");
			return FALSE;
		}	
		INF = (BYTE)atoi(str);		
		is103.START_IOA = MAKEWORD(INF,FUN);			
		

		str = m_GridData.GetItemText(i,nCol++);
		is103.AM_IOA = atoi(str);
		nTotalAmount+=is103.AM_IOA;

		str = m_GridData.GetItemText(i,nCol++);
		is103.ADDRESS_PMZ = atoi(str);

		if((is103.ADDRESS_PMZ < m_nStartPMZAddr)
			||(is103.ADDRESS_PMZ > m_nEndPMZAddr)
			||(is103.ADDRESS_PMZ + is103.AM_IOA - 1 > m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("����� ���. �������� � ������ %d ������� �� ������� ����� ������ ��������: %d..%d!",i,m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			for(int col = 0; col < m_GridData.GetColumnCount(); col++)
			{
				m_GridData.SetItemBkColour(i,col,RGB(255,128,255));
			}
			m_GridData.EnsureVisible(i,0);
			m_GridData.Refresh();
			//return FALSE;
		}
		m_Iec103m.m_IndividualStructure103Array.Add(is103);		
	}

	if(nTotalAmount > m_nEndPMZAddr+1)
	{
		str.Format("%d > %d !",nTotalAmount,m_nEndPMZAddr+1);
		AfxMessageBox("��������� ���-�� ���. �������� ������ ����������� ���������� ��� ������� ��������:"+str);
		//return FALSE;
	}

	for(int i = 0; i < m_Iec103m.m_IndividualStructure103Array.GetSize();i++)
	{
		for(int j = 0; j < m_Iec103m.m_IndividualStructure103Array.GetSize();j++)
		{
			if((IsIntersect(m_Iec103m.m_IndividualStructure103Array[i].ADDRESS_PMZ,
							m_Iec103m.m_IndividualStructure103Array[i].ADDRESS_PMZ+m_Iec103m.m_IndividualStructure103Array[i].AM_IOA-1,
							m_Iec103m.m_IndividualStructure103Array[j].ADDRESS_PMZ,
							m_Iec103m.m_IndividualStructure103Array[j].ADDRESS_PMZ+m_Iec103m.m_IndividualStructure103Array[j].AM_IOA-1))
							&&(i!=j))
			{
				str.Format("%d �� %d !\r\n(������ ���������� ������� ������)",j+1,i+1);
				AfxMessageBox("��������� ������� ���.��������:"+str);
				for(int col = 0; col < m_GridData.GetColumnCount(); col++)
				{
					m_GridData.SetItemBkColour(j+1,col,RGB(255,128,128));
					m_GridData.SetItemBkColour(i+1,col,RGB(255,128,128));
				}
				m_GridData.EnsureVisible(i+1,0);
				m_GridData.Refresh();
			}
		}
	}
//KP		
	CIndividualStructure103Array arr103;
	for(int j = 1; j < m_GridKP.GetRowCount(); j++)
	{
		IndividualStructure103	is103;
		is103.LINK_ADDRESS = atoi(m_GridKP.GetItemText(j,0));

		CGridCellCheck *pCell2 = (CGridCellCheck*) m_GridKP.GetCell(j, 1);
		if(pCell2->GetCheck())
			is103.C_CS_ENABLE = 1;
		else
			is103.C_CS_ENABLE = 0;

		str = m_GridKP.GetItemText(j,2);
		is103.GLOBAL_ASDU = atoi(str);
		if((m_Iec103m.SIZE_ASDU == 1)&&((is103.GLOBAL_ASDU>255)||(is103.GLOBAL_ASDU<0)))
		{
			AfxMessageBox("���������� ASDU Address: 0..255!");
			return FALSE;
		}	
		if((m_Iec103m.SIZE_ASDU == 2)&&((is103.GLOBAL_ASDU>65535)||(is103.GLOBAL_ASDU<0)))
		{
			AfxMessageBox("���������� ASDU Address: 0..65535!");
			return FALSE;
		}
		pCell2 = (CGridCellCheck*) m_GridKP.GetCell(j, 3);
		if(pCell2->GetCheck())
			is103.STATUS_TYPE = 1;
		else
			is103.STATUS_TYPE = 0;

		if(is103.STATUS_TYPE == 1)
		{
			str = m_GridKP.GetItemText(j,4);
			is103.STATUS_ADDRESS_PMZ = atoi(str);

			if((is103.STATUS_ADDRESS_PMZ < m_nStartPMZAddr)
				||(is103.STATUS_ADDRESS_PMZ > m_nEndPMZAddr))
			{
				CString tmp;
				tmp.Format("����� ����������� ������� � ������ %d ������� �� ������� ����� ������ ��������: %d..%d!",j,m_nStartPMZAddr,m_nEndPMZAddr);
				AfxMessageBox(tmp);
				//return FALSE;
			}
			str = m_GridKP.GetItemText(j,5);
			is103.STATUS_MASKA = atoi(str);
		}
		else
		{
			str = m_GridKP.GetItemText(j,4);
			is103.STATUS_ADDRESS_PMZ = atoi(str);			
			str = m_GridKP.GetItemText(j,5);
			is103.STATUS_MASKA = atoi(str);
		}
		arr103.Add(is103);
	}

	for(int i = 0; i < m_Iec103m.m_IndividualStructure103Array.GetSize();i++)
	{
		for(int j = 0; j < arr103.GetSize();j++)
		{
			if(m_Iec103m.m_IndividualStructure103Array[i].LINK_ADDRESS == arr103[j].LINK_ADDRESS)
			{
				m_Iec103m.m_IndividualStructure103Array[i].C_CS_ENABLE = arr103[j].C_CS_ENABLE;
				m_Iec103m.m_IndividualStructure103Array[i].GLOBAL_ASDU = arr103[j].GLOBAL_ASDU;
				m_Iec103m.m_IndividualStructure103Array[i].STATUS_ADDRESS_PMZ = arr103[j].STATUS_ADDRESS_PMZ;
				m_Iec103m.m_IndividualStructure103Array[i].STATUS_MASKA = arr103[j].STATUS_MASKA;
				m_Iec103m.m_IndividualStructure103Array[i].STATUS_TYPE = arr103[j].STATUS_TYPE;
				break;
			}			
		}
	}
	return TRUE;
}
void CIec103mDlg::OnOK()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CIec103mDlg::OnCancel()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

	CDialog::OnCancel();
}

BOOL CIec103mDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������
	strTitle.Format("������� �%d: IEC 870-5-103 (MASTER)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(19);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"��������");
	m_Grid.SetItemText(0,1,"��������");
	m_Grid.EnableSelection(0);
	m_Grid.SetRowResize(FALSE);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-����");
	str.Format("%d",m_Iec103m.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"��������, ���");
	str.Format("%d",m_Iec103m.BAUDRATE);
	m_Grid.SetItemText(2,1,str);
	m_Grid.SetCellType(2,1, RUNTIME_CLASS(CGridCellCombo));
	CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(2, 1);
	aOptions.Add("9600");
	aOptions.Add("19200");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	
	m_Grid.SetItemText(3,0,"���������� �������� ���");
	str.Format("%d",m_Iec103m.STOPBITS);
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
	if((m_Iec103m.PARITY!=1)&&(m_Iec103m.PARITY!=2))
		m_Grid.SetItemText(4,1,aOptions[0]);
	if(m_Iec103m.PARITY==1)
		m_Grid.SetItemText(4,1,aOptions[1]);
	if(m_Iec103m.PARITY==2)
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
	if((m_Iec103m.FLOWCONTROLL!=1)&&(m_Iec103m.FLOWCONTROLL!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_Iec103m.FLOWCONTROLL==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_Iec103m.FLOWCONTROLL==2)
		m_Grid.SetItemText(5,1,aOptions[2]);
	aOptions.RemoveAll();

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									

	
	Item.row = 6;
	Item.col = 0;							
	Item.strText = "������� ������\r\n������������ � �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(6,0,"������� ������ ������������ � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec103m.WAITRESP);
	m_Grid.SetItemText(6,1,str);
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 7;
	Item.col = 0;							
	Item.strText = "����� ����� �������\r\n� �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(7,0,"����� ����� ������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec103m.BYTETIME);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 8;
	Item.col = 0;							
	Item.strText = "�������� ����� ���������\r\n� �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(8,0,"�������� ����� ��������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec103m.NEXTMESSAGE);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetRowHeight(9,0);
	m_Grid.SetRowHeight(10,0);
	m_Grid.SetRowHeight(11,0);
	m_Grid.SetRowHeight(12,0);	

	Item.row = 13;
	Item.col = 0;							
	Item.strText = "������ ������\r\n���������� ������\r\n � ������� (0 - ���)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(13,0,"������ ������ ���������� ������, ���. (0 - ���)");
	str.Format("%d",m_Iec103m.PERIOD_C_IC_NA_1);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 14;
	Item.col = 0;							
	Item.strText = "������ ������������� �������\r\n � ������� (0 - ���)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(14,0,"������ ��� ������������� �������, ���. (0 - ���)");
	str.Format("%d",m_Iec103m.PERIOD_C_CS_NA_1);
	m_Grid.SetItemText(14,1,str);
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellNumeric));
	
	Item.row = 15;
	Item.col = 0;							
	Item.strText = "���������� ������ ���\r\n��������� \"���������������\"";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(15,0,"���������� ������ ��� ��������� \"���������������\"");
	str.Format("%d",m_Iec103m.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 16;
	Item.col = 0;							
	Item.strText = "������ ������� ������\r\n� ����� ������ ��������\r\n�� ������";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(16,0,"������ ������� ������ � ����� ������ �������� �� ������");
	str.Format("%d",m_Iec103m.ADRES_BADCHANEL);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 17;
	Item.col = 0;							
	Item.strText = "���������� ���������,\r\n������������ � ������� ������";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(17,0,"���������� ���������, ������������ � ������� ������");
	str.Format("%d",m_Iec103m.NUMBER_OF_DEVICES);
	m_Grid.SetItemText(17,1,str);
	m_Grid.SetCellType(17,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 18;
	Item.col = 0;							
	Item.strText = "����� �� �������������\r\n������� �� , �";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(18,0,"����� �� ������������� ������� �� , �");
	str.Format("%d",m_Iec103m.TIME_TU_EXPIRE);
	m_Grid.SetItemText(18,1,str);
	m_Grid.SetCellType(18,1, RUNTIME_CLASS(CGridCellNumeric));
	

	/*m_Grid.SetItemText(6,0,"������� ������ ������������ � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec103m.WAITRESP);
	m_Grid.SetItemText(6,1,str);
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(7,0,"����� ����� ������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec103m.BYTETIME);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(8,0,"�������� ����� ��������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_Iec103m.NEXTMESSAGE);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(9,0,"������ ���� LINK ADDRESS, ����");
	str.Format("%d",m_Iec103m.SIZE_LINK);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(9, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	m_Grid.SetRowHeight(9,0);

	m_Grid.SetItemText(10,0,"������ ���� CAUSE OF TRANSMISSION, ����");
	str.Format("%d",m_Iec103m.SIZE_COFT);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(10, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	m_Grid.SetRowHeight(10,0);

	m_Grid.SetItemText(11,0,"������ ���� ASDU ADDRESS, ����");
	str.Format("%d",m_Iec103m.SIZE_ASDU);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(11, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	m_Grid.SetRowHeight(11,0);

	m_Grid.SetItemText(12,0,"������ ���� INF. OBJECT ADDRESS, ����");
	str.Format("%d",m_Iec103m.SIZE_IOA);
	m_Grid.SetItemText(12,1,str);
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(12, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	aOptions.Add("3");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	m_Grid.SetRowHeight(12,0);

	m_Grid.SetItemText(13,0,"������ ������ ���������� ������, ���. (0 - ���)");
	str.Format("%d",m_Iec103m.PERIOD_C_IC_NA_1);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(14,0,"������ ��� ������������� �������, ���. (0 - ���)");
	str.Format("%d",m_Iec103m.PERIOD_C_CS_NA_1);
	m_Grid.SetItemText(14,1,str);
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.SetItemText(15,0,"���������� ������ ��� ��������� \"���������������\"");
	str.Format("%d",m_Iec103m.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(16,0,"������ ������� ������ � ����� ������ �������� �� ������");
	str.Format("%d",m_Iec103m.ADRES_BADCHANEL);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(17,0,"���������� ���������, ������������ � ������� ������");
	str.Format("%d",m_Iec103m.NUMBER_OF_DEVICES);
	m_Grid.SetItemText(17,1,str);
	m_Grid.SetCellType(17,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(18,0,"����� �� ������������� ������� �� , �");
	str.Format("%d",m_Iec103m.TIME_TU_EXPIRE);
	m_Grid.SetItemText(18,1,str);
	m_Grid.SetCellType(18,1, RUNTIME_CLASS(CGridCellNumeric));
	*/
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,100);
	//m_Grid.ResetScrollBars();
	m_Grid.Refresh();
			
	arrMain_Set_ObjectTypes.Add("1: ��������� � ��");//M_SP_TA_1
	arrMain_Set_ObjectTypes.Add("2: C�������� � �� � �����.�������");//M_SP_TB_1
	arrMain_Set_ObjectTypes.Add("3: �����. ��������,����� ���� 1");//M_DP_NA_1
	arrMain_Set_ObjectTypes.Add("4: �����. �������� � �� � �����.�������");//M_DP_TA_1
	arrMain_Set_ObjectTypes.Add("9: �����. ��������,����� ���� 2");//M_DP_NA_1
	arrMain_Set_ObjectTypes.Add("10:��������� ����������");//M_ME_NA_1
	
	m_GridData.SetColumnCount(8);
	//m_GridData.SetFixedColumnCount(1);
	m_GridData.SetRowCount(1);
	m_GridData.SetFixedRowCount(1);	
	m_GridData.EnableSelection(0);
	m_GridData.EnableTitleTips(0);
	//m_GridData.SetColumnResize(0);
	
	//GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_WORDBREAK;									

	int nCol = 0;

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "�����������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,170);	
	nCol++;

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "��� �������������� ��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,230);
	nCol++;

	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "Link\r\nAddress";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,50);
	nCol++;
	
	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "ASDU\r\nAddress";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,50);
	nCol++;

	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "FUN";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,30);
	nCol++;

	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "INF";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,30);
	nCol++;

	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "���-�� ���.\r\n��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,70);
	nCol++;
	
	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "���. �����\r\n� ����� ������\r\n��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,70);
	nCol++;

	UpdateDataGrid();
	
	
	m_GridKP.SetColumnCount(6);
	//m_GridData.SetFixedColumnCount(1);
	m_GridKP.SetRowCount(1);
	m_GridKP.SetFixedRowCount(1);	
	m_GridKP.EnableSelection(0);

	Item.row = 0;
	Item.col = 0;						
	Item.strText = "Link\r\nAddress";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(0,50);

	Item.row = 0;
	Item.col = 1;						
	Item.strText = "�������������\r\n�������";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(1,100);

	Item.row = 0;
	Item.col = 2;						
	Item.strText = "����������\r\n����� ASDU";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(2,80);

	Item.row = 0;
	Item.col = 3;						
	Item.strText = "����������\r\n������";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(3,80);

	Item.row = 0;
	Item.col = 4;
	Item.strText = "�����\r\n�����������\r\n�������";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(4,80);

	Item.row = 0;
	Item.col = 5;
	Item.strText = "�����\r\n�����������\r\n�������";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(5,80);

	UpdateKPGrid();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
void CIec103mDlg::UpdateKPGrid(void)
{
	CWordArray arrLA;
	CString str;
	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		str = m_GridData.GetItemText(i,2);//achtung! ne zabivat pri dobavlenii kolonok m_GridData)
		BOOL bExist = FALSE;
		for(int j = 0; j < arrLA.GetSize(); j++)
		{
			if( atoi(str) == arrLA[j])
			{
				bExist = TRUE;
				break;
			}
		}		
		if(!bExist)
			arrLA.Add(atoi(str));
	}

	m_GridKP.DeleteNonFixedRows();

	for(int i = 0; i < m_Iec103m.m_IndividualStructure103Array.GetSize(); i++)
	{
		for(int j = 0; j < arrLA.GetSize(); j++)
		{
			if(m_Iec103m.m_IndividualStructure103Array[i].LINK_ADDRESS == arrLA[j])
			{
				int nIndex = m_GridKP.InsertRow(NULL);

				str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].LINK_ADDRESS);
				m_GridKP.SetItemText(nIndex,0,str);				
				m_Grid.SetItemState(nIndex, 0, m_Grid.GetItemState(nIndex, 0) | GVIS_READONLY);

				m_GridKP.SetCellType(nIndex,1,RUNTIME_CLASS(CGridCellCheck));
				CGridCellCheck *pCell2 = (CGridCellCheck*) m_GridKP.GetCell(nIndex, 1);						
				pCell2->SetStrings("��","���");	
				if(m_Iec103m.m_IndividualStructure103Array[i].C_CS_ENABLE == 0)
					pCell2->SetCheck(0);
				else
					pCell2->SetCheck(1);

				str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].GLOBAL_ASDU);
				m_GridKP.SetItemText(nIndex,2,str);
				m_GridKP.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

				m_GridKP.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellCheck));
				pCell2 = (CGridCellCheck*) m_GridKP.GetCell(nIndex, 3);						
				pCell2->SetStrings("��","���");	
				if(m_Iec103m.m_IndividualStructure103Array[i].STATUS_TYPE == 0)
					pCell2->SetCheck(0);
				else
					pCell2->SetCheck(1);

				str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].STATUS_ADDRESS_PMZ);
				m_GridKP.SetItemText(nIndex,4,str);
				m_GridKP.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

				str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].STATUS_MASKA);
				m_GridKP.SetItemText(nIndex,5,str);
				m_GridKP.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellNumeric));
				arrLA.RemoveAt(j);
				break;
			}
		}
	}

	m_GridKP.AutoSizeRows();
	m_GridKP.Refresh();
}

afx_msg void CIec103mDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//��������� �����
	//m_Grid.AutoSize();
	m_Grid.Refresh();
}

afx_msg void CIec103mDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	 NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	 if(pItem->iColumn == 2)//achtung! ne zabivat pri dobavlenii kolonok m_GridData)
	 {
		 ProcessSave();
		 UpdateKPGrid();
	 }
}
void CIec103mDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	long nCentery = (long)(cy / 2);
	long nCenter = (long)(cx / 2);

	int dx = 5;
	//m_Grid.GetClientRect
	CRect r;
	if (IsWindow(m_Grid.m_hWnd))
	{		
		GetClientRect(&r);
		m_Grid.MoveWindow(dx, dx+20, 390/*nCenter - 2*dx*/, r.bottom - 60/*3*dx*/);		
	}

	if (IsWindow(m_GridData.m_hWnd))
	{		
		m_GridData.MoveWindow(/*3*dx+nCenter*/410, dx+20, cx-410/*nCenter - 5*dx*/, nCentery/*r.bottom - 60/*3*dx*/);		
	}

	if (IsWindow(m_GridKP.m_hWnd))
	{	
		m_GridKP.MoveWindow(410, nCentery+50, cx-410,r.bottom - nCentery-85);
	}

	CWnd* pWnd=NULL;
	pWnd = this->GetDlgItem(IDC_STATIC3);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(410 , nCentery+30, 100, 15);
	}

	pWnd = this->GetDlgItem(IDOK);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter - 100 , cy - 26, 79, 23);
	}
	pWnd = this->GetDlgItem(IDCANCEL);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter + 20, cy - 26, 79, 23);
	}

	pWnd = this->GetDlgItem(IDCANCEL2);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter + 150, cy - 26, 79, 23);
	}
	
	pWnd = this->GetDlgItem(IDC_BUTTON1);
	if(pWnd != NULL)
	{
		//MoveWindow(cx-150, cy - 26, 79, 23, TRUE);		
		pWnd->MoveWindow(cx-100, cy - 26, 99, 23);
	}	
	Invalidate(FALSE);
	// TODO: �������� ���� ��� ����������� ���������
}

afx_msg void CIec103mDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "�������� ����� ���.��������");	
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "������� ����� ���.��������");	
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "������...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CIec103mDlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CIec103mDlg::OnRClickGrid3(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();					
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT3, "������...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
void CIec103mDlg::UpdateDataGrid(void)
{
	CString str;
	m_GridData.DeleteNonFixedRows();
	for(int i = 0; i < m_Iec103m.m_IndividualStructure103Array.GetSize(); i++)
	{
		int nIndex = m_GridData.InsertRow(NULL);
		int nCol = 0;
		
		m_GridData.SetItemText(nIndex,nCol,m_Iec103m.m_IndividualStructure103Array[i].strCOMMENT);
		nCol++;
		
		m_GridData.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,nCol);		
		pCell->SetOptions(arrMain_Set_ObjectTypes);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID);
		if      (m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID == TYPE103_1)
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[0]);
		else if (m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID == TYPE103_2)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[1]);
		else if (m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID == TYPE103_3)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[2]);
		else if (m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID == TYPE103_4)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[3]);
		else if (m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID == TYPE103_9)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[4]);
		else if (m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID == TYPE103_10)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[5]);		
		else
			m_GridData.SetItemText(nIndex, nCol, "");
		m_GridData.SetItemData(nIndex,nCol,m_Iec103m.m_IndividualStructure103Array[i].TYPE_ID);
		nCol++;

		str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].LINK_ADDRESS);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;
		
		str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].COMMON_ADDRESS_ASDU);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",HIBYTE(m_Iec103m.m_IndividualStructure103Array[i].START_IOA));
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",LOBYTE(m_Iec103m.m_IndividualStructure103Array[i].START_IOA));
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].AM_IOA);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_Iec103m.m_IndividualStructure103Array[i].ADDRESS_PMZ);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;
	}
	//m_GridData.Auto
	m_GridData.AutoSizeRows();
	//m_GridData.AutoSizeColumn(0);
	m_GridData.Refresh();
}
afx_msg void CIec103mDlg::OnAdd()
{
	ProcessSave();

	IndividualStructure103 is103;
	CCellID cell = m_GridData.GetFocusCell();
	
	if((cell.row > 0)&&(m_Iec103m.m_IndividualStructure103Array.GetCount() > 1))
	{									
		m_Iec103m.m_IndividualStructure103Array.InsertAt(cell.row,is103);		
		UpdateDataGrid();
		UpdateKPGrid();
		return;
	}
	if((cell.row == m_Iec103m.m_IndividualStructure103Array.GetCount())
		||(cell.row == -1))
	{									
		m_Iec103m.m_IndividualStructure103Array.Add(is103);												
		UpdateDataGrid();
		UpdateKPGrid();
		return;
	}	

	/*ProcessSave();

	IndividualStructure103 is103;
	m_Iec103m.m_IndividualStructure103Array.Add(is103);

	UpdateDataGrid();
	UpdateKPGrid();*/
}
afx_msg void CIec103mDlg::OnDel()
{
	if(m_GridData.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID pCell = m_GridData.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_Iec103m.m_IndividualStructure103Array.RemoveAt(pCell.row-1);		
		UpdateDataGrid();
		UpdateKPGrid();
	}
	
}
void CIec103mDlg::OnBnClickedButton1()
{
	// TODO: �������� ���� ��� ����������� �����������
	CTuConfigTUDlg dlg;
	dlg.nProcNum=nProcNum;	
	dlg.m_nProcType = 5;
	dlg.m_TuArray.Copy(m_Iec103m.m_TuArray);
	dlg.m_nStartPMZAddr=m_nStartPMZAddr;
	dlg.m_nEndPMZAddr=m_nEndPMZAddr;

	if(dlg.DoModal()==IDOK)
	{
		m_Iec103m.m_TuArray.Copy(dlg.m_TuArray);
	}
}

void CIec103mDlg::OnBnClickedCancel2()
{
	// TODO: �������� ���� ��� ����������� �����������
	ProcessSave();
}

BOOL CIec103mDlg::PreTranslateMessage(MSG* pMsg)
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
