// Iec104mDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "Iec104mDlg.h"
#include "TuConfigTUDlg.h"
#include "AddDiapIECDlg.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAP	WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
#define IDM_PRINT3 WM_USER + 422
// диалоговое окно CIec104mDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CIec104mDlg, CDialog)

CIec104mDlg::CIec104mDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIec104mDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("Процесс №%d: IEC 870-5-104 (MASTER)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);

}

CIec104mDlg::~CIec104mDlg()
{
}

void CIec104mDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridData);	
	DDX_Control(pDX, IDC_GRID3, m_GridKP);	
}


BEGIN_MESSAGE_MAP(CIec104mDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_ADDDIAP, OnAddDiap)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON1, &CIec104mDlg::OnBnClickedButton1)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit1)
	ON_BN_CLICKED(IDCANCEL2, &CIec104mDlg::OnBnClickedCancel2)
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)
	ON_COMMAND(IDM_PRINT3, OnPrint3)
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid1)
	ON_NOTIFY(NM_RCLICK, IDC_GRID3, OnRClickGrid3)
END_MESSAGE_MAP()


afx_msg void CIec104mDlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CIec104mDlg::OnPrint2(void)
{
	m_GridData.Print();
}

afx_msg void CIec104mDlg::OnPrint3(void)
{
	m_GridKP.Print();
}

