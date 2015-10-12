// ModbusMDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "ModbusMDlg.h"
#include "TuConfigTUDlg.h"
#include "AddDiapModbusDlg.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAP	WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
// ���������� ���� CModbusMDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CModbusMDlg, CDialog)

CModbusMDlg::CModbusMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModbusMDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("������� �%d: MODBUS (MASTER)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);

}

CModbusMDlg::~CModbusMDlg()
{
}

void CModbusMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridData);	
}


BEGIN_MESSAGE_MAP(CModbusMDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_ADDDIAP, OnAddDiapason)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_WM_GETMINMAXINFO()	
	ON_BN_CLICKED(IDC_BUTTON1, &CModbusMDlg::OnBnClickedButton1)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit1)
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)	
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid1)	
END_MESSAGE_MAP()

afx_msg void CModbusMDlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CModbusMDlg::OnPrint2(void)
{
	m_GridData.Print();
}

afx_msg void CModbusMDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//��������� �����
	//m_Grid.AutoSize();
	m_Grid.Refresh();
}


// ����������� ��������� CModbusMDlg
void CModbusMDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
afx_msg void CModbusMDlg::OnGridEndEdit(NMHDR *pNoTsfyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNoTsfyStruct;

	if(pItem->iColumn == 1)
	{
		CString str;
		str = m_GridData.GetItemText(pItem->iRow,0 );					
		if(str == "��-32")	
		{
			m_GridData.SetItemText(pItem->iRow,3,"2");		
			m_GridData.SetItemText(pItem->iRow,4,"0");	
			m_GridData.SetItemText(pItem->iRow,5,"80");
		}
		else if(str == "��-32")
		{
			m_GridData.SetItemText(pItem->iRow,3,"1");		
			m_GridData.SetItemText(pItem->iRow,4,"0");	
			m_GridData.SetItemText(pItem->iRow,5,"112");
		}
		else if(str == "��-16")
		{
			m_GridData.SetItemText(pItem->iRow,3,"4");		
			m_GridData.SetItemText(pItem->iRow,4,"0");	
			m_GridData.SetItemText(pItem->iRow,5,"18");
		}
		else if(str == "MTE")
		{			
			m_GridData.SetItemText(pItem->iRow,4,"1004");				
		}
		else if(str == "���(2-� �������)")
		{			
			m_GridData.SetItemText(pItem->iRow,4,"1004");				
		}
		if((str == "��-32")||(str == "��-16")||(str == "��-32"))
			AfxMessageBox("��������!\r\n���������� �������� ���������� ��� ���������� �������,\r\n������� ������������ � ��� ���������� �� ���������� ������������ ���������.\r\n������ ��-32: ��������� 80, ���. �������� - 50\r\n������ ��-32: ��������� 112, ���. �������� - 114\r\n������ ��-16: ��������� 18, ���. �������� - 20",MB_ICONINFORMATION);
		
		m_GridData.Refresh();
	}
}
void CModbusMDlg::OnOK()
{
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CModbusMDlg::OnCancel()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

	CDialog::OnCancel();
}

