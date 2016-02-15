// AISTDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AISTDlg.h"


// диалоговое окно CAISTDlg
#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
//#define IDM_ADDDIAP	WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
// диалоговое окно CModbusMDlg
extern BOOL IsIntersect(int Start1,int End1,int Start2,int End2);

IMPLEMENT_DYNAMIC(CAISTDlg, CDialog)

CAISTDlg::CAISTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAISTDlg::IDD, pParent)
{		
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
	m_nChannelNumber=0;
}

CAISTDlg::~CAISTDlg()
{
}

void CAISTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridData);	
}


BEGIN_MESSAGE_MAP(CAISTDlg, CDialog)
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
END_MESSAGE_MAP()


// обработчики сообщений CAISTDlg
afx_msg void CAISTDlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CAISTDlg::OnPrint2(void)
{
	m_GridData.Print();
}

afx_msg void CAISTDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//проверить порты
	m_Grid.AutoSizeColumns();
	m_Grid.Refresh();
}
afx_msg void CAISTDlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	//пока пусто
	m_GridData.AutoSizeColumns();
	m_GridData.Refresh();
}

void CAISTDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	if(ProcessSave()==FALSE)
		return;
	CDialog::OnOK();
}


BOOL CAISTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Канал №%d: АИСТ(мастер)",m_nChannelNumber);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(5);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;	

	m_Grid.SetItemText(1,0,"Таймаут недостоверности, с");
	str.Format("%d",m_AIST.NO_LINK_PERIOD);
	m_Grid.SetItemText(1,1,str);
	m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellNumeric));	

	m_Grid.SetItemText(2,0,"Журнал обмена");		
	m_Grid.SetCellType(2,1, RUNTIME_CLASS(CGridCellCombo));
	CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(2, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_AIST.LOG_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(3,0,"Журнал аварий");		
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(3, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_AIST.ALARM_ENABLE);
	aOptions.RemoveAll();

	m_Grid.SetItemText(4,0,"Вывод на консоль");		
	m_Grid.SetCellType(4,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);
	pCell->SetCurSel(m_AIST.SERVICE);
	aOptions.RemoveAll();
		
	m_Grid.AutoSizeColumns();	
	m_Grid.Refresh();

	m_GridData.SetColumnCount(4);
	//m_GridData.SetFixedColumnCount(1);
	m_GridData.SetRowCount(1);
	m_GridData.SetFixedRowCount(1);	
	m_GridData.EnableTitleTips(0);
	//m_GridData.SetColumnResize(0);
	//m_GridData.EnableSelection(0);

	m_GridData.SetItemText(0,0,"Комментарий");	
	m_GridData.SetItemText(0, 1, "Тип информ.");
	m_GridData.SetItemText(0,2,"Адрес в протоколе");	
	m_GridData.SetItemText(0,3,"Адрес в ПМЗ");
	

	UpdateDataGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

BOOL CAISTDlg::PreTranslateMessage(MSG* pMsg)
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
void CAISTDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
void CAISTDlg::OnSize(UINT nType, int cx, int cy)
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
	
	Invalidate(FALSE);
}
afx_msg void CAISTDlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить инф.объект");	
	//MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAP, "Добавить диапазон наборов инф.объектов");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить инф.объект");
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CAISTDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();					
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CAISTDlg::OnAdd()
{
	ProcessSave();

	CCellID cell = m_GridData.GetFocusCell();
	IndividualStructureAIST mpr;
	if((cell.row > 0)&&(m_AIST.m_IndividualStructureAISTArray.GetCount() > 1))
	{									
		m_AIST.m_IndividualStructureAISTArray.InsertAt(cell.row,mpr);		
		UpdateDataGrid();
		return;
	}
	if((cell.row == m_AIST.m_IndividualStructureAISTArray.GetCount())
		||(cell.row == -1))
	{									
		m_AIST.m_IndividualStructureAISTArray.Add(mpr);												
		UpdateDataGrid();
		return;
	}	
}
afx_msg void CAISTDlg::OnDel()
{	
	if(m_GridData.GetRowCount()==1)
		return;

	ProcessSave();
	CCellID pCell = m_GridData.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_AIST.m_IndividualStructureAISTArray.RemoveAt(pCell.row-1);		
		UpdateDataGrid();
	}
	
}
void CAISTDlg::UpdateDataGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridData.DeleteNonFixedRows();

	for(int i = 0; i < m_AIST.m_IndividualStructureAISTArray.GetSize(); i++)
	{
		int nIndex = m_GridData.InsertRow(NULL);
		
		m_GridData.SetItemText(nIndex,0,m_AIST.m_IndividualStructureAISTArray[i].strCOMMENT);						

		strOptions.Add("ТС(1)");
		strOptions.Add("ТИ 1 байт(2)");
		strOptions.Add("ТИ 2 байта(3)");		
		m_GridData.SetCellType(nIndex,1, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo* pCell = (CGridCellCombo*) m_GridData.GetCell(nIndex,1);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE						
		pCell->SetCurSel(m_AIST.m_IndividualStructureAISTArray[i].PACKET_TYPE-1);		
		strOptions.RemoveAll();

		str.Format("%d", m_AIST.m_IndividualStructureAISTArray[i].ADDRESS_PARAM);
		m_GridData.SetItemText(nIndex, 2, str);
		m_GridData.SetCellType(nIndex, 2, RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_AIST.m_IndividualStructureAISTArray[i].ADDRESS_PMZ);
		m_GridData.SetItemText(nIndex,3,str);
		m_GridData.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));		
	}	
	m_GridData.AutoSize();
	m_GridData.Refresh();
}
BOOL CAISTDlg::ProcessSave(void)
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
	m_AIST.NO_LINK_PERIOD = atoi(str);

	CGridCellCombo* pCell = (CGridCellCombo*) m_Grid.GetCell(2, 1);
	m_AIST.LOG_ENABLE = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(3, 1);
	m_AIST.ALARM_ENABLE = pCell->GetCurSel();

	pCell = (CGridCellCombo*) m_Grid.GetCell(4, 1);
	m_AIST.SERVICE = pCell->GetCurSel();
	
	m_AIST.m_IndividualStructureAISTArray.RemoveAll();
	

	for(int i = 1; i < m_GridData.GetRowCount(); i++)
	{
		IndividualStructureAIST is101;	

		is101.strCOMMENT = m_GridData.GetItemText(i,0 );	

		pCell = (CGridCellCombo*)m_GridData.GetCell(i, 1);
		is101.PACKET_TYPE = pCell->GetCurSel() + 1;
					
		str = m_GridData.GetItemText(i,2);
		is101.ADDRESS_PARAM = atoi(str);
		if((is101.ADDRESS_PARAM>240)||(is101.ADDRESS_PARAM<0))
		{
			AfxMessageBox("Адрес в протокле: 0..240!");
			return FALSE;
		}	
		
		str = m_GridData.GetItemText(i,3);
		is101.ADDRESS_PMZ = atoi(str);
		
		if((is101.ADDRESS_PMZ < m_nStartPMZAddr)
			||(is101.ADDRESS_PMZ > m_nEndPMZAddr))
		{
			CString tmp;
			tmp.Format("Инф. объект в строке %d выходит за пределы карты памяти ПРОЦЕССА: %d..%d!\r\n(строки подсвечены сиреневым цветом)",i,m_nStartPMZAddr,m_nEndPMZAddr);
			AfxMessageBox(tmp);
			for(int col = 0; col < m_GridData.GetColumnCount(); col++)
			{
				m_GridData.SetItemBkColour(i,col,RGB(255,128,255));
			}
			m_GridData.EnsureVisible(i,0);
			m_GridData.Refresh();
			//return FALSE;
		}					
		m_AIST.m_IndividualStructureAISTArray.Add(is101);
	}
	
	for(int i = 0; i < m_AIST.m_IndividualStructureAISTArray.GetSize();i++)
	{
		for(int j = 0; j < m_AIST.m_IndividualStructureAISTArray.GetSize();j++)
		{
			if(m_AIST.m_IndividualStructureAISTArray[i].ADDRESS_PMZ == m_AIST.m_IndividualStructureAISTArray[j].ADDRESS_PMZ && i!=j)
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