// обработчики сообщений CIec104mDlg
void CIec104mDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
BOOL CIec104mDlg::ProcessSave(void)
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
	
	m_Iec104m.ADRESS_IP = m_Grid.GetItemText(1,1);
	
	str = m_Grid.GetItemText(2,1);
	m_Iec104m.GLOBAL_ASDU = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_Iec104m.UST_CONNECT_t0 = atoi(str);

	str = m_Grid.GetItemText(4,1);
	m_Iec104m.TEST_APDU_t1 = atoi(str);

	str = m_Grid.GetItemText(5,1);
	m_Iec104m.CONFIRM_t2 = atoi(str);

	str = m_Grid.GetItemText(6,1);
	m_Iec104m.SEND_TEST_t3 = atoi(str);

	str = m_Grid.GetItemText(7,1);
	m_Iec104m.MAX_DELTA_K = atoi(str);

	str = m_Grid.GetItemText(8,1);
	m_Iec104m.CONFIRM_AFTER_W = atoi(str);	

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<0)||(atoi(str)>3000))
	{
		AfxMessageBox("Время ожидания входного пакета данных в квантах 0..3000!");
		return FALSE;
	}
	m_Iec104m.SMOLLTIME = atoi(str);

	str = m_Grid.GetItemText(10,1);
	m_Iec104m.PORT = atoi(str);

	str = m_Grid.GetItemText(11,1);
	if((atoi(str)<1)||(atoi(str)>600))
	{
		AfxMessageBox("Таймаут установки признака недостоверности 1..600 c.!");
		return FALSE;
	}
	m_Iec104m.TIME_WAIT_FLAG_BAD = atoi(str);
	
	CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(12, 1);							
	if(pCell2->GetCheck())
		m_Iec104m.C_IС_NA_1_ENABLE = 1;
	else
		m_Iec104m.C_IС_NA_1_ENABLE = 0;
		

	str = m_Grid.GetItemText(13,1);
	if((atoi(str)<1)||(atoi(str)>172800))
	{
		AfxMessageBox("Интервал команды \"Общего опроса\" 1..172800 c.!");
		return FALSE;
	}
	m_Iec104m.PERIOD_C_IC_NA_1 = atoi(str);

	pCell2 = (CGridCellCheck*) m_Grid.GetCell(14, 1);							
	if(pCell2->GetCheck())
		m_Iec104m.C_IС_NA_1_WAIT_END_ACT = 1;
	else
		m_Iec104m.C_IС_NA_1_WAIT_END_ACT = 0;

	str = m_Grid.GetItemText(15,1);
	if((atoi(str)<1)||(atoi(str)>600))
	{
		AfxMessageBox("Время ожидания завершения команды \"Общего опроса\" 1..600 c.!");
		return FALSE;
	}
	m_Iec104m.TIME_WAIT_C_IC_NA_1 = atoi(str);

	pCell2 = (CGridCellCheck*) m_Grid.GetCell(16, 1);							
	if(pCell2->GetCheck())
		m_Iec104m.C_CS_NA_1_ENABLE = 1;
	else
		m_Iec104m.C_CS_NA_1_ENABLE = 0;

	str = m_Grid.GetItemText(17,1);
	if((atoi(str)<1)||(atoi(str)>172800))
	{
		AfxMessageBox("Интервал команды \"Синхронизация времени\" 1..172800 c.!");
		return FALSE;
	}
	m_Iec104m.PERIOD_C_CS_NA_1 = atoi(str);

	pCell2 = (CGridCellCheck*) m_Grid.GetCell(18, 1);							
	if(pCell2->GetCheck())
		m_Iec104m.C_CS_NA_1_WAIT_END_ACT = 1;
	else
		m_Iec104m.C_CS_NA_1_WAIT_END_ACT = 0;

	str = m_Grid.GetItemText(19,1);
	if((atoi(str)<1)||(atoi(str)>600))
	{
		AfxMessageBox("Время ожидания завершения команды \"Синхронизации времени\" 1..600 c.!");
		return FALSE;
	}
	m_Iec104m.TIME_WAIT_C_CS_NA_1 = atoi(str);

	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 11)
	{
		m_Iec104m.RES_ADRESS_IP = m_Grid.GetItemText(20,1);

		str = m_Grid.GetItemText(21,1);
		m_Iec104m.RES_PORT = atoi(str);
	}
	
	m_Iec104m.m_IndividualStructure104Array.RemoveAll();
	int nTotalAmount=0;

	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		IndividualStructure104 is104;	

		int nCol=0;

		is104.strCOMMENT = m_GridData.GetItemText(i,nCol++);

		str = m_GridData.GetItemText(i,nCol++ );										
		if(str == arrMain_Set_ObjectTypes[0])
		{
			is104.TYPE_ID = M_SP_NA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_SP_NA_1;
			is104.NUM_BYTE = 1;
			is104.NUM_BYTE_C_IC_NA_1 = 1;
			is104.POZITION_OF_QUALITY_FLAG = 0;						
		}
		else if(str == arrMain_Set_ObjectTypes[1])
		{
			is104.TYPE_ID = M_SP_TA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_SP_NA_1;
			is104.NUM_BYTE = 4;
			is104.NUM_BYTE_C_IC_NA_1 = 1;
			is104.POZITION_OF_QUALITY_FLAG = 0;			
		}
		else if(str == arrMain_Set_ObjectTypes[2])
		{
			is104.TYPE_ID = M_SP_TB_1;
			is104.TYPE_ID_C_IC_NA_1 = M_SP_NA_1;
			is104.NUM_BYTE = 8;
			is104.NUM_BYTE_C_IC_NA_1 = 1;
			is104.POZITION_OF_QUALITY_FLAG = 0;
		}
		else if(str == arrMain_Set_ObjectTypes[3])
		{
			is104.TYPE_ID = M_DP_NA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_DP_NA_1;
			is104.NUM_BYTE = 1;
			is104.NUM_BYTE_C_IC_NA_1 = 1;
			is104.POZITION_OF_QUALITY_FLAG = 0;
		}
		else if(str == arrMain_Set_ObjectTypes[4])
		{
			is104.TYPE_ID = M_DP_TA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_DP_NA_1;
			is104.NUM_BYTE = 4;
			is104.NUM_BYTE_C_IC_NA_1 = 1;
			is104.POZITION_OF_QUALITY_FLAG = 0;
		}
		else if(str == arrMain_Set_ObjectTypes[5])
		{
			is104.TYPE_ID = M_DP_TB_1;
			is104.TYPE_ID_C_IC_NA_1 = M_DP_NA_1;
			is104.NUM_BYTE = 8;
			is104.NUM_BYTE_C_IC_NA_1 = 1;
			is104.POZITION_OF_QUALITY_FLAG = 0;
		}
		else if(str == arrMain_Set_ObjectTypes[6])
		{
			is104.TYPE_ID = M_ME_NA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NA_1;
			is104.NUM_BYTE = 3;
			is104.NUM_BYTE_C_IC_NA_1 = 3;
			is104.POZITION_OF_QUALITY_FLAG = 2;
		}
		else if(str == arrMain_Set_ObjectTypes[7])
		{
			is104.TYPE_ID = M_ME_TA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NA_1;
			is104.NUM_BYTE = 6;
			is104.NUM_BYTE_C_IC_NA_1 = 3;
			is104.POZITION_OF_QUALITY_FLAG = 2;
		}
		else if(str == arrMain_Set_ObjectTypes[8])
		{
			is104.TYPE_ID = M_ME_TD_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NA_1;
			is104.NUM_BYTE = 10;
			is104.NUM_BYTE_C_IC_NA_1 = 3;
			is104.POZITION_OF_QUALITY_FLAG = 2;
		}
		else if(str == arrMain_Set_ObjectTypes[9])
		{
			is104.TYPE_ID = M_ME_ND_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_ND_1;
			is104.NUM_BYTE = 2;
			is104.NUM_BYTE_C_IC_NA_1 = 2;
			is104.POZITION_OF_QUALITY_FLAG = 0;
		}
		else if(str == arrMain_Set_ObjectTypes[10])
		{
			is104.TYPE_ID = M_ME_NB_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NB_1;
			is104.NUM_BYTE = 3;
			is104.NUM_BYTE_C_IC_NA_1 = 3;
			is104.POZITION_OF_QUALITY_FLAG = 2;
		}
		else if(str == arrMain_Set_ObjectTypes[11])
		{
			is104.TYPE_ID = M_ME_TB_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NB_1;
			is104.NUM_BYTE = 6;
			is104.NUM_BYTE_C_IC_NA_1 = 3;
			is104.POZITION_OF_QUALITY_FLAG = 2;
		}
		else if(str == arrMain_Set_ObjectTypes[12])
		{
			is104.TYPE_ID = M_ME_TE_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NB_1;
			is104.NUM_BYTE = 10;
			is104.NUM_BYTE_C_IC_NA_1 = 3;
			is104.POZITION_OF_QUALITY_FLAG = 2;
		}
		else if(str == arrMain_Set_ObjectTypes[13])
		{
			is104.TYPE_ID = M_ME_NC_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NC_1;
			is104.NUM_BYTE = 5;
			is104.NUM_BYTE_C_IC_NA_1 = 5;
			is104.POZITION_OF_QUALITY_FLAG = 4;
		}
		else if(str == arrMain_Set_ObjectTypes[14])
		{
			is104.TYPE_ID = M_ME_TC_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NC_1;
			is104.NUM_BYTE = 8;
			is104.NUM_BYTE_C_IC_NA_1 = 5;
			is104.POZITION_OF_QUALITY_FLAG = 4;
		}
		else if(str == arrMain_Set_ObjectTypes[15])
		{
			is104.TYPE_ID = M_ME_TF_1;
			is104.TYPE_ID_C_IC_NA_1 = M_ME_NC_1;
			is104.NUM_BYTE = 12;
			is104.NUM_BYTE_C_IC_NA_1 = 5;
			is104.POZITION_OF_QUALITY_FLAG = 4;
		}
		else if(str == arrMain_Set_ObjectTypes[16])
		{
			is104.TYPE_ID = M_BO_NA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_BO_NA_1;
			is104.NUM_BYTE = 5;
			is104.NUM_BYTE_C_IC_NA_1 = 5;
			is104.POZITION_OF_QUALITY_FLAG = 4;
		}
		else if(str == arrMain_Set_ObjectTypes[17])
		{
			is104.TYPE_ID = M_BO_TA_1;
			is104.TYPE_ID_C_IC_NA_1 = M_BO_NA_1;
			is104.NUM_BYTE = 8;
			is104.NUM_BYTE_C_IC_NA_1 = 5;
			is104.POZITION_OF_QUALITY_FLAG = 4;
		}
		else if(str == arrMain_Set_ObjectTypes[18])
		{
			is104.TYPE_ID = M_BO_TB_1;
			is104.TYPE_ID_C_IC_NA_1 = M_BO_NA_1;
			is104.NUM_BYTE = 12;
			is104.NUM_BYTE_C_IC_NA_1 = 5;
			is104.POZITION_OF_QUALITY_FLAG = 4;
		}
		else
		{
			AfxMessageBox("Неверный тип инф. объектов!");
			return FALSE;
		}				

		str = m_GridData.GetItemText(i,nCol++);
		is104.ORIGINATOR_ADDRESS = atoi(str);
		if((is104.ORIGINATOR_ADDRESS>255)||(is104.ORIGINATOR_ADDRESS<0))
		{
			AfxMessageBox("Originator Address: 0..255!");
			return FALSE;
		}		
		
		str = m_GridData.GetItemText(i,nCol++);
		is104.COMMON_ADDRESS_ASDU = atoi(str);		
		if((is104.COMMON_ADDRESS_ASDU>65535)||(is104.COMMON_ADDRESS_ASDU<0))
		{
			AfxMessageBox("ASDU Address: 0..65535!");
			return FALSE;
		}

		str = m_GridData.GetItemText(i,nCol++);
		is104.START_IOA = atoi(str);		
		if((is104.START_IOA>16777215)||(is104.START_IOA<0))
		{
			AfxMessageBox("Нач. IOA: 0..16777215!");
			return FALSE;
		}

		str = m_GridData.GetItemText(i,nCol++);
		is104.AM_IOA = atoi(str);
		nTotalAmount+=is104.AM_IOA;

		str = m_GridData.GetItemText(i,nCol++);
		is104.ADDRESS_PMZ = atoi(str);

		if((is104.ADDRESS_PMZ < m_nStartPMZAddr)
			||(is104.ADDRESS_PMZ > m_nEndPMZAddr)
			||(is104.ADDRESS_PMZ + is104.AM_IOA - 1 > m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("Набор инф. объектов в строке %d выходит за пределы карты памяти ПРОЦЕССА: %d..%d!",i,m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			for(int col = 0; col < m_GridData.GetColumnCount(); col++)
			{
				m_GridData.SetItemBkColour(i,col,RGB(255,128,255));
			}
			m_GridData.EnsureVisible(i,0);
			m_GridData.Refresh();
		}
		m_Iec104m.m_IndividualStructure104Array.Add(is104);		
	}

	if(nTotalAmount > m_nEndPMZAddr+1)
	{
		str.Format("%d > %d !",nTotalAmount,m_nEndPMZAddr+1);
		AfxMessageBox("Суммарное кол-во инф. объектов больше выделенного количества для данного процесса:"+str);
		//return FALSE;
	}

	for(int i = 0; i < m_Iec104m.m_IndividualStructure104Array.GetSize();i++)
	{
		for(int j = 0; j < m_Iec104m.m_IndividualStructure104Array.GetSize();j++)
		{
			if((IsIntersect(m_Iec104m.m_IndividualStructure104Array[i].ADDRESS_PMZ,
							m_Iec104m.m_IndividualStructure104Array[i].ADDRESS_PMZ+m_Iec104m.m_IndividualStructure104Array[i].AM_IOA-1,
							m_Iec104m.m_IndividualStructure104Array[j].ADDRESS_PMZ,
							m_Iec104m.m_IndividualStructure104Array[j].ADDRESS_PMZ+m_Iec104m.m_IndividualStructure104Array[j].AM_IOA-1))
							&&(i!=j))
			{
				str.Format("%d на %d !\r\n(строки подсвечены розовым цветом)",j+1,i+1);
				AfxMessageBox("Наложение наборов инф.объектов:"+str);
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
//KP		
	CIndividualStructure104Array arr104;
	for(int j = 1; j < m_GridKP.GetRowCount(); j++)
	{
		IndividualStructure104	is104;
		is104.COMMON_ADDRESS_ASDU= atoi(m_GridKP.GetItemText(j,0));
		
		pCell2 = (CGridCellCheck*) m_GridKP.GetCell(j, 1);
		if(pCell2->GetCheck())
			is104.STATUS_TYPE = 1;
		else
			is104.STATUS_TYPE = 0;

		if(is104.STATUS_TYPE == 1)
		{
			str = m_GridKP.GetItemText(j,2);
			is104.STATUS_ADDRESS = atoi(str);

			/*if((is104.STATUS_ADDRESS < m_nStartPMZAddr)
				||(is104.STATUS_ADDRESS > m_nEndPMZAddr))
			{
				CString tmp;
				tmp.Format("Адрес внутреннего статуса в строке %d выходит за пределы карты памяти ПРОЦЕССА: %d..%d!",j,m_nStartPMZAddr,m_nEndPMZAddr);
				AfxMessageBox(tmp);
				//return FALSE;
			}*/
			str = m_GridKP.GetItemText(j,3);
			is104.STATUS_MASKA = atoi(str);

			str = m_GridKP.GetItemText(j,4);
			is104.DOP_FLAG = atoi(str);
		}
		else
		{
			str = m_GridKP.GetItemText(j,2);
			is104.STATUS_ADDRESS = atoi(str);			
			str = m_GridKP.GetItemText(j,3);
			is104.STATUS_MASKA = atoi(str);
			str = m_GridKP.GetItemText(j,4);
			is104.DOP_FLAG = atoi(str);
		}
		arr104.Add(is104);
	}

	for(int i = 0; i < m_Iec104m.m_IndividualStructure104Array.GetSize();i++)
	{
		for(int j = 0; j < arr104.GetSize();j++)
		{
			if(m_Iec104m.m_IndividualStructure104Array[i].COMMON_ADDRESS_ASDU == arr104[j].COMMON_ADDRESS_ASDU)
			{				
				m_Iec104m.m_IndividualStructure104Array[i].STATUS_ADDRESS = arr104[j].STATUS_ADDRESS;
				m_Iec104m.m_IndividualStructure104Array[i].STATUS_MASKA = arr104[j].STATUS_MASKA;
				m_Iec104m.m_IndividualStructure104Array[i].STATUS_TYPE = arr104[j].STATUS_TYPE;
				m_Iec104m.m_IndividualStructure104Array[i].DOP_FLAG = arr104[j].DOP_FLAG;
				break;
			}			
		}
	}
	return TRUE;
}
void CIec104mDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CIec104mDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnCancel();
}

BOOL CIec104mDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Процесс №%d: IEC 870-5-104 (MASTER)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 11)
		m_Grid.SetRowCount(22);
	else
		m_Grid.SetRowCount(20);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;	
	m_Grid.SetItemText(1,0,"IP адрес клиента");
	str.Format("%s",m_Iec104m.ADRESS_IP);
	m_Grid.SetItemText(1,1,str);	

	m_Grid.SetItemText(2,0,"Адрес ASDU для \"Общего опроса\"");
	str.Format("%d",m_Iec104m.GLOBAL_ASDU);
	m_Grid.SetItemText(2,1,str);
	m_Grid.SetCellType(2,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(3,0,"Таймаут t0");
	str.Format("%d",m_Iec104m.UST_CONNECT_t0);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"Таймаут t1");
	str.Format("%d",m_Iec104m.TEST_APDU_t1);
	m_Grid.SetItemText(4,1,str);
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(5,0,"Таймаут t2");
	str.Format("%d",m_Iec104m.CONFIRM_t2);
	m_Grid.SetItemText(5,1,str);
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(6,0,"Таймаут t3");
	str.Format("%d",m_Iec104m.SEND_TEST_t3);
	m_Grid.SetItemText(6,1,str);
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(7,0,"Число K");
	str.Format("%d",m_Iec104m.MAX_DELTA_K);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(8,0,"Число W");
	str.Format("%d",m_Iec104m.CONFIRM_AFTER_W);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));	

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									
	Item.row = 9;
	Item.col = 0;			  
	Item.strText = "Время ожидания\r\nвходного пакета\r\nв квантах(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);	
	str.Format("%d",m_Iec104m.SMOLLTIME);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));	

	m_Grid.SetItemText(10,0,"Порт");
	str.Format("%d",m_Iec104m.PORT);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 11;
	Item.col = 0;							
	Item.strText = "Таймаут установки\r\nпризнака недостоверности\r\n(секунд)";
	m_Grid.SetItem(&Item);	
	str.Format("%d",m_Iec104m.TIME_WAIT_FLAG_BAD);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellNumeric));	

	Item.row = 12;
	Item.col = 0;							
	Item.strText = "Отправлять команду\r\n\"Общего опроса\"";
	m_Grid.SetItem(&Item);
	m_Grid.SetCellType(12,1,RUNTIME_CLASS(CGridCellCheck));
	CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(12, 1);						
	pCell2->SetStrings("Да","Нет");	
	if(m_Iec104m.C_IС_NA_1_ENABLE == 0)
		pCell2->SetCheck(0);
	else
		pCell2->SetCheck(1);

	Item.row = 13;
	Item.col = 0;							
	Item.strText = "Интервал команды\r\n\"Общего опроса\"\r\n(секунд)";
	m_Grid.SetItem(&Item);
	str.Format("%d",m_Iec104m.PERIOD_C_IC_NA_1);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 14;
	Item.col = 0;							
	Item.strText = "Ожидать завершение\r\n\"Общего опроса\"";
	m_Grid.SetItem(&Item);
	m_Grid.SetCellType(14,1,RUNTIME_CLASS(CGridCellCheck));
	pCell2 = (CGridCellCheck*) m_Grid.GetCell(14, 1);						
	pCell2->SetStrings("Да","Нет");	
	if(m_Iec104m.C_IС_NA_1_WAIT_END_ACT == 0)
		pCell2->SetCheck(0);
	else
		pCell2->SetCheck(1);

	Item.row = 15;
	Item.col = 0;							
	Item.strText = "Время ожидания\r\nзавершения команды\r\n\"Общего опроса\"";
	m_Grid.SetItem(&Item);
	str.Format("%d",m_Iec104m.TIME_WAIT_C_IC_NA_1);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 16;
	Item.col = 0;							
	Item.strText = "Отправлять команду\r\n\"Синхронизация времени\"";
	m_Grid.SetItem(&Item);
	m_Grid.SetCellType(16,1,RUNTIME_CLASS(CGridCellCheck));
	pCell2 = (CGridCellCheck*) m_Grid.GetCell(16, 1);						
	pCell2->SetStrings("Да","Нет");	
	if(m_Iec104m.C_CS_NA_1_ENABLE == 0)
		pCell2->SetCheck(0);
	else
		pCell2->SetCheck(1);

	Item.row = 17;
	Item.col = 0;							
	Item.strText = "Интервал команды\r\n\"Синхронизация времени\"\r\n(секунд)";
	m_Grid.SetItem(&Item);
	str.Format("%d",m_Iec104m.PERIOD_C_CS_NA_1);
	m_Grid.SetItemText(17,1,str);
	m_Grid.SetCellType(17,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 18;
	Item.col = 0;							
	Item.strText = "Ожидать завершение\r\n\"Синхронизации времени\"";
	m_Grid.SetItem(&Item);
	m_Grid.SetCellType(18,1,RUNTIME_CLASS(CGridCellCheck));
	pCell2 = (CGridCellCheck*) m_Grid.GetCell(18, 1);						
	pCell2->SetStrings("Да","Нет");	
	if(m_Iec104m.C_CS_NA_1_WAIT_END_ACT == 0)
		pCell2->SetCheck(0);
	else
		pCell2->SetCheck(1);

	Item.row = 19;
	Item.col = 0;							
	Item.strText = "Время ожидания\r\nзавершения команды\r\n\"Синхронизации времени\"";
	m_Grid.SetItem(&Item);
	str.Format("%d",m_Iec104m.TIME_WAIT_C_CS_NA_1);
	m_Grid.SetItemText(19,1,str);
	m_Grid.SetCellType(19,1, RUNTIME_CLASS(CGridCellNumeric));

	//ver 12
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 11)
	{
		m_Grid.SetItemText(20,0,"Резервный IP адрес клиента");
		str.Format("%s",m_Iec104m.RES_ADRESS_IP);
		m_Grid.SetItemText(20,1,str);	

		m_Grid.SetItemText(21,0,"Резервный порт");
		str.Format("%d",m_Iec104m.RES_PORT);
		m_Grid.SetItemText(21,1,str);
		m_Grid.SetCellType(21,1, RUNTIME_CLASS(CGridCellNumeric));
	}
	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,100);	
	m_Grid.Refresh();
	
				
	arrMain_Set_ObjectTypes.Add("1: Единичный ТС");//M_SP_NA_1
	arrMain_Set_ObjectTypes.Add("2: Единичный ТС с короткой МВ");//M_SP_TA_1
	arrMain_Set_ObjectTypes.Add("30:Единичный ТС с длинной МВ");//M_SP_TB_1
	arrMain_Set_ObjectTypes.Add("3: Двойной ТС");//M_DP_NA_1
	arrMain_Set_ObjectTypes.Add("4: Двойной ТС с короткой МВ");//M_DP_TA_1
	arrMain_Set_ObjectTypes.Add("31:Двойной ТС с длинной МВ");//M_DP_TB_1
	arrMain_Set_ObjectTypes.Add("9: ТИ доп.код");//M_ME_NA_1
	arrMain_Set_ObjectTypes.Add("10:ТИ доп.код с короткой МВ");//M_ME_TA_1
	arrMain_Set_ObjectTypes.Add("34:ТИ доп.код с длинной МВ");//M_ME_TD_1
	arrMain_Set_ObjectTypes.Add("21:ТИ доп.код без байта качества");//M_ME_ND_1
	arrMain_Set_ObjectTypes.Add("11:ТИ масштаб.");//M_ME_NB_1
	arrMain_Set_ObjectTypes.Add("12:ТИ масштаб. с короткой МВ");//M_ME_TB_1
	arrMain_Set_ObjectTypes.Add("35:ТИ масштаб. с длинной МВ");//M_ME_TE_1
	arrMain_Set_ObjectTypes.Add("13:ТИ плав.точка");//M_ME_NC_1
	arrMain_Set_ObjectTypes.Add("14:ТИ плав.точка с короткой МВ");//M_ME_TC_1
	arrMain_Set_ObjectTypes.Add("36:ТИ плав.точка с длинной МВ");//M_ME_TF_1
	arrMain_Set_ObjectTypes.Add("7: Строка 32 бита");//M_BO_NA_1
	arrMain_Set_ObjectTypes.Add("8: Строка 32 бита с короткой МВ");//M_BO_TA_1
	arrMain_Set_ObjectTypes.Add("33:Строка 32 бита с длинной МВ");//M_BO_TB_1

	m_GridData.SetColumnCount(7);	
	m_GridData.SetRowCount(1);
	m_GridData.SetFixedRowCount(1);	
	//m_GridData.EnableSelection(0);
	m_GridData.EnableTitleTips(0);	
	
	//GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_WORDBREAK;	

	int nCol = 0;
	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "Комментарий";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,170);	
	nCol++;

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "Тип информационных объектов";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,200);	
	nCol++;

	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "Orig.\r\nAddress";
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
	Item.strText = "Нач.\r\nIOA";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,60);
	nCol++;

	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "Кол-во инф.\r\nобъектов";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,70);
	nCol++;
	
	Item.row = 0;
	Item.col = nCol;						
	Item.strText = "Нач. адрес\r\nв карте памяти\r\nПРОЦЕССА";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(nCol,70);
	nCol++;

	UpdateDataGrid();	
	
	m_GridKP.SetColumnCount(5);	
	m_GridKP.SetRowCount(1);
	m_GridKP.SetFixedRowCount(1);	
	m_GridKP.EnableSelection(0);
	
	Item.row = 0;
	Item.col = 0;						
	Item.strText = "Адрес ASDU";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(0,80);

	Item.row = 0;
	Item.col = 1;						
	Item.strText = "Внутренний\r\nстатус";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(1,80);

	Item.row = 0;
	Item.col = 2;
	Item.strText = "Адрес\r\nвнутреннего\r\nстатуса";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(2,80);

	Item.row = 0;
	Item.col = 3;
	Item.strText = "Маска\r\nвнутреннего\r\nстатуса";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(3,80);

	Item.row = 0;
	Item.col = 4;
	Item.strText = "Доп.флаг";
	m_GridKP.SetItem(&Item);
	m_GridKP.SetColumnWidth(4,80);

	UpdateKPGrid();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CIec104mDlg::UpdateKPGrid(void)
{
	CWordArray arrLA;
	CString str;
	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		str = m_GridData.GetItemText(i,3);//achtung! ne zabivat pri dobavlenii kolonok m_GridData
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

	for(int i = 0; i < m_Iec104m.m_IndividualStructure104Array.GetSize(); i++)
	{
		for(int j = 0; j < arrLA.GetSize(); j++)
		{
			if(m_Iec104m.m_IndividualStructure104Array[i].COMMON_ADDRESS_ASDU == arrLA[j])
			{
				int nIndex = m_GridKP.InsertRow(NULL);

				str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].COMMON_ADDRESS_ASDU);
				m_GridKP.SetItemText(nIndex,0,str);				
				m_Grid.SetItemState(nIndex, 0, m_Grid.GetItemState(nIndex, 0) | GVIS_READONLY);								

				m_GridKP.SetCellType(nIndex,1,RUNTIME_CLASS(CGridCellCheck));
				CGridCellCheck* pCell2 = (CGridCellCheck*) m_GridKP.GetCell(nIndex, 1);						
				pCell2->SetStrings("Да","Нет");	
				if(m_Iec104m.m_IndividualStructure104Array[i].STATUS_TYPE == 0)
					pCell2->SetCheck(0);
				else
					pCell2->SetCheck(1);

				str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].STATUS_ADDRESS);
				m_GridKP.SetItemText(nIndex,2,str);
				m_GridKP.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

				str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].STATUS_MASKA);
				m_GridKP.SetItemText(nIndex,3,str);
				m_GridKP.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

				str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].DOP_FLAG);
				m_GridKP.SetItemText(nIndex,4,str);
				m_GridKP.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

				arrLA.RemoveAt(j);
				break;
			}
		}
	}

	m_GridKP.AutoSizeRows();
	m_GridKP.Refresh();
}
afx_msg void CIec104mDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	 NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	 if(pItem->iColumn == 3)//achtung! ne zabivat pri dobavlenii kolonok m_GridData)
	 {
		 ProcessSave();
		 UpdateKPGrid();
	 }
}
void CIec104mDlg::OnSize(UINT nType, int cx, int cy)
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
	// TODO: добавьте свой код обработчика сообщений
}

