// ModbusSDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "ModbusSDlg.h"
#include "AddDiapModbusCalcRetr.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAPASON		WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
#define IDM_COPY1 WM_USER + 422
#define IDM_COPY2 WM_USER + 423

// диалоговое окно CModbusSDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);


IMPLEMENT_DYNAMIC(CModbusSDlg, CDialog)

CModbusSDlg::CModbusSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModbusSDlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("Процесс №%d: MODBUS (SLAVE)",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);

}

CModbusSDlg::~CModbusSDlg()
{
}

void CModbusSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID_RETR, m_GridCalc);	
	DDX_Control(pDX, IDC_CALC_CAP, m_stCalcCap);
}


BEGIN_MESSAGE_MAP(CModbusSDlg, CDialog)
	ON_WM_SIZE()	
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit1)
	ON_COMMAND(IDM_ADD, OnAdd)	
	ON_COMMAND(IDM_DEL, OnDel)	
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)	
	ON_NOTIFY(NM_RCLICK, IDC_GRID_RETR, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid2)
	ON_COMMAND(IDM_ADDDIAPASON, OnAddDiapason)
	ON_COMMAND(IDM_COPY1, OnCopy1)
	ON_COMMAND(IDM_COPY2, OnCopy2)		
END_MESSAGE_MAP()
afx_msg void CModbusSDlg::OnPrint1(void)
{
	m_GridCalc.Print();
}

afx_msg void CModbusSDlg::OnPrint2(void)
{
	m_Grid.Print();
}

afx_msg void CModbusSDlg::OnCopy1(void)
{
	m_GridCalc.CopyToClipboard();
}

afx_msg void CModbusSDlg::OnCopy2(void)
{
	m_Grid.CopyToClipboard();
}


afx_msg void CModbusSDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//проверить порты
	m_Grid.AutoSize();
	m_Grid.Refresh();
}

afx_msg void CModbusSDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить");	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAPASON, "Добавить диапазон...");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить");	
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	
	MenuRButton.AppendMenu(MF_STRING, IDM_COPY1, "Скопировать в буфер обмена...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CModbusSDlg::OnRClickGrid2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();					
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "Печать...");	
	MenuRButton.AppendMenu(MF_STRING, IDM_COPY2, "Скопировать в буфер обмена...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}

// обработчики сообщений CModbusSDlg
void CModbusSDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
void CModbusSDlg::OnOK()
{
	
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}

void CModbusSDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnCancel();
}

