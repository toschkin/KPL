// RetrConfiglg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "RetrConfigDlg.h"
#include "RCalcRetrDlg.h"
#include "AddDiapRetr.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAPASON		WM_USER + 402
#define IDM_PRINT1 WM_USER + 420

// диалоговое окно CRetrConfigDlg

IMPLEMENT_DYNAMIC(CRetrConfigDlg, CDialog)

CRetrConfigDlg::CRetrConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRetrConfigDlg::IDD, pParent)
{
	nProcNum=0;
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
}

CRetrConfigDlg::~CRetrConfigDlg()
{
}

void CRetrConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CRetrConfigDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_COMMAND(IDM_ADDDIAPASON, OnAddDiapason)
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(NM_RCLICK, IDC_GRID, &CRetrConfigDlg::OnRClickGrid)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_BN_CLICKED(IDC_BUTTON1, &CRetrConfigDlg::OnBnClickedButton1)
	ON_COMMAND(IDM_PRINT1, OnPrint)
END_MESSAGE_MAP()


afx_msg void CRetrConfigDlg::OnPrint(void)
{
	m_Grid.Print();
}
// обработчики сообщений CRetrConfigDlg
void CRetrConfigDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}

void CRetrConfigDlg::OnOK()
{
	if(SaveGrid())
		CDialog::OnOK();
}

