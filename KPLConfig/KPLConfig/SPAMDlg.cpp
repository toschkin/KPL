// SPAmDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "SPAmDlg.h"
#include "TuConfigTUDlg.h"
#include "AddDiapSPADlg.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAP	WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
// диалоговое окно CSPAmDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CSPAmDlg, CDialog)

CSPAmDlg::CSPAmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSPAmDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("Процесс №%d: SPA (MASTER)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);

}

CSPAmDlg::~CSPAmDlg()
{
}

void CSPAmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridData);	
}


BEGIN_MESSAGE_MAP(CSPAmDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_ADDDIAP, OnAddDiapason)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_WM_GETMINMAXINFO()	
	ON_BN_CLICKED(IDC_BUTTON1, &CSPAmDlg::OnBnClickedButton1)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit1)
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)	
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid1)	
END_MESSAGE_MAP()

afx_msg void CSPAmDlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CSPAmDlg::OnPrint2(void)
{
	m_GridData.Print();
}

afx_msg void CSPAmDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//проверить порты
	//m_Grid.AutoSize();
	m_Grid.Refresh();
}


// обработчики сообщений CSPAmDlg
void CSPAmDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
afx_msg void CSPAmDlg::OnGridEndEdit(NMHDR *pNoTsfyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNoTsfyStruct;

	/*if(pItem->iColumn == 1)
	{
		CString str;
		str = m_GridData.GetItemText(pItem->iRow,0 );					
		if(str == "ТС-32")	
		{
			m_GridData.SetItemText(pItem->iRow,3,"2");		
			m_GridData.SetItemText(pItem->iRow,4,"0");	
			m_GridData.SetItemText(pItem->iRow,5,"80");
		}
		else if(str == "ТУ-32")
		{
			m_GridData.SetItemText(pItem->iRow,3,"1");		
			m_GridData.SetItemText(pItem->iRow,4,"0");	
			m_GridData.SetItemText(pItem->iRow,5,"112");
		}
		else if(str == "ТИ-16")
		{
			m_GridData.SetItemText(pItem->iRow,3,"4");		
			m_GridData.SetItemText(pItem->iRow,4,"0");	
			m_GridData.SetItemText(pItem->iRow,5,"18");
		}
		else if(str == "MTE")
		{			
			m_GridData.SetItemText(pItem->iRow,4,"1004");				
		}
		else if(str == "МТЕ(2-х байтный)")
		{			
			m_GridData.SetItemText(pItem->iRow,4,"1004");				
		}
		if((str == "ТС-32")||(str == "ТИ-16")||(str == "ТУ-32"))
			AfxMessageBox("Внимание!\r\nКоличество объектов информации для внутренних модулей,\r\nкоторый записывается в ОЗУ отличается от количества опрашиваемых регистров.\r\nМодуль ТС-32: регистров 80, инф. объектов - 50\r\nМодуль ТУ-32: регистров 112, инф. объектов - 114\r\nМодуль ТИ-16: регистров 18, инф. объектов - 20",MB_ICONINFORMATION);
		
		m_GridData.Refresh();
	}*/
}
void CSPAmDlg::OnOK()
{
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CSPAmDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnCancel();
}