afx_msg void CIec104mDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить набор инф.объектов");	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон наборов инф.объектов");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить набор инф.объектов");		
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CIec104mDlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CIec104mDlg::OnRClickGrid3(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();					
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT3, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
void CIec104mDlg::UpdateDataGrid(void)
{
	CString str;
	m_GridData.DeleteNonFixedRows();
	for(int i = 0; i < m_Iec104m.m_IndividualStructure104Array.GetSize(); i++)
	{
		int nIndex = m_GridData.InsertRow(NULL);
		int nCol = 0;

		m_GridData.SetItemText(nIndex,nCol,m_Iec104m.m_IndividualStructure104Array[i].strCOMMENT);
		nCol++;
		
		m_GridData.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,nCol);		
		pCell->SetOptions(arrMain_Set_ObjectTypes);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID);
		if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_SP_NA_1)
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[0]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_SP_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[1]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_SP_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[2]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_DP_NA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[3]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_DP_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[4]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_DP_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[5]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_NA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[6]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[7]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_TD_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[8]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_ND_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[9]);					
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_NB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[10]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[11]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_TE_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[12]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_NC_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[13]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_TC_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[14]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_ME_TF_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[15]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_BO_NA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[16]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_BO_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[17]);
		else if (m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID == M_BO_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[18]);			
		else
			m_GridData.SetItemText(nIndex, nCol, "");
		m_GridData.SetItemData(nIndex,nCol,m_Iec104m.m_IndividualStructure104Array[i].TYPE_ID);
		nCol++;
		
		str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].ORIGINATOR_ADDRESS);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].COMMON_ADDRESS_ASDU);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].START_IOA);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].AM_IOA);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_Iec104m.m_IndividualStructure104Array[i].ADDRESS_PMZ);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;
	}
	
	m_GridData.AutoSizeRows();	
	m_GridData.Refresh();
}
afx_msg void CIec104mDlg::OnAddDiap()
{
	//ProcessSave();
	CAddDiapIECDlg dlg;
	dlg.m_byProtocolType = TYPE_IEC104;
	if(dlg.DoModal() == IDOK)
	{
		m_Iec104m.m_IndividualStructure104Array.Append(dlg.m_arr104);
		UpdateDataGrid();
		UpdateKPGrid();
	}
}
afx_msg void CIec104mDlg::OnAdd()
{
	ProcessSave();
	CCellID cell = m_GridData.GetFocusCell();
	IndividualStructure104 is104;

	if((cell.row > 0)&&(m_Iec104m.m_IndividualStructure104Array.GetCount() > 1))
	{									
		m_Iec104m.m_IndividualStructure104Array.InsertAt(cell.row,is104);		
		UpdateDataGrid();
		UpdateKPGrid();
		return;
	}
	if((cell.row == m_Iec104m.m_IndividualStructure104Array.GetCount())
		||(cell.row == -1))
	{									
		m_Iec104m.m_IndividualStructure104Array.Add(is104);												
		UpdateDataGrid();
		UpdateKPGrid();
		return;
	}	
	
	/*IndividualStructure104 is104;
	m_Iec104m.m_IndividualStructure104Array.Add(is104);

	UpdateDataGrid();
	UpdateKPGrid();*/
}
afx_msg void CIec104mDlg::OnDel()
{
	if(m_GridData.GetRowCount()==1)
		return;
	ProcessSave();
	/*CCellID pCell = m_GridData.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_Iec104m.m_IndividualStructure104Array.RemoveAt(pCell.row-1);		
		UpdateDataGrid();
		UpdateKPGrid();
	}*/
	CCellID SelectedCell;
	CWordArray arGrigIndexes;	

	for(int m = 1; m < m_GridData.GetRowCount(); m++)
	{
		SelectedCell.row=m;
		SelectedCell.col=0;
		BOOL bRowSelected = FALSE;
		for(int s = 1; s < m_GridData.GetColumnCount(); s++)
		{
			if(m_GridData.GetItemState(SelectedCell.row,s) & GVIS_SELECTED)
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
		m_GridData.DeleteRow(arGrigIndexes[j]);				
		m_Iec104m.m_IndividualStructure104Array.RemoveAt(arGrigIndexes[j]-1);				
		for(int v = j+1; v < arGrigIndexes.GetSize();v++)
		{
			arGrigIndexes[v]--;
		}
	}
	if(arGrigIndexes.GetSize()>0)
	{
		UpdateDataGrid();
		UpdateKPGrid();
	}
	
}
void CIec104mDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CTuConfigTUDlg dlg;
	dlg.nProcNum=nProcNum;	
	dlg.m_nProcType = 7;
	dlg.m_TuArray.Copy(m_Iec104m.m_TuArray);
	dlg.m_nStartPMZAddr=m_nStartPMZAddr;
	dlg.m_nEndPMZAddr=m_nEndPMZAddr;

	if(dlg.DoModal()==IDOK)
	{
		m_Iec104m.m_TuArray.Copy(dlg.m_TuArray);
	}
}
afx_msg void CIec104mDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{	
	//m_Grid.AutoSize();
	m_Grid.Refresh();
}

void CIec104mDlg::OnBnClickedCancel2()
{
	// TODO: добавьте свой код обработчика уведомлений
	ProcessSave();
}

BOOL CIec104mDlg::PreTranslateMessage(MSG* pMsg)
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
