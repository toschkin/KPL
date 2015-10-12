// TUGranitDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "TUGranitDlg.h"
#include "afxdialogex.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_PRINT1 WM_USER + 420

// диалоговое окно CTUGranitDlg

IMPLEMENT_DYNAMIC(CTUGranitDlg, CDialog)

CTUGranitDlg::CTUGranitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTUGranitDlg::IDD, pParent)
{
	m_nChannelNumber=0;	
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);	
}

CTUGranitDlg::~CTUGranitDlg()
{
}

void CTUGranitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CTUGranitDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_DEL, OnDel)		
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_COMMAND(IDM_PRINT1, OnPrint)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
END_MESSAGE_MAP()


afx_msg void CTUGranitDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{	
	m_Grid.AutoSizeColumns();
	m_Grid.Refresh();
}

// обработчики сообщений CTUGranitDlg
afx_msg void CTUGranitDlg::OnPrint(void)
{
	m_Grid.Print();
}

BOOL CTUGranitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Настройка телеуправления для канала Гранит №%d",m_nChannelNumber);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);	

	m_Grid.SetColumnCount(8);	
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetRowCount(1);

	m_Grid.SetItemText(0,0,"№");
	m_Grid.SetItemText(0,1,"Комментарий");
	m_Grid.SetItemText(0,2,"№ КП");
	m_Grid.SetItemText(0,3,"№ Группы");
	m_Grid.SetItemText(0,4,"№ Объекта(ВКЛ)");
	m_Grid.SetItemText(0,5,"№ Объекта(ОТКЛ)");
	m_Grid.SetItemText(0,6,"АФБ(ВКЛ)");
	m_Grid.SetItemText(0,7,"АФБ(ОТКЛ)");

	UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CTUGranitDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	if(SaveGrid())
		CDialog::OnOK();	
}
BOOL CTUGranitDlg::PreTranslateMessage(MSG* pMsg)
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
void CTUGranitDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
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
afx_msg void CTUGranitDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить");
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
void CTUGranitDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
afx_msg void CTUGranitDlg::OnAdd()
{
	if(!SaveGrid())
		return;
	
	TUGranit tu;		
	m_TUGranitArray.Add(tu);
	UpdateGrid();
	m_Grid.EnsureVisible(m_Grid.GetRowCount()-1,0);
}
afx_msg void CTUGranitDlg::OnDel()
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
		m_TUGranitArray.RemoveAt(arGrigIndexes[j]-1);				
		for(int v = j+1; v < arGrigIndexes.GetSize();v++)
		{
			arGrigIndexes[v]--;
		}
	}		
	SaveGrid();	
	UpdateGrid();
}
void CTUGranitDlg::UpdateGrid(void)
{
	CString str;
	CStringArray aOptions;
	m_Grid.DeleteNonFixedRows();
	
	for(int i = 0; i < m_TUGranitArray.GetSize(); i++)
	{
		int nIndex = m_Grid.InsertRow(NULL);
		int col=0;

		str.Format("%d",i+1);
		m_Grid.SetItemText(nIndex,col++,str);

		m_Grid.SetItemText(nIndex,col++,m_TUGranitArray[i].strCOMMENT);
						
		str.Format("%d",m_TUGranitArray[i].N_KP);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_TUGranitArray[i].N_GROUP_2B);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_TUGranitArray[i].N_OBJECT_ON);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_TUGranitArray[i].N_OBJECT_OFF);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_TUGranitArray[i].AFB_ON);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_TUGranitArray[i].AFB_OFF);
		m_Grid.SetItemText(nIndex,col,str);
		m_Grid.SetCellType(nIndex,col++,RUNTIME_CLASS(CGridCellNumeric));			
	}	
	m_Grid.AutoSize();	
	m_Grid.Refresh();
}
BOOL CTUGranitDlg::SaveGrid(void)
{
	CString str;

	CTUGranitArray arrtu;

	for(int i = 1; i < m_Grid.GetRowCount(); i++)
	{
		int col=1;
		TUGranit tu;	

		tu.strCOMMENT = m_Grid.GetItemText(i,col++);
		
		str = m_Grid.GetItemText(i,col++);
		tu.N_KP = atoi(str);
		if((tu.N_KP>256)||(tu.N_KP<0))
		{
			AfxMessageBox("№ КП: 0..256!");
			return FALSE;
		}

		str = m_Grid.GetItemText(i,col++);
		tu.N_GROUP_2B = atoi(str);
		if((tu.N_GROUP_2B!=64)&&(tu.N_GROUP_2B!=128))
		{
			AfxMessageBox("№ Группы: 64 или 128!");
			return FALSE;
		}

		str = m_Grid.GetItemText(i,col++);
		tu.N_OBJECT_ON = atoi(str);

		str = m_Grid.GetItemText(i,col++);
		tu.N_OBJECT_OFF = atoi(str);
		
		str = m_Grid.GetItemText(i,col++);
		tu.AFB_ON = atoi(str);
		if((tu.AFB_ON>16)||(tu.AFB_ON<0))
		{
			AfxMessageBox("АФБ(ВКЛ): 0..16!");
			return FALSE;
		}

		str = m_Grid.GetItemText(i,col++);
		tu.AFB_OFF = atoi(str);
		if((tu.AFB_OFF>16)||(tu.AFB_OFF<0))
		{
			AfxMessageBox("АФБ(ОТКЛ): 0..16!");
			return FALSE;
		}			

		for(int j = 0; j < arrtu.GetSize(); j ++)
		{
			if((tu.N_KP == arrtu[j].N_KP)&&(tu.N_GROUP_2B == arrtu[j].N_GROUP_2B)&&(tu.N_OBJECT_ON == arrtu[j].N_OBJECT_ON)
				&&(tu.N_OBJECT_OFF == arrtu[j].N_OBJECT_OFF)&&(tu.AFB_ON == arrtu[j].AFB_ON)&&(tu.AFB_OFF == arrtu[j].AFB_OFF))
			{
				str.Format("Два одинаковых ТУ: №№ %d и %d!",i,j+1);
				AfxMessageBox(str);
				return FALSE;
			}
		}

		arrtu.Add(tu);
	}
	
	m_TUGranitArray.RemoveAll();
	m_TUGranitArray.Copy(arrtu);

	return TRUE;
}