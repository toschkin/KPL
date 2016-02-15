// GranitDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "GranitDlg.h"
#include "TUGranitDlg.h"


// диалоговое окно CGranitDlg
#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
//#define IDM_ADDDIAP	WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
// диалоговое окно CModbusMDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);

IMPLEMENT_DYNAMIC(CGranitDlg, CDialog)

CGranitDlg::CGranitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGranitDlg::IDD, pParent)
{		
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
	m_nChannelNumber=0;
}

CGranitDlg::~CGranitDlg()
{
}

void CGranitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridData);	
}


BEGIN_MESSAGE_MAP(CGranitDlg, CDialog)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()	
	ON_COMMAND(IDM_ADD, OnAdd)
	//ON_COMMAND(IDM_ADDDIAP, OnAddDiapason)
	ON_COMMAND(IDM_DEL, OnDel)		
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2,OnGridEndEdit1)
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)	
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid1)	
	ON_BN_CLICKED(IDC_BUTTON1, &CGranitDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// обработчики сообщений CGranitDlg
afx_msg void CGranitDlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CGranitDlg::OnPrint2(void)
{
	m_GridData.Print();
}

afx_msg void CGranitDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//проверить порты
	m_Grid.AutoSizeColumns();
	m_Grid.Refresh();
}
afx_msg void CGranitDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//пока пусто
	m_GridData.AutoSizeColumns();
	m_GridData.Refresh();
}

void CGranitDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}