BOOL CRetrConfigDlg::SaveGrid(void)
{
	CString str;
	CManyRetrArray ManyRetrArray;

	for(int i = 1; i < m_Grid.GetRowCount();i++)
	{
		ManyRetr tmp;		

		str = m_Grid.GetItemText(i,1);
		tmp.START_ADRES_OBJECT = atoi(str);

		str = m_Grid.GetItemText(i,2);
		tmp.START_ADRES_RETR = atoi(str);

		str = m_Grid.GetItemText(i,3);
		tmp.NUM_MANY_RETR_OBJECT = atoi(str);
	
		if(tmp.NUM_MANY_RETR_OBJECT == 0)
		{
			str.Format("Не задано количество объектов ретрансяляции! Строка: %d",i);
			m_Grid.SetFocusCell(i,3);
			AfxMessageBox(str);
			return FALSE;
		}

		str = m_Grid.GetItemText(i,4);
		if(str.IsEmpty())
		{
			str.Format("Не задан процесс ретрансяляции! Строка: %d",i);
			m_Grid.SetFocusCell(i,4);
			AfxMessageBox(str);
			return FALSE;
		}
		str.TrimLeft('№');
		int index = str.Find(' ');
		str = str.Left(index);
		tmp.PATH_DIRECT = atoi(str);		
		
		tmp.FLAG_RETR = 5;		

		tmp.strCOMMENT = m_Grid.GetItemText(i,5);

		ManyRetrArray.Add(tmp);
	}
	for(int j = 0; j < ManyRetrArray.GetSize(); j++)
	{
		if((ManyRetrArray[j].START_ADRES_OBJECT+ManyRetrArray[j].NUM_MANY_RETR_OBJECT > m_Retr.NUM_RETR_OBJECT)
			||(ManyRetrArray[j].START_ADRES_RETR+ManyRetrArray[j].NUM_MANY_RETR_OBJECT > m_Retr.NUM_RETR_OBJECT))
		{
			str.Format("Выход за пределы адресного пространства ретрансляции! Строка: %d",j+1);			
			AfxMessageBox(str);
			//return FALSE;
		}
		//Уточнить у Виталика!!!!			
		if(ManyRetrArray[j].START_ADRES_RETR+ManyRetrArray[j].NUM_MANY_RETR_OBJECT > m_Main_Set.m_ProcessInfoArray[ManyRetrArray[j].PATH_DIRECT-1].AMOUNT_SIGNIFICATE)
		{
			str.Format("Выход за пределы адресного пространства процесса! Строка: %d",j+1);			
			AfxMessageBox(str);
			//return FALSE;
		}
		
		for(int k = j+1; k < ManyRetrArray.GetSize(); k++)
		{
			if((ManyRetrArray[j].NUM_MANY_RETR_OBJECT == ManyRetrArray[k].NUM_MANY_RETR_OBJECT)
				&&(ManyRetrArray[j].PATH_DIRECT == ManyRetrArray[k].PATH_DIRECT)
				&&(ManyRetrArray[j].START_ADRES_OBJECT == ManyRetrArray[k].START_ADRES_OBJECT)
				&&(ManyRetrArray[j].START_ADRES_RETR == ManyRetrArray[k].START_ADRES_RETR))			
			{
				str.Format("Одинаковые наборы ретрансляции: %d и %d !",j+1,k+1);			
				AfxMessageBox(str);
				return FALSE;
			}
			if(ManyRetrArray[j].PATH_DIRECT == ManyRetrArray[k].PATH_DIRECT)//proverka na naloghenie
			{	
				//Газин сказал не надо проверять!!!
				/*//k=15..25   j=10..20 
				if((ManyRetrArray[k].START_ADRES_OBJECT >= ManyRetrArray[j].START_ADRES_RETR)
					&&(ManyRetrArray[k].START_ADRES_OBJECT <= ManyRetrArray[j].START_ADRES_OBJECT+ManyRetrArray[j].NUM_MANY_RETR_OBJECT))
				{
					str.Format("Наложение адресов в карте памяти для наборов ретрансляции: %d и %d !",j+1,k+1);
					AfxMessageBox(str);
					return FALSE;
				}
				//k=1..25   j=10..20 
				if((ManyRetrArray[k].START_ADRES_OBJECT <= ManyRetrArray[j].START_ADRES_OBJECT)
					&&(ManyRetrArray[k].START_ADRES_OBJECT+ManyRetrArray[k].NUM_MANY_RETR_OBJECT >= ManyRetrArray[j].START_ADRES_OBJECT+ManyRetrArray[j].NUM_MANY_RETR_OBJECT))
				{
					str.Format("Наложение адресов в карте памяти для наборов ретрансляции: %d и %d !",j+1,k+1);
					AfxMessageBox(str);
					return FALSE;
				}
				//k=1..15   j=10..20 
				if((ManyRetrArray[k].START_ADRES_OBJECT+ManyRetrArray[k].NUM_MANY_RETR_OBJECT >= ManyRetrArray[j].START_ADRES_OBJECT)
					&&(ManyRetrArray[k].START_ADRES_OBJECT+ManyRetrArray[k].NUM_MANY_RETR_OBJECT <= ManyRetrArray[j].START_ADRES_OBJECT+ManyRetrArray[j].NUM_MANY_RETR_OBJECT))
				{
					str.Format("Наложение адресов в карте памяти для наборов ретрансляции: %d и %d !",j+1,k+1);
					AfxMessageBox(str);
					return FALSE;
				}*/
				//////////////////////////////////////////////////////////////////////////////////////////////////
				//k=15..25   j=10..20 
				if((ManyRetrArray[k].START_ADRES_RETR >= ManyRetrArray[j].START_ADRES_RETR)
					&&(ManyRetrArray[k].START_ADRES_RETR < ManyRetrArray[j].START_ADRES_RETR+ManyRetrArray[j].NUM_MANY_RETR_OBJECT))
				{
					str.Format("Наложение адресов ретрансляции для наборов ретрансляции: %d и %d !",j+1,k+1);			
					AfxMessageBox(str);
					return FALSE;
				}
				//k=1..25   j=10..20 
				if((ManyRetrArray[k].START_ADRES_RETR <= ManyRetrArray[j].START_ADRES_RETR)
					&&(ManyRetrArray[k].START_ADRES_RETR+ManyRetrArray[k].NUM_MANY_RETR_OBJECT >= ManyRetrArray[j].START_ADRES_RETR+ManyRetrArray[j].NUM_MANY_RETR_OBJECT))
				{
					str.Format("Наложение адресов ретрансляции для наборов ретрансляции: %d и %d !",j+1,k+1);			
					AfxMessageBox(str);
					return FALSE;
				}
				//k=1..15   j=10..20 
				if((ManyRetrArray[k].START_ADRES_RETR >= ManyRetrArray[j].START_ADRES_RETR)
					&&(ManyRetrArray[k].START_ADRES_RETR+ManyRetrArray[k].NUM_MANY_RETR_OBJECT >= ManyRetrArray[j].START_ADRES_RETR)
					&&(ManyRetrArray[k].START_ADRES_RETR+ManyRetrArray[k].NUM_MANY_RETR_OBJECT <= ManyRetrArray[j].START_ADRES_RETR+ManyRetrArray[j].NUM_MANY_RETR_OBJECT))
				{
					str.Format("Наложение адресов ретрансляции для наборов ретрансляции: %d и %d !",j+1,k+1);			
					AfxMessageBox(str);
					return FALSE;
				}				
			}
		}		
	}

	CWordArray arrPD;
	for(int j = 0; j < ManyRetrArray.GetSize(); j++)
	{
		BOOL bFound = FALSE;
		for(int l = 0; l < arrPD.GetSize(); l++)
		{
			if(arrPD[l] == (WORD)ManyRetrArray[j].PATH_DIRECT)
			{
				ManyRetrArray[j].PLACE_OF_PUT = l;
				bFound = TRUE;
				break;
			}
		}
		if(!bFound)
		{
			ManyRetrArray[j].PLACE_OF_PUT = arrPD.Add((WORD)ManyRetrArray[j].PATH_DIRECT);			 
		}
	}	

	m_Retr.NUM_TRANSMIT_DIRECT = arrPD.GetSize();
	m_Retr.m_ManyRetrArray.RemoveAll();
	m_Retr.m_ManyRetrArray.Copy(ManyRetrArray);
	return TRUE;
}
void CRetrConfigDlg::OnCancel()
{

	// TODO: добавьте специализированный код или вызов базового класса
	CDialog::OnCancel();
}

