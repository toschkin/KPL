
// KPLConfigDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "KPLConfigDlg.h"
#include "IPDlg.h"
#include "GetFilesDlg.h"
#include "FileManip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char* iGetLastErrorText(void)
{
	DWORD err = GetLastError();

    char* msg= NULL;
	if(err)
	{
		// Ask Windows to prepare a standard message for a GetLastError() code:
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msg, 0, NULL);
		// Return the message
		return(msg);
	}
	else    
        return("OK");           
}

// диалоговое окно CKPLConfigDlg
#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_DETAIL	WM_USER + 402
#define IDM_ADDDIAP	WM_USER + 403
#define IDM_COPY	WM_USER + 404


BOOL IsIntersect(int Start1,int End1,int Start2,int End2)
{
	if((Start2>=Start1)&&(Start2<=End1))
		return TRUE;
	if((Start1>=Start2)&&(Start1<=End2))
		return TRUE;
	if((End2>=Start1)&&(End2<=End1))
		return TRUE;
	if((End1>=Start2)&&(End1<=End2))
		return TRUE;
	return FALSE;
}

CKPLConfigDlg::CKPLConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKPLConfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nOldTab=0;
	m_strFtpUser = "root";
	m_strFtpPassword = "vitamax";
	m_strFtpSite = "/home/work_file";
	m_strFtpHome = "/home";
	m_strFtpLog = "/home/logfile/log";
	m_strFtpAlarm = "/home/logfile/alarm";	
}

void CKPLConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, m_MainTab);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_COMBOVERSION, m_cmbVersion);
}

BEGIN_MESSAGE_MAP(CKPLConfigDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, &CKPLConfigDlg::OnTcnSelchangeMainTab)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, &CKPLConfigDlg::OnRClickGrid)
	ON_COMMAND(IDM_ADD, &CKPLConfigDlg::OnAdd)
	ON_COMMAND(IDM_ADDDIAP, &CKPLConfigDlg::OnAddDiapason)	
	ON_COMMAND(IDM_DEL, &CKPLConfigDlg::OnDel)
	ON_COMMAND(IDM_COPY, &CKPLConfigDlg::OnCopy)	
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, &CKPLConfigDlg::OnGridEndEdit)
	ON_WM_SIZE()
	ON_COMMAND(IDM_SAVE, &CKPLConfigDlg::OnSave)	
	ON_COMMAND(IDM_OPEN, &CKPLConfigDlg::OnOpen)
	ON_COMMAND(IDM_CLOSE, &CKPLConfigDlg::OnClose)
	ON_COMMAND(IDM_DETAIL, &CKPLConfigDlg::OnDetail)
	ON_COMMAND(IDM_PRINT, &CKPLConfigDlg::OnPrint)
	ON_COMMAND(IDM_SAVE_TO_KPL, &CKPLConfigDlg::OnSaveToKsri)
	ON_COMMAND(IDM_OPEN_FTP, &CKPLConfigDlg::OnOpenFtp)
	ON_COMMAND(IDM_UPLOADFW, &CKPLConfigDlg::OnUploadfw)
	ON_COMMAND(IDM_DOWNLOADFW, &CKPLConfigDlg::OnDownloadfw)
	ON_COMMAND(IDM_ALARM, &CKPLConfigDlg::OnAlarm)
	ON_COMMAND(IDM_LOG, &CKPLConfigDlg::OnLog)
	ON_COMMAND(ID_32794, &CKPLConfigDlg::On32794)
	ON_COMMAND(IDM_TELNET, &CKPLConfigDlg::OnTelnet)
	ON_CBN_SELENDOK(IDC_COMBOVERSION, &CKPLConfigDlg::OnCbnSelendokComboversion)
	ON_COMMAND(ID_STOPKPLSOFT, &CKPLConfigDlg::OnStopkplsoft)
END_MESSAGE_MAP()

CString GetEXEDirPath(void)
{
	CString path;	
	//Retrieving program directory	
	GetModuleFileName(NULL,path.GetBuffer(5000),5001);	
	path.ReleaseBuffer();	
	int nIndex = path.ReverseFind('\\');
	int nLength = path.GetLength();
	path.Delete(nIndex,nLength - nIndex);
	return path;
}
/*

*/
// обработчики сообщений CKPLConfigDlg

BOOL CKPLConfigDlg::OnInitDialog()
{	
	CDialog::OnInitDialog();

	m_WaitDlg.Create(IDD_WAITDIALOG,this);
	m_WaitDlg.CenterWindow();
	//CString m_strLogPath;
	//CString m_strAlarmPath;
	m_strAlarmPath = m_strLogPath = GetEXEDirPath();
	m_strLogPath+="\\Log";
	m_strAlarmPath+="\\Alarm";
	if(CFileManip::Existence(m_strLogPath) != CFileManip::FM_DIRECTORY)
	{
		if(!CFileManip::MkDir(m_strLogPath))		
			m_strLogPath.TrimRight("\\Log");
	}
	if(CFileManip::Existence(m_strAlarmPath) != CFileManip::FM_DIRECTORY)
	{
		if(!CFileManip::MkDir(m_strAlarmPath))		
			m_strAlarmPath.TrimRight("\\Alarm");
	}
	m_strLogPath+="\\";
	m_strAlarmPath+="\\";
	
	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	ShowWindow(SW_MAXIMIZE);

	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
	
	TabCtrlItem.pszText = "Общие настройки";
	m_MainTab.InsertItem( 0, &TabCtrlItem );

	TabCtrlItem.pszText = "Настройка процессов";
	m_MainTab.InsertItem( 1, &TabCtrlItem );

	TabCtrlItem.pszText = "Настройка карты памяти";
	m_MainTab.InsertItem( 2, &TabCtrlItem );

	TabCtrlItem.pszText = "Настройка масок";
	m_MainTab.InsertItem( 3, &TabCtrlItem );

	/*TabCtrlItem.pszText = "Настройка ";
	m_MainTab.InsertItem( 4, &TabCtrlItem );

	TabCtrlItem.pszText = "Монитор";
	m_MainTab.InsertItem( 5, &TabCtrlItem );*/
	
	m_Grid.SetRowCount(0);
	m_Grid.SetColumnCount(0);
	m_Grid.EnableSelection(FALSE);
	m_Grid.EnableTitleTips(TRUE);	

	arrMain_Set_ProcessesTypes.Add("Отсутствие задачи");
	arrMain_Set_ProcessesTypes.Add("MODBUS-master");
	arrMain_Set_ProcessesTypes.Add("MODBUS-slave");
	arrMain_Set_ProcessesTypes.Add("IEC870-5-101-master");
	arrMain_Set_ProcessesTypes.Add("IEC870-5-101-slave");
	arrMain_Set_ProcessesTypes.Add("IEC870-5-103-master");
	arrMain_Set_ProcessesTypes.Add("IEC870-5-104-master");
	arrMain_Set_ProcessesTypes.Add("IEC870-5-104-slave(PtP)");
	arrMain_Set_ProcessesTypes.Add("IEC870-5-104-slave(PtMP)");
	arrMain_Set_ProcessesTypes.Add("Задача ретрансляции");	
	arrMain_Set_ProcessesTypes.Add("Задача монитора");
	arrMain_Set_ProcessesTypes.Add("Синхронизация времени");
	arrMain_Set_ProcessesTypes.Add("КОРУНД-master");
	arrMain_Set_ProcessesTypes.Add("GPIO");
	arrMain_Set_ProcessesTypes.Add("Вывод на ДЩ");
	arrMain_Set_ProcessesTypes.Add("SPA-master");
	arrMain_Set_ProcessesTypes.Add("Modbus(TCP)-master");
	arrMain_Set_ProcessesTypes.Add("STM32");
	
	arrMain_Set_ObjectTypes.Add("Единичный ТС");//M_SP_NA_1
	arrMain_Set_ObjectTypes.Add("Единичный ТС с короткой МВ");//M_SP_TA_1
	arrMain_Set_ObjectTypes.Add("Единичный ТС с длинной МВ");//M_SP_TB_1
	arrMain_Set_ObjectTypes.Add("Двойной ТС");//M_DP_NA_1
	arrMain_Set_ObjectTypes.Add("Двойной ТС с короткой МВ");//M_DP_TA_1
	arrMain_Set_ObjectTypes.Add("Двойной ТС с длинной МВ");//M_DP_TB_1
	arrMain_Set_ObjectTypes.Add("ТИ доп.код");//M_ME_NA_1
	arrMain_Set_ObjectTypes.Add("ТИ доп.код с короткой МВ");//M_ME_TA_1
	arrMain_Set_ObjectTypes.Add("ТИ доп.код с длинной МВ");//M_ME_TD_1
	arrMain_Set_ObjectTypes.Add("ТИ доп.код без байта качества");//M_ME_ND_1
	arrMain_Set_ObjectTypes.Add("ТИ масштаб.");//M_ME_NB_1
	arrMain_Set_ObjectTypes.Add("ТИ масштаб. с короткой МВ");//M_ME_TB_1
	arrMain_Set_ObjectTypes.Add("ТИ масштаб. с длинной МВ");//M_ME_TE_1
	arrMain_Set_ObjectTypes.Add("ТИ плав.точка");//M_ME_NC_1
	arrMain_Set_ObjectTypes.Add("ТИ плав.точка с короткой МВ");//M_ME_TC_1
	arrMain_Set_ObjectTypes.Add("ТИ плав.точка с длинной МВ");//M_ME_TF_1
	arrMain_Set_ObjectTypes.Add("32 бита");//M_BO_NA_1
	arrMain_Set_ObjectTypes.Add("32 бита с короткой МВ");//M_BO_TA_1
	arrMain_Set_ObjectTypes.Add("32 бита с длинной МВ");//M_BO_TB_1

	arrObjectTypesInt.Add(M_SP_NA_1);//01 // ТС
	arrObjectTypesInt.Add(M_SP_TA_1);//02 // ТС со временем 24
	arrObjectTypesInt.Add(M_SP_TB_1);//1E // ТС со временем 56
	arrObjectTypesInt.Add(M_DP_NA_1);//03 // двойной ТС
	arrObjectTypesInt.Add(M_DP_TA_1);//04 // двойной ТС со временем 24
	arrObjectTypesInt.Add(M_DP_TB_1);//04 // двойной ТС со временем 24
	arrObjectTypesInt.Add(M_ME_NA_1);//09 // ТИ нормализов.
	arrObjectTypesInt.Add(M_ME_TA_1);//0A // ТИ нормализов. со временем 24
	arrObjectTypesInt.Add(M_ME_TD_1);//22 // ТИ нормализов. со временем 56
	arrObjectTypesInt.Add(M_ME_ND_1);//15 // ТИ нормализов.без описателя качества
	arrObjectTypesInt.Add(M_ME_NB_1);//0B // ТИ масштабированые
	arrObjectTypesInt.Add(M_ME_TB_1);//0C // ТИ масштабированые со временем 24
	arrObjectTypesInt.Add(M_ME_TE_1);//23 // ТИ масштабированые со временем 56
	arrObjectTypesInt.Add(M_ME_NC_1);//0D // ShortFloatingPointNumber
	arrObjectTypesInt.Add(M_ME_TC_1);//0E // ShortFloatingPointNumber 24
	arrObjectTypesInt.Add(M_ME_TF_1);//24 // ShortFloatingPointNumber 56
	arrObjectTypesInt.Add(M_BO_NA_1);//07 // Bitstring of 32 bit	
	arrObjectTypesInt.Add(M_BO_TA_1);//08 // Bitstring of 32 bit 24	
	arrObjectTypesInt.Add(M_BO_TB_1);//21 // Bitstring of 32 bit 56
	
	
	UpdateCombo();
	ChangeTab(0);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CKPLConfigDlg::UpdateCombo(void)
{
	int nCurSel = 0;
	m_cmbVersion.ResetContent();	
	CString strFormat;
	for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_arrVersions.GetSize(); i++)
	{
		strFormat.Format("%d.%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_arrVersions[i]/10,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_arrVersions[i]%10);
		if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_nVersion == ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_arrVersions[i])
		{
			strFormat+=" *";
			nCurSel=i;
		}
		m_cmbVersion.AddString(strFormat);
		m_cmbVersion.SetItemData(i,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_arrVersions[i]);
	}	
	m_cmbVersion.SetCurSel(nCurSel);
}
// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CKPLConfigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CKPLConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKPLConfigDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: добавьте свой код обработчика уведомлений
	
	if(SaveTab(m_nOldTab))
		ChangeTab(m_MainTab.GetCurSel());
	else
		m_MainTab.SetCurSel(m_nOldTab);
	*pResult = 0;
}

void CKPLConfigDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	int dx = 5;
	if (IsWindow(m_MainTab.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_MainTab.MoveWindow(dx, dx+30, r.right - r.left - 2*dx, r.bottom - r.top - 2*dx -30, TRUE);
	}
	if (IsWindow(m_Grid.m_hWnd))
	{
		CRect r;
		m_MainTab.GetClientRect(&r);
		m_Grid.MoveWindow(2*dx, 70, r.right - r.left - 4*dx, r.bottom - r.top - 40 - dx*2, TRUE);		
	}
	// TODO: добавьте свой код обработчика сообщений
}

