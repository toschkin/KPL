// STM32Dlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "STM32Dlg.h"
#include "GranitDlg.h"
#include "afxdialogex.h"

#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
#define IDM_SETTINGS WM_USER + 422
#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#include "AISTDlg.h"

// ���������� ���� CSTM32Dlg

IMPLEMENT_DYNAMIC(CSTM32Dlg, CDialog)

CSTM32Dlg::CSTM32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSTM32Dlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("������� �%d: STM32",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
}

CSTM32Dlg::~CSTM32Dlg()
{
}

void CSTM32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridSTMChannels);	
}


BEGIN_MESSAGE_MAP(CSTM32Dlg, CDialog)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid1)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_ADD, OnAdd)	
	ON_COMMAND(IDM_DEL, OnDel)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2, OnGridEndEdit1)
END_MESSAGE_MAP()


// ����������� ��������� CSTM32Dlg
afx_msg void CSTM32Dlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{	
	m_Grid.AutoSizeColumns();
	m_Grid.Refresh();
	ProcessSave(TRUE);	
}
afx_msg void CSTM32Dlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{		
	m_GridSTMChannels.AutoSizeColumns();
	m_GridSTMChannels.Refresh();
	ProcessSave(TRUE);	
}

BOOL CSTM32Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������
	strTitle.Format("������� �%d: STM32",nProcNum);
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
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"��������, ���");		
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
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"���������� �������� ���");	
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
	aOptions.RemoveAll();

	m_Grid.SetItemText(6,0,"�������� ������");	
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(6, 1);
	aOptions.Add("���");
	aOptions.Add("����������");
	aOptions.Add("�����������");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	aOptions.RemoveAll();

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									
	Item.row = 7;
	Item.col = 0;							
	Item.strText = "������� ������\r\n������������ � �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 8;
	Item.col = 0;							
	Item.strText = "����� ����� �������\r\n� �������\r\n(1����� = 10 ��.)";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 9;
	Item.col = 0;							
	Item.strText = "�������� ����� ���������\r\n� �������\r\n(��.)";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 10;
	Item.col = 0;							
	Item.strText = "���������� ������ ���\r\n��������� \"���������������\"";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));	

	m_Grid.SetItemText(11,0,"����� �� �������");	
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(11, 1);
	aOptions.Add("���");
	aOptions.Add("��");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	aOptions.RemoveAll();
	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,60);
	m_Grid.Refresh();

	m_GridSTMChannels.SetColumnCount(4);
	//m_GridSTMChannels.SetFixedColumnCount(1);
	m_GridSTMChannels.SetRowCount(1);
	m_GridSTMChannels.SetFixedRowCount(1);	
	m_GridSTMChannels.EnableTitleTips(0);
	//m_GridSTMChannels.SetColumnResize(0);
	//m_GridSTMChannels.EnableSelection(0);

	m_GridSTMChannels.SetItemText(0,0,"� ������");
	m_GridSTMChannels.SetItemText(0,1,"��������");
	m_GridSTMChannels.SetItemText(0,2,"��������");
	m_GridSTMChannels.SetItemText(0,3,"�����������");	

	UpdateChannelsGrid();
	UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
void CSTM32Dlg::UpdateGrid()
{
	CString str;
	str.Format("%d",m_STM.PORT+1);
	m_Grid.SetItemText(1,1,str);
	str.Format("%d",m_STM.BAUDRATE);
	m_Grid.SetItemText(2,1,str);
	str.Format("%d",m_STM.AMOUNTBYTE);
	m_Grid.SetItemText(3,1,str);str.Format("%d",m_STM.STOPBITS);
	m_Grid.SetItemText(4,1,str);
	if((m_STM.PARITY!=1)&&(m_STM.PARITY!=2))
		m_Grid.SetItemText(5,1,"NONE");
	if(m_STM.PARITY==1)
		m_Grid.SetItemText(5,1,"EVEN");
	if(m_STM.PARITY==2)
		m_Grid.SetItemText(5,1,"ODD");
	if((m_STM.CONTROLPOTOK!=1)&&(m_STM.CONTROLPOTOK!=2))
		m_Grid.SetItemText(6,1,"���");
	if(m_STM.CONTROLPOTOK==1)
		m_Grid.SetItemText(6,1,"����������");
	if(m_STM.CONTROLPOTOK==2)
		m_Grid.SetItemText(6,1,"�����������");
	str.Format("%d",m_STM.WAITRESP);
	m_Grid.SetItemText(7,1,str);
	str.Format("%d",m_STM.BYTETIME);
	m_Grid.SetItemText(8,1,str);
	str.Format("%d",m_STM.NEXTMESSAGE);
	m_Grid.SetItemText(9,1,str);
	str.Format("%d",m_STM.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(10,1,str);
	if(m_STM.SERVICE==0)
		m_Grid.SetItemText(11,1,"���");	
	else
		m_Grid.SetItemText(11,1,"��");	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,60);
	m_Grid.Refresh();
}

void CSTM32Dlg::OnOK()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	if(ProcessSave(FALSE)==FALSE)
		return;
	CDialog::OnOK();
}


