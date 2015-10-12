// TuConfigTUDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "TuConfigTUDlg.h"
#include "AddDiapTUDlg.h"


#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAPASON		WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
// диалоговое окно CTuConfigTUDlg

IMPLEMENT_DYNAMIC(CTuConfigTUDlg, CDialog)

CTuConfigTUDlg::CTuConfigTUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTuConfigTUDlg::IDD, pParent)
{
	m_nProcType = 1;//3- iec 101 master
	nProcNum=0;
	strTitle.Format("Настройка телеуправления для процесса №%d",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);		
}
CTuConfigTUDlg::~CTuConfigTUDlg()
{
}

void CTuConfigTUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CTuConfigTUDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_COMMAND(IDM_ADDDIAPASON, OnAddDiapason)
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(NM_RCLICK, IDC_GRID, &CTuConfigTUDlg::OnRClickGrid)
	ON_COMMAND(IDM_PRINT1, OnPrint)
END_MESSAGE_MAP()


afx_msg void CTuConfigTUDlg::OnPrint(void)
{
	m_Grid.Print();
}
// обработчики сообщений CTuConfigTUDlg
void CTuConfigTUDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}

void CTuConfigTUDlg::OnOK()
{
	if(SaveGrid())
		CDialog::OnOK();
	
}
BOOL CTuConfigTUDlg::SaveGrid(void)
{
	CString str;

	CTuArray arrtu;

	for(int i = 1; i < m_Grid.GetRowCount(); i++)
	{
		int col=1;
		CTu tu;	

		tu.strCOMMENT = m_Grid.GetItemText(i,col++);

		/*str = m_Grid.GetItemText(i,col++);
		if(str == "Внутр.модули ТУ(MODBUS)")
			tu.TYPE_PRIBOR = 1;
		else if((str == "Одноступенчатое ТУ(IEC101)")||(str == "Внешнее устройство ТУ"))
			tu.TYPE_PRIBOR = 2;
		else if(str == "Одноступенчатое ТУ(IEC103)")
			tu.TYPE_PRIBOR = 2;
		else if(str == "Двуступенчатое ТУ(IEC101)")
			tu.TYPE_PRIBOR = 3;
		else		
			tu.TYPE_PRIBOR = atoi(str);			*/

		CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(i,col++);	
		
		switch(m_nProcType )
				{
					case PROT_MODBUS:
					case PROT_MODBUSTCP: 
						{
							tu.TYPE_PRIBOR = pCell->GetCurSel();							
							break;
						}
					case PROT_IEC101: 
					case PROT_IEC104: 					
					case PROT_IEC103: 
						{
							tu.TYPE_PRIBOR = pCell->GetCurSel()+2;							
							break;
						}
				}
				
		str = m_Grid.GetItemText(i,col++);
		tu.ADRESS = atoi(str);
		if((tu.ADRESS>65535)||(tu.ADRESS<0))
		{
			AfxMessageBox("Адрес устройства: 0..65535!");
			return FALSE;
		}

		if(m_nProcType == PROT_SPA)	
		{
			CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(i,col++);	
			tu.FUNCTION = pCell->GetCurSel()+1;
		}
		else
		{
			str = m_Grid.GetItemText(i,col++);			
			if(str == "Force Single Coil(5)")
				tu.FUNCTION = 5;		
			else if(str == "Preset Single Reg(6)")
				tu.FUNCTION = 6;		
			else if(str == "C_SC_NA(45)")
				tu.FUNCTION = 45;
			else if(str == "C_DC_NA(46)")
				tu.FUNCTION = 46;
			else if(str == "DCO(20)")
				tu.FUNCTION = 20;		
			else		
				tu.FUNCTION = atoi(str);		
		}

		if(m_nProcType == PROT_SPA)
		{
			str = m_Grid.GetItemText(i,col++);
			tu.REGTU_ON = atoi(str);
			if((tu.REGTU_ON>65535)||(tu.REGTU_ON<0))
			{
				AfxMessageBox("Номер данных для ТУ на ВКЛЮЧЕНИЕ: 0..65535!");
				return FALSE;
			}
			
			str = m_Grid.GetItemText(i,col++);
			tu.REGTU_OFF = atoi(str);
			if((tu.REGTU_OFF>16777215)||(tu.REGTU_OFF<0))
			{
				AfxMessageBox("Номер данных для ТУ на ОТКЛЮЧЕНИЕ: 0..65535!");
				return FALSE;
			}

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_ON = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_OFF = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.IEC_ASDU = atoi(str);
		}
		if(m_nProcType == PROT_MODBUS)
		{
			str = m_Grid.GetItemText(i,col++);
			tu.REGTU_ON = atoi(str);
			if((tu.REGTU_ON>16777215)||(tu.REGTU_ON<0))
			{
				AfxMessageBox("Адрес ТУ на ВКЛЮЧЕНИЕ: 0..16777215!");
				return FALSE;
			}
			
			str = m_Grid.GetItemText(i,col++);
			tu.REGTU_OFF = atoi(str);
			if((tu.REGTU_OFF>16777215)||(tu.REGTU_OFF<0))
			{
				AfxMessageBox("Адрес ТУ на ОТКЛЮЧЕНИЕ: 0..16777215!");
				return FALSE;
			}

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_ON = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_OFF = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TU_CLOSER = atoi(str);
			if(((tu.TU_CLOSER>6000)||(tu.TU_CLOSER<0))&&(tu.TU_CLOSER != 16777215))
			{
				AfxMessageBox("Время замыкания реле: 0..6000!\r\nПостоянное замыкание: 16777215");
				return FALSE;
			}
			
			str = m_Grid.GetItemText(i,col++);
			tu.WAIT_RESP_TU = atoi(str);
			if((tu.WAIT_RESP_TU>6000)||(tu.WAIT_RESP_TU<1))
			{
				AfxMessageBox("Время ожидания подтверждения ТУ: 1..6000!");
				return FALSE;
			}

			str = m_Grid.GetItemText(i,col++);
			tu.TIMER_SEL_EXEC = atoi(str);

			for(int j = 0; j < arrtu.GetSize(); j ++)
			{
				if((tu.ADRESS == arrtu[j].ADRESS)&&(tu.REGTU_ON == arrtu[j].REGTU_ON)&&(tu.REGTU_OFF == arrtu[j].REGTU_OFF))
				{
					str.Format("Два одинаковых ТУ: №№ %d и %d!",i,j+1);
					AfxMessageBox(str);
					return FALSE;
				}
			}
		}
	
		if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
		{
			str = m_Grid.GetItemText(i,col++);
			tu.REGTU_ON = atoi(str);
			if((tu.REGTU_ON>16777215)||(tu.REGTU_ON<0))
			{
				AfxMessageBox("Адрес ТУ: 0..16777215!");
				return FALSE;
			}
			
			tu.REGTU_OFF = atoi(str);
			/*str = m_Grid.GetItemText(i,5);
			tu.REGTU_OFF = atoi(str);
			if((tu.REGTU_OFF>16777215)||(tu.REGTU_OFF<0))
			{
				AfxMessageBox("Адрес ТУ на ОТКЛЮЧЕНИЕ: 0..16777215!");
				return FALSE;
			}*/

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_ON = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_OFF = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TU_CLOSER = atoi(str);
			if(((tu.TU_CLOSER>6000)||(tu.TU_CLOSER<0))&&(tu.TU_CLOSER != 16777215))
			{
				AfxMessageBox("Время замыкания реле: 0..6000!\r\nПостоянное замыкание: 16777215");
				return FALSE;
			}
			
			str = m_Grid.GetItemText(i,col++);
			tu.WAIT_RESP_TU = atoi(str);
			if((tu.WAIT_RESP_TU>6000)||(tu.WAIT_RESP_TU<1))
			{
				AfxMessageBox("Время ожидания подтверждения ТУ: 1..6000!");
				return FALSE;
			}

			for(int j = 0; j < arrtu.GetSize(); j ++)
			{
				if((tu.ADRESS == arrtu[j].ADRESS)&&(tu.REGTU_ON == arrtu[j].REGTU_ON)&&(tu.REGTU_OFF == arrtu[j].REGTU_OFF))
				{
					str.Format("Два одинаковых ТУ: %d и %d!",i,j+1);
					AfxMessageBox(str);
					return FALSE;
				}
			}

			str = m_Grid.GetItemText(i,col++);
			tu.ADDRESS_TS = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TS_ON = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TS_OFF = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.ADDRESS_DAMAGE_TU = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.MASKA_DAMAGE_TU = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.IEC_ASDU = atoi(str);
			
			CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(i,16);						
			if(pCell2->GetCheck())
				tu.TU_ACT_TRM_ENABLE=1;
			else
				tu.TU_ACT_TRM_ENABLE=0;		

			str = m_Grid.GetItemText(i,col++);
			tu.TIMER_SEL_EXEC = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TIMER_ACT_TRM = atoi(str);
		}

		if(m_nProcType == PROT_IEC103)
		{
			
			BYTE FUN = 0;
			BYTE INF = 0;			
			str = m_Grid.GetItemText(i,col++);
			if((atoi(str)>255)||(atoi(str)<0))
			{
				AfxMessageBox("Адрес ТУ (FUN): 0..255!");
				return FALSE;
			}
			FUN = (BYTE)atoi(str);
			str = m_Grid.GetItemText(i,col++);
			if((atoi(str)>255)||(atoi(str)<0))
			{
				AfxMessageBox("Адрес ТУ (INF): 0..255!");
				return FALSE;
			}
			INF = (BYTE)atoi(str);							
			tu.REGTU_ON = MAKEWORD(INF,FUN);		

			/*str = m_Grid.GetItemText(i,6);
			if((atoi(str)>255)||(atoi(str)<0))
			{
				AfxMessageBox("Адрес ТУ на ОТКЛЮЧЕНИЕ (FUN): 0..255!");
				return FALSE;
			}
			FUN = (BYTE)atoi(str);
			str = m_Grid.GetItemText(i,7);
			if((atoi(str)>255)||(atoi(str)<0))
			{
				AfxMessageBox("Адрес ТУ на ОТКЛЮЧЕНИЕ (INF): 0..255!");
				return FALSE;
			}
			INF = (BYTE)atoi(str);							*/
			tu.REGTU_OFF = MAKEWORD(INF,FUN);		

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_ON = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.DATATU_OFF = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TU_CLOSER = atoi(str);
			if(((tu.TU_CLOSER>6000)||(tu.TU_CLOSER<0))&&(tu.TU_CLOSER != 16777215))
			{
				AfxMessageBox("Время замыкания реле: 0..6000!\r\nПостоянное замыкание: 16777215");
				return FALSE;
			}
			
			str = m_Grid.GetItemText(i,col++);
			tu.WAIT_RESP_TU = atoi(str);
			if((tu.WAIT_RESP_TU>6000)||(tu.WAIT_RESP_TU<1))
			{
				AfxMessageBox("Время ожидания подтверждения ТУ: 1..6000!");
				return FALSE;
			}

			for(int j = 0; j < arrtu.GetSize(); j ++)
			{
				if((tu.ADRESS == arrtu[j].ADRESS)&&(tu.REGTU_ON == arrtu[j].REGTU_ON)&&(tu.REGTU_OFF == arrtu[j].REGTU_OFF))
				{
					str.Format("Два одинаковых ТУ: %d и %d!",i,j+1);
					AfxMessageBox(str);
					return FALSE;
				}
			}
			str = m_Grid.GetItemText(i,col++);
			tu.ADDRESS_TS = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TS_ON = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TS_OFF = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.ADDRESS_DAMAGE_TU = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.MASKA_DAMAGE_TU = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.IEC_ASDU = atoi(str);

			str = m_Grid.GetItemText(i,col++);
			tu.TIMER_SEL_EXEC = atoi(str);
		}
										
		arrtu.Add(tu);
	}
	
	m_TuArray.RemoveAll();
	m_TuArray.Copy(arrtu);

	return TRUE;
}
void CTuConfigTUDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса
	CDialog::OnCancel();
}