void CKPLConfigDlg::ChangeTab(int tab)
{
	m_nOldTab = tab;

	m_Grid.DeleteAllItems();
	m_Grid.SetColumnResize();
	m_Grid.SetRowResize(0);
	m_Grid.EnableSelection(FALSE);
	m_Grid.SetListMode(FALSE);
	m_Grid.SetFixedColumnSelection(FALSE);

	switch(tab)
	{
		case 0://obshie
			{
				m_Grid.SetColumnCount(2);
				m_Grid.SetFixedColumnCount(1);
				m_Grid.SetRowCount(6);
				if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 19)
					m_Grid.SetRowCount(9);

				m_Grid.SetFixedRowCount(1);
				m_Grid.SetColumnWidth(0,60);
				m_Grid.SetItemText(0,0,"Параметр");
				m_Grid.SetItemText(0,1,"Значение");
				CString str;
				m_Grid.SetItemText(1,0,"Размер индивидуальных буферов межпроцессного взаимодействия");
				str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.REAL_SIZE_DIRECT_BUFER);
				m_Grid.SetItemText(1,1,str);
				m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

				m_Grid.SetItemText(2,0,"Размер общедоступного буфера межпроцессного взаимодействия");
				str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.REAL_NUM_GENFAST_OBJECT);
				m_Grid.SetItemText(2,1,str);
				m_Grid.SetCellType(2, 1, RUNTIME_CLASS(CGridCellNumeric));

				m_Grid.SetItemText(3,0,"Общее количество информационных объектов в карте памяти");
				str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT);
				m_Grid.SetItemText(3,1,str);
				m_Grid.SetCellType(3, 1, RUNTIME_CLASS(CGridCellNumeric));				

				m_Grid.SetItemText(4,0,"Название п/с");				
				m_Grid.SetItemText(4,1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_strPSNAME);				

				m_Grid.SetItemText(5,0,"Количество портов");				
				m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellCombo));
				CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
				pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
				CStringArray arrOptions;
				arrOptions.Add("8_PORT");
				arrOptions.Add("4_PORT");
				arrOptions.Add("12_PORT");
				pCell->SetOptions(arrOptions);		
				pCell->SetStyle(CBS_DROPDOWNLIST); //C
				m_Grid.SetItemText(5,1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.KPLType);				

				if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 19)
				{
					m_Grid.SetItemText(6,0,"IP адрес КПЛ");					
					m_Grid.SetItemText(6,1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.MY_IP);

					m_Grid.SetItemText(7,0,"Маска подсети КПЛ");					
					m_Grid.SetItemText(7,1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.MY_IP_MASK);

					m_Grid.SetItemText(8,0,"Шлюз КПЛ");					
					m_Grid.SetItemText(8,1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.MY_IP_GW);
				}

				m_Grid.AutoSize();
				m_Grid.Refresh();
				break;
			}
		case 1://processes
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.nFormat = DT_CENTER|DT_WORDBREAK;									
				
				m_Grid.SetColumnCount(8);				
				m_Grid.SetFixedColumnCount(1);
				m_Grid.SetRowCount(1);
				m_Grid.SetFixedRowCount(1);				
				m_Grid.SetItemText(0,0,"№");
				m_Grid.SetItemText(0,1,"Тип процесса");
				
				Item.row = 0;
				Item.col = 2;							
				Item.strText = "Начальный адрес\r\nполя данных";
				m_Grid.SetItem(&Item);				

				Item.row = 0;
				Item.col = 3;							
				Item.strText = "Кол-во инф.объектов\r\nв поле данных";
				m_Grid.SetItem(&Item);				

				Item.row = 0;
				Item.col = 4;							
				Item.strText = "Ретрансляция\r\nиз процесса";
				m_Grid.SetItem(&Item);				
				
				Item.row = 0;
				Item.col = 5;							
				Item.strText = "Журнал авар.\r\nсообщений";
				m_Grid.SetItem(&Item);				

				Item.row = 0;
				Item.col = 6;							
				Item.strText = "Журнал обмена\r\nданными";
				m_Grid.SetItem(&Item);				
											
				m_Grid.SetItemText(0,7,"Комментарий");	
				m_Grid.AutoSizeRows();
								

				if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize() == 0)
				{
					ProcessInfo pi;
					pi.TYPE_PROTOKOL = 9;
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Add(pi);					
					pi.TYPE_PROTOKOL = 12;
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Add(pi);
					pi.TYPE_PROTOKOL = 13;
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Add(pi);					
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.Add(0);
				}
				BOOL bNewConfig = FALSE;
				for(int i =0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize(); i++)
				{
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 13)
					{
						bNewConfig = TRUE;
						break;
					}
				}
				if(!bNewConfig)
				{
					ProcessInfo pi;
					pi.TYPE_PROTOKOL = 13;
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.InsertAt(2,pi);					
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.InsertAt(2,0);
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.RenumerateChannels(2,FALSE);
				}
				CString str;				
				for(int i =0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize(); i++)
				{
					int nIndex = m_Grid.InsertRow(NULL);
					str.Format("%d",i+1);
					m_Grid.SetItemText(nIndex,0,str);					
															
					if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 255)//po izmen
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[0]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 1)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[1]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 2)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[2]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 3)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[3]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 4)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[4]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 5)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[5]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 7)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[6]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 8)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[7]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 14)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[8]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 9)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[9]);
					/*else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 12)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[9]);*/
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 10)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[10]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 13)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[11]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 15)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[12]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 16)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[13]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 18)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[14]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 17)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[15]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 19)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[16]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 21)//po srezam
						m_Grid.SetItemText(nIndex,1, arrMain_Set_ProcessesTypes[17]);					
					else
						m_Grid.SetItemText(nIndex, 1, _T("Неизвестный тип"));
					
					if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL != 12)&&
						(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL != 9))
					{
						if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL != 13))
						{
							m_Grid.SetCellType(nIndex, 1, RUNTIME_CLASS(CGridCellCombo));
							CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex, 1);							
							CStringArray tmpArr;
							tmpArr.Copy(arrMain_Set_ProcessesTypes);

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 20)
								tmpArr.SetSize(tmpArr.GetSize()-1);

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 19)
								tmpArr.SetSize(tmpArr.GetSize()-1);

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 18)
								tmpArr.SetSize(tmpArr.GetSize()-1);

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 17)
								tmpArr.SetSize(tmpArr.GetSize()-1);

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 15)
								tmpArr.SetSize(tmpArr.GetSize()-1);

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 13)
								tmpArr.SetSize(tmpArr.GetSize()-1);
														
							pCell->SetOptions(tmpArr);		
							pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
						}
						else
						{
							m_Grid.SetItemState(nIndex, 1, m_Grid.GetItemState(nIndex, 1) | GVIS_READONLY);
						}

						str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].START_ADDRESS_MAP);
						m_Grid.SetItemText(nIndex,2,str);
						m_Grid.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

						str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].AMOUNT_SIGNIFICATE);
						m_Grid.SetItemText(nIndex,3,str);
						m_Grid.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

						if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 1)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 3)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 5)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 7)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 15)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 13)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 17)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 16)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 19)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 21))
						{							
							m_Grid.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellCombo));
							CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 4);						
							CStringArray tmpArr;
							tmpArr.Add("Нет");
							tmpArr.Add("Разрешить");							
							pCell2->SetOptions(tmpArr);		
							pCell2->SetStyle(CBS_DROPDOWNLIST); 
							
							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT[i] == 0)
								pCell2->SetCurSel(0);
							else
								pCell2->SetCurSel(1);
						}
						else
							m_Grid.SetItemState(nIndex, 4, m_Grid.GetItemState(nIndex, 4) | GVIS_READONLY);					

						m_Grid.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellCombo));
						CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 5);
						CStringArray tmpArr;
						tmpArr.Add("Нет");
						tmpArr.Add("Да");							
						pCell2->SetOptions(tmpArr);		
						pCell2->SetStyle(CBS_DROPDOWNLIST); 
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].YESNOLOGALARM == 1)//inversno
							pCell2->SetCurSel(0);
						else
							pCell2->SetCurSel(1);

						m_Grid.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellCombo));
						pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 6);
						pCell2->SetOptions(tmpArr);		
						pCell2->SetStyle(CBS_DROPDOWNLIST); 
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].YESNOLOGPROTOKOL == 1)
							pCell2->SetCurSel(0);
						else
							pCell2->SetCurSel(1);
					}
					else
					{
						m_Grid.SetItemState(nIndex, 1, m_Grid.GetItemState(nIndex, 1) | GVIS_READONLY);
						m_Grid.SetItemState(nIndex, 2, m_Grid.GetItemState(nIndex, 2) | GVIS_READONLY);
						//m_Grid.SetItemState(nIndex, 3, m_Grid.GetItemState(nIndex, 1) | GVIS_READONLY);
						m_Grid.SetItemState(nIndex, 4, m_Grid.GetItemState(nIndex, 4) | GVIS_READONLY);
												
						/*m_Grid.SetItemBkColour(nIndex, 1,RGB(150,150,150));
						m_Grid.SetItemBkColour(nIndex, 2,RGB(150,150,150));
						m_Grid.SetItemBkColour(nIndex, 3,RGB(150,150,150));*/
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 9)							
						{
							str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.NUM_RETR_OBJECT);
							m_Grid.SetItemText(nIndex,3,str);
							m_Grid.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

							m_Grid.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellCombo));
							CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 5);
							CStringArray tmpArr;
							tmpArr.Add("Нет");
							tmpArr.Add("Да");							
							pCell2->SetOptions(tmpArr);		
							pCell2->SetStyle(CBS_DROPDOWNLIST); 
							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].YESNOLOGALARM == 1)//inversno?
								pCell2->SetCurSel(0);
							else
								pCell2->SetCurSel(1);

							/*m_Grid.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellCheck));
							CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(nIndex, 5);
							pCell2->SetStrings("Да","Нет");		
							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].YESNOLOGALARM == 0)
								pCell2->SetCheck(FALSE);
							else
								pCell2->SetCheck(TRUE);*/

							/*m_Grid.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellCheck));
							pCell2 = (CGridCellCheck*) m_Grid.GetCell(nIndex, 6);
							pCell2->SetStrings("Да","Нет");		
							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].YESNOLOGPROTOKOL == 0)
								pCell2->SetCheck(FALSE);
							else
								pCell2->SetCheck(TRUE);*/
							m_Grid.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellCombo));
							pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 6);
							pCell2->SetOptions(tmpArr);		
							pCell2->SetStyle(CBS_DROPDOWNLIST); 
							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].YESNOLOGPROTOKOL == 1)
								pCell2->SetCurSel(0);
							else
								pCell2->SetCurSel(1);
						}

						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 12)							
						{
							m_Grid.SetRowHeight(nIndex,0);
							m_Grid.SetItemState(nIndex, 5, m_Grid.GetItemState(nIndex, 5) | GVIS_READONLY);
							m_Grid.SetItemState(nIndex, 6, m_Grid.GetItemState(nIndex, 6) | GVIS_READONLY);
						}	
					}
					m_Grid.SetItemData(nIndex, 1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL);										
					m_Grid.SetItemText(nIndex,7,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[i].strCOMMENT);
				}
				
				m_Grid.AutoSizeColumns();
				m_Grid.Refresh();
				break;
			}
		case 2://io
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.nFormat = DT_CENTER|DT_WORDBREAK;

				m_Grid.EnableSelection(TRUE);
				//m_Grid.SetListMode(TRUE);
				m_Grid.SetColumnCount(11);
				m_Grid.SetFixedColumnCount(1);
				m_Grid.SetRowCount(1);
				m_Grid.SetFixedRowCount(1);				
				m_Grid.SetItemText(0,0,"№");
				m_Grid.SetItemText(0,1,"Комментарий");
				m_Grid.SetItemText(0,2,"Тип инф.объектов");

				Item.row = 0;
				Item.col = 3;							
				Item.strText = "Начальный адрес\r\nв карте памяти";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 4;							
				Item.strText = "Кол-во инф.\r\nобъектов";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 5;							
				Item.strText = "Кол-во байт\r\nв объекте";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 6;
				Item.strText = "Нач.протокольный\r\nадрес (только IEC)";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 7;
				Item.strText = "Адрес ASDU \r\n(только IEC)";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 8;
				Item.strText = "\"Быстрый\"\r\nбуфер";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 9;
				Item.strText = "Размер \"Быстрого\"\r\nбуфера";
				m_Grid.SetItem(&Item);		

				Item.row = 0;
				Item.col = 10;
				Item.strText = "Номер\r\nпроцесса";
				m_Grid.SetItem(&Item);		
				
				m_Grid.SetColumnWidth(0,30);
				m_Grid.SetRowHeight(0,m_Grid.GetRowHeight(0)*2);
				 
				CString str;
				for(int i =0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetSize(); i++)
				{
					int nIndex = m_Grid.InsertRow(NULL);
					str.Format("%d",i+1);
					m_Grid.SetItemText(nIndex,0,str);

					m_Grid.SetItemText(nIndex,1,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].strCOMMENT);
					
					m_Grid.SetCellType(nIndex, 2, RUNTIME_CLASS(CGridCellCombo));
					CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex, 2);
					pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex, 2);
					pCell->SetOptions(arrMain_Set_ObjectTypes);		
					pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT);
					if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_SP_NA_1)
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[0]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_SP_TA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[1]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_SP_TB_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[2]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_DP_NA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[3]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_DP_TA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[4]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_DP_TB_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[5]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_NA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[6]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_TA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[7]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_TD_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[8]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_ND_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[9]);					
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_NB_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[10]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_TB_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[11]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_TE_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[12]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_NC_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[13]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_TC_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[14]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_ME_TF_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[15]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_BO_NA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[16]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_BO_TA_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[17]);
					else if (((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT == M_BO_TB_1)//po srezam
						m_Grid.SetItemText(nIndex,2, arrMain_Set_ObjectTypes[18]);			
					else
						m_Grid.SetItemText(nIndex, 2, str);
					m_Grid.SetItemData(nIndex, 2,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].TYPE_OBJECT);

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].START_ADRES_PMZ);
					m_Grid.SetItemText(nIndex,3,str);
					m_Grid.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].NUMBER_OBJECT);
					m_Grid.SetItemText(nIndex,4,str);
					m_Grid.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].NUM_DATE);
					m_Grid.SetItemText(nIndex,5,str);
					m_Grid.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellNumeric));

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].REAL_ADRES);
					m_Grid.SetItemText(nIndex,6,str);
					m_Grid.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellNumeric));

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].ADRES_ASDU);
					m_Grid.SetItemText(nIndex,7,str);
					m_Grid.SetCellType(nIndex,7,RUNTIME_CLASS(CGridCellNumeric));

					CStringArray arrOpts;
					arrOpts.Add("Нет");
					arrOpts.Add("Да");
					m_Grid.SetCellType(nIndex, 8, RUNTIME_CLASS(CGridCellCombo));
					CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 8);					
					pCell2->SetOptions(arrOpts);		
					pCell2->SetStyle(CBS_DROPDOWN); 					
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].YES_NO_FASTBUF)
						m_Grid.SetItemText(nIndex,8,"Да");
					else
						m_Grid.SetItemText(nIndex,8,"Нет");

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].SIZE_FAST_BUF);
					m_Grid.SetItemText(nIndex,9,str);
					m_Grid.SetCellType(nIndex,9,RUNTIME_CLASS(CGridCellNumeric));					

					m_Grid.SetCellType(nIndex, 10, RUNTIME_CLASS(CGridCellCombo));
					pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex, 10);					
					CStringArray arrMain_Set_Processes;
					arrMain_Set_Processes.Add("0");
					for(int proc = 0; proc < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize(); proc++)
					{
						if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 2)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 4)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 14)
							||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 8))
						{
							str.Format("%d",proc+1);
							arrMain_Set_Processes.Add(str);
						}
					}					
					pCell->SetOptions(arrMain_Set_Processes);		
					pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE	
					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[i].NUMBER_DIRECT);
					m_Grid.SetItemText(nIndex,10,str);
					/*m_Grid.SetCellType(nIndex,9,RUNTIME_CLASS(CGridCellNumeric));*/
				}				
				if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_nVersion < 11)
					m_Grid.SetColumnWidth(1,0);

				m_Grid.AutoSizeColumns();
				m_Grid.Refresh();
				break;
			}
		case 3://masks
			{
				m_Grid.SetColumnCount(8);
				m_Grid.SetFixedColumnCount(1);
				m_Grid.SetRowCount(1);
				m_Grid.SetFixedRowCount(1);				
				m_Grid.SetItemText(0,0,"№");
				m_Grid.SetItemText(0,1,"Адрес информационного объекта");
				m_Grid.SetItemText(0,2,"Маска для целых значений");
				m_Grid.SetItemText(0,3,"Маска для значений с плав. точкой");
				m_Grid.SetItemText(0,4,"Физический \"0\" в квантах");
				m_Grid.SetItemText(0,5,"Знаковое число");
				m_Grid.SetItemText(0,6,"Мертвая зона физического \"0\"");
				m_Grid.SetItemText(0,7,"Комментарий");
				m_Grid.SetColumnWidth(0,30);
				m_Grid.EnableSelection(TRUE);
				//m_Grid.SetListMode(TRUE);
				m_Grid.SetFixedColumnSelection(FALSE);

				CString str;
				for(int i =0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetSize(); i++)
				{
					int nIndex = m_Grid.InsertRow(NULL);
					str.Format("%d",i+1);
					m_Grid.SetItemText(nIndex,0,str);

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].ADR_MASKA);
					m_Grid.SetItemText(nIndex,1,str);
					m_Grid.SetCellType(nIndex,1,RUNTIME_CLASS(CGridCellNumeric));

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].MASKAINT);
					m_Grid.SetItemText(nIndex,2,str);
					m_Grid.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].MASKAFLOAT);
					m_Grid.SetItemText(nIndex,3,str);
					m_Grid.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));		

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].VALUE_0);
					m_Grid.SetItemText(nIndex,4,str);
					m_Grid.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));		

					CStringArray arrOpts;
					arrOpts.Add("Нет");
					arrOpts.Add("Да");
					m_Grid.SetCellType(nIndex, 5, RUNTIME_CLASS(CGridCellCombo));
					CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(nIndex, 5);					
					pCell2->SetOptions(arrOpts);		
					pCell2->SetStyle(CBS_DROPDOWN); 					
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].TYPE_VALUE)
						m_Grid.SetItemText(nIndex,5,"Да");
					else
						m_Grid.SetItemText(nIndex,5,"Нет");

					/*m_Grid.SetCellType(nIndex, 5, RUNTIME_CLASS(CGridCellCheck));
					CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(nIndex, 5);					
					pCell2->SetStrings("Да","Нет");
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].TYPE_VALUE)
						pCell2->SetCheck(TRUE);
					else
						pCell2->SetCheck(FALSE);		*/

					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].MASKA_VALUE_0);
					m_Grid.SetItemText(nIndex,6,str);
					m_Grid.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellNumeric));								
										
					m_Grid.SetItemText(nIndex,7,((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[i].strCOMMENT);
				}
				m_Grid.AutoSize();
				m_Grid.Refresh();
				break;
			}
		default:
			{
				m_Grid.SetRowCount(0);
				m_Grid.SetColumnCount(0);
			}
	}
}
BOOL CKPLConfigDlg::SaveTab(int tab)
{
	CGridCellBase *pCell1;
	for(int i = 0; i < m_Grid.GetRowCount(); i++)
	{
		for(int j = 0; j < m_Grid.GetColumnCount(); j++)
		{
			pCell1 = m_Grid.GetCell(i,j);	
			if(pCell1->IsEditing())
			{
				pCell1->EndEdit();
			}		
		}
	}	
	
	switch(tab)
	{
		case 0:
			{				
				CString str;								
				str = m_Grid.GetItemText(1,1);
				if((atoi(str)<0)||(atoi(str)>1000))
				{
					AfxMessageBox(m_Grid.GetItemText(1,0)+"в пределах 0..1000!");
					return FALSE;
				}
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.REAL_SIZE_DIRECT_BUFER = atoi(str);
				
				str = m_Grid.GetItemText(2,1);
				if((atoi(str)<0)||(atoi(str)>2000))
				{
					AfxMessageBox(m_Grid.GetItemText(2,0)+"в пределах 0..2000!");
					return FALSE;
				}
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.REAL_NUM_GENFAST_OBJECT = atoi(str);	
				
				str = m_Grid.GetItemText(3,1);
				if((atoi(str)<0)||(atoi(str)>10000))
				{
					AfxMessageBox(m_Grid.GetItemText(3,0)+"в пределах 0..10000!");
					return FALSE;
				}
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT = atoi(str);				

				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_strPSNAME = m_Grid.GetItemText(4,1);				
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.KPLType = m_Grid.GetItemText(5,1);				

				if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 19)
				{
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.MY_IP = m_Grid.GetItemText(6,1);				
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.MY_IP_MASK = m_Grid.GetItemText(7,1);			
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.MY_IP_GW = m_Grid.GetItemText(8,1);			
				}				
				break;
			}
		case 1:
			{	
				CProcessInfoArray ProcessInfoArray;
				CArray<int,int> retr;
				CString str;
				int nMinStartAddrMap=100000;
				int nTotalAmount = 0;
				int nMasterAmount = 0;
				int tmpNUM_RETR_OBJECT=0;
				for(int i = 1; i < m_Grid.GetRowCount(); i++)
				{							
					ProcessInfo pi;
					str = m_Grid.GetItemText(i,1);
					if(str == arrMain_Set_ProcessesTypes[0])
						pi.TYPE_PROTOKOL=255;
					else if (str == arrMain_Set_ProcessesTypes[1])
						pi.TYPE_PROTOKOL=1;
					else if (str == arrMain_Set_ProcessesTypes[2])
						pi.TYPE_PROTOKOL=2;
					else if (str == arrMain_Set_ProcessesTypes[3])
						pi.TYPE_PROTOKOL=3;
					else if (str == arrMain_Set_ProcessesTypes[4])
						pi.TYPE_PROTOKOL=4;
					else if (str == arrMain_Set_ProcessesTypes[5])
						pi.TYPE_PROTOKOL=5;
					else if (str == arrMain_Set_ProcessesTypes[6])
						pi.TYPE_PROTOKOL=7;
					else if (str == arrMain_Set_ProcessesTypes[7])
						pi.TYPE_PROTOKOL=8;
					else if (str == arrMain_Set_ProcessesTypes[8])
						pi.TYPE_PROTOKOL=14;
					else if (str == arrMain_Set_ProcessesTypes[9])
						pi.TYPE_PROTOKOL=9;
					/*else if (str == arrMain_Set_ProcessesTypes[9])
						pi.TYPE_PROTOKOL=12;*/
					else if (str == arrMain_Set_ProcessesTypes[10])
						pi.TYPE_PROTOKOL=10;
					else if (str == arrMain_Set_ProcessesTypes[11])
						pi.TYPE_PROTOKOL=13;
					else if (str == arrMain_Set_ProcessesTypes[12])
						pi.TYPE_PROTOKOL=15;
					else if (str == arrMain_Set_ProcessesTypes[13])
						pi.TYPE_PROTOKOL=16;
					else if (str == arrMain_Set_ProcessesTypes[14])
						pi.TYPE_PROTOKOL=18;
					else if (str == arrMain_Set_ProcessesTypes[15])
						pi.TYPE_PROTOKOL=17;
					else if (str == arrMain_Set_ProcessesTypes[16])
						pi.TYPE_PROTOKOL=19;
					else if (str == arrMain_Set_ProcessesTypes[17])
						pi.TYPE_PROTOKOL=21;
					else
						pi.TYPE_PROTOKOL=m_Grid.GetItemData(i, 1);

					str = m_Grid.GetItemText(i,2);
					pi.START_ADDRESS_MAP = atoi(str);

					if(nMinStartAddrMap > pi.START_ADDRESS_MAP)
						nMinStartAddrMap = pi.START_ADDRESS_MAP;

					str = m_Grid.GetItemText(i,3);
					pi.AMOUNT_SIGNIFICATE = atoi(str);

					if(pi.TYPE_PROTOKOL==9)
						tmpNUM_RETR_OBJECT = pi.AMOUNT_SIGNIFICATE;

					if((pi.TYPE_PROTOKOL==2)
						||(pi.TYPE_PROTOKOL==4)						
						||(pi.TYPE_PROTOKOL==8)
						||(pi.TYPE_PROTOKOL==18))//SLAVE sumiruem
					{
						nTotalAmount+=pi.AMOUNT_SIGNIFICATE;						
					}
					if((pi.TYPE_PROTOKOL==1)
						||(pi.TYPE_PROTOKOL==3)
						||(pi.TYPE_PROTOKOL==5)
						||(pi.TYPE_PROTOKOL==7)
						||(pi.TYPE_PROTOKOL==15)
						||(pi.TYPE_PROTOKOL==16)
						||(pi.TYPE_PROTOKOL==17)
						||(pi.TYPE_PROTOKOL==19)
						||(pi.TYPE_PROTOKOL==21)
						||(pi.TYPE_PROTOKOL==13))//MASTER berem MAX
					{
						if(nMasterAmount <= pi.AMOUNT_SIGNIFICATE)
							nMasterAmount = pi.AMOUNT_SIGNIFICATE;
					}
					if((pi.TYPE_PROTOKOL!=255)&&(pi.TYPE_PROTOKOL!=12)&&(pi.TYPE_PROTOKOL!=10))											
					{
						CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(i,5);						
						if(pCell2->GetCurSel()==1)
							pi.YESNOLOGALARM=0;
						else
							pi.YESNOLOGALARM=1;		
						pCell2 = (CGridCellCombo*) m_Grid.GetCell(i,6);						
						if(pCell2->GetCurSel()==1)
							pi.YESNOLOGPROTOKOL=0;
						else
							pi.YESNOLOGPROTOKOL=1;		
					}
					pi.strCOMMENT = m_Grid.GetItemText(i,7);
					ProcessInfoArray.Add(pi);
															
					if((pi.TYPE_PROTOKOL == 1)
						||(pi.TYPE_PROTOKOL==3)
						||(pi.TYPE_PROTOKOL==5)
						||(pi.TYPE_PROTOKOL==7)
						||(pi.TYPE_PROTOKOL==15)
						||(pi.TYPE_PROTOKOL==16)
						||(pi.TYPE_PROTOKOL==17)
						||(pi.TYPE_PROTOKOL==21)
						||(pi.TYPE_PROTOKOL==19)
						||(pi.TYPE_PROTOKOL==13))//master
					{
						CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(i, 4);						
						if(pCell2->GetCurSel()==1)
							retr.Add(5);
						else
							retr.Add(0);					
					}
					else
						retr.Add(0);
				}
				BOOL bTuPresent = FALSE;
				BOOL bRetrPresent = FALSE;
				BOOL bGPSPresent = FALSE;
				for(int i = 0; i < ProcessInfoArray.GetSize(); i++)
				{
					if(ProcessInfoArray[i].TYPE_PROTOKOL == 9)					
						bRetrPresent = TRUE;											
					if(ProcessInfoArray[i].TYPE_PROTOKOL == 12)
						bTuPresent = TRUE;
					if(ProcessInfoArray[i].TYPE_PROTOKOL == 13)
						bGPSPresent = TRUE;				
				}
				if((!bRetrPresent)||(!bTuPresent)||(!bGPSPresent))
				{
					AfxMessageBox("Обязательно должны присутствовать процессы телеуправления,ретрансляции и синхронизации времени!");
					return FALSE;
				}				
				nTotalAmount = nTotalAmount + nMinStartAddrMap + nMasterAmount;

				if(tmpNUM_RETR_OBJECT > nTotalAmount)
					nTotalAmount += (tmpNUM_RETR_OBJECT - nTotalAmount);
		
					if(nTotalAmount >= 10000)
					{
						AfxMessageBox("Суммарное кол-во инф. объектов процессов превышает 10000!");
						return FALSE;
					}
				//}
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.RemoveAll();
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Copy(ProcessInfoArray);
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.Copy(retr);	
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.NUM_RETR_OBJECT = tmpNUM_RETR_OBJECT;
				break;
			}
		case 2: //io
			{
				CIniObjectArray IniObjectArray;
				CString str;	
				int nTotalAmount = 0;
				int nMaxStartAddr=0;
				int nMaxAmount=0;
				for(int i = 1; i < m_Grid.GetRowCount(); i++)
				{	
					IniObject io;

					str = m_Grid.GetItemText(i,5);
					io.NUM_DATE = atoi(str);
					
					if((io.NUM_DATE<=0)||(io.NUM_DATE>12))
					{
						AfxMessageBox("Кол-во байт объекта: 1..12!");
						return FALSE;
					}
										
					io.strCOMMENT = m_Grid.GetItemText(i,1);

					str = m_Grid.GetItemText(i,2);
					for(int l = 0; l < arrMain_Set_ObjectTypes.GetSize();l++)					
					{
						if(str == arrMain_Set_ObjectTypes[l])
						{
							io.TYPE_OBJECT = m_Grid.GetItemData(i,2);
							break;
						}
					}
					if(io.TYPE_OBJECT==0)
						io.TYPE_OBJECT = atoi(str);

					if((io.TYPE_OBJECT == M_SP_NA_1)||(io.TYPE_OBJECT == M_SP_TA_1)||(io.TYPE_OBJECT == M_SP_TB_1))
					{
							io.GENTYPE_OBJECT=M_SP_NA_1;
							io.GEN_NUMBYTE = 1;
					}
					else if((io.TYPE_OBJECT == M_DP_NA_1)||(io.TYPE_OBJECT == M_DP_TA_1)||(io.TYPE_OBJECT == M_DP_TB_1))
					{
							io.GENTYPE_OBJECT=M_DP_NA_1;
							io.GEN_NUMBYTE=1;
					}
					else if((io.TYPE_OBJECT == M_ME_NA_1)||(io.TYPE_OBJECT == M_ME_TA_1)||(io.TYPE_OBJECT == M_ME_TD_1))
					{
							io.GENTYPE_OBJECT=M_ME_NA_1;
							io.GEN_NUMBYTE=3;
					}
					else if((io.TYPE_OBJECT == M_ME_NB_1)||(io.TYPE_OBJECT == M_ME_TB_1)||(io.TYPE_OBJECT == M_ME_TE_1))
					{
							io.GENTYPE_OBJECT=M_ME_NB_1;
							io.GEN_NUMBYTE=3;
					}
					else if((io.TYPE_OBJECT == M_ME_NC_1)||(io.TYPE_OBJECT == M_ME_TC_1)||(io.TYPE_OBJECT == M_ME_TF_1))
					{
							io.GENTYPE_OBJECT=M_ME_NC_1;
							io.GEN_NUMBYTE=5;
					}
					else if((io.TYPE_OBJECT == M_ME_ND_1))
					{
							io.GENTYPE_OBJECT=M_ME_ND_1;
							io.GEN_NUMBYTE=2;
					}
					else if((io.TYPE_OBJECT == M_BO_NA_1)||(io.TYPE_OBJECT == M_BO_TA_1)||(io.TYPE_OBJECT == M_BO_TB_1))
					{
							io.GENTYPE_OBJECT=M_BO_NA_1;
							io.GEN_NUMBYTE=5;
					}
					else
					{
						io.GENTYPE_OBJECT = io.TYPE_OBJECT;
						io.GEN_NUMBYTE = io.NUM_DATE;
					}

					str = m_Grid.GetItemText(i,3);
					io.START_ADRES_PMZ = atoi(str);

					if(io.START_ADRES_PMZ >= nMaxStartAddr)
					{
						nMaxStartAddr = io.START_ADRES_PMZ;					
						nMaxAmount = io.NUMBER_OBJECT;
					}

					str = m_Grid.GetItemText(i,4);
					io.NUMBER_OBJECT = atoi(str);					
					nTotalAmount += io.NUMBER_OBJECT;

					str = m_Grid.GetItemText(i,6);
					io.REAL_ADRES = atoi(str);

					str = m_Grid.GetItemText(i,7);
					io.ADRES_ASDU = atoi(str);

					str = m_Grid.GetItemText(i,9);
					io.SIZE_FAST_BUF = atoi(str);

					str = m_Grid.GetItemText(i,10);
					io.NUMBER_DIRECT = atoi(str);
					
					str = m_Grid.GetItemText(i,8);									
					if(str == "Да")
						io.YES_NO_FASTBUF=1;
					else
					{
						io.YES_NO_FASTBUF=0;
						io.SIZE_FAST_BUF = 0;
					}

					IniObjectArray.Add(io);
				}
				/*if(nTotalAmount > ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
				{
					str.Format("%d",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT);
					AfxMessageBox("Суммарное кол-во инф. объектов в карте памяти превышает\r\nобщее количество информационных объектов в карте памяти:"+str+" ! \r\n(См.Общие настройки: Oбщее количество информационных объектов в карте памяти)");
					return FALSE;
				}*/
				/*if(nTotalAmount > ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
				{
					
					if(nTotalAmount < 10000)
						((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT = nTotalAmount;
					else*/
					if(nTotalAmount >= 10000)
					{
						AfxMessageBox("Суммарное кол-во инф. объектов процессов превышает 10000!");
						return FALSE;
					}
				//}

				if((nMaxStartAddr + nMaxAmount) > ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
				{
					str.Format("0..%d !",((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT-1);
					AfxMessageBox("Карта памяти выходит за общее адресное поле:"+str);
					//return FALSE;
				}

				for(int i = 0; i < IniObjectArray.GetSize(); i++)
				{
					for(int j = 0; j < IniObjectArray.GetSize(); j++)
					{
						if((IsIntersect(IniObjectArray[i].START_ADRES_PMZ,
										IniObjectArray[i].START_ADRES_PMZ+IniObjectArray[i].NUMBER_OBJECT-1,
										IniObjectArray[j].START_ADRES_PMZ,
										IniObjectArray[j].START_ADRES_PMZ+IniObjectArray[j].NUMBER_OBJECT-1))
										&&(i!=j))

						//if(((IniObjectArray[i].START_ADRES_PMZ+IniObjectArray[i].NUMBER_OBJECT-1) >= IniObjectArray[j].START_ADRES_PMZ)
						//	&&(i<j))
						{
							str.Format("%d на %d !",j+1,i+1);
							AfxMessageBox("Наложение наборов инф.объектов:"+str);
							return FALSE;
						}
					}					
				}

				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.RemoveAll();
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.Copy(IniObjectArray);
				break;
			}
		case 3://mask
			{	
				CIniMaskArray IniMaskArray;
				CString str;				
				for(int i = 1; i < m_Grid.GetRowCount(); i++)
				{							
					IniMask im;
					str = m_Grid.GetItemText(i,1);
					im.ADR_MASKA = atoi(str);
					if(im.ADR_MASKA >= ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
					{
						AfxMessageBox("Адрес инф.объекта выходит за пределы карты памяти! \r\n(См.Общие настройки: Oбщее количество информационных объектов в карте памяти)");
						//return FALSE;
					}
					str = m_Grid.GetItemText(i,2);
					im.MASKAINT = atoi(str);
					str = m_Grid.GetItemText(i,3);
					im.MASKAFLOAT = atoi(str);		

					str = m_Grid.GetItemText(i,4);
					im.VALUE_0 = atoi(str);						
					
					str = m_Grid.GetItemText(i,5);									
					if(str == "Да")
						im.TYPE_VALUE=1;
					else
						im.TYPE_VALUE=0;						
					
					//CGridCellCheck *pCell2 = (CGridCellCheck*) m_Grid.GetCell(i, 5);										
					//im.TYPE_VALUE = pCell2->GetCheck();
					
					str = m_Grid.GetItemText(i,6);
					im.MASKA_VALUE_0 = atoi(str);											

					str = m_Grid.GetItemText(i,7);
					im.strCOMMENT = str;

					IniMaskArray.Add(im);
				}				
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.RemoveAll();
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.Copy(IniMaskArray);
				break;
			}
	}
	return TRUE;
}
afx_msg void CKPLConfigDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;
	switch(m_MainTab.GetCurSel())
	{
		case 1 :
			{						
				CMenu MenuRButton;
				MenuRButton.CreatePopupMenu();				
				MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить процесс");	
				MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить процесс");
				if(pItem->iRow >= 1)
					MenuRButton.AppendMenu(MF_STRING, IDM_DETAIL, "Настройки процесса...");

				MenuRButton.AppendMenu(MF_SEPARATOR);
				MenuRButton.AppendMenu(MF_STRING, IDM_COPY, "Скопировать таблицу в буфер обмена");

				POINT point;
				GetCursorPos(&point);
				MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
				MenuRButton.DestroyMenu();
				break;
			}
		case 2 :
			{						
				CMenu MenuRButton;
				MenuRButton.CreatePopupMenu();				
				MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить набор инф.объектов");	
				MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон наборов инф.объектов");	
				MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить набор инф.объектов");		

				MenuRButton.AppendMenu(MF_SEPARATOR);
				MenuRButton.AppendMenu(MF_STRING, IDM_COPY, "Скопировать таблицу в буфер обмена");

				POINT point;
				GetCursorPos(&point);
				MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
				MenuRButton.DestroyMenu();
				break;
			}
		case 3 :
			{						
				CMenu MenuRButton;
				MenuRButton.CreatePopupMenu();				
				MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить маску");	
				MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон масок");	
				MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить маску");				
				
				MenuRButton.AppendMenu(MF_SEPARATOR);
				MenuRButton.AppendMenu(MF_STRING, IDM_COPY, "Скопировать таблицу в буфер обмена");

				POINT point;
				GetCursorPos(&point);
				MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
				MenuRButton.DestroyMenu();
				break;
			}
	}	
}
afx_msg void CKPLConfigDlg::OnAddDiapason()
{
	switch(m_MainTab.GetCurSel())
	{	
		case 2 : //io
			{					
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetSize()==((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
					{
						AfxMessageBox("Количество должно быть не более \r\nобщего количества информационных объектов в карте памяти!");						
						break;
					}
					else
					{		
						CCellID cell = m_Grid.GetFocusCell();
						if((cell.row > 0)&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetCount() > 1))
						{														
							CString str;
							m_AddIODiapDlg.arrMain_Set_Processes.RemoveAll();
							m_AddIODiapDlg.arrMain_Set_Processes.Add("0");
							for(int proc = 0; proc < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize(); proc++)
							{
								if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 2)
									||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 4)
									||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 8))
								{
									str.Format("%d",proc+1);
									m_AddIODiapDlg.arrMain_Set_Processes.Add(str);
								}
							}
							m_AddIODiapDlg.arrMain_Set_ObjectTypes.Copy(arrMain_Set_ObjectTypes);
							m_AddIODiapDlg.arrObjectTypesInt.Copy(arrObjectTypesInt);

							if(m_AddIODiapDlg.DoModal()==IDOK)
							{								
								((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.InsertAt(cell.row++,&m_AddIODiapDlg.m_arrIniObject);
								ChangeTab(m_MainTab.GetCurSel());
							}
							break;
						}
						if((cell.row == ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetCount())
							||(cell.row == -1))
						{												
							CString str;
							m_AddIODiapDlg.arrMain_Set_Processes.RemoveAll();
							m_AddIODiapDlg.arrMain_Set_Processes.Add("0");
							for(int proc = 0; proc < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize(); proc++)
							{
								if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 2)
									||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 4)
									||(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[proc].TYPE_PROTOKOL == 8))
								{
									str.Format("%d",proc+1);
									m_AddIODiapDlg.arrMain_Set_Processes.Add(str);
								}
							}
							m_AddIODiapDlg.arrMain_Set_ObjectTypes.Copy(arrMain_Set_ObjectTypes);
							m_AddIODiapDlg.arrObjectTypesInt.Copy(arrObjectTypesInt);

							if(m_AddIODiapDlg.DoModal()==IDOK)
							{																				
								((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.Append(m_AddIODiapDlg.m_arrIniObject);
								ChangeTab(m_MainTab.GetCurSel());
							}
							break;
						}						
					}								
				}
				break;
			}
		case 3 : //mask
			{					
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetSize()==((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
					{
						AfxMessageBox("Количество масок должно быть не более \r\nобщего количества информационных объектов в карте памяти!");
						break;
					}
					else
					{
						CCellID cell = m_Grid.GetFocusCell();
						if((cell.row > 0)&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetCount() > 1))
						{		
							if(m_AddDiapMaskDlg.DoModal()==IDOK)
							{
								IniMask pi;
								for(int a = m_AddDiapMaskDlg.m_nStartIOA; a <=m_AddDiapMaskDlg.m_nEndIOA; a++)
								{
									pi = m_AddDiapMaskDlg.m_IniMask;
									pi.ADR_MASKA = a;
									((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.InsertAt(cell.row++,pi);
								}																
								ChangeTab(m_MainTab.GetCurSel());
							}
							break;
						}
						if((cell.row == ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetCount())
							||(cell.row == -1))
						{					
							if(m_AddDiapMaskDlg.DoModal()==IDOK)
							{
								CIniMaskArray pi;
								for(int a = m_AddDiapMaskDlg.m_nStartIOA; a <=m_AddDiapMaskDlg.m_nEndIOA; a++)
								{
									pi.Add(m_AddDiapMaskDlg.m_IniMask);
									pi[pi.GetSize()-1].ADR_MASKA = a;
								}															
								((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.Append(pi);											
								ChangeTab(m_MainTab.GetCurSel());
							}
							break;
						}															
					}					
				}
				break;
			}
	}
}
afx_msg void CKPLConfigDlg::OnAdd()
{
	switch(m_MainTab.GetCurSel())
	{
		case 1 :
			{					
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetSize()==20)
					{
						AfxMessageBox("Количество процессов не более 20!");						
						break;
					}
					else
					{
						CCellID cell = m_Grid.GetFocusCell();
						if(((cell.row == 1)||(cell.row == 3))&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetCount() == 3))
						{
							ProcessInfo pi;
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Add(pi);
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.Add(0);						
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
						if(((cell.row == 1)||(cell.row == 3))&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetCount() > 3))
						{							
							ProcessInfo pi;							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.InsertAt(3,pi);
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.InsertAt(3,0);
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.RenumerateChannels(3,FALSE);
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
						if((cell.row > 3)&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetCount() == 4))
						{							
							ProcessInfo pi;
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Add(pi);
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.Add(0);						
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
						if((cell.row > 3)&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.GetCount() > 4))
						{							
							ProcessInfo pi;							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.InsertAt(cell.row,pi);
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.InsertAt(cell.row,0);							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.RenumerateChannels(cell.row,FALSE);
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
						if(cell.row == -1)
						{
							ProcessInfo pi;
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.Add(pi);
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.Add(0);						
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
					}					
				}
				break;
			}
		case 2 :
			{					
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetSize()==((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
					{
						AfxMessageBox("Количество должно быть не более \r\nобщего количества информационных объектов в карте памяти!");						
						break;
					}
					else
					{		
						CCellID cell = m_Grid.GetFocusCell();
						if((cell.row > 0)&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetCount() > 1))
						{							
							IniObject pi;
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.InsertAt(cell.row,pi);
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
						if((cell.row == ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetCount())
							||(cell.row == -1))
						{					
							IniObject pi;							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.Add(pi);											
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}						
					}					
				}
				break;
			}
		case 3 :
			{					
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetSize()==((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.AMOUNT_OBJECT)
					{
						AfxMessageBox("Количество масок должно быть не более \r\nобщего количества информационных объектов в карте памяти!");						
						break;
					}
					else
					{
						CCellID cell = m_Grid.GetFocusCell();
						if((cell.row > 0)&&(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetCount() > 1))
						{							
							IniMask pi;
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.InsertAt(cell.row,pi);
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}
						if((cell.row == ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetCount())
							||(cell.row == -1))
						{					
							IniMask pi;							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.Add(pi);											
							ChangeTab(m_MainTab.GetCurSel());
							break;
						}															
					}					
				}
				break;
			}
	}
}
afx_msg void CKPLConfigDlg::OnDel()
{
	if(AfxMessageBox("Удалить?",MB_YESNO|MB_ICONQUESTION)!=IDYES)
		return;
			
	CCellID pCell = m_Grid.GetFocusCell();
	switch(m_MainTab.GetCurSel())
	{
		case 1 :
			{
				if((pCell.row > 0)&&(pCell.col > 0))
				{
					SaveTab(m_MainTab.GetCurSel());
					//iec101m
					BOOL bRemoved=FALSE;
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusTCPMArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusTCPMArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusTCPMArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}	
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray[i].m_nProcNum==pCell.row)
						{							
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.RemoveAt(i);							
							bRemoved = TRUE;
							break;
						}					
					}
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray[i].m_nProcNum==pCell.row)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.RemoveAt(i);
							bRemoved = TRUE;
							break;
						}
					}					
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray[i].m_nProcNum==pCell.row)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.RemoveAt(i);
							bRemoved = TRUE;
							break;
						}
					}					
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray[i].m_nProcNum==pCell.row)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.RemoveAt(i);
							bRemoved = TRUE;
							break;
						}
					}					
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray[i].m_nProcNum==pCell.row)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.RemoveAt(i);
							bRemoved = TRUE;
							break;
						}
					}					
					for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.GetSize(); i++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray[i].m_nProcNum==pCell.row)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.RemoveAt(i);
							bRemoved = TRUE;
							break;
						}
					}
					if(bRemoved)					
						((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.RenumerateChannels(pCell.row);

					if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].TYPE_PROTOKOL == 255))
						((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.RenumerateChannels(pCell.row);

					if((((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].TYPE_PROTOKOL == 9)||
						(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].TYPE_PROTOKOL == 13)||
						(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].TYPE_PROTOKOL == 12))
					{
						AfxMessageBox("Обязательно должны присутствовать процессы ретрансляции и синхронизации времени!");
						break;
					}
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray.RemoveAt(pCell.row-1);
					((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.m_RECIVE_DIRECT.RemoveAt(pCell.row-1);
					ChangeTab(m_MainTab.GetCurSel());
				}
				break;
			}
		case 2 :
			{
				if((pCell.row > 0)&&(pCell.col > 0))
				{
					SaveTab(m_MainTab.GetCurSel());

					for(int a = 1; a < m_Grid.GetRowCount();a++)
					{
						for(int b = 1; b < m_Grid.GetColumnCount();b++)
						{
							if(m_Grid.GetItemState(a,b) & GVIS_SELECTED)						
							{
								((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[a-1].ADRES_ASDU = -123456;
								break;
							}
						}
					}																
					for(int a = 0; a < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.GetSize();a++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray[a].ADRES_ASDU == -123456)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.RemoveAt(a);
							a--;
						}
					}
					ChangeTab(m_MainTab.GetCurSel());
					//((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniObjectArray.RemoveAt(pCell.row-1);					
					//ChangeTab(m_MainTab.GetCurSel());
				}
				break;
			}
		case 3 :
			{
				if((pCell.row > 0)&&(pCell.col > 0))
				{
					SaveTab(m_MainTab.GetCurSel());
					
					for(int a = 1; a < m_Grid.GetRowCount();a++)
					{
						for(int b = 1; b < m_Grid.GetColumnCount();b++)
						{
							if(m_Grid.GetItemState(a,b) & GVIS_SELECTED)						
							{
								((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[a-1].ADR_MASKA = -123456;
								break;
							}
						}
					}																
					for(int a = 0; a < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.GetSize();a++)
					{
						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray[a].ADR_MASKA == -123456)
						{
							((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_IniMaskArray.RemoveAt(a);
							a--;
						}
					}
					ChangeTab(m_MainTab.GetCurSel());
				}
				break;
			}
	}
	//
}
afx_msg void CKPLConfigDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	
	switch(m_nOldTab)//(m_MainTab.GetCurSel())
	{
		case 2 :
			{	
				if((pItem->iColumn == 2)&&(pItem->iRow > 0))
				{
					CString str;
					str = m_Grid.GetItemText(pItem->iRow,pItem->iColumn );
					if(str == arrMain_Set_ObjectTypes[0])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_SP_NA_1);
						m_Grid.SetItemText(pItem->iRow,5,"1");
					}
					else if(str == arrMain_Set_ObjectTypes[1])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_SP_TA_1);
						m_Grid.SetItemText(pItem->iRow,5,"4");
					}
					else if(str == arrMain_Set_ObjectTypes[2])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_SP_TB_1);
						m_Grid.SetItemText(pItem->iRow,5,"8");
					}
					else if(str == arrMain_Set_ObjectTypes[3])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_DP_NA_1);
						m_Grid.SetItemText(pItem->iRow,5,"1");
					}
					else if(str == arrMain_Set_ObjectTypes[4])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_DP_TA_1);
						m_Grid.SetItemText(pItem->iRow,5,"4");
					}
					else if(str == arrMain_Set_ObjectTypes[5])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_DP_TB_1);
						m_Grid.SetItemText(pItem->iRow,5,"8");
					}
					else if(str == arrMain_Set_ObjectTypes[6])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_NA_1);
						m_Grid.SetItemText(pItem->iRow,5,"3");
					}
					else if(str == arrMain_Set_ObjectTypes[7])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_TA_1);
						m_Grid.SetItemText(pItem->iRow,5,"6");
					}
					else if(str == arrMain_Set_ObjectTypes[8])
					{
						m_Grid.SetItemText(pItem->iRow,5,"10");
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_TD_1);
					}
					else if(str == arrMain_Set_ObjectTypes[9])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_ND_1);
						m_Grid.SetItemText(pItem->iRow,5,"2");
					}
					else if(str == arrMain_Set_ObjectTypes[10])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_NB_1);
						m_Grid.SetItemText(pItem->iRow,5,"3");
					}
					else if(str == arrMain_Set_ObjectTypes[11])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_TB_1);
						m_Grid.SetItemText(pItem->iRow,5,"6");
					}
					else if(str == arrMain_Set_ObjectTypes[12])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_TE_1);
						m_Grid.SetItemText(pItem->iRow,5,"10");
					}
					else if(str == arrMain_Set_ObjectTypes[13])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_NC_1);
						m_Grid.SetItemText(pItem->iRow,5,"5");
					}
					else if(str == arrMain_Set_ObjectTypes[14])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_TC_1);
						m_Grid.SetItemText(pItem->iRow,5,"8");
					}
					else if(str == arrMain_Set_ObjectTypes[15])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_ME_TF_1);
						m_Grid.SetItemText(pItem->iRow,5,"12");
					}
					else if(str == arrMain_Set_ObjectTypes[16])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_BO_NA_1);
						m_Grid.SetItemText(pItem->iRow,5,"5");
					}
					else if(str == arrMain_Set_ObjectTypes[17])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_BO_TA_1);
						m_Grid.SetItemText(pItem->iRow,5,"8");
					}
					else if(str == arrMain_Set_ObjectTypes[18])
					{
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,M_BO_TB_1);
						m_Grid.SetItemText(pItem->iRow,5,"12");
					}
					else
						m_Grid.SetItemData(pItem->iRow,pItem->iColumn,atoi(str));												
				}
				break;
			}
		case 1 :
			{	
				if((pItem->iColumn == 3)&&(pItem->iRow > 2))
				{
					CString str;
					str = m_Grid.GetItemText(pItem->iRow,pItem->iColumn );

					if((m_Grid.GetItemData(pItem->iRow,1)==1)
						||(m_Grid.GetItemData(pItem->iRow,1)==3)
						||(m_Grid.GetItemData(pItem->iRow,1)==5)
						||(m_Grid.GetItemData(pItem->iRow,1)==7)
						||(m_Grid.GetItemData(pItem->iRow,1)==15)
						||(m_Grid.GetItemData(pItem->iRow,1)==16)
						||(m_Grid.GetItemData(pItem->iRow,1)==17)
						||(m_Grid.GetItemData(pItem->iRow,1)==19)
						||(m_Grid.GetItemData(pItem->iRow,1)==21)
						||(m_Grid.GetItemData(pItem->iRow,1)==13))
					{
						for(int i = 1; i < m_Grid.GetRowCount(); i++)
						{
							if(((m_Grid.GetItemData(i,1)==1)
								||(m_Grid.GetItemData(i,1)==3)
								||(m_Grid.GetItemData(i,1)==5)
								||(m_Grid.GetItemData(i,1)==7)
								||(m_Grid.GetItemData(i,1)==15)
								||(m_Grid.GetItemData(i,1)==16)
								||(m_Grid.GetItemData(i,1)==17)
								||(m_Grid.GetItemData(i,1)==19)
								||(m_Grid.GetItemData(i,1)==21)
								||(m_Grid.GetItemData(i,1)==13))
								&&(pItem->iRow != i))
							{								
								m_Grid.SetItemText(i,pItem->iColumn ,str);
								m_Grid.Refresh();
							}
						}
					}
				}
				if((pItem->iColumn == 1)&&(pItem->iRow > 3))
				{
					CString str;
					str = m_Grid.GetItemText(pItem->iRow,pItem->iColumn );
					
					int nChangedData = 255;

					if(str == arrMain_Set_ProcessesTypes[0])
						nChangedData = 255;
					else if (str == arrMain_Set_ProcessesTypes[1])
						nChangedData = 1;
					else if (str == arrMain_Set_ProcessesTypes[2])
						nChangedData = 2;
					else if (str == arrMain_Set_ProcessesTypes[3])
						nChangedData = 3;
					else if (str == arrMain_Set_ProcessesTypes[4])
						nChangedData = 4;
					else if (str == arrMain_Set_ProcessesTypes[5])
						nChangedData = 5;
					else if (str == arrMain_Set_ProcessesTypes[6])
						nChangedData = 7;
					else if (str == arrMain_Set_ProcessesTypes[7])
						nChangedData = 8;
					else if (str == arrMain_Set_ProcessesTypes[8])
						nChangedData = 14;
					else if (str == arrMain_Set_ProcessesTypes[9])
						nChangedData = 9;
					/*else if (str == arrMain_Set_ProcessesTypes[9])
						nChangedData = 12;*/
					else if (str == arrMain_Set_ProcessesTypes[10])
						nChangedData = 10;
					else if (str == arrMain_Set_ProcessesTypes[11])
						nChangedData = 13;
					else if (str == arrMain_Set_ProcessesTypes[12])
						nChangedData = 15;
					else if (str == arrMain_Set_ProcessesTypes[13])
						nChangedData = 16;
					else if (str == arrMain_Set_ProcessesTypes[14])
						nChangedData = 18;
					else if (str == arrMain_Set_ProcessesTypes[15])
						nChangedData = 17;
					else if (str == arrMain_Set_ProcessesTypes[16])
						nChangedData = 19;
					else if (str == arrMain_Set_ProcessesTypes[17])
						nChangedData = 21;

					if(nChangedData == 9)
					{
						for(int i = 1; i < m_Grid.GetRowCount(); i++)
						{
							if((m_Grid.GetItemData(i,1)==9)&&(i != pItem->iRow))
							{
								AfxMessageBox("Недопустимо две задачи ретрансляции!");
								m_Grid.SetItemText(pItem->iRow,pItem->iColumn ,arrMain_Set_ProcessesTypes[0]);
								m_Grid.SetItemData(pItem->iRow,pItem->iColumn,255);
							}
						}
					}
					if(nChangedData == 10)
					{
						for(int i = 1; i < m_Grid.GetRowCount(); i++)
						{
							if((m_Grid.GetItemData(i,1)==10)&&(i != pItem->iRow))
							{
								AfxMessageBox("Недопустимо две задачи монитора!");
								m_Grid.SetItemText(pItem->iRow,pItem->iColumn ,arrMain_Set_ProcessesTypes[0]);
								m_Grid.SetItemData(pItem->iRow,pItem->iColumn,255);
							}
						}
					}
					if(nChangedData == 12)
					{
						for(int i = 1; i < m_Grid.GetRowCount(); i++)
						{
							if((m_Grid.GetItemData(i,1)==12)&&(i != pItem->iRow))
							{
								AfxMessageBox("Недопустимо две задачи телеуправления!");
								m_Grid.SetItemText(pItem->iRow,pItem->iColumn ,arrMain_Set_ProcessesTypes[0]);
								m_Grid.SetItemData(pItem->iRow,pItem->iColumn,255);
							}
						}
					}
					if(nChangedData == 13)
					{
						for(int i = 1; i < m_Grid.GetRowCount(); i++)
						{
							if((m_Grid.GetItemData(i,1)==13)&&(i != pItem->iRow))
							{
								AfxMessageBox("Недопустимо две задачи синхронизации времени!");
								m_Grid.SetItemText(pItem->iRow,pItem->iColumn ,arrMain_Set_ProcessesTypes[0]);
								m_Grid.SetItemData(pItem->iRow,pItem->iColumn,255);
							}
						}
					}
					if(((nChangedData > 0)&&(nChangedData < 9))
						||(nChangedData == 14)
						||(nChangedData == 15)
						||(nChangedData == 16)
						||(nChangedData == 17)
						||(nChangedData == 19)
						||(nChangedData == 21)
						||(nChangedData == 18))//protocol selected
					{
						switch(nChangedData)
						{
							case 3://IEC870-5-101-master
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CIec101m Iec101m;
										Iec101m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec101mPath;
										CString strIec101mTuPath;										
										strIec101mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										strIec101mPath.Format("%siec101m%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										CIec101m tmp2;
										if(tmp2.LoadFromFile(strIec101mPath))
										{
											tmp2.m_nProcNum = Iec101m.m_nProcNum;
											tmp2.LoadFromTuFile(strIec101mTuPath);
											Iec101m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.Add(Iec101m);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);								
									}											
									break;
								}
							case 21://STM32
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CSTM Iec101m;
										Iec101m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec101mPath;
										CString strIec101mTuPath;										
										//strIec101mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										strIec101mPath.Format("%sstm_m%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);										
										CSTM tmp2;
										tmp2.m_nProcNum = Iec101m.m_nProcNum;
										if(tmp2.LoadFromFile(strIec101mPath))
										{																						
											Iec101m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray.Add(Iec101m);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);								
									}											
									break;
								}
							case 19://ModbusTCP-master
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusTCPMArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusTCPMArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CModbusTCPM Iec101m;
										Iec101m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec101mPath;
										CString strIec101mTuPath;										
										strIec101mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										strIec101mPath.Format("%smodbus_tcp_m%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										CModbusTCPM tmp2;
										if(tmp2.LoadFromFile(strIec101mPath))
										{
											tmp2.m_nProcNum = Iec101m.m_nProcNum;
											tmp2.LoadFromTuFile(strIec101mTuPath);
											Iec101m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusTCPMArray.Add(Iec101m);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);								
									}											
									break;
								}
							case 17://SPAm
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CSPAm SPAm;
										SPAm.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strSPAmPath;
										CString strSPAmTuPath;										
										strSPAmTuPath.Format("%stu%d.ini",m_strLastProjectPath,SPAm.m_nProcNum);
										strSPAmPath.Format("%sSPAm%d.ini",m_strLastProjectPath,SPAm.m_nProcNum);
										CSPAm tmp2;
										if(tmp2.LoadFromFile(strSPAmPath))
										{
											tmp2.m_nProcNum = SPAm.m_nProcNum;
											tmp2.LoadFromTuFile(strSPAmTuPath);
											SPAm = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.Add(SPAm);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);								
									}											
									break;
								}
							case 16://gpio
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CGPIOm GPIOm;
										GPIOm.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strGPIOmPath;
										CString strGPIOmTuPath;										
										strGPIOmTuPath.Format("%stu%d.ini",m_strLastProjectPath,GPIOm.m_nProcNum);
										strGPIOmPath.Format("%sGPIOm%d.ini",m_strLastProjectPath,GPIOm.m_nProcNum);
										CGPIOm tmp2;
										if(tmp2.LoadFromFile(strGPIOmPath))
										{
											tmp2.m_nProcNum = GPIOm.m_nProcNum;
											tmp2.LoadFromTuFile(strGPIOmTuPath);
											GPIOm = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.Add(GPIOm);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);								
									}											
									break;
								}
							case 18://BUI
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CMapboard Iec101m;
										Iec101m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec101mPath;
										//CString strIec101mTuPath;										
										//strIec101mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										strIec101mPath.Format("%sshield%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										CMapboard tmp2;
										if(tmp2.LoadFromFile(strIec101mPath))
										{
											tmp2.m_nProcNum = Iec101m.m_nProcNum;
											//tmp2.LoadFromTuFile(strIec101mTuPath);
											Iec101m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.Add(Iec101m);	
									}							
									m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,4,"");
									break;
								}
							case 15://Korund
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CIecKorundm Iec101m;
										Iec101m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec101mPath;
										//CString strIec101mTuPath;										
										//strIec101mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										strIec101mPath.Format("%sKorundm%d.ini",m_strLastProjectPath,Iec101m.m_nProcNum);
										CIecKorundm tmp2;
										if(tmp2.LoadFromFile(strIec101mPath))
										{
											tmp2.m_nProcNum = Iec101m.m_nProcNum;
											//tmp2.LoadFromTuFile(strIec101mTuPath);
											Iec101m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.Add(Iec101m);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);				
									}											
									break;
								}
							case 5://IEC870-5-103-master
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CIec103m Iec103m;
										Iec103m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec103mPath;
										CString strIec103mTuPath;										
										strIec103mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec103m.m_nProcNum);
										strIec103mPath.Format("%siec103m%d.ini",m_strLastProjectPath,Iec103m.m_nProcNum);
										CIec103m tmp2;
										if(tmp2.LoadFromFile(strIec103mPath))
										{
											tmp2.m_nProcNum = Iec103m.m_nProcNum;
											tmp2.LoadFromTuFile(strIec103mTuPath);
											Iec103m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.Add(Iec103m);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));										
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										pCell2->SetStyle(CBS_DROPDOWNLIST);
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										
										pCell2->SetCurSel(0);				
									}											
									break;
								}
							case 7://IEC870-5-104-master
								{									
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CIec104m Iec104m;
										Iec104m.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec104mPath;
										CString strIec104mTuPath;										
										strIec104mTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec104m.m_nProcNum);
										strIec104mPath.Format("%siec104m%d.ini",m_strLastProjectPath,Iec104m.m_nProcNum);
										CIec104m tmp2;
										if(tmp2.LoadFromFile(strIec104mPath))
										{
											tmp2.m_nProcNum = Iec104m.m_nProcNum;
											tmp2.LoadFromTuFile(strIec104mTuPath);
											Iec104m = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.Add(Iec104m);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);				
									}											
									break;
								}
							case 8://IEC870-5-104-slave ptp
							case 14://IEC870-5-104-slave ptmp
								{
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}	
									if(!bExist)
									{
										CIec104s Iec104s;
										Iec104s.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec104sPath;
										CString strIec104sTuPath;										
										strIec104sTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec104s.m_nProcNum);
										strIec104sPath.Format("%siec104s%d.ini",m_strLastProjectPath,Iec104s.m_nProcNum);
										CIec104s tmp2;
										if(tmp2.LoadFromFile(strIec104sPath))
										{
											tmp2.m_nProcNum = Iec104s.m_nProcNum;											
											Iec104s = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.Add(Iec104s);
									}	
									m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,4,"");
									break;
								}
							case 4://IEC870-5-101-slave
								{
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CIec101s Iec101s;
										Iec101s.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strIec101sPath;
										CString strIec101sTuPath;										
										strIec101sTuPath.Format("%stu%d.ini",m_strLastProjectPath,Iec101s.m_nProcNum);
										strIec101sPath.Format("%siec101s%d.ini",m_strLastProjectPath,Iec101s.m_nProcNum);
										CIec101s tmp2;
										if(tmp2.LoadFromFile(strIec101sPath))
										{
											tmp2.m_nProcNum = Iec101s.m_nProcNum;											
											Iec101s = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.Add(Iec101s);
									}		
									m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,4,"");
									break;									
								}
							case 1://modbus-master
								{
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CModbusM ModbusM;
										ModbusM.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strModbusMPath;
										CString strModbusMTuPath;										
										strModbusMTuPath.Format("%stu%d.ini",m_strLastProjectPath,ModbusM.m_nProcNum);
										strModbusMPath.Format("%smodm%d.ini",m_strLastProjectPath,ModbusM.m_nProcNum);
										CModbusM tmp2;
										if(tmp2.LoadFromFile(strModbusMPath))
										{
											tmp2.m_nProcNum = ModbusM.m_nProcNum;
											tmp2.LoadFromTuFile(strModbusMTuPath);
											ModbusM = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.Add(ModbusM);
										m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) & ~GVIS_READONLY);
										m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCellCombo));
										CGridCellCombo *pCell2 = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, 4);		
										CStringArray tmpArr;
										tmpArr.Add("Нет");
										tmpArr.Add("Разрешить");							
										pCell2->SetOptions(tmpArr);		
										pCell2->SetStyle(CBS_DROPDOWNLIST); 														
										pCell2->SetCurSel(0);				
									}																							
									break;										
								}
							case 2://modbus-s
								{
									BOOL bExist = FALSE;																											
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray[i].m_nProcNum==pItem->iRow)
										{
											bExist = TRUE;											
											break;
										}
									}				
									if(!bExist)
									{
										CModbusS ModbusS;
										ModbusS.m_nProcNum = pItem->iRow;
										//Пытаемся подчитать из файла
										CString strModbusSPath;
										CString strModbusSTuPath;										
										strModbusSTuPath.Format("%stu%d.ini",m_strLastProjectPath,ModbusS.m_nProcNum);
										strModbusSPath.Format("%smods%d.ini",m_strLastProjectPath,ModbusS.m_nProcNum);
										CModbusS tmp2;
										if(tmp2.LoadFromFile(strModbusSPath))
										{
											tmp2.m_nProcNum = ModbusS.m_nProcNum;										
											ModbusS = tmp2;
										}
										//
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.Add(ModbusS);
									}		
									m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,4,"");
									break;										

								}
							default:
								{
									m_Grid.SetItemState(pItem->iRow, 4, m_Grid.GetItemState(pItem->iRow, 4) | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,4,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,4,"");
									/*m_Grid.SetItemState(pItem->iRow, 5, m_Grid.GetItemState(pItem->iRow, 5 | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,5,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,5,"");
									m_Grid.SetItemState(pItem->iRow, 6, m_Grid.GetItemState(pItem->iRow, 6) | GVIS_READONLY);
									m_Grid.SetCellType(pItem->iRow,6,RUNTIME_CLASS(CGridCell));
									m_Grid.SetItemText(pItem->iRow,6,"");*/
									break;
								}
						}
					}
				}				
				break;
			}
	}
	m_Grid.AutoSize();
	m_Grid.Refresh();
}