void CSTM32Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}


BOOL CSTM32Dlg::PreTranslateMessage(MSG* pMsg)
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
afx_msg void CSTM32Dlg::OnSettings(void)
{
	CCellID cell = m_GridSTMChannels.GetFocusCell();	
	if(cell.row > 0)
	{		
		if (m_STM.m_IndividualStructureSTMArray[cell.row - 1].PROTOCOL_TYPE == PROTOCOL_TYPE_GRANIT)
		{
			CGranitDlg dlg;
			dlg.m_Granit = m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_Granit;
			dlg.m_nStartPMZAddr = m_nStartPMZAddr;
			dlg.m_nEndPMZAddr = m_nEndPMZAddr;
			dlg.m_nChannelNumber = m_STM.m_IndividualStructureSTMArray[cell.row - 1].CHANNEL;
			if (dlg.DoModal() == IDOK)
			{
				m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_Granit = dlg.m_Granit;
				//��� ���������� ����� ���. ��������
				int nTotalAmount = 0;

				for (int i = 0; i < m_STM.m_IndividualStructureSTMArray.GetSize(); i++)
				{
					for (int k = 0; k < m_STM.m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray.GetSize(); k++)
					{
						nTotalAmount += m_STM.m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].NUMBER;
					}
				}
				if (nTotalAmount > m_nEndPMZAddr + 1)
				{
					CString str;
					str.Format("%d > %d !", nTotalAmount, m_nEndPMZAddr + 1);
					AfxMessageBox("��������� ���-�� ���. �������� ����������� � ������� ������ ����������� ���������� ��� ������� ��������:" + str);
					//return FALSE;
				}
			}
		}
		if (m_STM.m_IndividualStructureSTMArray[cell.row - 1].PROTOCOL_TYPE == PROTOCOL_TYPE_AIST)
		{
			//CAISTDlg
			CAISTDlg dlg;
			dlg.m_AIST = m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_AIST;
			dlg.m_nStartPMZAddr = m_nStartPMZAddr;
			dlg.m_nEndPMZAddr = m_nEndPMZAddr;
			dlg.m_nChannelNumber = m_STM.m_IndividualStructureSTMArray[cell.row - 1].CHANNEL;
			if (dlg.DoModal() == IDOK)
			{
				m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_AIST = dlg.m_AIST;
				//��� ���������� ����� ���. ��������
				int nTotalAmount = 0;

				for (int i = 0; i < m_STM.m_IndividualStructureSTMArray.GetSize(); i++)
				{
					for (int k = 0; k < m_STM.m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray.GetSize(); k++)
					{
						nTotalAmount++;
					}
				}
				if (nTotalAmount > m_nEndPMZAddr + 1)
				{
					CString str;
					str.Format("%d > %d !", nTotalAmount, m_nEndPMZAddr + 1);
					AfxMessageBox("��������� ���-�� ���. �������� ����������� � ������� ������ ����������� ���������� ��� ������� ��������:" + str);
					//return FALSE;
				}
			}
		}
	}
}
afx_msg void CSTM32Dlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CSTM32Dlg::OnPrint2(void)
{
	m_GridSTMChannels.Print();
}

afx_msg void CSTM32Dlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CSTM32Dlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();						
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "�������� �����");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "������� �����");
	MenuRButton.AppendMenu(MF_STRING, IDM_SETTINGS, "��������� ������...");	
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "������...");	
	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CSTM32Dlg::OnAdd()
{
	ProcessSave(TRUE);

	if(m_STM.m_IndividualStructureSTMArray.GetCount()==4)
	{
		AfxMessageBox("��������� �� ����� 4-� �������!");
		return;
	}
	CCellID cell = m_GridSTMChannels.GetFocusCell();
	IndividualStructureSTM mpr;
	if((cell.row > 0)&&(m_STM.m_IndividualStructureSTMArray.GetCount() > 1))
	{									
		m_STM.m_IndividualStructureSTMArray.InsertAt(cell.row,mpr);		
		UpdateChannelsGrid();
		return;
	}
	if((cell.row == m_STM.m_IndividualStructureSTMArray.GetCount())
		||(cell.row == -1))
	{									
		m_STM.m_IndividualStructureSTMArray.Add(mpr);												
		UpdateChannelsGrid();
		return;
	}	
}
afx_msg void CSTM32Dlg::OnDel()
{	
	if(m_GridSTMChannels.GetRowCount()==1)
		return;

	ProcessSave(TRUE);
	CCellID pCell = m_GridSTMChannels.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_STM.m_IndividualStructureSTMArray.RemoveAt(pCell.row-1);		
		UpdateChannelsGrid();
	}
}

