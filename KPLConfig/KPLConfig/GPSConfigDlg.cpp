// GPSConfigDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "GPSConfigDlg.h"

#define IDM_PRINT1 WM_USER + 420
// диалоговое окно CGPSConfigDlg

IMPLEMENT_DYNAMIC(CGPSConfigDlg, CDialog)

CGPSConfigDlg::CGPSConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGPSConfigDlg::IDD, pParent)
{
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
}

CGPSConfigDlg::~CGPSConfigDlg()
{
}

void CGPSConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CGPSConfigDlg, CDialog)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_COMMAND(IDM_PRINT1, OnPrint)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
END_MESSAGE_MAP()

afx_msg void CGPSConfigDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CGPSConfigDlg::OnPrint(void)
{
	m_Grid.Print();
}
// обработчики сообщений CGPSConfigDlg
void CGPSConfigDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	CString str;
		
	str = m_Grid.GetItemText(15,1);
	if(str=="только ОИК")
		m_GPSTime.SYNC_FROM=1;
	if(str=="ОИК и GPS")
		m_GPSTime.SYNC_FROM=2;
	if(str=="только GPS")
		m_GPSTime.SYNC_FROM=3;
	if(str=="сервер времени NTP")
		m_GPSTime.SYNC_FROM=4;
	
	str = m_Grid.GetItemText(1,1);
	if(m_GPSTime.SYNC_FROM!=1)//not only oik
	{
		if((atoi(str)<=0)||(atoi(str)>255))
		{
			AfxMessageBox("Неверно задан СОМ-порт!");
			return ;
		}
		//проверить порты
	
		if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.IsPortDuplicated(atoi(str)-1,-1))
		{
			AfxMessageBox("Данный СОМ-порт занят под другую задачу!");
			return ;
		}
	}

	m_GPSTime.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_GPSTime.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_GPSTime.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(4,1);
	if(str == "NONE")
		m_GPSTime.PARITY = 0;
	if(str == "EVEN")
		m_GPSTime.PARITY = 1;
	if(str == "ODD")
		m_GPSTime.PARITY = 2;

	str = m_Grid.GetItemText(5,1);
	if(str == "нет")
		m_GPSTime.FLOWCONTROLL = 0;
	if(str == "аппаратный")
		m_GPSTime.FLOWCONTROLL = 1;
	if(str == "программный")
		m_GPSTime.FLOWCONTROLL = 2;
	
	str = m_Grid.GetItemText(6,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Пауза между байтами в квантах 1..3000!");
		return ;
	}
	m_GPSTime.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Интервал между запросами в квантах 1..3000!");
		return ;
	}
	m_GPSTime.NEXTMESSAGE = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		AfxMessageBox("Количество ошибок для генерации \"недостоверности\" 0..50!");
		return ;
	}
	m_GPSTime.NUMBER_NO_ANSWER = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if(str=="Garmin")
		m_GPSTime.TYPE_OF_GPS = 1;

	str = m_Grid.GetItemText(10,1);
	if((atoi(str)<0)||(atoi(str)>4320))
	{
		AfxMessageBox("Период для синхронизации времени: 0 - нет, 1..4320 мин.!");
		return ;
	}
	m_GPSTime.PERIOD_C_CS_NA_1 = atoi(str);

	str = m_Grid.GetItemText(11,1);
	if(str=="Нет")
		m_GPSTime.SERVICE=0;
	else
		m_GPSTime.SERVICE=1;

	str = m_Grid.GetItemText(12,1);
	if(str=="Нет")
		m_GPSTime.SUMMER_TIME_ON=0;
	else
		m_GPSTime.SUMMER_TIME_ON=1;
	
	str = m_Grid.GetItemText(13,1);
	if((atoi(str)<-12)||(atoi(str)>13))
	{
		AfxMessageBox("Коррекция времени согласно часового пояса: -12..13!");
		return;
	}
	m_GPSTime.GMT_CORRECTION = atoi(str);

	str = m_Grid.GetItemText(14,1);
	if(str=="Нет")
		m_GPSTime.ENABLE_SCRIPT=0;
	else
		m_GPSTime.ENABLE_SCRIPT=1;	

	str = m_Grid.GetItemText(16,1);
	m_GPSTime.m_IndividualStructureGPSArray[0].ADDRESS_PMZ = atoi(str);
	
	CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(17, 1);
	m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA = pCell->GetCurSel();
	
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA > 0)
	{
		if((m_GPSTime.m_IndividualStructureGPSArray[0].ADDRESS_PMZ<m_nStartPMZAddr)||(m_GPSTime.m_IndividualStructureGPSArray[0].ADDRESS_PMZ>m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("Запись времени в карту памяти по адресу %d..%d!",m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			//return FALSE;
		}
	}

	str = m_Grid.GetItemText(18,1);
	m_GPSTime.m_IndividualStructureGPSArray[1].ADDRESS_PMZ = atoi(str);
	
	str = m_Grid.GetItemText(19,1);
	if(str=="не записывать")
		m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA=0;
	else if(str=="записывать")
		m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA=1;
	else
	{
		m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA=atoi(str);
	}
		
	if(m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA > 0)
	{
		if((m_GPSTime.m_IndividualStructureGPSArray[1].ADDRESS_PMZ<m_nStartPMZAddr)||(m_GPSTime.m_IndividualStructureGPSArray[1].ADDRESS_PMZ>m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("Запись времени в карту памяти по адресу %d..%d!",m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			//return FALSE;
		}
	}
	if(m_GPSTime.m_nVersion > 19)
	{
		str = m_Grid.GetItemText(20,1);
		m_GPSTime.GPS_SYNC_ATTEMPT_TIME = atoi(str);

		m_GPSTime.NTP_SERVER_IP = m_Grid.GetItemText(21,1);

		CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(22, 1);
		m_GPSTime.NTP_LOG = (int)pCell2->GetCheck();
	}

	CDialog::OnOK();
}
BOOL CGPSConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	if(m_GPSTime.m_nVersion > 19)	
		m_Grid.SetRowCount(23);	
	else
		m_Grid.SetRowCount(21);

	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-порт");
	str.Format("%d",m_GPSTime.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"Скорость, бод");
	str.Format("%d",m_GPSTime.BAUDRATE);
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
	
	m_Grid.SetItemText(3,0,"Стоповых бит");
	str.Format("%d",m_GPSTime.STOPBITS);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(3, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	
	m_Grid.SetItemText(4,0,"Контроль четности");	
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	aOptions.Add("NONE");
	aOptions.Add("EVEN");
	aOptions.Add("ODD");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_GPSTime.PARITY!=1)&&(m_GPSTime.PARITY!=2))
		m_Grid.SetItemText(4,1,aOptions[0]);
	if(m_GPSTime.PARITY==1)
		m_Grid.SetItemText(4,1,aOptions[1]);
	if(m_GPSTime.PARITY==2)
		m_Grid.SetItemText(4,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(5,0,"Контроль потока");	
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
	aOptions.Add("нет");
	aOptions.Add("аппаратный");
	aOptions.Add("программный");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_GPSTime.FLOWCONTROLL!=1)&&(m_GPSTime.FLOWCONTROLL!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_GPSTime.FLOWCONTROLL==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_GPSTime.FLOWCONTROLL==2)
		m_Grid.SetItemText(5,1,aOptions[2]);
	aOptions.RemoveAll();	

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;	

	Item.row = 6;
	Item.col = 0;							
	Item.strText = "Пауза между байтами\r\nв квантах\r\n(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(7,0,"Пауза между байтами в квантах (1квант = 10 мс.)");
	str.Format("%d",m_GPSTime.BYTETIME);
	m_Grid.SetItemText(6,1,str);
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 7;
	Item.col = 0;							
	Item.strText = "Интервал очистки буфера\r\nв квантах\r\n(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(8,0,"Интервал между запросами в квантах (1квант = 10 мс.)");
	str.Format("%d",m_GPSTime.NEXTMESSAGE);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));
	
	Item.row = 8;
	Item.col = 0;							
	Item.strText = "Количество ошибок для\r\nгенерации \"недостоверности\"";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(15,0,"Количество ошибок для генерации \"недостоверности\"");
	str.Format("%d",m_GPSTime.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(9,0,"Приемник GPS");	
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(9, 1);
	aOptions.Add("Garmin");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_GPSTime.TYPE_OF_GPS==1)
		m_Grid.SetItemText(9,1,aOptions[0]);	

	aOptions.RemoveAll();

	Item.row = 10;
	Item.col = 0;							
	Item.strText = "Период синхронизации времени\r\nв минутах (0 - нет)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(14,0,"Период для синхронизации времени, мин. (0 - нет)");
	str.Format("%d",m_GPSTime.PERIOD_C_CS_NA_1);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(11,0,"Вывод на консоль");	
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(11, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_GPSTime.SERVICE==0)
		m_Grid.SetItemText(11,1,aOptions[0]);	
	else
		m_Grid.SetItemText(11,1,aOptions[1]);	
	aOptions.RemoveAll();

	m_Grid.SetItemText(12,0,"Переход на летнее время");	
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(12, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_GPSTime.SUMMER_TIME_ON==0)
		m_Grid.SetItemText(12,1,aOptions[0]);	
	else
		m_Grid.SetItemText(12,1,aOptions[1]);	
	aOptions.RemoveAll();
	
	Item.row = 13;
	Item.col = 0;							
	Item.strText = "Коррекция времени\r\nсогласно часового\r\nпояса";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(16,0,"Запись статуса канала в карту памяти ПРОЦЕССА по адресу");
	str.Format("%d",m_GPSTime.GMT_CORRECTION);
	m_Grid.SetItemText(13,1,str);	

	m_Grid.SetItemText(14,0,"Загрузка скрипта настройки");	
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(14, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_GPSTime.ENABLE_SCRIPT==0)
		m_Grid.SetItemText(14,1,aOptions[0]);	
	else
		m_Grid.SetItemText(14,1,aOptions[1]);	
	aOptions.RemoveAll();

	m_Grid.SetItemText(15,0,"Синхронизация с");	
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(15, 1);
	aOptions.Add("только ОИК");
	aOptions.Add("ОИК и GPS");
	aOptions.Add("только GPS");
	if(m_GPSTime.m_nVersion > 19)	
		aOptions.Add("сервер времени NTP");

	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_GPSTime.SYNC_FROM==1)
		m_Grid.SetItemText(15,1,aOptions[0]);	
	if(m_GPSTime.SYNC_FROM==2)
		m_Grid.SetItemText(15,1,aOptions[1]);	
	if(m_GPSTime.SYNC_FROM==3)
		m_Grid.SetItemText(15,1,aOptions[2]);	
	if((m_GPSTime.SYNC_FROM==4)&&(m_GPSTime.m_nVersion > 19))
		m_Grid.SetItemText(15,1,aOptions[3]);	
	aOptions.RemoveAll();

	Item.row = 16;
	Item.col = 0;							
	Item.strText = "Нач.адрес времени\r\nв карте памяти";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(16,0,"Запись статуса канала в карту памяти ПРОЦЕССА по адресу");
	str.Format("%d",m_GPSTime.m_IndividualStructureGPSArray[0].ADDRESS_PMZ);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(17,0,"Записывать время как");	
	m_Grid.SetCellType(17,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(17, 1);
	aOptions.Add("не записывать");
	aOptions.Add("час:мин.");
	aOptions.Add("час:мин.:сек.");
	aOptions.Add("час:мин.:сек. день");
	aOptions.Add("час:мин.:сек. день.мес.");
	aOptions.Add("час:мин.:сек. день.мес.год");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA==0)
		m_Grid.SetItemText(17,1,aOptions[0]);	
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA==1)
		m_Grid.SetItemText(17,1,aOptions[1]);	
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA==2)
		m_Grid.SetItemText(17,1,aOptions[2]);	
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA==3)
		m_Grid.SetItemText(17,1,aOptions[3]);	
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA==4)
		m_Grid.SetItemText(17,1,aOptions[4]);	
	if(m_GPSTime.m_IndividualStructureGPSArray[0].AM_IOA==5)
		m_Grid.SetItemText(17,1,aOptions[5]);
	aOptions.RemoveAll();

	Item.row = 18;
	Item.col = 0;							
	Item.strText = "Нач.адрес статуса\r\nв карте памяти";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(16,0,"Запись статуса канала в карту памяти ПРОЦЕССА по адресу");
	str.Format("%d",m_GPSTime.m_IndividualStructureGPSArray[1].ADDRESS_PMZ);
	m_Grid.SetItemText(18,1,str);
	m_Grid.SetCellType(18,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(19,0,"Записывать статус как");	
	m_Grid.SetCellType(19,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(19, 1);
	aOptions.Add("не записывать");
	aOptions.Add("записывать");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWN);
	if(m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA==0)
		m_Grid.SetItemText(19,1,aOptions[0]);	
	else if(m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA==1)
		m_Grid.SetItemText(19,1,aOptions[1]);	
	else
	{
		CString str;
		str.Format("%d",m_GPSTime.m_IndividualStructureGPSArray[1].AM_IOA);
		m_Grid.SetItemText(19,1,str);	
	}	

	if(m_GPSTime.SYNC_FROM==1)//only oik
	{
		for(int row = 1; row < m_Grid.GetRowCount(); row++)
		{
			if((row != 15)&&(row != 16)&&(row != 17))
				m_Grid.SetItemState(row, 1, GVIS_READONLY);
		}
	}

	
	Item.row = 20;
	Item.col = 0;							
	Item.strText = "Интервал синхронизации\r\nот GPS (в минутах)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(16,0,"Запись статуса канала в карту памяти ПРОЦЕССА по адресу");
	str.Format("%d",m_GPSTime.GPS_SYNC_ATTEMPT_TIME);
	m_Grid.SetItemText(20,1,str);
	m_Grid.SetCellType(20,1, RUNTIME_CLASS(CGridCellNumeric));

	if(m_GPSTime.m_nVersion > 19)	
	{
		Item.row = 21;
		Item.col = 0;							
		Item.strText = "Адрес NTP-сервера";
		m_Grid.SetItem(&Item);	
		m_Grid.SetItemText(21,1,m_GPSTime.NTP_SERVER_IP);	

		m_Grid.SetItemText(22,0,"Log-файл NTP");	
		m_Grid.SetCellType(22,1, RUNTIME_CLASS(CGridCellCheck));
		CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(22, 1);
		pCell2->SetStrings("Вести","Не вести");
		if(m_GPSTime.NTP_LOG)
			pCell2->SetCheck(TRUE);
		else
			pCell2->SetCheck(FALSE);

	}
	m_Grid.AutoSize();	
	m_Grid.SetColumnWidth(1,200);
	m_Grid.Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
afx_msg void CGPSConfigDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	
	CString str;
		
	str = m_Grid.GetItemText(15,1);
	if(str=="только ОИК")
		m_GPSTime.SYNC_FROM=1;
	if(str=="ОИК и GPS")
		m_GPSTime.SYNC_FROM=2;
	if(str=="только GPS")
		m_GPSTime.SYNC_FROM=3;
	if(str=="сервер времени NTP")
		m_GPSTime.SYNC_FROM=4;

	if(m_GPSTime.SYNC_FROM==1)//only oik
	{
		for(int row = 1; row < m_Grid.GetRowCount(); row++)
		{
			if((row != 15)&&(row != 16)&&(row != 17))
				m_Grid.SetItemState(row, 1, GVIS_READONLY);
		}
	}
	else
	{		
		for(int row = 1; row < m_Grid.GetRowCount(); row++)
		{
			if((row != 15)&&(row != 16)&&(row != 17))
				m_Grid.SetItemState(row, 1, 0);
		}
	}
	m_Grid.Refresh();
}

BOOL CGPSConfigDlg::PreTranslateMessage(MSG* pMsg)
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