BOOL CSPAmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Процесс №%d: SPA (MASTER)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(14);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-порт");
	str.Format("%d",m_SPAm.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"Скорость, бод");
	str.Format("%d",m_SPAm.BAUDRATE);
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
	
	m_Grid.SetItemText(3,0,"Количество бит в байте");
	str.Format("%d",m_SPAm.AMOUNTBYTE);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"Количество стоповых бит");
	str.Format("%d",m_SPAm.STOPBITS);
	m_Grid.SetItemText(4,1,str);
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	aOptions.Add("1");
	aOptions.Add("2");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	
	m_Grid.SetItemText(5,0,"Контроль четности");	
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
	aOptions.Add("NONE");
	aOptions.Add("EVEN");
	aOptions.Add("ODD");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_SPAm.PARITY!=1)&&(m_SPAm.PARITY!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_SPAm.PARITY==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_SPAm.PARITY==2)
		m_Grid.SetItemText(5,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(6,0,"Контроль потока");	
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(6, 1);
	aOptions.Add("нет");
	aOptions.Add("аппаратный");
	aOptions.Add("программный");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if((m_SPAm.FLOWCONTROLL!=1)&&(m_SPAm.FLOWCONTROLL!=2))
		m_Grid.SetItemText(6,1,aOptions[0]);
	if(m_SPAm.FLOWCONTROLL==1)
		m_Grid.SetItemText(6,1,aOptions[1]);
	if(m_SPAm.FLOWCONTROLL==2)
		m_Grid.SetItemText(6,1,aOptions[2]);
	aOptions.RemoveAll();

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									
	Item.row = 7;
	Item.col = 0;							
	Item.strText = "Таймаут ответа\r\nподчиненного в квантах\r\n(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);

	//m_Grid.SetItemText(7,0,"Таймаут ответа подчиненного в квантах (1квант = 10 мс.)");
	str.Format("%d",m_SPAm.WAITRESP);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 8;
	Item.col = 0;							
	Item.strText = "Пауза между байтами\r\nв квантах\r\n(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(8,0,"Пауза между байтами в квантах (1квант = 10 мс.)");
	str.Format("%d",m_SPAm.BYTETIME);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 9;
	Item.col = 0;							
	Item.strText = "Интервал между запросами\r\nв квантах\r\n(мс.)";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(9,0,"Интервал между запросами в квантах (1квант = 10 мс.)");
	str.Format("%d",m_SPAm.NEXTMESSAGE);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 10;
	Item.col = 0;							
	Item.strText = "Количество ошибок для\r\nгенерации \"недостоверности\"";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(10,0,"Количество ошибок для генерации \"недостоверности\"");
	str.Format("%d",m_SPAm.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(10,1,str);
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 11;
	Item.col = 0;							
	Item.strText = "Количество устройств,\r\nподключённых к данному каналу";
	m_Grid.SetItem(&Item);
	//m_Grid.SetItemText(17,0,"Количество устройств, подключённых к данному каналу");
	str.Format("%d",m_SPAm.NUMBER_OF_DEVICES);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(12,0,"Резервный порт");
	str.Format("%d",m_SPAm.RES_PORT+1);
	m_Grid.SetItemText(12,1,str);
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(13,0,"Вывод на консоль");	
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(13, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_SPAm.SERVICE==0)
		m_Grid.SetItemText(13,1,aOptions[0]);	
	else
		m_Grid.SetItemText(13,1,aOptions[1]);	
	aOptions.RemoveAll();
	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,60);
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


	m_GridData.SetColumnCount(10);
	//m_GridData.SetFixedColumnCount(1);
	m_GridData.SetRowCount(1);
	m_GridData.SetFixedRowCount(1);	
	m_GridData.EnableTitleTips(0);
	//m_GridData.SetColumnResize(0);
	//m_GridData.EnableSelection(0);
	
//	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_WORDBREAK;									

	Item.row = 0;
	Item.col = 0;							
	Item.strText = "Комментарий";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(0,170);
	
	Item.row = 0;
	Item.col = 1;						
	Item.strText = "Адрес\r\nустройства";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(1,70);

	Item.row = 0;
	Item.col = 2;						
	Item.strText = "Номер\r\nканала";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(2,60);

	Item.row = 0;
	Item.col = 3;						
	Item.strText = "Тип данных";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(3,205);

	Item.row = 0;
	Item.col = 4;						
	Item.strText = "Категория данных";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(4,180);

	Item.row = 0;
	Item.col = 5;						
	Item.strText = "Номер\r\nданных";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(5,55);	
	
	Item.row = 0;
	Item.col = 6;						
	Item.strText = "Нач. адрес\r\nв карте\r\nпамяти\r\nПРОЦЕССА";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(6,80);
	
	Item.row = 0;//
	Item.col = 7;						
	Item.strText = "Тип\r\nстатуса";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(7,50);

	Item.row = 0;//
	Item.col = 8;						
	Item.strText = "Адрес\r\nстатуса";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(8,50);

	Item.row = 0;//
	Item.col = 9;						
	Item.strText = "Маска\r\nстатуса";
	m_GridData.SetItem(&Item);
	m_GridData.SetColumnWidth(9,50);


	UpdateDataGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CSPAmDlg::OnSize(UINT nType, int cx, int cy)
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
		m_Grid.MoveWindow(dx, dx+20, 270/*nCenter - 2*dx*/, r.bottom - 60/*3*dx*/);		
	}

	if (IsWindow(m_GridData.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_GridData.MoveWindow(/*3*dx+nCenter*/280, dx+20, cx-280/*nCenter - 5*dx*/, r.bottom - 60/*3*dx*/);		
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
		pWnd->MoveWindow(cx-100, cy - 26, 99, 23);
	}	
	Invalidate(FALSE);
	// TODO: добавьте свой код обработчика сообщений
}

