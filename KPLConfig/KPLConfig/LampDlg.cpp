// LampDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "LampDlg.h"
#include "AddDiapTSIndicDlg.h"
#include "AddDiapTIIndicDlg.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAP	WM_USER + 402

#define IDM_PRINT1 WM_USER + 420

// диалоговое окно CLampDlg

IMPLEMENT_DYNAMIC(CLampDlg, CDialog)

CLampDlg::CLampDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLampDlg::IDD, pParent)
{
	m_byTypeInd = IND_TS;
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
}

CLampDlg::~CLampDlg()
{
}

void CLampDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);	
}


BEGIN_MESSAGE_MAP(CLampDlg, CDialog)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_COMMAND(IDM_PRINT1, OnPrint)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_ADDDIAP, OnAddDiap)
	ON_COMMAND(IDM_DEL, OnDel)
END_MESSAGE_MAP()


afx_msg void CLampDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить");	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить");	
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	
	
	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CLampDlg::OnPrint(void)
{
	m_Grid.Print();
}
// обработчики сообщений CLampDlg

void CLampDlg::OnOK()
{
	CDialog::OnOK();
}

BOOL CLampDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_byTypeInd==IND_TS)
		strTitle="Индикаторы ТС";
	else
		strTitle="Индикаторы ТИ";
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	if(m_byTypeInd==IND_TS)
	{
		m_Grid.SetColumnCount(12);
		m_Grid.SetFixedColumnCount(1);	
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetItemText(0,0,"№ п.п.");
		m_Grid.SetItemText(0,1,"Тип индикатора");
		m_Grid.SetItemText(0,2,"Тип вывода на ДЩ");
		m_Grid.SetItemText(0,3,"Адрес ПКТС");	
		m_Grid.SetItemText(0,4,"№ Индикатора");	
		m_Grid.SetItemText(0,5,"Адрес и.о. в ПМЗ");	
		m_Grid.SetItemText(0,6,"№ Байта и.о.");	
		m_Grid.SetItemText(0,7,"Бит");	
		m_Grid.SetItemText(0,8,"Цвет ВКЛ.");	
		m_Grid.SetItemText(0,9,"Цвет ОТКЛ.");	
		m_Grid.SetItemText(0,10,"Значение ВКЛ.");	
		m_Grid.SetItemText(0,11,"Комментарий");	
	}
	else
	{
		m_Grid.SetColumnCount(13);
		m_Grid.SetFixedColumnCount(1);	
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetItemText(0,0,"№ п.п.");
		m_Grid.SetItemText(0,1,"Тип индикатора");	
		m_Grid.SetItemText(0,2,"Адрес ПКТИ");	
		m_Grid.SetItemText(0,3,"№ Индикатора");	
		m_Grid.SetItemText(0,4,"Адрес и.о. в ПМЗ");	
		m_Grid.SetItemText(0,5,"Знак +");	
		m_Grid.SetItemText(0,6,"Масштаб");	
		m_Grid.SetItemText(0,7,"Смещение 0");	
		m_Grid.SetItemText(0,8,"Мин. физ.вел.");	
		m_Grid.SetItemText(0,9,"Макс. физ.вел.");	
		m_Grid.SetItemText(0,10,"Формат знач.");	
		m_Grid.SetItemText(0,11,"Десят.точка");
		m_Grid.SetItemText(0,12,"Комментарий");	
	}
	DrawGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CLampDlg::DrawRowTS(int nRow)
{
	CString str;
	CStringArray aOptions;
	str.Format("%d",nRow);
	m_Grid.SetItemText(nRow,0,str);			
	
	BYTE nIndType = m_Mapboard.m_MacrosBUTSArray[nRow-1].TYPE & 0x0F;			
	BYTE nMapboardType = (m_Mapboard.m_MacrosBUTSArray[nRow-1].TYPE & 0xF0)>> 4;			
				
	switch(nIndType)
	{
		case 2: 
			{
				str = "единичный";
				break;
			}
		case 3:
			{
				str = "матричный";
				break;
			}
		default:
			str = "";
	}			
	m_Grid.SetItemText(nRow,1,str);
	m_Grid.SetCellType(nRow,1, RUNTIME_CLASS(CGridCellCombo));
	CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 1);
	aOptions.Add("единичный");
	aOptions.Add("матричный");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();

	
	m_Grid.SetCellType(nRow,2, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 2);
	aOptions.Add("светлый");
	aOptions.Add("тёмный");
	aOptions.Add("полутёмный");
	aOptions.Add("ПНУ");
	aOptions.Add("инв. полутёмный");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(nMapboardType);			
	aOptions.RemoveAll();

	str.Format("%d",m_Mapboard.m_MacrosBUTSArray[nRow-1].ADDRESS_BUTS);
	m_Grid.SetItemText(nRow,3,str);
	m_Grid.SetCellType(nRow,3, RUNTIME_CLASS(CGridCellNumeric));

	str.Format("%d",m_Mapboard.m_MacrosBUTSArray[nRow-1].NUMBER_POSITION);
	m_Grid.SetItemText(nRow,4,str);
	m_Grid.SetCellType(nRow,4, RUNTIME_CLASS(CGridCellNumeric));

	str.Format("%d",m_Mapboard.m_MacrosBUTSArray[nRow-1].ADDRESS_PMZ);
	m_Grid.SetItemText(nRow,5,str);
	m_Grid.SetCellType(nRow,5, RUNTIME_CLASS(CGridCellNumeric));

	str.Format("%d",m_Mapboard.m_MacrosBUTSArray[nRow-1].POS_BYTE);
	m_Grid.SetItemText(nRow,6,str);
	m_Grid.SetCellType(nRow,6, RUNTIME_CLASS(CGridCellNumeric));

	str.Format("%d",m_Mapboard.m_MacrosBUTSArray[nRow-1].POS_BIT);
	m_Grid.SetItemText(nRow,7,str);
	m_Grid.SetCellType(nRow,7, RUNTIME_CLASS(CGridCellNumeric));
	
	m_Grid.SetCellType(nRow,8, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 8);
	aOptions.Add("потушен");
	aOptions.Add("зелёный");
	aOptions.Add("красный");
	aOptions.Add("оранжевый");
	aOptions.Add("красн.-зел.");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Mapboard.m_MacrosBUTSArray[nRow-1].COLOR_ON);			
	aOptions.RemoveAll();

	m_Grid.SetCellType(nRow,9, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 9);
	aOptions.Add("потушен");
	aOptions.Add("зелёный");
	aOptions.Add("красный");
	aOptions.Add("оранжевый");
	aOptions.Add("красн.-зел.");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Mapboard.m_MacrosBUTSArray[nRow-1].COLOR_OFF);			
	aOptions.RemoveAll();

	str.Format("%d",m_Mapboard.m_MacrosBUTSArray[nRow-1].ON_VALUE);
	m_Grid.SetItemText(nRow,10,str);
	m_Grid.SetCellType(nRow,10, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(nRow,11,m_Mapboard.m_MacrosBUTSArray[nRow-1].strCOMMENT);
}
void CLampDlg::DrawRowTI(int nRow)
{
	CString str;
	CStringArray aOptions;
	str.Format("%d",nRow);
	m_Grid.SetItemText(nRow,0,str);			
	
	BYTE nIndType = m_Mapboard.m_MacrosBUIArray[nRow-1].TYPE;			
					
	switch(nIndType)
	{
		case 4: 
			{
				str = "сегментный";
				break;
			}		
		default:
			str = "";
	}			
	m_Grid.SetItemText(nRow,1,str);
	m_Grid.SetCellType(nRow,1, RUNTIME_CLASS(CGridCellCombo));
	CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 1);
	aOptions.Add("сегментный");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	aOptions.RemoveAll();
	

	str.Format("%d",m_Mapboard.m_MacrosBUIArray[nRow-1].ADDRESS_BUI);
	m_Grid.SetItemText(nRow,2,str);
	m_Grid.SetCellType(nRow,2, RUNTIME_CLASS(CGridCellNumeric));

	str.Format("%d",m_Mapboard.m_MacrosBUIArray[nRow-1].NUMBER_POSITION);
	m_Grid.SetItemText(nRow,3,str);
	m_Grid.SetCellType(nRow,3, RUNTIME_CLASS(CGridCellNumeric));

	str.Format("%d",m_Mapboard.m_MacrosBUIArray[nRow-1].ADDRESS_PMZ);
	m_Grid.SetItemText(nRow,4,str);
	m_Grid.SetCellType(nRow,4, RUNTIME_CLASS(CGridCellNumeric));

	CArray<DWORD,DWORD> arrData;
	int nCurIndex = 0;
	
	aOptions.Add("_");arrData.Add(0x3A); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;	
	aOptions.Add("/\\");arrData.Add(0x3C); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("\\/");arrData.Add(0x3D); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add(">");arrData.Add(0x3E); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("<");arrData.Add(0x3F); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;	
	aOptions.Add("+");arrData.Add(0x5C); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("-");arrData.Add(0x5D); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;				
	aOptions.Add("A");arrData.Add(0x41); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("B");arrData.Add(0x42); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("C");arrData.Add(0x43); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("D");arrData.Add(0x44); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("E");arrData.Add(0x45); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("F");arrData.Add(0x46); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("G");arrData.Add(0x47); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("H");arrData.Add(0x48); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("I");arrData.Add(0x49); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("J");arrData.Add(0x4A); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("K");arrData.Add(0x4B); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("L");arrData.Add(0x4C); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("M");arrData.Add(0x4D); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("N");arrData.Add(0x4E); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("O");arrData.Add(0x4F); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("P");arrData.Add(0x50); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Q");arrData.Add(0x51); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("R");arrData.Add(0x52); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("S");arrData.Add(0x53); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("T");arrData.Add(0x54); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("U");arrData.Add(0x55); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("V");arrData.Add(0x56); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("W");arrData.Add(0x57); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("X");arrData.Add(0x58); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Y");arrData.Add(0x59); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Z");arrData.Add(0x5A); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;				
	aOptions.Add("А");arrData.Add(0x80); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Б");arrData.Add(0x81); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("В");arrData.Add(0x82); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Г");arrData.Add(0x83); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Д");arrData.Add(0x84); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Е");arrData.Add(0x85); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ж");arrData.Add(0x86); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("З");arrData.Add(0x87); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("И");arrData.Add(0x88); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Й");arrData.Add(0x89); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("К");arrData.Add(0x8A); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Л");arrData.Add(0x8B); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("М");arrData.Add(0x8C); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Н");arrData.Add(0x8D); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("О");arrData.Add(0x8E); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("П");arrData.Add(0x8F); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Р");arrData.Add(0x90); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("С");arrData.Add(0x91); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Т");arrData.Add(0x92); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("У");arrData.Add(0x93); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ф");arrData.Add(0x94); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Х");arrData.Add(0x95); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ц");arrData.Add(0x96); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ч");arrData.Add(0x97); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ш");arrData.Add(0x98); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Щ");arrData.Add(0x99); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ъ");arrData.Add(0x9A); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ы");arrData.Add(0x9B); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ь");arrData.Add(0x9C); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Э");arrData.Add(0x9D); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Ю");arrData.Add(0x9E); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	aOptions.Add("Я");arrData.Add(0x9F); if(m_Mapboard.m_MacrosBUIArray[nRow-1].ZNAK == arrData[arrData.GetSize()-1])nCurIndex=arrData.GetSize()-1;
	
	m_Grid.SetCellType(nRow,5, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 5);	
	pCell->SetOptions(aOptions);
	pCell->SetItemDataArray(arrData);
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(nCurIndex);			
	aOptions.RemoveAll();

	str.Format("%f",m_Mapboard.m_MacrosBUIArray[nRow-1].CENA_SHKALI);
	m_Grid.SetItemText(nRow,6,str);

	str.Format("%f",m_Mapboard.m_MacrosBUIArray[nRow-1].SMESHENIE);
	m_Grid.SetItemText(nRow,7,str);

	str.Format("%f",m_Mapboard.m_MacrosBUIArray[nRow-1].MIN);
	m_Grid.SetItemText(nRow,8,str);

	str.Format("%f",m_Mapboard.m_MacrosBUIArray[nRow-1].MAX);
	m_Grid.SetItemText(nRow,9,str);
	
	m_Grid.SetCellType(nRow,10, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 10);
	aOptions.Add("прямой код");
	aOptions.Add("дополн. код");
	aOptions.Add("КОМПАС");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	pCell->SetCurSel(m_Mapboard.m_MacrosBUIArray[nRow-1].DOP_FLAG & 0x03);			
	aOptions.RemoveAll();

	m_Grid.SetCellType(nRow,11, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(nRow, 11);
	aOptions.Add("нет");
	aOptions.Add("есть");		
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	if(m_Mapboard.m_MacrosBUIArray[nRow-1].DOP_FLAG & 0x04)
		pCell->SetCurSel(1);			
	else		
		pCell->SetCurSel(0);			
	aOptions.RemoveAll();

	m_Grid.SetItemText(nRow,12,m_Mapboard.m_MacrosBUIArray[nRow-1].strCOMMENT);
}
void CLampDlg::DrawGrid(void)
{
	m_Grid.DeleteNonFixedRows();	
	if(m_byTypeInd==IND_TS)
	{
		m_Grid.SetRowCount(m_Mapboard.m_MacrosBUTSArray.GetCount()+1);
				
		for(int nRow = 1; nRow < m_Grid.GetRowCount();nRow++)
		{
			DrawRowTS(nRow);
		}	
	}
	else//IND_TI
	{
		m_Grid.SetRowCount(m_Mapboard.m_MacrosBUIArray.GetCount()+1);
				
		for(int nRow = 1; nRow < m_Grid.GetRowCount();nRow++)
		{
			DrawRowTI(nRow);
		}
	}
	m_Grid.AutoSize();
	m_Grid.Refresh();
}
afx_msg void CLampDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{	
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	 	
	if(m_byTypeInd==IND_TS)	
	{
		switch(pItem->iColumn)
		{
			case 1:
				{
					if(m_Grid.GetItemText(pItem->iRow,pItem->iColumn) == "единичный")					
						m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].TYPE = (m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].TYPE & 0xF0)|0x02;					
					else
						m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].TYPE = (m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].TYPE & 0xF0)|0x03;
					break;
				}
			case 2:
				{
					CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, pItem->iColumn);
					BYTE nMapboardType = 0;
					nMapboardType = (BYTE)pCell->GetCurSel()<<4;					
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].TYPE = (m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].TYPE & 0x0F)|nMapboardType;					
					break;
				}
			case 3:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].ADDRESS_BUTS = (BYTE)atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 4:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].NUMBER_POSITION = (BYTE)atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 5:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].ADDRESS_PMZ = atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 6:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].POS_BYTE = (BYTE)atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 7:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].POS_BIT = (BYTE)atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}	
			case 8:
				{
					CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, pItem->iColumn);
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].COLOR_ON = pCell->GetCurSel();
					break;
				}
			case 9:
				{
					CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, pItem->iColumn);
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].COLOR_OFF = pCell->GetCurSel();
					break;
				}	
			case 10:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].ON_VALUE = atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 11:
				{															
					m_Mapboard.m_MacrosBUTSArray[pItem->iRow-1].strCOMMENT = m_Grid.GetItemText(pItem->iRow,pItem->iColumn);					
					break;
				}
		}
	}
	else//IND_TI
	{
		switch(pItem->iColumn)
		{
			case 1:
				{
					if(m_Grid.GetItemText(pItem->iRow,pItem->iColumn) == "сегментный")					
						m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].TYPE = 4;					
					else
						m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].TYPE = 4;//??????
					break;
				}			
			case 2:
				{															
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].ADDRESS_BUI = (BYTE)atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 3:
				{															
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].NUMBER_POSITION = (BYTE)atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 4:
				{															
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].ADDRESS_PMZ = atoi(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}			
			case 5:
				{
					CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, pItem->iColumn);
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].ZNAK = pCell->GetItemData(pCell->GetCurSel());
					break;
				}
			case 6:
				{
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].CENA_SHKALI = atof(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}	
			case 7:
				{
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].SMESHENIE = atof(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}	
			case 8:
				{
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].MIN = atof(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 9:
				{
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].MAX = atof(m_Grid.GetItemText(pItem->iRow,pItem->iColumn));					
					break;
				}
			case 10:
				{
					CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, pItem->iColumn);					
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].DOP_FLAG = (m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].DOP_FLAG & 0xFC)|pCell->GetCurSel();					
					break;
				}
			case 11:
				{
					CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(pItem->iRow, pItem->iColumn);					
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].DOP_FLAG = (m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].DOP_FLAG & 0xFB)|(pCell->GetCurSel()<<2);
					break;
				}	
			case 12:
				{															
					m_Mapboard.m_MacrosBUIArray[pItem->iRow-1].strCOMMENT = m_Grid.GetItemText(pItem->iRow,pItem->iColumn);					
					break;
				}
		}	
	}
	m_Grid.AutoSize();
	m_Grid.Refresh();
}
void CLampDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}

void CLampDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
	long nCentery = (long)(cy / 2);
	long nCenter = (long)(cx / 2);

	int dx = 5;
	//m_Grid.GetClientRect
	if (IsWindow(m_Grid.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_Grid.MoveWindow(2*dx, 10, r.right - r.left - 4*dx, r.bottom - r.top - 70 - dx*2, TRUE);		
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

	Invalidate(FALSE);
}
afx_msg void CLampDlg::OnAddDiap()
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
	CCellID cell = m_Grid.GetFocusCell();	
	//AddDiapTSIndicDlg
	if(m_byTypeInd==IND_TS)
	{
		CAddDiapTSIndicDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			if((cell.row == m_Grid.GetRowCount()-1)||(cell.row < 1))
				m_Mapboard.m_MacrosBUTSArray.Append(dlg.m_MacrosBUTSArray);
			else
				m_Mapboard.m_MacrosBUTSArray.InsertAt(cell.row,&dlg.m_MacrosBUTSArray);
		}
	}
	else//IND_TI
	{
		CAddDiapTIIndicDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			if((cell.row == m_Grid.GetRowCount()-1)||(cell.row < 1))
				m_Mapboard.m_MacrosBUIArray.Append(dlg.m_MacrosBUIArray);
			else
				m_Mapboard.m_MacrosBUIArray.InsertAt(cell.row,&dlg.m_MacrosBUIArray);
		}
		
	}
	DrawGrid();
}
afx_msg void CLampDlg::OnAdd()
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
	CCellID cell = m_Grid.GetFocusCell();	
	if(m_byTypeInd==IND_TS)
	{
		MacrosBUTS st;
		if((cell.row == m_Grid.GetRowCount()-1)||(cell.row < 1))
			m_Mapboard.m_MacrosBUTSArray.Add(st);
		else
			m_Mapboard.m_MacrosBUTSArray.InsertAt(cell.row,st);
					
	}
	else//IND_TI
	{
		MacrosBUI st;
		if((cell.row == m_Grid.GetRowCount()-1)||(cell.row < 1))
			m_Mapboard.m_MacrosBUIArray.Add(st);
		else
			m_Mapboard.m_MacrosBUIArray.InsertAt(cell.row,st);
	}
	
	DrawGrid();
}
afx_msg void CLampDlg::OnDel()
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
	if(m_byTypeInd==IND_TS)
	{
		for(int j = 0; j < arGrigIndexes.GetSize();j++)
		{				
			m_Grid.DeleteRow(arGrigIndexes[j]);				
			m_Mapboard.m_MacrosBUTSArray.RemoveAt(arGrigIndexes[j]-1);				
			for(int v = j+1; v < arGrigIndexes.GetSize();v++)
			{
				arGrigIndexes[v]--;
			}
		}
			
	}
	else//IND_TI
	{
		for(int j = 0; j < arGrigIndexes.GetSize();j++)
		{				
			m_Grid.DeleteRow(arGrigIndexes[j]);				
			m_Mapboard.m_MacrosBUIArray.RemoveAt(arGrigIndexes[j]-1);				
			for(int v = j+1; v < arGrigIndexes.GetSize();v++)
			{
				arGrigIndexes[v]--;
			}
		}
	}
	if(arGrigIndexes.GetSize()>0)
	{
		DrawGrid();	
	}
}