BOOL CModbusSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Процесс №%d: MODBUS (SLAVE)",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(17);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-порт");
	str.Format("%d",m_ModbusS.PORT+1);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"Скорость, бод");
	str.Format("%d",m_ModbusS.BAUDRATE);
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
	
	m_Grid.SetItemText(3,0,"Размер байта");
	str.Format("%d",m_ModbusS.AMOUNTBYTE);
	m_Grid.SetItemText(3,1,str);
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"Стоповых бит");
	str.Format("%d",m_ModbusS.STOPBITS);
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
	if((m_ModbusS.PARITY!=1)&&(m_ModbusS.PARITY!=2))
		m_Grid.SetItemText(5,1,aOptions[0]);
	if(m_ModbusS.PARITY==1)
		m_Grid.SetItemText(5,1,aOptions[1]);
	if(m_ModbusS.PARITY==2)
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
	if((m_ModbusS.CONTROLPOTOK!=1)&&(m_ModbusS.CONTROLPOTOK!=2))
		m_Grid.SetItemText(6,1,aOptions[0]);
	if(m_ModbusS.CONTROLPOTOK==1)
		m_Grid.SetItemText(6,1,aOptions[1]);
	if(m_ModbusS.CONTROLPOTOK==2)
		m_Grid.SetItemText(6,1,aOptions[2]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(7,0,"Ожидание запроса,квант (1квант = 10 мс.)");
	str.Format("%d",m_ModbusS.WAITRESP);
	m_Grid.SetItemText(7,1,str);
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(8,0,"Пауза между байтами,квант (1квант = 10 мс.)");
	str.Format("%d",m_ModbusS.BYTETIME);
	m_Grid.SetItemText(8,1,str);
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(9,0,"Адрес устройства");
	str.Format("%d",m_ModbusS.ADRESS_KP);
	m_Grid.SetItemText(9,1,str);
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.SetItemText(10,0,"Режим протокола");	
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(10, 1);
	aOptions.Add("RTU");
	aOptions.Add("ASCII");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	if(m_ModbusS.MODBUS_TYPE==0)
		m_Grid.SetItemText(10,1,aOptions[0]);
	else
		m_Grid.SetItemText(10,1,aOptions[1]);
	aOptions.RemoveAll();

	m_Grid.SetItemText(11,0,"Cтартовый адрес области ТС");
	str.Format("%d",m_ModbusS.START_ADDRESS_TS);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.SetItemText(12,0,"Количество ТС");
	str.Format("%d",m_ModbusS.SIZE_TS);
	m_Grid.SetItemText(12,1,str);
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(13,0,"Старт. адрес битов неисправности ТС");
	str.Format("%d",m_ModbusS.ADDRESS_ALARM_TS);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(14,0,"Cтартовый адрес области ТИ");
	str.Format("%d",m_ModbusS.START_ADDRESS_TI);
	m_Grid.SetItemText(14,1,str);
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.SetItemText(15,0,"Количество ТИ");
	str.Format("%d",m_ModbusS.SIZE_TI);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(16,0,"Старт. адрес битов неисправности ТИ");
	str.Format("%d",m_ModbusS.ADDRESS_ALARM_TI);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,60);
	m_Grid.Refresh();
	
	//ver 11
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion > 10)
	{
		m_GridCalc.SetColumnCount(15);
		//m_GridCalc.SetFixedColumnCount(1);
		m_GridCalc.SetRowCount(1);
		m_GridCalc.SetFixedRowCount(1);	
		m_GridCalc.EnableTitleTips(0);
		//m_GridCalc.SetColumnResize(0);
		m_GridCalc.EnableSelection(0);
		
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.nFormat = DT_CENTER|DT_WORDBREAK;									

		Item.row = 0;
		Item.col = 0;							
		Item.strText = "Комментарий";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(0,80);

		Item.row = 0;
		Item.col = 1;							
		Item.strText = "Тип\r\nретрансляции";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(1,90);

		Item.row = 0;
		Item.col = 2;						
		Item.strText = "Адрес\r\nинф. объекта\r\nисточника";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(2,65);

		Item.row = 0;
		Item.col = 3;						
		Item.strText = "Позиция\r\nбайта\r\nв инф.\r\nобъекте\r\nисточнике\r\n(0..11)";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(3,70);

		Item.row = 0;
		Item.col = 4;						
		Item.strText = "Позиция\r\nбита\r\nв байте\r\nинф.\r\nобъекта\r\nисточника\r\n(0..7)";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(4,70);
			 
		Item.row = 0;
		Item.col = 5;						
		Item.strText = "Кол-во байт\r\nдля\r\nретрансляции";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(5,80);
		
		Item.row = 0;
		Item.col = 6;						
		Item.strText = "Адрес\r\nинф.\r\nобъекта\r\nполучателя";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(6,70);

		Item.row = 0;//DOP_BYTE1
		Item.col = 7;						
		Item.strText = "Позиция байта\r\nв инф. объекте\r\nполучателе\r\n(0..11)";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(7,80);

		Item.row = 0;//DOP_BYTE2
		Item.col = 8;						
		Item.strText =  "Позиция бита\r\nв байте\r\nинф. объекта\r\nполучателя\r\n(0..7)";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(8,80);

		Item.row = 0;//DOP_BYTE3
		Item.col = 9;						
		Item.strText = "Двухбайтное\r\nзначение\r\nсо знаком";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(9,80);

		Item.row = 0;//DOP_BYTE4
		Item.col = 10;						
		Item.strText = "Масштаб";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(10,80);

		Item.row = 0;//ADRES_4B
		Item.col = 11;						
		Item.strText = "Смещение 0";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(11,80);

		Item.row = 0;//
		Item.col = 12;						
		Item.strText = "Минимум.\r\nфиз.вел.";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(12,80);

		Item.row = 0;//
		Item.col = 13;						
		Item.strText = "Максимум\r\nфиз.вел.";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(13,80);

		Item.row = 0;//
		Item.col = 14;						
		Item.strText = "Размах\r\nшкалы";
		m_GridCalc.SetItem(&Item);
		m_GridCalc.SetColumnWidth(14,60);
		
		UpdateCalcGrid();
	}
	else
	{
		m_GridCalc.ShowWindow(SW_HIDE);
		m_stCalcCap.ShowWindow(SW_HIDE);		
	}
	//RessizeControls(1,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