void CKPLConfigDlg::OnSave()
{
	// TODO: добавьте свой код обработчика команд
	switch(m_MainTab.GetCurSel())
	{
		case 0 :
		case 1 :
		case 2 :
		case 3 :
			{
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					CFileDialog dlg(FALSE, _T("ini"), "main_set.ini", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Файлы настроек (*.ini)| *.ini|Все файлы (*.*)|*.*||"));
					if (dlg.DoModal() == IDOK)
					{		
						CString sFile = dlg.GetPathName(); // имя файла. также можно использовать				
						int nInd = sFile.ReverseFind('\\');
						if(nInd != -1)
							sFile.Truncate(nInd+1);

						CString strCapion;					
						strCapion.Format("Настройка КПЛ [%s]",sFile);					
						this->SetWindowText(strCapion);

						if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.SaveProject(sFile,"")!=TRUE)
						{
							AfxMessageBox("Во время сохранения проекта произошли ошибки!");
							return;
						}	
						m_strLastProjectPath = sFile;
					}
				}
				break;
			}
	}
	
}

void CKPLConfigDlg::OnOpen()
{
	switch(m_MainTab.GetCurSel())
	{
		case 0 :
		case 1 :
		case 2 :
		case 3 :
			{
				//SaveTab(m_MainTab.GetCurSel());				
				CFileDialog dlg(TRUE, _T("ini"), "main_set.ini", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Файлы настроек (*.ini)| *.ini|Все файлы (*.*)|*.*||"));
				if (dlg.DoModal() == IDOK)
				{		
					CString sFile = dlg.GetPathName(); // имя файла. также можно использовать
					int nInd = sFile.ReverseFind('\\');
					if(nInd != -1)
						sFile.Truncate(nInd+1);

					CString strCapion;					
					strCapion.Format("Настройка КПЛ [%s]",sFile);					
					this->SetWindowText(strCapion);

					if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.LoadProject(sFile)!=TRUE)
					{
						AfxMessageBox("Не удалось открыть проект!");
						return;
					}
					m_strLastProjectPath = sFile;
					UpdateCombo();
					ChangeTab(m_MainTab.GetCurSel());			
				}
				break;
			}
	}
}

void CKPLConfigDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	//CDialog::OnOK();
}

void CKPLConfigDlg::OnCancel()
{
	if(AfxMessageBox("Выйти из программы?",MB_YESNO|MB_ICONQUESTION)==IDYES)
	{	
		if(AfxMessageBox("Сохранить конфигурацию?",MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			OnSave();
		}
		CDialog::OnCancel();
	}	
}

void CKPLConfigDlg::OnClose()
{
	// TODO: добавьте свой код обработчика команд
	if(AfxMessageBox("Сохранить конфигурацию?",MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		OnSave();
	}
	CKPLProject tmp;
	tmp.m_nVersion = KPL_CURRENTVERSION;
	((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject = tmp;
	CGridCellBase *pCell1;
	for(int i = 0; i < m_Grid.GetRowCount(); i++)
	{
		for(int j = 0; j < m_Grid.GetColumnCount(); j++)
		{
			pCell1 = m_Grid.GetCell(i,j);	
			if(pCell1->IsEditing())
			{
				pCell1->EndEdit();
			}		
		}
	}
	CString strCapion;					
	strCapion.Format("Настройка КПЛ");					
	this->SetWindowText(strCapion);

	UpdateCombo();
	ChangeTab(m_MainTab.GetCurSel());
}

afx_msg void CKPLConfigDlg::OnDetail()
{
	CCellID pCell = m_Grid.GetFocusCell();
	switch(m_MainTab.GetCurSel())
	{
		case 1 :
			{
				if((pCell.row > 0)&&(pCell.col > 0))
				{
					if(SaveTab(m_MainTab.GetCurSel()))
					{
						switch(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].TYPE_PROTOKOL)
						{
							case 21://STM32
								{
									CSTM32Dlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_STM = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_STM.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray.Add(dlg.m_STM);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray[i].m_nProcNum==dlg.m_STM.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_STMArray[i] = dlg.m_STM;
												break;
											}
										}
									}
									break;
								}
							case 16://GPIO
								{
									CGPIOmDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_GPIOm = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_GPIOm.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.Add(dlg.m_GPIOm);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray[i].m_nProcNum==dlg.m_GPIOm.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPIOmArray[i] = dlg.m_GPIOm;
												break;
											}
										}
									}
									break;
								}
							case 15://KORUND
								{									
									CKorundmDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Korundm = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Korundm.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.Add(dlg.m_Korundm);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray[i].m_nProcNum==dlg.m_Korundm.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_IecKorundmArray[i] = dlg.m_Korundm;
												break;
											}
										}
									}
									break;
								}
							case 19://Modbus TCP master
								{
									/*CSPAmDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_SPAm = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_SPAm.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.Add(dlg.m_SPAm);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i].m_nProcNum==dlg.m_SPAm.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i] = dlg.m_SPAm;
												break;
											}
										}
									}*/
									break;
								}
							case 17://SPA
								{
									CSPAmDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_SPAm = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_SPAm.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.Add(dlg.m_SPAm);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i].m_nProcNum==dlg.m_SPAm.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_SPAmArray[i] = dlg.m_SPAm;
												break;
											}
										}
									}
									break;
								}
							case 3://IEC870-5-101-master
								{
									CIec101mDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Iec101m = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Iec101m.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.Add(dlg.m_Iec101m);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray[i].m_nProcNum==dlg.m_Iec101m.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101mArray[i] = dlg.m_Iec101m;
												break;
											}
										}
									}
									break;
								}
							case 7://IEC870-5-104-master
								{
									CIec104mDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Iec104m = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Iec104m.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.Add(dlg.m_Iec104m);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray[i].m_nProcNum==dlg.m_Iec104m.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104mArray[i] = dlg.m_Iec104m;
												break;
											}
										}
									}
									break;
								}
							case 5://IEC870-5-103-master
								{
									CIec103mDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Iec103m = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Iec103m.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.Add(dlg.m_Iec103m);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray[i].m_nProcNum==dlg.m_Iec103m.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec103mArray[i] = dlg.m_Iec103m;
												break;
											}
										}
									}
									break;
								}
							case 8://IEC870-5-104-slave
							case 14://IEC870-5-104-slave
								{
									CIec104sDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Iec104s = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Iec104s.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.Add(dlg.m_Iec104s);
									}
									dlg.m_byProcType = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].TYPE_PROTOKOL;
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray[i].m_nProcNum==dlg.m_Iec104s.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec104sArray[i] = dlg.m_Iec104s;
												break;
											}
										}
									}
									break;
								}
							case 4://IEC870-5-101-slave
								{
									CIec101sDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Iec101s = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Iec101s.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.Add(dlg.m_Iec101s);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray[i].m_nProcNum==dlg.m_Iec101s.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Iec101sArray[i] = dlg.m_Iec101s;
												break;
											}
										}
									}
									break;
								}
							case 18://BUI(-slave)
								{
									CMapboardDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_Mapboard = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_Mapboard.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.Add(dlg.m_Mapboard);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray[i].m_nProcNum==dlg.m_Mapboard.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_MapboardArray[i] = dlg.m_Mapboard;
												break;
											}
										}
									}
									break;
								}
							case 1://modbus-master
								{
									CModbusMDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_ModbusM = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_ModbusM.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.Add(dlg.m_ModbusM);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray[i].m_nProcNum==dlg.m_ModbusM.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusMArray[i] = dlg.m_ModbusM;
												break;
											}
										}
									}
									break;
								}
							case 9://m_Retr CRetrConfigDlg
								{
									CRetrConfigDlg dlg;																		
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr.NUM_RETR_OBJECT;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}									
									dlg.m_Retr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr;										
									dlg.m_Main_Set = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set;										
									if(dlg.DoModal()==IDOK)
									{
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Retr = dlg.m_Retr;
									}
									break;
								}								
							case 2://modbus-s
								{
									CModbusSDlg dlg;									
									BOOL bExist = FALSE;
									
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									if((dlg.m_nStartPMZAddr==dlg.m_nEndPMZAddr)||(dlg.m_nEndPMZAddr<0))
									{
										AfxMessageBox("Для данного процесса сначала необходимо заполнить поле:\r\n\"Количество информ.объектов в поле данных\"!");
										return;
									}
									for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.GetSize(); i++)
									{
										if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray[i].m_nProcNum==pCell.row)
										{
											bExist = TRUE;
											dlg.m_ModbusS = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray[i];
											dlg.nProcNum = pCell.row;
											break;
										}
									}				
									if(!bExist)
									{
										dlg.nProcNum = pCell.row;
										dlg.m_ModbusS.m_nProcNum = pCell.row;
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.Add(dlg.m_ModbusS);
									}
									if(dlg.DoModal()==IDOK)
									{
										for(int i = 0; i < ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray.GetSize(); i++)
										{
											if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray[i].m_nProcNum==dlg.m_ModbusS.m_nProcNum)
											{												
												((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_ModbusSArray[i] = dlg.m_ModbusS;
												break;
											}
										}
									}
									break;
								}
							case 13://m_GPSTime CGPSConfigDlg
								{
									CGPSConfigDlg dlg;																																																					
									dlg.m_nStartPMZAddr =0;// ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].START_ADDRESS_MAP;
									dlg.m_nEndPMZAddr = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_ProcessInfoArray[pCell.row-1].AMOUNT_SIGNIFICATE - 1;

									dlg.m_GPSTime = ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPSTime;																			
									if(dlg.DoModal()==IDOK)
									{
										((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_GPSTime = dlg.m_GPSTime;
									}
									break;
								}	
						}						
					}
				}
				break;
			}
	}
}
void CKPLConfigDlg::OnPrint()
{
	// TODO: добавьте свой код обработчика команд
	m_Grid.Print();
}