BOOL CModbusMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������
	strTitle.Format("������� �%d: MODBUS (MASTER)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(12);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"��������");
	m_Grid.SetItemText(0,1,"��������");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-����");
	str.Format("%d",m_ModbusM.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"��������, ���");
	str.Format("%d",m_ModbusM.BAUDRATE);
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
	str.Format("%d",m_ModbusM.AMOUNTBYTE);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"���������� �������� ���");
	str.Format("%d",m_ModbusM.STOPBITS);
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
	if((m_ModbusM.PARITY!=1)&&(m_ModbusM.PARITY!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_ModbusM.PARITY==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_ModbusM.PARITY==2)
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
	if((m_ModbusM.CONTROLPOTOK!=1)&&(m_ModbusM.CONTROLPOTOK!=2))
		m_Grid.SetItemText(6,1,aOptions[0]);
	if(m_ModbusM.CONTROLPOTOK==1)
		m_Grid.SetItemText(6,1,aOptions[1]);
	if(m_ModbusM.CONTROLPOTOK==2)
		m_Grid.SetItemText(6,1,aOptions[2]);
	aOptions.RemoveAll();

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									
	Item.row = 7;
	Item.col = 0;							
	Item.strText = "������� ������\r\n������������ � �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);

	//m_Grid.SetItemText(7,0,"������� ������ ������������ � ������� (1����� = 10 ��.)");
	str.Format("%d",m_ModbusM.WAITRESP);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 8;
	Item.col = 0;							
	Item.strText = "����� ����� �������\r\n� �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(8,0,"����� ����� ������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_ModbusM.BYTETIME);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 9;
	Item.col = 0;							
	Item.strText = "�������� ����� ���������\r\n� �������\r\n(��.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(9,0,"�������� ����� ��������� � ������� (1����� = 10 ��.)");
	str.Format("%d",m_ModbusM.NEXTMESSAGE);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 10;
	Item.col = 0;							
	Item.strText = "���������� ������ ���\r\n��������� \"���������������\"";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(10,0,"���������� ������ ��� ��������� \"���������������\"");
	str.Format("%d",m_ModbusM.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(11,0,"����� ���������");	
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(11, 1);
	aOptions.Add("RTU");
	aOptions.Add("ASCII");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	if(m_ModbusM.MODBUS_TYPE==0)
		m_Grid.SetItemText(11,1,aOptions[0]);
	else
		m_Grid.SetItemText(11,1,aOptions[1]);
	aOptions.RemoveAll();
	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,100);
	m_Grid.Refresh();
		
	m_GridData.SetColumnCount(15);
	//m_GridData.SetFixedColumnCount(1);
	m_GridData.SetRowCount(1);
	m_GridData.SetFixedRowCount(1);	
	m_GridData.EnableTitleTips(0);
	//m_GridData.SetColumnResize(0);
	m_GridData.EnableSelection(0);
	
//	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_WORDBREAK;									

	Item.row = 0;
	Item.col = 0;							
	Item.strText = "�����������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(0,170);

	Item.row = 0;
	Item.col = 1;							
	Item.strText = "���\r\n�������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(1,70);

	Item.row = 0;
	Item.col = 2;						
	Item.strText = "�����\r\n����������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(2,65);

	Item.row = 0;
	Item.col = 3;						
	Item.strText = "�����\r\n�������\r\nMODBUS";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(3,55);

	Item.row = 0;
	Item.col = 4;						
	Item.strText = "���. �����\r\nMODBUS";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(4,55);
	
	Item.row = 0;
	Item.col = 5;						
	Item.strText = "���-��\r\n���������\r\nMODBUS";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(5,70);
	
	Item.row = 0;
	Item.col = 6;						
	Item.strText = "���. �����\r\n� �����\r\n������\r\n��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(6,90);

	Item.row = 0;//DOP_BYTE1
	Item.col = 7;						
	Item.strText = "���. �����\r\n2-� �������\r\n���.��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(7,80);

	Item.row = 0;//DOP_BYTE2
	Item.col = 8;						
	Item.strText = "����������\r\n2-� �������\r\n���.��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(8,80);

	Item.row = 0;//DOP_BYTE3
	Item.col = 9;						
	Item.strText = "���. �������\r\n4-� �������\r\n���.��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(9,80);

	Item.row = 0;//DOP_BYTE4
	Item.col = 10;						
	Item.strText = "����������\r\n4-� �������\r\n���.��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(10,80);

	Item.row = 0;//ADRES_4B
	Item.col = 11;						
	Item.strText = "���. ����� �\r\n����� ������\r\n��� 4-� \r\n������� ���.\r\n��������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(11,90);

	Item.row = 0;//
	Item.col = 12;						
	Item.strText = "��� �������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(12,110);

	Item.row = 0;//
	Item.col = 13;						
	Item.strText = "�����\r\n�������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(13,60);

	Item.row = 0;//
	Item.col = 14;						
	Item.strText = "�����\r\n�������";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(14,70);


	UpdateDataGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