BOOL CGranitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Канал №%d: Гранит",m_nChannelNumber);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(20);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"Тип протокола");		
	m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellCombo));
	CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(1, 1);
	aOptions.Add("запрос по таймеру");
	aOptions.Add("режим \"подслушки\"");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.TYPE-1);
	aOptions.RemoveAll();

	m_Grid.SetItemText(2,0,"Меандр");
	str.Format("%d",m_Granit.MEANDER_VALUE);
	m_Grid.SetItemText(2,1,str);
	m_Grid.SetCellType(2, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(3,0,"Инверсия запроса");		
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(3, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.INVERT_REQUEST);
	aOptions.RemoveAll();

	m_Grid.SetItemText(4,0,"Инверсия ответа");		
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.INVERT_RESPONSE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(5,0,"Подтверждение пакета");		
	m_Grid.SetCellType(5,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.SEND_CONFIRM);
	aOptions.RemoveAll();

	m_Grid.SetItemText(6,0,"Запрос после меандра");		
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(6, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.IC_ON_MEANDER);
	aOptions.RemoveAll();

	m_Grid.SetItemText(7,0,"Меандр перед посылкой");		
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(7, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.ADD_MEANDER_BEFORE_REQ);
	aOptions.RemoveAll();

	m_Grid.SetItemText(8,0,"Опрос ТС");		
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(8, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.C_IC_TS_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(9,0,"Опрос ТИТ");		
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(9, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.C_IC_TIT_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(10,0,"Опрос ТИИ");		
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(10, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.C_IC_TII_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(11,0,"Период опроса, с");
	str.Format("%d",m_Granit.C_IC_NA_1_PERIOD);
	m_Grid.SetItemText(11,1,str);
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(12,0,"Период посылки меандра, мс");
	str.Format("%d",m_Granit.MEANDER_PERIOD);
	m_Grid.SetItemText(12,1,str);
	m_Grid.SetCellType(12,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(13,0,"Таймаут ответа КП, с");
	str.Format("%d",m_Granit.REQ_RESPONSE_PERIOD);
	m_Grid.SetItemText(13,1,str);
	m_Grid.SetCellType(13,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(14,0,"Таймаут на ТУ, с");
	str.Format("%d",m_Granit.TU_RESPONSE_PERIOD);
	m_Grid.SetItemText(14,1,str);
	m_Grid.SetCellType(14,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(15,0,"Таймаут недостоверности, с");
	str.Format("%d",m_Granit.NO_LINK_PERIOD);
	m_Grid.SetItemText(15,1,str);
	m_Grid.SetCellType(15,1, RUNTIME_CLASS(CGridCellNumeric));

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									
	Item.row = 16;
	Item.col = 0;							
	Item.strText = "Кол-во безответных\r\nзапросов для генерации\r\nнеисправности";
	m_Grid.SetItem(&Item);
	str.Format("%d",m_Granit.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(16,1,str);
	m_Grid.SetCellType(16,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(17,0,"Журнал обмена");		
	m_Grid.SetCellType(17,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(17, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.LOG_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(18,0,"Журнал аварий");		
	m_Grid.SetCellType(18,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(18, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.ALARM_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(19,0,"Вывод на консоль");		
	m_Grid.SetCellType(19,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(19, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_Granit.SERVICE);
	aOptions.RemoveAll();
		
	m_Grid.AutoSizeColumns();	
	m_Grid.Refresh();

	m_GridData.SetColumnCount(7);
	//m_GridData.SetFixedColumnCount(1);
	m_GridData.SetRowCount(1);
	m_GridData.SetFixedRowCount(1);	
	m_GridData.EnableTitleTips(0);
	//m_GridData.SetColumnResize(0);
	//m_GridData.EnableSelection(0);

	m_GridData.SetItemText(0,0,"Комментарий");
	m_GridData.SetItemText(0,1,"№ КП");
	m_GridData.SetItemText(0,2,"АФБ");
	m_GridData.SetItemText(0,3,"Тип информ.");
	m_GridData.SetItemText(0,4,"№ Группы");
	m_GridData.SetItemText(0,5,"Адрес в ПМЗ");
	m_GridData.SetItemText(0,6,"Кол-во инф. объектов");

	UpdateDataGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

BOOL CGranitDlg::PreTranslateMessage(MSG* pMsg)
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
void CGranitDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
void CGranitDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений	
	
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
}
afx_msg void CGranitDlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить набор инф.объектов");	
	//MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон наборов инф.объектов");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить набор инф.объектов");
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CGranitDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();					
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CGranitDlg::OnAdd()
{
	ProcessSave();

	CCellID cell = m_GridData.GetFocusCell();
	IndividualStructureGranit mpr;
	if((cell.row > 0)&&(m_Granit.m_IndividualStructureGranitArray.GetCount() > 1))
	{									
		m_Granit.m_IndividualStructureGranitArray.InsertAt(cell.row,mpr);		
		UpdateDataGrid();
		return;
	}
	if((cell.row == m_Granit.m_IndividualStructureGranitArray.GetCount())
		||(cell.row == -1))
	{									
		m_Granit.m_IndividualStructureGranitArray.Add(mpr);												
		UpdateDataGrid();
		return;
	}	
}
afx_msg void CGranitDlg::OnDel()
{	
	if(m_GridData.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID pCell = m_GridData.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_Granit.m_IndividualStructureGranitArray.RemoveAt(pCell.row-1);		
		UpdateDataGrid();
	}
	
}
void CGranitDlg::UpdateDataGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridData.DeleteNonFixedRows();

	for(int i = 0; i < m_Granit.m_IndividualStructureGranitArray.GetSize(); i++)
	{
		int nIndex = m_GridData.InsertRow(NULL);
		
		m_GridData.SetItemText(nIndex,0,m_Granit.m_IndividualStructureGranitArray[i].strCOMMENT);
		
		str.Format("%d",m_Granit.m_IndividualStructureGranitArray[i].N_KP);
		m_GridData.SetItemText(nIndex,1,str);
		m_GridData.SetCellType(nIndex,1,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_Granit.m_IndividualStructureGranitArray[i].AFB);
		m_GridData.SetItemText(nIndex,2,str);
		m_GridData.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

		strOptions.Add("ТС(2)");
		strOptions.Add("ТИТ(3)");
		strOptions.Add("ТИТ(6)");
		strOptions.Add("ТИТ(7)");
		strOptions.Add("ТИИ(4)");		
		m_GridData.SetCellType(nIndex,3, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo* pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,3);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		if (m_Granit.m_IndividualStructureGranitArray[i].INFO_TYPE == 2)
			pCell->SetCurSel(0);
		else if (m_Granit.m_IndividualStructureGranitArray[i].INFO_TYPE == 3)
			pCell->SetCurSel(1);
		else if (m_Granit.m_IndividualStructureGranitArray[i].INFO_TYPE == 6)
			pCell->SetCurSel(2);
		else if (m_Granit.m_IndividualStructureGranitArray[i].INFO_TYPE == 7)
			pCell->SetCurSel(3);
		else 
			pCell->SetCurSel(4);
		strOptions.RemoveAll();

		str.Format("%d",m_Granit.m_IndividualStructureGranitArray[i].GROUP_NUMBER);
		m_GridData.SetItemText(nIndex,4,str);
		m_GridData.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_Granit.m_IndividualStructureGranitArray[i].ADDRESS_PMZ);
		m_GridData.SetItemText(nIndex,5,str);
		m_GridData.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_Granit.m_IndividualStructureGranitArray[i].NUMBER);
		m_GridData.SetItemText(nIndex,6,str);
		m_GridData.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellNumeric));

	}	
	m_GridData.AutoSize();
	m_GridData.Refresh();
}
BOOL CGranitDlg::ProcessSave(void)
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
	
	CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(1, 1);
	m_Granit.TYPE = pCell->GetCurSel()+1;

	str = m_Grid.GetItemText(2,1);
	m_Granit.MEANDER_VALUE = atoi(str);

	pCell = (CGridCellCombo*) m_Grid.GetCell(3, 1);
	m_Granit.INVERT_REQUEST = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	m_Granit.INVERT_RESPONSE = pCell->GetCurSel();
	
	pCell = (CGridCellCombo*) m_Grid.GetCell(5, 1);
	m_Granit.SEND_CONFIRM = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(6, 1);
	m_Granit.IC_ON_MEANDER = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(7, 1);
	m_Granit.ADD_MEANDER_BEFORE_REQ = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(8, 1);
	m_Granit.C_IC_TS_ENABLE = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(9, 1);
	m_Granit.C_IC_TIT_ENABLE = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(10, 1);
	m_Granit.C_IC_TII_ENABLE = pCell->GetCurSel();

	str = m_Grid.GetItemText(11,1);
	m_Granit.C_IC_NA_1_PERIOD = atoi(str);

	str = m_Grid.GetItemText(12,1);
	m_Granit.MEANDER_PERIOD = atoi(str);

	str = m_Grid.GetItemText(13,1);
	m_Granit.REQ_RESPONSE_PERIOD = atoi(str);

	str = m_Grid.GetItemText(14,1);
	m_Granit.TU_RESPONSE_PERIOD = atoi(str);

	str = m_Grid.GetItemText(15,1);
	m_Granit.NO_LINK_PERIOD = atoi(str);

	str = m_Grid.GetItemText(16,1);
	m_Granit.NUMBER_NO_ANSWER = atoi(str);

	pCell = (CGridCellCombo*) m_Grid.GetCell(17, 1);
	m_Granit.LOG_ENABLE = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(18, 1);
	m_Granit.ALARM_ENABLE = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(19, 1);
	m_Granit.SERVICE = pCell->GetCurSel();
	
	m_Granit.m_IndividualStructureGranitArray.RemoveAll();
	

	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		IndividualStructureGranit is101;	

		is101.strCOMMENT = m_GridData.GetItemText(i,0 );	

		str = m_GridData.GetItemText(i,1);
		is101.N_KP = atoi(str);
		if((is101.N_KP>256)||(is101.N_KP<0))
		{
			AfxMessageBox("№ КП: 0..256!");
			return FALSE;
		}	

		str = m_GridData.GetItemText(i,2);
		is101.AFB = atoi(str);
		if((is101.AFB>16)||(is101.AFB<0))
		{
			AfxMessageBox("АФБ: 0..16!");
			return FALSE;
		}	

		pCell = (CGridCellCombo*) m_GridData.GetCell(i,3);		
		
		if(pCell->GetCurSel() == 0)
			is101.INFO_TYPE = 2;
		else if(pCell->GetCurSel() == 1)
			is101.INFO_TYPE = 3;
		else if(pCell->GetCurSel() == 2)
			is101.INFO_TYPE = 6;
		else if(pCell->GetCurSel() == 3)
			is101.INFO_TYPE = 7;
		else if(pCell->GetCurSel() == 4)
			is101.INFO_TYPE = 4;
	
		str = m_GridData.GetItemText(i,4);
		is101.GROUP_NUMBER = atoi(str);
		if((is101.GROUP_NUMBER>16)||(is101.GROUP_NUMBER<0))
		{
			AfxMessageBox("АФБ: 0..16!");
			return FALSE;
		}

		str = m_GridData.GetItemText(i,5);
		is101.ADDRESS_PMZ = atoi(str);

		str = m_GridData.GetItemText(i,6);
		is101.NUMBER = atoi(str);

		if((is101.ADDRESS_PMZ < m_nStartPMZAddr)
			||(is101.ADDRESS_PMZ > m_nEndPMZAddr)
			||(is101.ADDRESS_PMZ + is101.NUMBER - 1 > m_nEndPMZAddr))
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
		m_Granit.m_IndividualStructureGranitArray.Add(is101);
	}
	
	for(int i = 0; i < m_Granit.m_IndividualStructureGranitArray.GetSize();i++)
	{
		for(int j = 0; j < m_Granit.m_IndividualStructureGranitArray.GetSize();j++)
		{
			if((IsIntersect(m_Granit.m_IndividualStructureGranitArray[i].ADDRESS_PMZ,
							m_Granit.m_IndividualStructureGranitArray[i].ADDRESS_PMZ+m_Granit.m_IndividualStructureGranitArray[i].NUMBER-1,
							m_Granit.m_IndividualStructureGranitArray[j].ADDRESS_PMZ,
							m_Granit.m_IndividualStructureGranitArray[j].ADDRESS_PMZ+m_Granit.m_IndividualStructureGranitArray[j].NUMBER-1))
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
	return TRUE;
}

void CGranitDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CTUGranitDlg dlg;
	dlg.m_nChannelNumber=m_nChannelNumber;	
	
	dlg.m_TUGranitArray.Copy(m_Granit.m_TUGranitArray);
	dlg.m_nStartPMZAddr=m_nStartPMZAddr;
	dlg.m_nEndPMZAddr=m_nEndPMZAddr;

	if(dlg.DoModal()==IDOK)
	{
		m_Granit.m_TUGranitArray.Copy(dlg.m_TUGranitArray);
	}	
}