void CKPLConfigDlg::OnSaveToKsri()
{
	// TODO: добавьте свой код обработчика команд	
	switch(m_MainTab.GetCurSel())
	{
		case 0 :
		case 1 :
		case 2 :
		case 3 :
			{
				if(SaveTab(m_MainTab.GetCurSel()))
				{
					CIPDlg dlg;
					if(dlg.DoModal()==IDOK)
					{
						if(dlg.m_strIP.IsEmpty())
						{
							AfxMessageBox("Не удалось сохранить проект!\r\nНе введен IP-адрес КПЛ.");
							return;
						}
						CWaitCursor wait;
						m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
						m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlg.m_strIP);						
						/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
						CString strFtpSite;
						CString strServerName;
						CString strObject;
						INTERNET_PORT nPort;
						DWORD dwServiceType;
						CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
						CFtpConnection* pFtpConn = NULL;
						
						strFtpSite = "ftp://"+dlg.m_strIP+m_strFtpSite;												
						
						if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
						{
							m_WaitDlg.ShowWindow(SW_HIDE);
							AfxMessageBox("Неверный формат адреса FTP сервера!");							
							return;
						}

						try
						{			
							pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
						}
						catch (CInternetException* pEx)
						{		
							m_WaitDlg.ShowWindow(SW_HIDE);								
							// catch errors from WinINet
							TCHAR szErr[1024];
							if (pEx->GetErrorMessage(szErr, 1024))
							{
								CString str3,str4;
								str3 = szErr;
								str4 = "Ошибка установки FTP соединения: " + str3;
								AfxMessageBox(str4);
								pEx->Delete();																		
							}								
							return;
						}
						m_WaitDlg.ShowWindow(SW_HIDE);
						if(pFtpConn != NULL)
						{
							char lpPathBuffer[512];
							DWORD dwRetVal;
							CString strDirectory="";
							dwRetVal = GetTempPath(512,     // length of the buffer
													lpPathBuffer); // buffer for path 
							if (dwRetVal > 512 || (dwRetVal == 0))															
								strDirectory="";							
							else
								strDirectory = lpPathBuffer;

							if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.SaveProject(strDirectory,strObject,pFtpConn)!=TRUE)
							{
								AfxMessageBox("Не удалось сохранить проект!");								
								return;
							}
							else
								AfxMessageBox("Проект успешно сохранен!",MB_ICONINFORMATION);

							pFtpConn->Close();							
						}						
					}					
				}
				break;
			}
	}
}