void CSTM32Dlg::UpdateChannelsGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridSTMChannels.DeleteNonFixedRows();

	for(int i = 0; i < m_STM.m_IndividualStructureSTMArray.GetSize(); i++)
	{
		int nIndex = m_GridSTMChannels.InsertRow(NULL);
		int nCol = 0;
			
		strOptions.Add("1");
		strOptions.Add("2");	
		strOptions.Add("3");
		strOptions.Add("4");		
		m_GridSTMChannels.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo* pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		pCell->SetCurSel(m_STM.m_IndividualStructureSTMArray[i].CHANNEL-1);
		strOptions.RemoveAll();		
		nCol++;

		strOptions.Add("������");
		strOptions.Add("A���(������)");
		m_GridSTMChannels.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		
		pCell->SetCurSel(m_STM.m_IndividualStructureSTMArray[i].PROTOCOL_TYPE-1);
		
		strOptions.RemoveAll();		
		nCol++;

		strOptions.Add("600");
		strOptions.Add("200");	
		strOptions.Add("300");
		strOptions.Add("100");		
		m_GridSTMChannels.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 1)		
			pCell->SetCurSel(0);
		else if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 2)
			pCell->SetCurSel(1);
		else if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 3)
			pCell->SetCurSel(2);
		else if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 6)
			pCell->SetCurSel(3);				
		strOptions.RemoveAll();		
		nCol++;

		m_GridSTMChannels.SetItemText(nIndex,nCol,m_STM.m_IndividualStructureSTMArray[i].strCOMMENT);
		nCol++;		
	}

	m_GridSTMChannels.AutoSize();	
	m_GridSTMChannels.Refresh();
}
BOOL CSTM32Dlg::ProcessSave(BOOL bSilent)
{	
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	CString str;
		
	str = m_Grid.GetItemText(1,1);
	if((atoi(str)<=0)||(atoi(str)>255))
	{
		if(!bSilent)
		{
			AfxMessageBox("������� ����� ���-����!");
			return FALSE;
		}
	}
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.IsPortDuplicated(atoi(str)-1,nProcNum))
	{
		if(!bSilent)
		{
			AfxMessageBox("������ ���-���� ����� ��� ������ ������!");
			return FALSE;
		}
	}
	m_STM.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_STM.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_STM.AMOUNTBYTE = atoi(str);
	if((m_STM.AMOUNTBYTE > 8)||(m_STM.AMOUNTBYTE < 5))
	{
		if(!bSilent)
		{
			AfxMessageBox("���������� ��� � ����� 5..8!");			
			return FALSE;	
		}
	}
	str = m_Grid.GetItemText(4,1);
	m_STM.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(5,1);
	if(str == "NONE")
		m_STM.PARITY = 0;
	if(str == "EVEN")
		m_STM.PARITY = 1;
	if(str == "ODD")
		m_STM.PARITY = 2;

	str = m_Grid.GetItemText(6,1);
	if(str == "���")
		m_STM.CONTROLPOTOK = 0;
	if(str == "����������")
		m_STM.CONTROLPOTOK = 1;
	if(str == "�����������")
		m_STM.CONTROLPOTOK = 2;

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		if(!bSilent)
		{
			AfxMessageBox("������� ������ ������������ � ������� 1..3000!");
			return FALSE;
		}
	}
	m_STM.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		if(!bSilent)
		{
			AfxMessageBox("����� ����� ������� � ������� 1..3000!");
			return FALSE;
		}
	}
	m_STM.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		if(!bSilent)
		{
			AfxMessageBox("�������� ����� ��������� � ������������� 1..3000!");
			return FALSE;
		}
	}
	m_STM.NEXTMESSAGE = atoi(str);
	
	str = m_Grid.GetItemText(10,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		if(!bSilent)
		{
			AfxMessageBox("���������� ������ ��� ��������� \"���������������\" 0..50!");
			return FALSE;
		}
	}
	m_STM.NUMBER_NO_ANSWER = atoi(str);
	
	str = m_Grid.GetItemText(11,1);
	if(str=="���")
		m_STM.SERVICE=0;
	else
		m_STM.SERVICE=1;
		
	for(int i = 1; i < m_GridSTMChannels.GetRowCount(); i++)
	{		
		int nCol = 0;
		IndividualStructureSTM tmp;		

		CGridCellCombo* pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(i,nCol++);									
		tmp.CHANNEL = pCell->GetCurSel()+1;

		for(int j = 0; j < m_STM.m_IndividualStructureSTMArray.GetSize();j++)
		{
			if((tmp.CHANNEL == m_STM.m_IndividualStructureSTMArray[j].CHANNEL)
				&&(i-1!=j))
			{
				if(!bSilent)
				{
					AfxMessageBox("����������� ��� ���������� ������ ������!");
					return FALSE;
				}
			}
		}
		m_STM.m_IndividualStructureSTMArray[i-1].CHANNEL = tmp.CHANNEL;

		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(i,nCol++);									
		m_STM.m_IndividualStructureSTMArray[i-1].PROTOCOL_TYPE = pCell->GetCurSel()+1;

		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(i,nCol++);
		if(pCell->GetCurSel() == 0)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 1;
		else if(pCell->GetCurSel() == 1)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 2;
		else if(pCell->GetCurSel() == 2)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 3;
		else if(pCell->GetCurSel() == 3)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 6;

		m_STM.m_IndividualStructureSTMArray[i-1].strCOMMENT = m_GridSTMChannels.GetItemText(i,nCol++);				
	}	
	return TRUE;
}