BOOL CTuConfigTUDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	strTitle.Format("Настройка телеуправления для процесса №%d",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);	

	
	m_Grid.SetColumnCount(12);
	if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
		m_Grid.SetColumnCount(20);
	if(m_nProcType == PROT_IEC103)
		m_Grid.SetColumnCount(20);
	if(m_nProcType == PROT_SPA)
		m_Grid.SetColumnCount(10);

	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetRowCount(1);

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_WORDBREAK;	

	int nCol = 0;

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "№";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++,20);

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "Комментарий";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++,180);

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "Тип устройства";
	m_Grid.SetItem(&Item);
	if(m_nProcType == PROT_SPA)	
		m_Grid.SetColumnWidth(nCol++,0);	
	else
		m_Grid.SetColumnWidth(nCol++,170);	

	Item.row = 0;
	Item.col = nCol;							
	Item.strText = "Адрес\r\nустройства";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++,70);

	Item.row = 0;
	Item.col = nCol;	
	if(m_nProcType == PROT_SPA)	
		Item.strText = "Категория данных";
	else
		Item.strText = "Тип функции ТУ";
	m_Grid.SetItem(&Item);
	if((m_nProcType == PROT_IEC103)||(m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
		m_Grid.SetColumnWidth(nCol++,90);		
	else if(m_nProcType == PROT_SPA)
		m_Grid.SetColumnWidth(nCol++,180);		
	else
		m_Grid.SetColumnWidth(nCol++,115);

	if(m_nProcType == PROT_SPA)
	{
		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Номер данных\r\nкоммнады на\r\nВКЛЮЧЕНИЕ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Номер данных\r\nкоммнады на\r\nОТКЛЮЧЕНИЕ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ВКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ОТКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Номер канала";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);
	}

	if(m_nProcType == PROT_MODBUS)
	{
		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТУ на\r\nВКЛЮЧЕНИЕ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТУ на\r\nОТКЛЮЧЕНИЕ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ВКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ОТКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Время замыкания\r\nреле в квантах\r\n(1квант = 10 мс.)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,110);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Время ожидания\r\nподтверждения ТУ\r\nв квантах\r\n(1квант = 10 мс.)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,110);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Интервал\r\nмежду\r\nкомандами,мкс";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);	
	}
	
	if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
	{
		Item.row = 0;
		Item.col = nCol;							
		//Item.strText = "Адрес ТУ на\r\nВКЛЮЧЕНИЕ";
		Item.strText = "Адрес ТУ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТУ на\r\nОТКЛЮЧЕНИЕ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,0);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ВКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ОТКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Время замыкания\r\nреле в квантах\r\n(1квант = 10 мс.)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,110);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Время ожидания\r\nподтверждения ТУ\r\nв квантах\r\n(1квант = 10 мс.)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,110);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТС";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,60);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТС ВКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТС ОТКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;
		Item.strText = "Адрес статуса\r\nнеисправности ТУ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;
		Item.strText = "Маска статуса\r\nнеисправности ТУ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;
		Item.strText = "Адрес\r\nASDU";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,50);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Ожидать\r\nзавершение\r\nактивации";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,70);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Таймаут\r\nподтверждения\r\nкоманды,с";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Таймаут\r\nзавершения\r\nактивации,с";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,85);
	}

	if(m_nProcType == PROT_IEC103)	
	{
		Item.row = 0;
		Item.col = nCol;							
		//Item.strText = "Адрес ТУ на\r\nВКЛЮЧЕНИЕ\r\n(FUN)";
		Item.strText = "Адрес ТУ\r\n(FUN)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		//Item.strText = "Адрес ТУ на\r\nВКЛЮЧЕНИЕ\r\n(INF)";
		Item.strText = "Адрес ТУ\r\n(INF)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТУ на\r\nОТКЛЮЧЕНИЕ\r\n(FUN)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,0);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТУ на\r\nОТКЛЮЧЕНИЕ\r\n(INF)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,0);
			
		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ВКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТУ ОТКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Время замыкания\r\nреле в квантах\r\n(1квант = 10 мс.)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,110);

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Время ожидания\r\nподтверждения ТУ\r\nв квантах\r\n(1квант = 10 мс.)";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,110);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Адрес ТС";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,60);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТС ВКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Значение соотв.\r\n\"ТС ОТКЛ.\"";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;
		Item.strText = "Адрес статуса\r\nнеисправности ТУ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;
		Item.strText = "Маска статуса\r\nнеисправности ТУ";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);

		Item.row = 0;
		Item.col = nCol;
		Item.strText = "Адрес\r\nASDU";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,50);	

		Item.row = 0;
		Item.col = nCol;							
		Item.strText = "Таймаут\r\nподтверждения\r\nкоманды,с";
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(nCol++,90);	
	}

	UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CTuConfigTUDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	long nCentery = (long)(cy / 2);
	long nCenter = (long)(cx / 2);

	int dx = 5;
	if (IsWindow(m_Grid.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_Grid.MoveWindow(dx, dx, r.right - r.left - 2*dx, r.bottom - r.top - 50, TRUE);
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
}
afx_msg void CTuConfigTUDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить");	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAPASON, "Добавить диапазон");	
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить");
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
void CTuConfigTUDlg::UpdateGrid(void)
{
	CString str;
	CStringArray aOptions;
	m_Grid.DeleteNonFixedRows();
	
	for(int i = 0; i < m_TuArray.GetSize(); i++)
	{
		int nIndex = m_Grid.InsertRow(NULL);
		int col=0;

		str.Format("%d",i+1);
		m_Grid.SetItemText(nIndex,col++,str);

		m_Grid.SetItemText(nIndex,col++,m_TuArray[i].strCOMMENT);
				
		if(m_nProcType != PROT_SPA)
		{
			switch(m_nProcType )
			{
				case PROT_MODBUS:
					{
						aOptions.Add("Внешнее устройство ТУ");
						aOptions.Add("Модули МКСУ");	
						aOptions.Add("ИПЦ");	
						aOptions.Add("ТУ одна комманда");	
						aOptions.Add("ТУ Овен");	
						break;
					}
				case PROT_IEC101: 
				case PROT_IEC104: 
					{
						aOptions.Add("Одноступенчатое ТУ(IEC101)");
						aOptions.Add("Двуступенчатое ТУ(IEC101)");	
						break;
					}
				case PROT_IEC103: 
					{
						aOptions.Add("Одноступенчатое ТУ(IEC101)");						
						break;
					}
				case PROT_MODBUSTCP: 
			{
						aOptions.Add("Одноступенчатое ТУ");	
						aOptions.Add("Модули МКСУ");
						aOptions.Add("ИПЦ");
						aOptions.Add("резерв");
						aOptions.Add("ТУ Овен");
						break;
					}
			}
			/*if(m_nProcType == PROT_MODBUS)
			{
				aOptions.Add("Внутр.модули ТУ(MODBUS)");
				aOptions.Add("Внешнее устройство ТУ");			
			}
			if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
			{
				aOptions.Add("Одноступенчатое ТУ(IEC101)");
				aOptions.Add("Двуступенчатое ТУ(IEC101)");			
			}
			if(m_nProcType == PROT_IEC103)
				aOptions.Add("Одноступенчатое ТУ(IEC103)");*/
			m_Grid.SetCellType(nIndex,col, RUNTIME_CLASS(CGridCellCombo));
			CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex,col);		
			pCell->SetOptions(aOptions);		
			pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE			
			str.Format("%d",m_TuArray[i].TYPE_PRIBOR);

			if((m_TuArray[i].TYPE_PRIBOR < 0)||(m_TuArray[i].TYPE_PRIBOR >4))
				m_Grid.SetItemText(nIndex,col++, str);
			else
			{
				switch(m_nProcType )
				{
					case PROT_MODBUS:
					case PROT_MODBUSTCP: 
						{
							pCell->SetCurSel(m_TuArray[i].TYPE_PRIBOR);
							break;
						}
					case PROT_IEC101: 
					case PROT_IEC104: 					
					case PROT_IEC103: 
						{
							pCell->SetCurSel(m_TuArray[i].TYPE_PRIBOR-2);				
							break;
						}
				}
				col++;
			}
			aOptions.RemoveAll();
			/*if(m_TuArray[i].TYPE_PRIBOR == 1)
				m_Grid.SetItemText(nIndex,col++, aOptions[0]);
			if(m_TuArray[i].TYPE_PRIBOR == 2)
			{
				if(m_nProcType == PROT_MODBUS)
					m_Grid.SetItemText(nIndex,col++, aOptions[1]);
				else
					m_Grid.SetItemText(nIndex,col++, aOptions[0]);
			}					
			if(m_TuArray[i].TYPE_PRIBOR == 3)
				m_Grid.SetItemText(nIndex,col++, aOptions[1]);	*/							
		}
		else
			col++;

		str.Format("%d",m_TuArray[i].ADRESS);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		if(m_nProcType == PROT_MODBUS)
		{
			aOptions.Add("Force Single Coil(5)");
			aOptions.Add("Preset Single Reg(6)");
		}
		if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
		{
			aOptions.Add("C_SC_NA(45)");
			aOptions.Add("C_DC_NA(46)");
		}
		if(m_nProcType == PROT_IEC103)
		{
			aOptions.Add("DCO(20)");
		}
		if(m_nProcType == PROT_SPA)
		{
			aOptions.Add("1-I-input data");
			aOptions.Add("2-O-output data");	
			aOptions.Add("3-S-setting value");
			aOptions.Add("4-V-variable");
			aOptions.Add("5-M-memory data");
			aOptions.Add("6-C-condition of slave status");
			aOptions.Add("7-F-slave identification");//0		
			aOptions.Add("8-T-time");
			aOptions.Add("9-D-date and time");
			aOptions.Add("10-last events");
			aOptions.Add("11-B-backup events");
			aOptions.Add("12-A-alarms valid");
		}
		m_Grid.SetCellType(nIndex,col, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex,col);		
		pCell->SetOptions(aOptions);
		pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE			
		str.Format("%d",m_TuArray[i].FUNCTION);
		m_Grid.SetItemText(nIndex,col, str);
		if(m_nProcType != PROT_SPA)
		{
			if(m_TuArray[i].FUNCTION == 5)
				m_Grid.SetItemText(nIndex,col++, aOptions[0]);
			if(m_TuArray[i].FUNCTION == 6)
				m_Grid.SetItemText(nIndex,3, aOptions[1]);
			if(m_TuArray[i].FUNCTION == 45)
				m_Grid.SetItemText(nIndex,col++, aOptions[0]);
			if(m_TuArray[i].FUNCTION == 46)
				m_Grid.SetItemText(nIndex,col++, aOptions[1]);
			if(m_TuArray[i].FUNCTION == 20)
				m_Grid.SetItemText(nIndex,col++, aOptions[0]);
			if((m_TuArray[i].FUNCTION != 45)&&(m_TuArray[i].FUNCTION != 46)
				&&(m_TuArray[i].FUNCTION != 20)&&(m_TuArray[i].FUNCTION != 5)
				&&(m_TuArray[i].FUNCTION != 6))
				m_Grid.SetItemText(nIndex,col++, str);		
		}
		else//PROT_SPA
		{
			pCell->SetCurSel(m_TuArray[i].FUNCTION-1);
			col++;
		}
		aOptions.RemoveAll();

		if(m_nProcType == PROT_SPA)
		{
			str.Format("%d",m_TuArray[i].REGTU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].REGTU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].IEC_ASDU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));
		}
		if(m_nProcType == PROT_MODBUS)
		{
			str.Format("%d",m_TuArray[i].REGTU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].REGTU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TU_CLOSER);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].WAIT_RESP_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TIMER_SEL_EXEC);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));
		}
		if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
		{
			str.Format("%d",m_TuArray[i].REGTU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].REGTU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TU_CLOSER);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].WAIT_RESP_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].ADDRESS_TS);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TS_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TS_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].ADDRESS_DAMAGE_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].MASKA_DAMAGE_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].IEC_ASDU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			m_Grid.SetCellType(nIndex,col,RUNTIME_CLASS(CGridCellCheck));
			CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(nIndex, col++);									
			pCell2->SetStrings("Да","Нет");		
			if(m_TuArray[i].TU_ACT_TRM_ENABLE == 0)
				pCell2->SetCheck(FALSE);
			else
				pCell2->SetCheck(TRUE);

			str.Format("%d",m_TuArray[i].TIMER_SEL_EXEC);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TIMER_ACT_TRM);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		}
		if(m_nProcType == PROT_IEC103)
		{
			str.Format("%d",HIBYTE(m_TuArray[i].REGTU_ON));
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",LOBYTE(m_TuArray[i].REGTU_ON));
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",HIBYTE(m_TuArray[i].REGTU_OFF));
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",LOBYTE(m_TuArray[i].REGTU_OFF));
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].DATATU_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TU_CLOSER);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].WAIT_RESP_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].ADDRESS_TS);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TS_ON);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TS_OFF);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].ADDRESS_DAMAGE_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].MASKA_DAMAGE_TU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].IEC_ASDU);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

			str.Format("%d",m_TuArray[i].TIMER_SEL_EXEC);
			m_Grid.SetItemText(nIndex,col,str);
			m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));
		}		
	}
	//m_GridData.Auto
	m_Grid.AutoSizeRows();
	//m_GridData.AutoSizeColumn(0);
	m_Grid.Refresh();
}
afx_msg void CTuConfigTUDlg::OnAdd()
{
	if(!SaveGrid())
		return;
	
	CTu tu;
	if(m_nProcType == PROT_MODBUS)
	{
		tu.TYPE_PRIBOR=1;
		tu.FUNCTION = 5;
	}
	if(m_nProcType == PROT_SPA)
	{		
		tu.FUNCTION = 2;
		tu.DATATU_ON = 1;
		tu.DATATU_OFF = 0;
	}
	if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
	{
		tu.TYPE_PRIBOR=2;			
		tu.FUNCTION = 45;
	}
	if(m_nProcType == PROT_IEC103)
	{
		tu.TYPE_PRIBOR=2;
		tu.FUNCTION = 20;
		tu.DATATU_OFF = 1;
		tu.DATATU_ON = 2;
	}	
	m_TuArray.Add(tu);
	UpdateGrid();
	m_Grid.EnsureVisible(m_Grid.GetRowCount()-1,0);
}
afx_msg void CTuConfigTUDlg::OnDel()
{
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
		m_TuArray.RemoveAt(arGrigIndexes[j]-1);				
		for(int v = j+1; v < arGrigIndexes.GetSize();v++)
		{
			arGrigIndexes[v]--;
		}
	}	
	/*CCellID pCell = m_Grid.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_TuArray.RemoveAt(pCell.row-1);		
	}*/
	SaveGrid();	
	UpdateGrid();
}
afx_msg void CTuConfigTUDlg::OnAddDiapason()
{
	CAddDiapTUDlg dlg;
	dlg.m_nProcType = m_nProcType;
	if(dlg.DoModal() == IDOK)
	{ 
		m_TuArray.Append(dlg.m_TuArray);
	}
	UpdateGrid();
	m_Grid.EnsureVisible(m_Grid.GetRowCount()-1,0);
}	
BOOL CTuConfigTUDlg::PreTranslateMessage(MSG* pMsg)
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