void CKPLConfigDlg::OnOpenFtp()
{
	// TODO: добавьте свой код обработчика команд
	CIPDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не удалось прочитать проект!\r\nНе введен IP-адрес КПЛ.");
			return;
		}
		CWaitCursor wait;
		m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
		m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlg.m_strIP);
		
		/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
		CString strFtpSite;
		CString strServerName;
		CString strObject;
		INTERNET_PORT nPort;
		DWORD dwServiceType;
		CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
		CFtpConnection* pFtpConn = NULL;
		
		strFtpSite = "ftp://"+dlg.m_strIP+m_strFtpSite;												
		
		
		if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
		{
			m_WaitDlg.ShowWindow(SW_HIDE);
			AfxMessageBox("Неверный формат адреса FTP сервера!");			
			return;
		}

		try
		{			
			pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
		}
		catch (CInternetException* pEx)
		{		
			m_WaitDlg.ShowWindow(SW_HIDE);
			// catch errors from WinINet
			TCHAR szErr[1024];
			if (pEx->GetErrorMessage(szErr, 1024))
			{
				CString str3,str4;
				str3 = szErr;
				str4 = "Ошибка установки FTP соединения: " + str3;
				AfxMessageBox(str4);
				pEx->Delete();											
			}											
			return;
		}
		m_WaitDlg.ShowWindow(SW_HIDE);
		if(pFtpConn != NULL)
		{
			CString strDirectory="";
			CString strTmpDir = GetEXEDirPath()+"\\Tmp\\";
			/*if(CFileManip::Existence(strTmpDir) == CFileManip::FM_NOTEXIST)
			{
				if(CFileManip::MkDir(strTmpDir))
				{
					strDirectory = strTmpDir;
				}
				else
				{
					strDirectory = strTmpDir;

					CString strMsg;
					strMsg.Format("Не удалось создать временную директорию: %s",strTmpDir);
					//AfxMessageBox(strMsg);	
					//return;
				}
			}
			else
			{
				strDirectory = strTmpDir;
				CFileManip::DelTree(strTmpDir+"*.*");	
			}*/
			CFileManip::MkDir(strTmpDir);
			CFileManip::DelTree(strTmpDir+"*.*");	
			strDirectory = strTmpDir;


			/*char lpPathBuffer[512];
			DWORD dwRetVal;
			
			dwRetVal = GetTempPath(512,     // length of the buffer
									lpPathBuffer); // buffer for path 
			if (dwRetVal > 512 || (dwRetVal == 0))															
				strDirectory="";							
			else
				strDirectory = lpPathBuffer;*/

			CFtpFileFind finder(pFtpConn);
			BOOL bWorking = finder.FindFile(m_strFtpSite+"/*.*");

			while (bWorking)
			{
				bWorking = finder.FindNextFile();
				CString str = finder.GetFileName();				
				BOOL bret = pFtpConn->GetFile(m_strFtpSite+"/"+str,strDirectory+str,FALSE);		
				if(!bret)
				{
					CString strMsg;
					strMsg.Format("Ошибка при загрузке файла %s: %s",m_strFtpSite+"/"+str,strDirectory+str,iGetLastErrorText());
					AfxMessageBox(strMsg);	
					return;
				}
			}				

			CString strCapion;					
			strCapion.Format("Настройка КПЛ [%s]",strDirectory);					
			this->SetWindowText(strCapion);

			if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.LoadProject(strDirectory)!=TRUE)
			{
				AfxMessageBox("Не удалось открыть проект!");				
				return;
			}
			pFtpConn->Close();			
			UpdateCombo();
			ChangeTab(m_MainTab.GetCurSel());			
		}		
	}
}
BOOL CKPLConfigDlg::ChangeFileOptionsOnTelnet(CString strHost)
{
	m_pTelnetSocket = new CClientSocket();
	BOOL bOK;
	if(m_pTelnetSocket != NULL)
	{
		bOK = m_pTelnetSocket->Create();
		if(bOK == TRUE)
		{
			m_pTelnetSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT | FD_OOB);
			m_pTelnetSocket->Connect(strHost, 23);
			Sleep(300);
			CString strText;
			strText = "root\r\n";
			m_pTelnetSocket->Send(strText, strText.GetLength());			
			Sleep(300);

			strText = "vitamax\r\n";
			m_pTelnetSocket->Send(strText, strText.GetLength());			
			Sleep(300);

			
			strText = "chmod 777 /home/VICTORY.out\r\n";
			m_pTelnetSocket->Send(strText, strText.GetLength());
			Sleep(300);

			m_pTelnetSocket->Close();
			delete m_pTelnetSocket;
			m_pTelnetSocket = NULL;
			return TRUE;
		}
		else
		{			
			delete m_pTelnetSocket;
			m_pTelnetSocket = NULL;
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}
BOOL CKPLConfigDlg::RebootOnTelnet(CString strHost)
{
	m_pTelnetSocket = new CClientSocket();
	BOOL bOK;
	if(m_pTelnetSocket != NULL)
	{
		bOK = m_pTelnetSocket->Create();
		if(bOK == TRUE)
		{
			m_pTelnetSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT | FD_OOB);
			m_pTelnetSocket->Connect(strHost, 23);
			Sleep(300);
			CString strText;
			strText = "root\r\n";
			m_pTelnetSocket->Send(strText, strText.GetLength());			
			Sleep(300);

			strText = "vitamax\r\n";
			m_pTelnetSocket->Send(strText, strText.GetLength());			
			Sleep(300);

			strText = "reboot\r\n";
			m_pTelnetSocket->Send(strText, strText.GetLength());
			Sleep(300);

			m_pTelnetSocket->Close();
			delete m_pTelnetSocket;
			m_pTelnetSocket = NULL;
			return TRUE;
		}
		else
		{			
			delete m_pTelnetSocket;
			m_pTelnetSocket = NULL;
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}
void CKPLConfigDlg::OnUploadfw()
{
	// TODO: добавьте свой код обработчика команд
	CIPDlg dlgIP;
	if(dlgIP.DoModal()==IDOK)
	{
		if(dlgIP.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не удалось загрузить прошивку!\r\nНе введен IP-адрес КПЛ.");
			return;
		}
		CWaitCursor wait;
		m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
		m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlgIP.m_strIP);		
		/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
		CString strFtpSite;
		CString strServerName;
		CString strObject;
		INTERNET_PORT nPort;
		DWORD dwServiceType;
		CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
		CFtpConnection* pFtpConn = NULL;
		
		strFtpSite = "ftp://"+dlgIP.m_strIP+m_strFtpHome;												
		
		if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
		{
			m_WaitDlg.ShowWindow(SW_HIDE);
			AfxMessageBox("Неверный формат адреса FTP сервера!");			
			return;
		}

		try
		{					
			pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
		}
		catch (CInternetException* pEx)
		{		
			m_WaitDlg.ShowWindow(SW_HIDE);		
			// catch errors from WinINet
			TCHAR szErr[1024];
			if (pEx->GetErrorMessage(szErr, 1024))
			{
				CString str3,str4;
				str3 = szErr;
				str4 = "Ошибка установки FTP соединения: " + str3;
				AfxMessageBox(str4);
				pEx->Delete();								
			}			
			return;
		}
		m_WaitDlg.ShowWindow(SW_HIDE);

		if(pFtpConn != NULL)
		{			
			CFileDialog dlg(TRUE, _T("out"), "VICTORY.out", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Файлы прошивки (*.out)| *.out|Все файлы (*.*)|*.*||"));
			if (dlg.DoModal() == IDOK)
			{	
				m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
				m_WaitDlg.SetText("Остановка программы в КПЛ...");

				if(!SendAndCheckServiceCommandFile(pFtpConn,strObject,SERVICE_COMMAND_EXIT_APP,10000))
				{
					if(AfxMessageBox("Не удалось остановить программу в КПЛ.\r\nВозможно программа уже остановлена.\r\nПродолжить загрузку прошивки?",MB_ICONQUESTION|MB_YESNO)==IDNO)	
					{
						pFtpConn->Close();								
						m_InternetSession.Close();
						m_WaitDlg.ShowWindow(SW_HIDE);
						return;
					}										
				}

				m_WaitDlg.SetText("Загрузка прошивки в КПЛ...");
				CString sFile = dlg.GetPathName(); // имя файла. также можно использовать				
				CString strOutFile = strObject+"/"+dlg.GetFileName();
				CWaitCursor wait;
				if(!pFtpConn->PutFile(sFile,strOutFile))
				{
					m_WaitDlg.ShowWindow(SW_HIDE);
					DWORD aaa = 0;
					DWORD bbb =2000;					
					char lpszBuffer[2000];
					InternetGetLastResponseInfo(	  &aaa,
													  lpszBuffer,													  
													&bbb);
					CString strMes;
					strMes.Format("Не удалось загрузить прошивку в КПЛ!\r\n%s",lpszBuffer);
					AfxMessageBox(strMes);					
				}
				else
				{
					m_WaitDlg.SetText("Изменение аттрибутов файла прошивки...");
					if(!ChangeFileOptionsOnTelnet(dlgIP.m_strIP))										
						AfxMessageBox("Ошибка при изменении аттрибутов файла прошивки");

					m_WaitDlg.ShowWindow(SW_HIDE);
					
					if(AfxMessageBox("Прошивка успешно загружена. Перезагрузить КПЛ?",MB_ICONQUESTION|MB_YESNO)==IDYES)
					{
						m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
						m_WaitDlg.SetText("Перезагрузка в КПЛ...");
						if(RebootOnTelnet(dlgIP.m_strIP))
						{
							m_WaitDlg.ShowWindow(SW_HIDE);
							AfxMessageBox("Комманда перезагрузки КПЛ отправлена.",MB_ICONINFORMATION);
						}
						else
						{
							m_WaitDlg.ShowWindow(SW_HIDE);
							AfxMessageBox("Ошибка при отправке комманды перезагрузки КПЛ");
						}
					}										
				}				
			}						
			pFtpConn->Close();			
			m_InternetSession.Close();			
		}		
	}
}

void CKPLConfigDlg::OnDownloadfw()
{
	// TODO: добавьте свой код обработчика команд
	CIPDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не удалось считать прошивку!\r\nНе введен IP-адрес КПЛ.");
			return;
		}
		CWaitCursor wait;
		m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
		m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlg.m_strIP);		
		/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
		CString strFtpSite;
		CString strServerName;
		CString strObject;
		INTERNET_PORT nPort;
		DWORD dwServiceType;
		CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
		CFtpConnection* pFtpConn = NULL;
		
		strFtpSite = "ftp://"+dlg.m_strIP+m_strFtpHome;													
		
		if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
		{
			m_WaitDlg.ShowWindow(SW_HIDE);
			AfxMessageBox("Неверный формат адреса FTP сервера!");
			return;
		}

		try
		{				
			pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
		}
		catch (CInternetException* pEx)
		{	
			m_WaitDlg.ShowWindow(SW_HIDE);			
			// catch errors from WinINet
			TCHAR szErr[1024];
			if (pEx->GetErrorMessage(szErr, 1024))
			{
				CString str3,str4;
				str3 = szErr;
				str4 = "Ошибка установки FTP соединения: " + str3;
				AfxMessageBox(str4);
				pEx->Delete();									
			}									
			return;
		}
		m_WaitDlg.ShowWindow(SW_HIDE);
		if(pFtpConn != NULL)
		{						
			CFileDialog dlg(FALSE, _T("out"), "VICTORY", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Файлы прошивки (*.out)| *.out|Все файлы (*.*)|*.*||"));
			if (dlg.DoModal() == IDOK)
			{		

				CString sFile = dlg.GetPathName(); // имя файла. также можно использовать				
				/*int nInd = sFile.ReverseFind('\\');
				if(nInd != -1)
					sFile.Truncate(nInd+1);*/
				CWaitCursor wait;
				CFtpFileFind finder(pFtpConn);
				BOOL bWorking = finder.FindFile(m_strFtpHome+"/VICTORY.out");
				
				int nFilesCount = 0;
				while (bWorking)
				{		
						
					bWorking = finder.FindNextFile();
					CString str = finder.GetFileName();					
					
					m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
					m_WaitDlg.SetText("Загрузка прошивки из КПЛ...");

					if(pFtpConn->GetFile(m_strFtpHome+"/"+str,sFile,FALSE))
						nFilesCount++;
				}		
				if(nFilesCount==0)
				{
					m_WaitDlg.ShowWindow(SW_HIDE);
					AfxMessageBox("Не удалось считать прошивку!\r\nНе найден файл VICTORY.out в КПЛ.");										
				}
				else
				{
					m_WaitDlg.ShowWindow(SW_HIDE);
					AfxMessageBox("Прошивка успешно считана.\r\nСохранена:\r\n"+sFile,MB_ICONINFORMATION);
				}
			}						
			pFtpConn->Close();			
		}
	}
}