void CModbusMDlg::OnSize(UINT nType, int cx, int cy)
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
		m_Grid.MoveWindow(dx, dx+20, 390/*nCenter - 2*dx*/, r.bottom - 60/*3*dx*/);		
	}

	if (IsWindow(m_GridData.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_GridData.MoveWindow(/*3*dx+nCenter*/410, dx+20, cx-420/*nCenter - 5*dx*/, r.bottom - 60/*3*dx*/);		
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

	/*pWnd = this->GetDlgItem(IDC_STATIC2);
	if(pWnd != NULL)
	{
		CRect r;
		GetClientRect(&r);
		pWnd->MoveWindow(410, dx, 200, 15);
	}*/

	pWnd = this->GetDlgItem(IDC_BUTTON1);
	if(pWnd != NULL)
	{
		//MoveWindow(cx-150, cy - 26, 79, 23, TRUE);		
		pWnd->MoveWindow(cx-110, cy - 26, 99, 23);
	}	
	Invalidate(FALSE);
	// TODO: �������� ���� ��� ����������� ���������
}

afx_msg void CModbusMDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "�������� ����� ���.��������");	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "�������� �������� ������� ���.��������");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "������� ����� ���.��������");
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "������...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CModbusMDlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
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
void CModbusMDlg::UpdateDataGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridData.DeleteNonFixedRows();


	for(int i = 0; i < m_ModbusM.m_ModbusPriborArray.GetSize(); i++)
	{
		int nIndex = m_GridData.InsertRow(NULL);
		
		m_GridData.SetItemText(nIndex,0,m_ModbusM.m_ModbusPriborArray[i].strCOMMENT);

		strOptions.Add("SATEC");
		strOptions.Add("���");	
		strOptions.Add("���(2-� �������)");
		strOptions.Add("��-32");
		strOptions.Add("��-32");
		strOptions.Add("��-16");
		strOptions.Add("�������");//0		
		strOptions.Add("SATEC TC");
		m_GridData.SetCellType(nIndex,1, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,1);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		//str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].PRIBOR);
		if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 4)
			m_GridData.SetItemText(nIndex,1, "��-32");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 5)
			m_GridData.SetItemText(nIndex,1, "��-32");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 6)
			m_GridData.SetItemText(nIndex,1, "��-16");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 1)
			m_GridData.SetItemText(nIndex,1, "SATEC");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 8)
			m_GridData.SetItemText(nIndex,1, "SATEC TC");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 2)
			m_GridData.SetItemText(nIndex,1, "���");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 7)
			m_GridData.SetItemText(nIndex,1, "���(2-� �������)");
		else if (m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 0)
			m_GridData.SetItemText(nIndex,1, "�������");
		else 
		{
			str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].PRIBOR);
			m_GridData.SetItemText(nIndex,1, str);
		}
		strOptions.RemoveAll();
		
		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].ADRESS);
		m_GridData.SetItemText(nIndex,2,str);
		m_GridData.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].FUNCTION);
		m_GridData.SetItemText(nIndex,3,str);
		m_GridData.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].START_ADRESS);
		m_GridData.SetItemText(nIndex,4,str);
		m_GridData.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].NUMBER);
		m_GridData.SetItemText(nIndex,5,str);
		m_GridData.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].ADRESS_PMZ);
		m_GridData.SetItemText(nIndex,6,str);
		m_GridData.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].DOP_BYTE1);
		m_GridData.SetItemText(nIndex,7,str);
		m_GridData.SetCellType(nIndex,7,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].DOP_BYTE2);
		m_GridData.SetItemText(nIndex,8,str);
		m_GridData.SetCellType(nIndex,8,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].DOP_BYTE3);
		m_GridData.SetItemText(nIndex,9,str);
		m_GridData.SetCellType(nIndex,9,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].DOP_BYTE4);
		m_GridData.SetItemText(nIndex,10,str);
		m_GridData.SetCellType(nIndex,10,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].ADRES_4B);
		m_GridData.SetItemText(nIndex,11,str);
		m_GridData.SetCellType(nIndex,11,RUNTIME_CLASS(CGridCellNumeric));

		strOptions.Add("���");
		strOptions.Add("� �������");
		strOptions.Add("� ����� ������");
		m_GridData.SetCellType(nIndex,12, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,12);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		//str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].PRIBOR);
		if (m_ModbusM.m_ModbusPriborArray[i].TYPE_STATUS == 0)
			m_GridData.SetItemText(nIndex,12, "���");
		else if (m_ModbusM.m_ModbusPriborArray[i].TYPE_STATUS == 1)
			m_GridData.SetItemText(nIndex,12, "� �������");		
		else 
			m_GridData.SetItemText(nIndex,12, "� ����� ������");
		strOptions.RemoveAll();

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].ADRES_STATUS);
		m_GridData.SetItemText(nIndex,13,str);
		m_GridData.SetCellType(nIndex,13,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].MASKA_STATUS);
		m_GridData.SetItemText(nIndex,14,str);
		m_GridData.SetCellType(nIndex,14,RUNTIME_CLASS(CGridCellNumeric));
	}
	//m_GridData.Auto
	m_GridData.AutoSizeRows();
	//m_GridData.AutoSizeColumn(0);*/
	m_GridData.AutoSizeRows();
	m_GridData.Refresh();
}
BOOL CModbusMDlg::ProcessSave(void)
{
	for(int row = 1; row < m_GridData.GetRowCount(); row++)
	{
		for(int col = 0; col < m_GridData.GetColumnCount(); col++)
		{
			m_GridData.SetItemBkColour(row,col,RGB(255,255,255));
		}
	}
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

	m_ModbusM.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_ModbusM.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_ModbusM.AMOUNTBYTE = atoi(str);
	if((m_ModbusM.AMOUNTBYTE > 8)||(m_ModbusM.AMOUNTBYTE < 5))
	{
		AfxMessageBox("���������� ��� � ����� 5..8!");
		return FALSE;	
	}
	str = m_Grid.GetItemText(4,1);
	m_ModbusM.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(5,1);
	if(str == "NONE")
		m_ModbusM.PARITY = 0;
	if(str == "EVEN")
		m_ModbusM.PARITY = 1;
	if(str == "ODD")
		m_ModbusM.PARITY = 2;

	str = m_Grid.GetItemText(6,1);
	if(str == "���")
		m_ModbusM.CONTROLPOTOK = 0;
	if(str == "����������")
		m_ModbusM.CONTROLPOTOK = 1;
	if(str == "�����������")
		m_ModbusM.CONTROLPOTOK = 2;

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("������� ������ ������������ � ������� 1..3000!");
		return FALSE;
	}
	m_ModbusM.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("����� ����� ������� � ������� 1..3000!");
		return FALSE;
	}
	m_ModbusM.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("�������� ����� ��������� � ������������� 1..3000!");
		return FALSE;
	}
	m_ModbusM.NEXTMESSAGE = atoi(str);
	
	str = m_Grid.GetItemText(10,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		AfxMessageBox("���������� ������ ��� ��������� \"���������������\" 0..50!");
		return FALSE;
	}
	m_ModbusM.NUMBER_NO_ANSWER = atoi(str);

	str = m_Grid.GetItemText(11,1);
	if(str == "RTU")
		m_ModbusM.MODBUS_TYPE = 0;
	if(str == "ASCII")
		m_ModbusM.MODBUS_TYPE = 1;
		
	m_ModbusM.m_ModbusPriborArray.RemoveAll();
	int nTotalAmount=0;

	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		ModbusPribor is101;	

		is101.strCOMMENT = m_GridData.GetItemText(i,0 );	

		str = m_GridData.GetItemText(i,1 );					
		if(str == "��-32")		
			is101.PRIBOR = 4;					
		else if(str == "��-32")
			is101.PRIBOR = 5;	
		else if(str == "��-16")
			is101.PRIBOR = 6;	
		else if(str == "�������")
			is101.PRIBOR = 0;	
		else if(str == "SATEC")
			is101.PRIBOR = 1;	
		else if(str == "SATEC TC")
			is101.PRIBOR = 8;	
		else if(str == "���")
			is101.PRIBOR = 2;	
		else if(str == "���(2-� �������)")
			is101.PRIBOR = 7;	
		else
			is101.PRIBOR = atoi(str);
				
		str = m_GridData.GetItemText(i,2);
		is101.ADRESS = atoi(str);
		if((is101.ADRESS>255)||(is101.ADRESS<0))
		{
			AfxMessageBox("����� ����������: 1..255!");
			return FALSE;
		}		

		str = m_GridData.GetItemText(i,3);
		is101.FUNCTION = atoi(str);
		if((is101.FUNCTION > 4)||(is101.FUNCTION<1))
		{
			AfxMessageBox("����� �������: 1..4!");
			return FALSE;
		}		
		
		str = m_GridData.GetItemText(i,4);
		is101.START_ADRESS = atoi(str);
		if(((is101.START_ADRESS>65535)||(is101.START_ADRESS<0)))
		{
			AfxMessageBox("���. ����� MODBUS: 0..65535!");
			return FALSE;
		}	
				
		str = m_GridData.GetItemText(i,5);
		is101.NUMBER = atoi(str);		
		
		int tmpNumber=0;
		if(is101.PRIBOR == 4)		
			tmpNumber=50;		
		else if(is101.PRIBOR == 5)
			tmpNumber=114;
		else if(is101.PRIBOR == 6)
			tmpNumber=20;
		else 
			tmpNumber=is101.NUMBER;		
		nTotalAmount+=tmpNumber;

		str = m_GridData.GetItemText(i,6);
		is101.ADRESS_PMZ = atoi(str);

		if((is101.ADRESS_PMZ < m_nStartPMZAddr)
			||(is101.ADRESS_PMZ > m_nEndPMZAddr)
			||(is101.ADRESS_PMZ + tmpNumber - 1 > m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("����� ���. �������� � ������ %d ������� �� ������� ����� ������ ��������: %d..%d!\r\n(������ ���������� ��������� ������)",i,m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			for(int col = 0; col < m_GridData.GetColumnCount(); col++)
			{
				m_GridData.SetItemBkColour(i,col,RGB(255,128,255));
			}
			m_GridData.EnsureVisible(i,0);
			m_GridData.Refresh();
			//return FALSE;
		}		

		str = m_GridData.GetItemText(i,7);
		is101.DOP_BYTE1 = atoi(str);
		
		str = m_GridData.GetItemText(i,8);
		is101.DOP_BYTE2 = atoi(str);
		
		str = m_GridData.GetItemText(i,9);
		is101.DOP_BYTE3 = atoi(str);
		
		str = m_GridData.GetItemText(i,10);
		is101.DOP_BYTE4 = atoi(str);

		str = m_GridData.GetItemText(i,11);
		is101.ADRES_4B = atoi(str);
			
		str = m_GridData.GetItemText(i,12 );					
		if(str == "���")		
			is101.TYPE_STATUS = 0;					
		else if(str == "� �������")
			is101.TYPE_STATUS = 1;			
		else if(str == "� ����� ������")
			is101.TYPE_STATUS = 2;	

		str = m_GridData.GetItemText(i,13);
		is101.ADRES_STATUS = atoi(str);

		str = m_GridData.GetItemText(i,14);
		is101.MASKA_STATUS = atoi(str);
	
		m_ModbusM.m_ModbusPriborArray.Add(is101);		
	}

	if(nTotalAmount > m_nEndPMZAddr+1)
	{
		str.Format("%d > %d !",nTotalAmount,m_nEndPMZAddr+1);
		AfxMessageBox("��������� ���-�� ���. �������� ������ ����������� ���������� ��� ������� ��������:"+str);
		//return FALSE;
	}

	for(int i = 0; i < m_ModbusM.m_ModbusPriborArray.GetSize();i++)
	{
		for(int j = 0; j < m_ModbusM.m_ModbusPriborArray.GetSize();j++)
		{
			int tmpNumberI=0;
			int tmpNumberJ=0;
			if(m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 4)		
				tmpNumberI=50;		
			else if(m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 5)
				tmpNumberI=114;
			else if(m_ModbusM.m_ModbusPriborArray[i].PRIBOR == 6)
				tmpNumberI=20;			
			else 
				tmpNumberI=m_ModbusM.m_ModbusPriborArray[i].DOP_BYTE2 + m_ModbusM.m_ModbusPriborArray[i].DOP_BYTE4;	

			if(m_ModbusM.m_ModbusPriborArray[j].PRIBOR == 4)		
				tmpNumberJ=50;		
			else if(m_ModbusM.m_ModbusPriborArray[j].PRIBOR == 5)
				tmpNumberJ=114;
			else if(m_ModbusM.m_ModbusPriborArray[j].PRIBOR == 6)
				tmpNumberJ=20;
			else 
				tmpNumberJ=m_ModbusM.m_ModbusPriborArray[j].DOP_BYTE2 + m_ModbusM.m_ModbusPriborArray[j].DOP_BYTE4;	
				//tmpNumberJ=m_ModbusM.m_ModbusPriborArray[j].NUMBER;	


			if((IsIntersect(m_ModbusM.m_ModbusPriborArray[i].ADRESS_PMZ,
							m_ModbusM.m_ModbusPriborArray[i].ADRESS_PMZ+tmpNumberI-1,
							m_ModbusM.m_ModbusPriborArray[j].ADRESS_PMZ,
							m_ModbusM.m_ModbusPriborArray[j].ADRESS_PMZ+tmpNumberJ-1))
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
				return FALSE;
			}
		}
	}
	return TRUE;
}
afx_msg void CModbusMDlg::OnAddDiapason()
{
	CAddDiapModbusDlg dlg;
	if(dlg.DoModal() == IDOK)
	{ 
		m_ModbusM.m_ModbusPriborArray.Append(dlg.m_PriborArray);
		UpdateDataGrid();	
	}
}