afx_msg void CModbusSDlg::OnAdd()
{
	ProcessSave();

	CalcStructureModbusS mpr;
	m_ModbusS.m_CalcStructureModbusSArray.Add(mpr);

	UpdateCalcGrid();
}
afx_msg void CModbusSDlg::OnDel()
{	
	if(m_GridCalc.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID pCell = m_GridCalc.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_ModbusS.m_CalcStructureModbusSArray.RemoveAt(pCell.row-1);		
		UpdateCalcGrid();
	}
	
}
void CModbusSDlg::UpdateCalcGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridCalc.DeleteNonFixedRows();


	for(int i = 0; i < m_ModbusS.m_CalcStructureModbusSArray.GetSize(); i++)
	{
		int nIndex = m_GridCalc.InsertRow(NULL);		
		
		m_GridCalc.SetItemText(nIndex,0,m_ModbusS.m_CalcStructureModbusSArray[i].strCOMMENT);

		strOptions.Add("битовая");
		strOptions.Add("байтовая");	
		strOptions.Add("2 байта в 1");
		strOptions.Add("4 байта в 1");
		m_GridCalc.SetCellType(nIndex,1, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_GridCalc.GetCell(nIndex,1);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		//str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].PRIBOR);
		if (m_ModbusS.m_CalcStructureModbusSArray[i].TYPE == 1)
			pCell->SetCurSel(0);			
		else if (m_ModbusS.m_CalcStructureModbusSArray[i].TYPE == 2)
			pCell->SetCurSel(1);			
		else if (m_ModbusS.m_CalcStructureModbusSArray[i].TYPE == 4)
			pCell->SetCurSel(2);			
		else if (m_ModbusS.m_CalcStructureModbusSArray[i].TYPE == 6)
			pCell->SetCurSel(3);						
		else
		{
			str.Format("%u",m_ModbusS.m_CalcStructureModbusSArray[i].TYPE);
			m_GridCalc.SetItemText(nIndex,1,str);
		}
		strOptions.RemoveAll();

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].ADDRESS_FROM);
		m_GridCalc.SetItemText(nIndex,2,str);
		m_GridCalc.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].POSITION_BYTE);
		m_GridCalc.SetItemText(nIndex,3,str);
		m_GridCalc.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].POSITION_BIT);
		m_GridCalc.SetItemText(nIndex,4,str);
		m_GridCalc.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].NUMBER_BYTE);
		m_GridCalc.SetItemText(nIndex,5,str);
		m_GridCalc.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].ADDRESS_TOO);
		m_GridCalc.SetItemText(nIndex,6,str);
		m_GridCalc.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellNumeric));
		
		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].POSITION_BYTE_TOO);
		m_GridCalc.SetItemText(nIndex,7,str);
		m_GridCalc.SetCellType(nIndex,7,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].POSITION_BIT_TOO);
		m_GridCalc.SetItemText(nIndex,8,str);
		m_GridCalc.SetCellType(nIndex,8,RUNTIME_CLASS(CGridCellNumeric));

		m_GridCalc.SetCellType(nIndex,9,RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridCalc.GetCell(nIndex, 9);
		strOptions.Add("Нет");	
		strOptions.Add("Да");
		pCell->SetOptions(strOptions);		
		if(m_ModbusS.m_CalcStructureModbusSArray[i].DOPKODE_YES_NO == 1)
			pCell->SetCurSel(1);
		else
			pCell->SetCurSel(0);
		strOptions.RemoveAll();

		/*m_GridCalc.SetCellType(nIndex,9,RUNTIME_CLASS(CGridCellCheck));
		CGridCellCheck* pCell2 = (CGridCellCheck*) m_GridCalc.GetCell(nIndex, 9);
		pCell2->SetStrings("Да","Нет");		
		if(m_ModbusS.m_CalcStructureModbusSArray[i].DOPKODE_YES_NO == 1)
			pCell2->SetCheck(TRUE);
		else
			pCell2->SetCheck(FALSE);*/

		str.Format("%f",m_ModbusS.m_CalcStructureModbusSArray[i].CENA_SHKALI);
		m_GridCalc.SetItemText(nIndex,10,str);

		str.Format("%f",m_ModbusS.m_CalcStructureModbusSArray[i].SMESHENIE);
		m_GridCalc.SetItemText(nIndex,11,str);

		str.Format("%f",m_ModbusS.m_CalcStructureModbusSArray[i].MIN_FIZ);
		m_GridCalc.SetItemText(nIndex,12,str);

		str.Format("%f",m_ModbusS.m_CalcStructureModbusSArray[i].MAX_FIZ);
		m_GridCalc.SetItemText(nIndex,13,str);

		str.Format("%d",m_ModbusS.m_CalcStructureModbusSArray[i].MAX_SHKALA_FIZ);
		m_GridCalc.SetItemText(nIndex,14,str);
		m_GridCalc.SetCellType(nIndex,14,RUNTIME_CLASS(CGridCellNumeric));
	}

	m_GridCalc.AutoSizeRows();
	m_GridCalc.Refresh();
}
void CModbusSDlg::RessizeControls(int cx,int cy)
{
	long nCentery = (long)(cy / 2);
	long nCenter = (long)(cx / 2);	
	
	int dx = 5;
	//if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_nVersion > 10)
	{
		if (IsWindow(m_Grid.m_hWnd))
		{
			CRect r;
			GetClientRect(&r);
			m_Grid.MoveWindow(dx, dx+20, 320/*nCenter - 2*dx*/, r.bottom - 60/*3*dx*/);		
		}

		if (IsWindow(m_GridCalc.m_hWnd))
		{
			CRect r;
			GetClientRect(&r);
			m_GridCalc.MoveWindow(/*3*dx+nCenter*/340, dx+20, cx-350/*nCenter - 5*dx*/, r.bottom - 60/*3*dx*/);		
		}
	}
	/*else
	{
		if (IsWindow(m_Grid.m_hWnd))
		{
			CRect r;
			GetClientRect(&r);
			m_Grid.MoveWindow(2*dx, 30, r.right - r.left - 4*dx, r.bottom - r.top - 70 - dx*2, TRUE);		
		}
	}*/

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

	//Invalidate(FALSE);
}
void CModbusSDlg::OnSize(UINT nType, int cx, int cy)
{	
	CDialog::OnSize(nType, cx, cy);

	RessizeControls(cx, cy);
	// TODO: добавьте свой код обработчика сообщений
}
BOOL CModbusSDlg::ProcessSave(void)
{
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

	m_ModbusS.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_ModbusS.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_ModbusS.AMOUNTBYTE = atoi(str);
	if((m_ModbusS.AMOUNTBYTE > 8)||(m_ModbusS.AMOUNTBYTE < 5))
	{
		AfxMessageBox("Количество бит в байте 5..8!");
		return FALSE;	
	}
	str = m_Grid.GetItemText(4,1);
	m_ModbusS.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(5,1);
	if(str == "NONE")
		m_ModbusS.PARITY = 0;
	if(str == "EVEN")
		m_ModbusS.PARITY = 1;
	if(str == "ODD")
		m_ModbusS.PARITY = 2;

	str = m_Grid.GetItemText(6,1);
	if(str == "нет")
		m_ModbusS.CONTROLPOTOK = 0;
	if(str == "аппаратный")
		m_ModbusS.CONTROLPOTOK = 1;
	if(str == "программный")
		m_ModbusS.CONTROLPOTOK = 2;

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Таймаут ответа подчиненного в квантах 1..3000!");
		return FALSE;
	}
	m_ModbusS.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		AfxMessageBox("Пауза между байтами в квантах 1..3000!");
		return FALSE;
	}
	m_ModbusS.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<=0)||(atoi(str)>247))
	{
		AfxMessageBox("Адрес устройства 1..247!");
		return FALSE;
	}
	m_ModbusS.ADRESS_KP = atoi(str);
		
	str = m_Grid.GetItemText(10,1);
	if(str == "RTU")
		m_ModbusS.MODBUS_TYPE = 0;
	if(str == "ASCII")
		m_ModbusS.MODBUS_TYPE = 1;

	str = m_Grid.GetItemText(11,1);	
	m_ModbusS.START_ADDRESS_TS = atoi(str);

	str = m_Grid.GetItemText(12,1);	
	m_ModbusS.SIZE_TS = atoi(str);

	str = m_Grid.GetItemText(13,1);	
	m_ModbusS.ADDRESS_ALARM_TS = atoi(str);

	str = m_Grid.GetItemText(14,1);	
	m_ModbusS.START_ADDRESS_TI = atoi(str);

	str = m_Grid.GetItemText(15,1);	
	m_ModbusS.SIZE_TI = atoi(str);

	str = m_Grid.GetItemText(16,1);	
	m_ModbusS.ADDRESS_ALARM_TI = atoi(str);
	
	//ver 11
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_nVersion > 10)
	{
		m_ModbusS.m_CalcStructureModbusSArray.RemoveAll();

		for(int i = 1; i < m_GridCalc.GetRowCount(); i++)
		{
			CalcStructureModbusS is101;	

			is101.strCOMMENT = m_GridCalc.GetItemText(i,0 );	

			str = m_GridCalc.GetItemText(i,1 );					
			if(str == "битовая")		
				is101.TYPE = 1;					
			else if(str == "байтовая")
				is101.TYPE = 2;	
			else if(str == "2 байта в 1")
				is101.TYPE = 4;	
			else if(str == "4 байта в 1")
				is101.TYPE = 6;	
			else
			{
				str = m_GridCalc.GetItemText(i,1);
				is101.TYPE = atoi(str);
			}

			str = m_GridCalc.GetItemText(i,2);
			is101.ADDRESS_FROM = atoi(str);

			str = m_GridCalc.GetItemText(i,3);
			is101.POSITION_BYTE = atoi(str);
			if((is101.POSITION_BYTE>11)||(is101.POSITION_BYTE<0))
			{
				AfxMessageBox("Позиция байта в информационном объекте с которого выполняется ретрансляция: 0..11!");
				return FALSE;
			}	

			str = m_GridCalc.GetItemText(i,4);
			is101.POSITION_BIT = atoi(str);
			if(((is101.POSITION_BIT>7)||(is101.POSITION_BIT<0))&&(is101.TYPE == 1))
			{
				AfxMessageBox("Позиция бита в байте инф. объекта источника: 0..7!");
				return FALSE;
			}

			str = m_GridCalc.GetItemText(i,5);
			is101.NUMBER_BYTE = atoi(str);

			str = m_GridCalc.GetItemText(i,6);
			is101.ADDRESS_TOO = atoi(str);

			str = m_GridCalc.GetItemText(i,7);
			is101.POSITION_BYTE_TOO = atoi(str);			
			if(is101.POSITION_BYTE_TOO + is101.NUMBER_BYTE > 12)
			{
				AfxMessageBox("(POSITION_BYTE_TOO+NUMBER_BYTE)<=12");
				return FALSE;
			}

			str = m_GridCalc.GetItemText(i,8);
			is101.POSITION_BIT_TOO = atoi(str);
			if(((is101.POSITION_BIT_TOO>7)||(is101.POSITION_BIT_TOO<0))&&(is101.TYPE == 1))
			{
				AfxMessageBox("Позиция бита в байте инф. объекта получателя: 0..7!");
				return FALSE;
			}

			str = m_GridCalc.GetItemText(i,9 );					
			if(str == "Да")		
				is101.DOPKODE_YES_NO = 1;					
			else
				is101.DOPKODE_YES_NO = 0;	

			str = m_GridCalc.GetItemText(i,10);
			is101.CENA_SHKALI = atof(str);

			str = m_GridCalc.GetItemText(i,11);
			is101.SMESHENIE = atof(str);

			str = m_GridCalc.GetItemText(i,12);
			is101.MIN_FIZ = atof(str);

			str = m_GridCalc.GetItemText(i,13);
			is101.MAX_FIZ = atof(str);
				
			str = m_GridCalc.GetItemText(i,14);
			is101.MAX_SHKALA_FIZ = atoi(str);			
			if((is101.MAX_SHKALA_FIZ>255)||(is101.MAX_SHKALA_FIZ<0))
			{
				AfxMessageBox("Размах шкалы: 0..255");
				return FALSE;
			}
			
			m_ModbusS.m_CalcStructureModbusSArray.Add(is101);		
			
		}
	}
	
	return TRUE;
}
BOOL CModbusSDlg::PreTranslateMessage(MSG* pMsg)
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
afx_msg void CModbusSDlg::OnAddDiapason()
{
	if(!ProcessSave())
		return;

	CAddDiapModbusCalcRetr dlg;	
	dlg.m_ModbusS = m_ModbusS;
	if(dlg.DoModal()==IDOK)
	{
		m_ModbusS = dlg.m_ModbusS;
		UpdateCalcGrid();
	}
}	