void CKPLConfigDlg::OnAlarm()
{
	// TODO: добавьте свой код обработчика команд
	CIPDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не удалось считать прошивку!\r\nНе введен IP-адрес КПЛ.");
			return;
		}
		CWaitCursor wait;
		m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
		m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlg.m_strIP);		
		/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
		CString strFtpSite;
		CString strServerName;
		CString strObject;
		INTERNET_PORT nPort;
		DWORD dwServiceType;
		CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
		CFtpConnection* pFtpConn = NULL;
		
		strFtpSite = "ftp://"+dlg.m_strIP+m_strFtpAlarm;													
		
		if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
		{
			m_WaitDlg.ShowWindow(SW_HIDE);
			AfxMessageBox("Неверный формат адреса FTP сервера!");
			return;
		}

		try
		{			
			pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
		}
		catch (CInternetException* pEx)
		{		
			m_WaitDlg.ShowWindow(SW_HIDE);			
			// catch errors from WinINet
			TCHAR szErr[1024];
			if (pEx->GetErrorMessage(szErr, 1024))
			{
				CString str3,str4;
				str3 = szErr;
				str4 = "Ошибка установки FTP соединения: " + str3;
				AfxMessageBox(str4);
				pEx->Delete();							
			}	
			return;
		}
		m_WaitDlg.ShowWindow(SW_HIDE);
		if(pFtpConn != NULL)
		{			
			CGetFilesDlg dlgGet;
			dlgGet.m_byTypeDlg = TYPE_ALARM;
			dlgGet.m_strAlarmPath = m_strAlarmPath;
			dlgGet.m_pFtpConn = pFtpConn;
			dlgGet.m_strFtpAlarm = m_strFtpAlarm;
			dlgGet.DoModal();
			
			pFtpConn->Close();			
		}
	}
}