afx_msg void CSPAmDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CSPAmDlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
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
void CSPAmDlg::UpdateDataGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridData.DeleteNonFixedRows();


	for(int i = 0; i < m_SPAm.m_IndividualStructureSPAArray.GetSize(); i++)
	{
		int nIndex = m_GridData.InsertRow(NULL);

		int nCol = 0;
		
		m_GridData.SetItemText(nIndex,nCol,m_SPAm.m_IndividualStructureSPAArray[i].strCOMMENT);
		nCol++;

		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].SLAVE_ADDRESS);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].CHANNEL_NUM);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		m_GridData.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,nCol);		
		pCell->SetOptions(arrMain_Set_ObjectTypes);		
		pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID);
		if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_SP_NA_1)
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[0]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_SP_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[1]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_SP_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[2]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_DP_NA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[3]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_DP_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[4]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_DP_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[5]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_NA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[6]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[7]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_TD_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[8]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_ND_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[9]);					
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_NB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[10]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[11]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_TE_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[12]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_NC_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[13]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_TC_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[14]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_ME_TF_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[15]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_BO_NA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[16]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_BO_TA_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[17]);
		else if (m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID == M_BO_TB_1)//po srezam
			m_GridData.SetItemText(nIndex,nCol, arrMain_Set_ObjectTypes[18]);			
		else
		{
			str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].TYPE_ID);
			m_GridData.SetItemText(nIndex, nCol,str );		
		}
		nCol++;

		strOptions.Add("1-I-input data");
		strOptions.Add("2-O-output data");	
		strOptions.Add("3-S-setting value");
		strOptions.Add("4-V-variable");
		strOptions.Add("5-M-memory data");
		strOptions.Add("6-C-condition of slave status");
		strOptions.Add("7-F-slave identification");//0		
		strOptions.Add("8-T-time");
		strOptions.Add("9-D-date and time");
		strOptions.Add("10-last events");
		strOptions.Add("11-B-backup events");
		strOptions.Add("12-A-alarms valid");
		m_GridData.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		if((m_SPAm.m_IndividualStructureSPAArray[i].DATA_CAT<1)||(m_SPAm.m_IndividualStructureSPAArray[i].DATA_CAT>12))
		{
			str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].DATA_CAT);
			m_GridData.SetItemText(nIndex,nCol, str);				
		}
		else
			pCell->SetCurSel(m_SPAm.m_IndividualStructureSPAArray[i].DATA_CAT-1);
		strOptions.RemoveAll();		
		nCol++;

		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].DATA_NUM);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].ADDRESS_PMZ);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;
	
		strOptions.Add("нет");
		strOptions.Add("есть");		
		m_GridData.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,nCol);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); 
		if(m_SPAm.m_IndividualStructureSPAArray[i].TYPE_STATUS == 0)
			pCell->SetCurSel(0);
		else
			pCell->SetCurSel(1);			
		strOptions.RemoveAll();		
		nCol++;
		
		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].ADRES_STATUS);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;

		str.Format("%d",m_SPAm.m_IndividualStructureSPAArray[i].MASKA_STATUS);
		m_GridData.SetItemText(nIndex,nCol,str);
		m_GridData.SetCellType(nIndex,nCol,RUNTIME_CLASS(CGridCellNumeric));
		nCol++;
	}

	m_GridData.AutoSizeRows();
	
	m_GridData.AutoSizeRows();
	m_GridData.Refresh();
}
BOOL CSPAmDlg::ProcessSave(void)
{
	for(int row = 1; row < m_GridData.GetRowCount(); row++)
	{
		for(int col = 0; col < m_GridData.GetColumnCount(); col++)
		{
			m_GridData.SetItemBkColour(row,col,RGB(255,255,255));
		}
	}
	// TODO: добавьте специализированный код или вызов базового класса
	CString str;
		
	str = m_Grid.GetItemText(1,1);
	if((atoi(str)<=0)||(atoi(str)>255))
	{
		AfxMessageBox("Неверно задан СОМ-порт!");
		return FALSE;
	}
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.IsPortDuplicated(atoi(str)-1,nProcNum))
	{
		AfxMessageBox("Данный СОМ-порт занят под другую задачу!");
		return FALSE;
	}
	m_SPAm.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_SPAm.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_SPAm.AMOUNTBYTE = atoi(str);
	if((m_SPAm.AMOUNTBYTE > 8)||(m_SPAm.AMOUNTBYTE < 5))
	{
		AfxMessageBox("Количество бит в байте 5..8!");
		return FALSE;	
	}
	str = m_Grid.GetItemText(4,1);
	m_SPAm.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(5,1);
	if(str == "NONE")
		m_SPAm.PARITY = 0;
	if(str == "EVEN")
		m_SPAm.PARITY = 1;
	if(str == "ODD")
		m_SPAm.PARITY = 2;

	str = m_Grid.GetItemText(6,1);
	if(str == "нет")
		m_SPAm.FLOWCONTROLL = 0;
	if(str == "аппаратный")
		m_SPAm.FLOWCONTROLL = 1;
	if(str == "программный")
		m_SPAm.FLOWCONTROLL = 2;

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Таймаут ответа подчиненного в квантах 1..3000!");
		return FALSE;
	}
	m_SPAm.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Пауза между байтами в квантах 1..3000!");
		return FALSE;
	}
	m_SPAm.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Интервал между запросами в миллисекундах 1..3000!");
		return FALSE;
	}
	m_SPAm.NEXTMESSAGE = atoi(str);
	
	str = m_Grid.GetItemText(10,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		AfxMessageBox("Количество ошибок для генерации \"недостоверности\" 0..50!");
		return FALSE;
	}
	m_SPAm.NUMBER_NO_ANSWER = atoi(str);
	
	str = m_Grid.GetItemText(11,1);
	m_SPAm.NUMBER_OF_DEVICES = atoi(str);	

	str = m_Grid.GetItemText(12,1);
	if((atoi(str)<=0)||(atoi(str)>255))
	{
		AfxMessageBox("Неверно задан Резервный СОМ-порт!");
		return FALSE;
	}	
	m_SPAm.RES_PORT = atoi(str);	

	str = m_Grid.GetItemText(13,1);
	if(str=="Нет")
		m_SPAm.SERVICE=0;
	else
		m_SPAm.SERVICE=1;
		
	m_SPAm.m_IndividualStructureSPAArray.RemoveAll();
	int nTotalAmount=0;

	
	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		IndividualStructureSPA is101;	
		int nCol = 0;

		is101.strCOMMENT = m_GridData.GetItemText(i,nCol++);	

		str = m_GridData.GetItemText(i,nCol++);	
		if((atoi(str) < 1)||(atoi(str) > 999))
		{
			AfxMessageBox("Адрес устройства: 1..999!");
			return FALSE;
		}
		is101.SLAVE_ADDRESS = atoi(str);

		str = m_GridData.GetItemText(i,nCol++);	
		if((atoi(str) < 1)||(atoi(str) > 999))
		{
			AfxMessageBox("Номер канала: 1..999!");
			return FALSE;
		}
		is101.CHANNEL_NUM = atoi(str);

		str = m_GridData.GetItemText(i,nCol++);	
		if(str == arrMain_Set_ObjectTypes[0])		
			is101.TYPE_ID = M_SP_NA_1;					
		else if(str == arrMain_Set_ObjectTypes[1])		
			is101.TYPE_ID = M_SP_TA_1;			
		else if(str == arrMain_Set_ObjectTypes[2])		
			is101.TYPE_ID = M_SP_TB_1;			
		else if(str == arrMain_Set_ObjectTypes[3])		
			is101.TYPE_ID = M_DP_NA_1;			
		else if(str == arrMain_Set_ObjectTypes[4])
			is101.TYPE_ID = M_DP_TA_1;			
		else if(str == arrMain_Set_ObjectTypes[5])		
			is101.TYPE_ID = M_DP_TB_1;			
		else if(str == arrMain_Set_ObjectTypes[6])		
			is101.TYPE_ID = M_ME_NA_1;			
		else if(str == arrMain_Set_ObjectTypes[7])		
			is101.TYPE_ID = M_ME_TA_1;			
		else if(str == arrMain_Set_ObjectTypes[8])		
			is101.TYPE_ID = M_ME_TD_1;			
		else if(str == arrMain_Set_ObjectTypes[9])		
			is101.TYPE_ID = M_ME_ND_1;		
		else if(str == arrMain_Set_ObjectTypes[10])		
			is101.TYPE_ID = M_ME_NB_1;			
		else if(str == arrMain_Set_ObjectTypes[11])		
			is101.TYPE_ID = M_ME_TB_1;		
		else if(str == arrMain_Set_ObjectTypes[12])		
			is101.TYPE_ID = M_ME_TE_1;			
		else if(str == arrMain_Set_ObjectTypes[13])		
			is101.TYPE_ID = M_ME_NC_1;			
		else if(str == arrMain_Set_ObjectTypes[14])		
			is101.TYPE_ID = M_ME_TC_1;		
		else if(str == arrMain_Set_ObjectTypes[15])		
			is101.TYPE_ID = M_ME_TF_1;			
		else if(str == arrMain_Set_ObjectTypes[16])		
			is101.TYPE_ID = M_BO_NA_1;		
		else if(str == arrMain_Set_ObjectTypes[17])		
			is101.TYPE_ID = M_BO_TA_1;			
		else if(str == arrMain_Set_ObjectTypes[18])		
			is101.TYPE_ID = M_BO_TB_1;			
		else
		{
			is101.TYPE_ID = atoi(str);
		}		

		CGridCellCombo* pCell = (CGridCellCombo*) m_GridData.GetCell(i,nCol++);				
		is101.DATA_CAT = pCell->GetCurSel()+1;
		
		str = m_GridData.GetItemText(i,nCol++);	
		if((atoi(str) < 1)||(atoi(str) > 65535))
		{
			AfxMessageBox("Номер данных: 1..65535!");
			return FALSE;
		}
		is101.DATA_NUM = atoi(str);		

		nTotalAmount+=1;

		str = m_GridData.GetItemText(i,nCol++);
		is101.ADDRESS_PMZ = atoi(str);

		if((is101.ADDRESS_PMZ < m_nStartPMZAddr)
			||(is101.ADDRESS_PMZ > m_nEndPMZAddr)
			||(is101.ADDRESS_PMZ > m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("Набор инф. объектов в строке %d выходит за пределы карты памяти ПРОЦЕССА: %d..%d!\r\n(строки подсвечены сиреневым цветом)",i,m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			for(int col = 0; col < m_GridData.GetColumnCount(); col++)
			{
				m_GridData.SetItemBkColour(i,col,RGB(255,128,255));
			}
			m_GridData.EnsureVisible(i,0);
			m_GridData.Refresh();
			//return FALSE;
		}	

		pCell = (CGridCellCombo*) m_GridData.GetCell(i,nCol++);				
		is101.TYPE_STATUS = pCell->GetCurSel();
		
		str = m_GridData.GetItemText(i,nCol++);			
		is101.ADRES_STATUS = atoi(str);

		str = m_GridData.GetItemText(i,nCol++);			
		is101.MASKA_STATUS = atoi(str);		
	
		m_SPAm.m_IndividualStructureSPAArray.Add(is101);		
	}

	if(nTotalAmount > m_nEndPMZAddr+1)
	{
		str.Format("%d > %d !",nTotalAmount,m_nEndPMZAddr+1);
		AfxMessageBox("Суммарное кол-во инф. объектов больше выделенного количества для данного процесса:"+str);
		//return FALSE;
	}

	for(int i = 0; i < m_SPAm.m_IndividualStructureSPAArray.GetSize();i++)
	{
		for(int j = 0; j < m_SPAm.m_IndividualStructureSPAArray.GetSize();j++)
		{
			if((m_SPAm.m_IndividualStructureSPAArray[i].ADDRESS_PMZ == m_SPAm.m_IndividualStructureSPAArray[j].ADDRESS_PMZ)
				&&(i!=j))
			{
				str.Format("%d на %d !\r\n(строки подсвечены розовым цветом)",j+1,i+1);
				AfxMessageBox("Наложение инф.объектов:"+str);
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
afx_msg void CSPAmDlg::OnAddDiapason()
{
	CAddDiapSPADlg dlg;
	if(dlg.DoModal() == IDOK)
	{ 
		m_SPAm.m_IndividualStructureSPAArray.Append(dlg.m_arrData);
		UpdateDataGrid();	
	}
}

afx_msg void CSPAmDlg::OnAdd()
{
	ProcessSave();

	CCellID cell = m_GridData.GetFocusCell();
	IndividualStructureSPA mpr;
	if((cell.row > 0)&&(m_SPAm.m_IndividualStructureSPAArray.GetCount() > 1))
	{									
		m_SPAm.m_IndividualStructureSPAArray.InsertAt(cell.row,mpr);		
		UpdateDataGrid();
		return;
	}
	if((cell.row == m_SPAm.m_IndividualStructureSPAArray.GetCount())
		||(cell.row == -1))
	{									
		m_SPAm.m_IndividualStructureSPAArray.Add(mpr);												
		UpdateDataGrid();
		return;
	}	
}
afx_msg void CSPAmDlg::OnDel()
{	
	if(m_GridData.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID pCell = m_GridData.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_SPAm.m_IndividualStructureSPAArray.RemoveAt(pCell.row-1);		
		UpdateDataGrid();
	}
	
}
void CSPAmDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CTuConfigTUDlg dlg;
	dlg.nProcNum=nProcNum;	
	dlg.m_nProcType = 17;
	dlg.m_TuArray.Copy(m_SPAm.m_TuArray);
	dlg.m_nStartPMZAddr=m_nStartPMZAddr;
	dlg.m_nEndPMZAddr=m_nEndPMZAddr;

	if(dlg.DoModal()==IDOK)
	{
		m_SPAm.m_TuArray.Copy(dlg.m_TuArray);
	}
}


BOOL CSPAmDlg::PreTranslateMessage(MSG* pMsg)
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