afx_msg void CModbusMDlg::OnAdd()
{
	ProcessSave();

	CCellID cell = m_GridData.GetFocusCell();
	ModbusPribor mpr;
	if((cell.row > 0)&&(m_ModbusM.m_ModbusPriborArray.GetCount() > 1))
	{									
		m_ModbusM.m_ModbusPriborArray.InsertAt(cell.row,mpr);		
		UpdateDataGrid();
		return;
	}
	if((cell.row == m_ModbusM.m_ModbusPriborArray.GetCount())
		||(cell.row == -1))
	{									
		m_ModbusM.m_ModbusPriborArray.Add(mpr);												
		UpdateDataGrid();
		return;
	}	
}
afx_msg void CModbusMDlg::OnDel()
{	
	if(m_GridData.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID pCell = m_GridData.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_ModbusM.m_ModbusPriborArray.RemoveAt(pCell.row-1);		
		UpdateDataGrid();
	}
	
}
void CModbusMDlg::OnBnClickedButton1()
{
	// TODO: �������� ���� ��� ����������� �����������
	CTuConfigTUDlg dlg;
	dlg.nProcNum=nProcNum;	
	dlg.m_nProcType = 1;
	dlg.m_TuArray.Copy(m_ModbusM.m_TuArray);
	dlg.m_nStartPMZAddr=m_nStartPMZAddr;
	dlg.m_nEndPMZAddr=m_nEndPMZAddr;

	if(dlg.DoModal()==IDOK)
	{
		m_ModbusM.m_TuArray.Copy(dlg.m_TuArray);
	}
}


BOOL CModbusMDlg::PreTranslateMessage(MSG* pMsg)
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