void CKPLConfigDlg::OnLog()
{
	// TODO: добавьте свой код обработчика команд
	CIPDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не удалось считать прошивку!\r\nНе введен IP-адрес КПЛ.");
			return;
		}

		CWaitCursor wait;				
		
		m_WaitDlg.ShowWindow(SW_SHOWNORMAL);		
		m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlg.m_strIP);		
		/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
		CString strFtpSite;
		CString strServerName;
		CString strObject;
		INTERNET_PORT nPort;
		DWORD dwServiceType;
		CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
		CFtpConnection* pFtpConn = NULL;
		
		strFtpSite = "ftp://"+dlg.m_strIP+m_strFtpLog;													
		
		if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
		{
			m_WaitDlg.ShowWindow(SW_HIDE);
			AfxMessageBox("Неверный формат адреса FTP сервера!");
			return;
		}

		try
		{			
			pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
		}
		catch (CInternetException* pEx)
		{		
			m_WaitDlg.ShowWindow(SW_HIDE);			
			// catch errors from WinINet
			TCHAR szErr[1024];
			if (pEx->GetErrorMessage(szErr, 1024))
			{
				CString str3,str4;
				str3 = szErr;
				str4 = "Ошибка установки FTP соединения: " + str3;
				AfxMessageBox(str4);
				pEx->Delete();							
			}							
			return;
		}
		m_WaitDlg.ShowWindow(SW_HIDE);
		if(pFtpConn != NULL)
		{			
			CGetFilesDlg dlgGet;
			dlgGet.m_byTypeDlg = TYPE_LOG;
			dlgGet.m_strLogPath = m_strLogPath;
			dlgGet.m_pFtpConn = pFtpConn;
			dlgGet.m_strFtpLog = m_strFtpLog;
			dlgGet.DoModal();
			
			pFtpConn->Close();			
		}
	}
}

void CKPLConfigDlg::On32794()
{
	CIPDlg dlgIP;
	if(dlgIP.DoModal()==IDOK)
	{
		if(dlgIP.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не введен IP-адрес КПЛ.");
			return;
		}
		// TODO: добавьте свой код обработчика команд
		if(AfxMessageBox("Перезагрузить КПЛ?",MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			CWaitCursor wait;
			m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
			m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlgIP.m_strIP);		
			/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
			CString strFtpSite;
			CString strServerName;
			CString strObject;
			INTERNET_PORT nPort;
			DWORD dwServiceType;
			CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
			CFtpConnection* pFtpConn = NULL;
			
			strFtpSite = "ftp://"+dlgIP.m_strIP+m_strFtpHome;												
			
			if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
			{
				m_WaitDlg.ShowWindow(SW_HIDE);
				AfxMessageBox("Неверный формат адреса FTP сервера!");			
				return;
			}

			try
			{					
				pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
			}
			catch (CInternetException* pEx)
			{		
				m_WaitDlg.ShowWindow(SW_HIDE);		
				// catch errors from WinINet
				TCHAR szErr[1024];
				if (pEx->GetErrorMessage(szErr, 1024))
				{
					CString str3,str4;
					str3 = szErr;
					str4 = "Ошибка установки FTP соединения: " + str3;
					AfxMessageBox(str4);
					pEx->Delete();								
				}			
				return;
			}
			m_WaitDlg.ShowWindow(SW_HIDE);

			if(pFtpConn != NULL)
			{			
				
				m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
				m_WaitDlg.SetText("Остановка программы в КПЛ...");

				if(!SendAndCheckServiceCommandFile(pFtpConn,strObject,SERVICE_COMMAND_EXIT_APP,10000))
				{
					if(AfxMessageBox("Не удалось остановить программу в КПЛ.\r\nВозможно программа уже остановлена.\r\nПродолжить?",MB_ICONQUESTION|MB_YESNO)==IDNO)	
					{
						pFtpConn->Close();								
						m_InternetSession.Close();
						m_WaitDlg.ShowWindow(SW_HIDE);
						return;
					}										
				}

				pFtpConn->Close();			
				m_InternetSession.Close();	
				m_WaitDlg.ShowWindow(SW_HIDE);
				//reboot
				if(RebootOnTelnet(dlgIP.m_strIP))
					AfxMessageBox("Комманда перезагрузки КПЛ отправлена.",MB_ICONINFORMATION);
				else
					AfxMessageBox("Ошибка при отправке комманды перезагрузки КПЛ");
			}						
		}
	}
	
}

void CKPLConfigDlg::OnTelnet()
{
	// TODO: добавьте свой код обработчика команд
	
	CIPDlg dlgIP;
	if(dlgIP.DoModal()==IDOK)
	{
		if(dlgIP.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не введен IP-адрес КПЛ.");
			return;
		}
		CString strPath;
		strPath = GetEXEDirPath()+"\\CTelnet.exe";
		if(CFileManip::Existence(strPath) == CFileManip::FM_FILE)
		{
			HINSTANCE ret = ShellExecute( NULL,
					NULL,
					strPath.GetBuffer(),
					NULL,
					NULL,
					SW_SHOW);
		}
		else
			AfxMessageBox("Не найден файл:\r\n"+strPath);
	}
}

BOOL CKPLConfigDlg::SendAndCheckServiceCommandFile(CFtpConnection* pFtpConn,CString strFtp,int nCommand,int nTimeout)
{
	if(pFtpConn == NULL)
		return FALSE;

	//TEmp file
	char lpPathBuffer[512];
	DWORD dwRetVal;
	CString strFile="";
	dwRetVal = GetTempPath(512,     // length of the buffer
							lpPathBuffer); // buffer for path 
	if (dwRetVal > 512 || (dwRetVal == 0))															
		strFile="";							
	else
		strFile = lpPathBuffer;	
	strFile+="service.txt";	
	CString strBuf;
	strBuf.Format("%d",nCommand);
	CFile f;
	try
	{
		f.Open(strFile,CFile::modeCreate|CFile::modeWrite);
		f.Write((void*)strBuf.GetBuffer(),strBuf.GetLength());
		f.Close();		
	}
	catch(...)
	{
		return FALSE;
	}
	//loading to FTP
	strFtp+="/logfile/service.txt";
	if(!pFtpConn->PutFile(strFile,strFtp))
	{
		return FALSE;
	}	
	//reading resp
	for(int i = 0; i < nTimeout/100;i++)
	{
		if(!pFtpConn->GetFile(strFtp,strFile,FALSE))
			return FALSE;
		CFile f;		
		strBuf="";
		try
		{
			if(!f.Open(strFile,CFile::modeRead))
				return FALSE;
			CHAR buffer[4096];
			DWORD dwRead=0;			
			do
			{
				dwRead = f.Read(buffer, 4096);
				if(dwRead > 0)
				{
					int nLen = strBuf.GetLength();
					strBuf+=buffer;
					strBuf.Truncate(nLen+dwRead);
				}
			}
			while (dwRead > 0);
			f.Close();
			int nReplyOnCommand = atoi(strBuf);
			if(nReplyOnCommand == nCommand+100)						
				return TRUE;			
		}
		catch(...)
		{
			return FALSE;
		}
		Sleep(100);
	}
	return FALSE;
}

void CKPLConfigDlg::OnCbnSelendokComboversion()
{
	// TODO: добавьте свой код обработчика уведомлений	
	int nVerSelected = m_cmbVersion.GetItemData(m_cmbVersion.GetCurSel());
	if(nVerSelected != ((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_nVersion)
	{
		if(SaveTab(m_MainTab.GetCurSel()))
		{
			if(AfxMessageBox("Выбранная Вами версия настроек КПЛ-32\r\nотличается от текущей.\r\nПродолжить?",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{
				((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_nVersion = nVerSelected;
				ChangeTab(m_MainTab.GetCurSel());
			}
		}						
	}
	UpdateCombo();
}
void CKPLConfigDlg::OnCopy()
{
	m_Grid.CopyToClipboard();
}



void CKPLConfigDlg::OnStopkplsoft()
{
	CIPDlg dlgIP;
	if(dlgIP.DoModal()==IDOK)
	{
		if(dlgIP.m_strIP.IsEmpty())
		{
			AfxMessageBox("Не введен IP-адрес КПЛ.");
			return;
		}
		// TODO: добавьте свой код обработчика команд
		if(AfxMessageBox("Остановить ПО КПЛ?",MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			CWaitCursor wait;
			m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
			m_WaitDlg.SetText("Установка соединения с КПЛ: "+dlgIP.m_strIP);		
			/////////////////////////////ESTABLISHING CONNECTION////////////////////////////////////
			CString strFtpSite;
			CString strServerName;
			CString strObject;
			INTERNET_PORT nPort;
			DWORD dwServiceType;
			CInternetSession  m_InternetSession("KPLApp",1,INTERNET_OPEN_TYPE_DIRECT);						
			CFtpConnection* pFtpConn = NULL;
			
			strFtpSite = "ftp://"+dlgIP.m_strIP+m_strFtpHome;												
			
			if (!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
			{
				m_WaitDlg.ShowWindow(SW_HIDE);
				AfxMessageBox("Неверный формат адреса FTP сервера!");			
				return;
			}

			try
			{					
				pFtpConn = m_InternetSession.GetFtpConnection(strServerName,m_strFtpUser, m_strFtpPassword, nPort);				
			}
			catch (CInternetException* pEx)
			{		
				m_WaitDlg.ShowWindow(SW_HIDE);		
				// catch errors from WinINet
				TCHAR szErr[1024];
				if (pEx->GetErrorMessage(szErr, 1024))
				{
					CString str3,str4;
					str3 = szErr;
					str4 = "Ошибка установки FTP соединения: " + str3;
					AfxMessageBox(str4);
					pEx->Delete();								
				}			
				return;
			}
			m_WaitDlg.ShowWindow(SW_HIDE);

			if(pFtpConn != NULL)
			{			
				
				m_WaitDlg.ShowWindow(SW_SHOWNORMAL);
				m_WaitDlg.SetText("Остановка программы в КПЛ...");

				if(!SendAndCheckServiceCommandFile(pFtpConn,strObject,SERVICE_COMMAND_STOP_SOFT,10000))
				{
					AfxMessageBox("Не удалось остановить программу в КПЛ.\r\nВозможно программа уже остановлена.",MB_ICONINFORMATION);					
					pFtpConn->Close();								
					m_InternetSession.Close();
					m_WaitDlg.ShowWindow(SW_HIDE);					
					return;							
				}				
				pFtpConn->Close();								
				m_InternetSession.Close();
				m_WaitDlg.ShowWindow(SW_HIDE);
				AfxMessageBox("Встроенное ПО КПЛ остановлено.",MB_ICONINFORMATION);
			}						
		}
	}
}