BOOL CRetrConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	this->GetWindowRect(&m_Rect);	

	m_Grid.SetColumnCount(6);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetRowCount(1);
	m_Grid.SetItemText(0,0,"№");
	m_Grid.SetItemText(0,1,"Нач.адрес в карте памяти");
	m_Grid.SetItemText(0,2,"Нач.адрес ретрансляции");
	m_Grid.SetItemText(0,3,"Количество инф.объектов");
	m_Grid.SetItemText(0,4,"Процесс ретрансляции");
	m_Grid.SetItemText(0,5,"Комментарий");
	
	UpdateGrid();

	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.m_Main_Set.m_nVersion < 14)
	{
		CWnd* pWnd = this->GetDlgItem(IDC_BUTTON1);
		pWnd->ShowWindow(SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CRetrConfigDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	long nCentery = (long)(cy / 2);
	long nCenter = (long)(cx / 2);

	int dx = 10;
	if (IsWindow(m_Grid.m_hWnd))
	{
		CRect r;
		GetClientRect(&r);
		m_Grid.MoveWindow(dx, dx, r.right - r.left - 2*dx, r.bottom - r.top - 50, TRUE);
	}

	CWnd* pWnd = this->GetDlgItem(IDOK);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter - 100 , cy - 31, 79, 23);
	}
	pWnd = this->GetDlgItem(IDCANCEL);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(nCenter + 20, cy - 31, 79, 23);
	}

	pWnd = this->GetDlgItem(IDC_BUTTON1);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(dx, cy - 31, 160, 23);
	}	
}
afx_msg void CRetrConfigDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
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
void CRetrConfigDlg::UpdateGrid(void)
{
	CString str;
	CStringArray aOptions;
	CWordArray aProcesses;
	for(int j = 0; j < m_Main_Set.m_ProcessInfoArray.GetSize();j++)
	{
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 2)
		{
			str.Format("№%d (MODBUS-slave)",j+1);
			aProcesses.Add(j+1);
			aOptions.Add(str);
		}
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 4)
		{
			str.Format("№%d (IEC870-5-101-slave)",j+1);
			aOptions.Add(str);
			aProcesses.Add(j+1);
		}
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 8)
		{
			str.Format("№%d (IEC870-5-104-slave PtP)",j+1);
			aOptions.Add(str);
			aProcesses.Add(j+1);
		}		
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 14)
		{
			str.Format("№%d (IEC870-5-104-slave PtMP)",j+1);
			aOptions.Add(str);
			aProcesses.Add(j+1);
		}		
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 18)
		{
			str.Format("№%d (Вывод на ДЩ)",j+1);
			aOptions.Add(str);
			aProcesses.Add(j+1);
		}	
	}

	m_Grid.DeleteNonFixedRows();
	
	for(int i = 0; i < m_Retr.m_ManyRetrArray.GetSize();i++)
	{
		int nIndex = m_Grid.InsertRow(NULL);

		str.Format("%d",i+1);
		m_Grid.SetItemText(nIndex,0,str);
		str.Format("%d",m_Retr.m_ManyRetrArray[i].START_ADRES_OBJECT);
		m_Grid.SetItemText(nIndex,1,str);
		str.Format("%d",m_Retr.m_ManyRetrArray[i].START_ADRES_RETR);
		m_Grid.SetItemText(nIndex,2,str);
		str.Format("%d",m_Retr.m_ManyRetrArray[i].NUM_MANY_RETR_OBJECT);
		m_Grid.SetItemText(nIndex,3,str);
				
		m_Grid.SetCellType(nIndex,4, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex,4);		
		pCell->SetOptions(aOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE	
		for(int k = 0; k < aProcesses.GetSize(); k++)
		{
			if(aProcesses[k] == m_Retr.m_ManyRetrArray[i].PATH_DIRECT)
			{
				pCell->SetCurSel(k);
				break;
			}
		}
		m_Grid.SetItemText(nIndex,5,m_Retr.m_ManyRetrArray[i].strCOMMENT);
	}

	m_Grid.AutoSize();	
	m_Grid.Refresh();
}
afx_msg void CRetrConfigDlg::OnAdd()
{
	if(!SaveGrid())
		return;
	ManyRetr ManyRetr1;
	if((m_Retr.m_ManyRetrArray.GetSize() == 0)||(m_Grid.GetFocusCell().row == m_Grid.GetRowCount()-1))
	{
		m_Retr.m_ManyRetrArray.Add(ManyRetr1);
		UpdateGrid();
		m_Grid.EnsureVisible(m_Grid.GetRowCount()-1,0);
	}
	else
	{
		if(m_Grid.GetFocusCell().row > 0)
		{
			m_Retr.m_ManyRetrArray.InsertAt(m_Grid.GetFocusCell().row,ManyRetr1);
			UpdateGrid();		
		}
	}
	
}
afx_msg void CRetrConfigDlg::OnDel()
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
		m_Retr.m_ManyRetrArray.RemoveAt(arGrigIndexes[j]-1);				
		for(int v = j+1; v < arGrigIndexes.GetSize();v++)
		{
			arGrigIndexes[v]--;
		}
	}	
	SaveGrid();		
	UpdateGrid();
}
afx_msg void CRetrConfigDlg::OnAddDiapason()
{
	if(!SaveGrid())
		return;

	CAddDiapRetr dlg;
	dlg.m_Main_Set = m_Main_Set;
	dlg.m_Retr = m_Retr;
	if(dlg.DoModal()==IDOK)
	{
		m_Retr = dlg.m_Retr;
		UpdateGrid();
	}
}	
afx_msg void CRetrConfigDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	m_Grid.AutoSize();
	m_Grid.Refresh();
}
void CRetrConfigDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CRCalcRetrDlg dlg;
	dlg.m_Retr = m_Retr;
	if(dlg.DoModal() == IDOK)
	{
		m_Retr = dlg.m_Retr;
	}
}

BOOL CRetrConfigDlg::PreTranslateMessage(MSG* pMsg)
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
