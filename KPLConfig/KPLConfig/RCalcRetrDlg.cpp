// RCalcRetrDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "RCalcRetrDlg.h"

#include "AddDiapRCalc.h"

#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#define IDM_ADDDIAPASON		WM_USER + 402
#define IDM_PRINT1 WM_USER + 420
// диалоговое окно CRCalcRetrDlg

IMPLEMENT_DYNAMIC(CRCalcRetrDlg, CDialog)

CRCalcRetrDlg::CRCalcRetrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRCalcRetrDlg::IDD, pParent)
{
	m_Rect = CRect(0,0,0,0);		
}

CRCalcRetrDlg::~CRCalcRetrDlg()
{
}

void CRCalcRetrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CRCalcRetrDlg, CDialog)
	ON_WM_SIZE()	
	ON_COMMAND(IDM_ADD, OnAdd)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_COMMAND(IDM_ADDDIAPASON, OnAddDiapason)
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_COMMAND(IDM_PRINT1, OnPrint)
END_MESSAGE_MAP()

afx_msg void CRCalcRetrDlg::OnPrint(void)
{
	m_Grid.Print();
}
// обработчики сообщений CRCalcRetrDlg
void CRCalcRetrDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}
BOOL CRCalcRetrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->GetWindowRect(&m_Rect);	


	m_Grid.SetColumnCount(13);
	//m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(1);
	m_Grid.SetFixedRowCount(1);	
	m_Grid.EnableTitleTips(0);
	//m_Grid.SetColumnResize(0);
	m_Grid.EnableSelection(1);
	
	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_WORDBREAK;									

	int nCol = 0;

	Item.row = 0;
	Item.col = nCol ;							
	Item.strText = "Комментарий";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);

	Item.row = 0;
	Item.col = nCol ;							
	Item.strText = "Тип\r\nретрансляции";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,95);

	Item.row = 0;
	Item.col = nCol ;						
	Item.strText = "Адрес\r\nинф. объекта\r\nисточника";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,65);

	Item.row = 0;
	Item.col = nCol ;						
	Item.strText = "Позиция\r\nбайта\r\nв инф.\r\nобъекте\r\nисточнике\r\n(0..11)";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,70);
		 
	Item.row = 0;
	Item.col = nCol ;						
	Item.strText = "Кол-во байт\r\nдля\r\nретрансляции";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);
	
	Item.row = 0;
	Item.col = nCol ;						
	Item.strText = "Адрес\r\nинф.\r\nобъекта\r\nполучателя";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,70);

	Item.row = 0;//DOP_BYTE1
	Item.col = nCol ;						
	Item.strText = "Позиция байта\r\nв инф. объекте\r\nполучателе\r\n(0..11)";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);	

	Item.row = 0;//DOP_BYTE3
	Item.col = nCol ;						
	Item.strText = "Двухбайтное\r\nзначение\r\nсо знаком";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);

	Item.row = 0;//DOP_BYTE4
	Item.col = nCol ;						
	Item.strText = "Масштаб";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);

	Item.row = 0;//ADRES_4B
	Item.col = nCol ;						
	Item.strText = "Смещение 0";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);

	Item.row = 0;//
	Item.col = nCol ;						
	Item.strText = "Минимум.\r\nфиз.вел.";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);

	Item.row = 0;//
	Item.col = nCol ;						
	Item.strText = "Максимум\r\nфиз.вел.";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,80);

	Item.row = 0;//
	Item.col = nCol ;						
	Item.strText = "Размах\r\nшкалы";
	m_Grid.SetItem(&Item);
	m_Grid.SetColumnWidth(nCol++ ,60);
	
	UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CRCalcRetrDlg::OnOK()
{
	//
	if(SaveGrid())
		CDialog::OnOK();
}

void CRCalcRetrDlg::OnSize(UINT nType, int cx, int cy)
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
}
afx_msg void CRCalcRetrDlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();				
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить");	
	MenuRButton.AppendMenu(MF_STRING, IDM_ADDDIAPASON, "Добавить диапазон...");	
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить");
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT1, "Печать...");	

	

	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
void CRCalcRetrDlg::UpdateGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_Grid.DeleteNonFixedRows();

	for(int i = 0; i < m_Retr.m_CalcTIArray.GetSize(); i++)
	{
		int nIndex = m_Grid.InsertRow(NULL);		
		
		m_Grid.SetItemText(nIndex,0,m_Retr.m_CalcTIArray[i].strCOMMENT);
		
		strOptions.Add("байтовая");	
		strOptions.Add("2 байта в 1");
		strOptions.Add("4 байта в 1");
		strOptions.Add("4 байта в 2");
		strOptions.Add("4 байта в 2+1");

		m_Grid.SetCellType(nIndex,1, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex,1);		
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE		
		//str.Format("%d",m_ModbusM.m_ModbusPriborArray[i].PRIBOR);
		if (m_Retr.m_CalcTIArray[i].TYPE == 2)
			pCell->SetCurSel(0);			
		else if (m_Retr.m_CalcTIArray[i].TYPE == 4)
			pCell->SetCurSel(1);			
		else if (m_Retr.m_CalcTIArray[i].TYPE == 6)
			pCell->SetCurSel(2);			
		else if (m_Retr.m_CalcTIArray[i].TYPE == 7)
			pCell->SetCurSel(3);						
		else if (m_Retr.m_CalcTIArray[i].TYPE == 8)
			pCell->SetCurSel(4);
		else
		{
			str.Format("%u",m_Retr.m_CalcTIArray[i].TYPE);
			m_Grid.SetItemText(nIndex,1,str);
		}
		strOptions.RemoveAll();

		str.Format("%d",m_Retr.m_CalcTIArray[i].ADDRESS_FROM);
		m_Grid.SetItemText(nIndex,2,str);
		m_Grid.SetCellType(nIndex,2,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_Retr.m_CalcTIArray[i].POSITION_BYTE);
		m_Grid.SetItemText(nIndex,3,str);
		m_Grid.SetCellType(nIndex,3,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_Retr.m_CalcTIArray[i].NUMBER_BYTE);
		m_Grid.SetItemText(nIndex,4,str);
		m_Grid.SetCellType(nIndex,4,RUNTIME_CLASS(CGridCellNumeric));

		str.Format("%d",m_Retr.m_CalcTIArray[i].ADDRESS_TOO);
		m_Grid.SetItemText(nIndex,5,str);
		m_Grid.SetCellType(nIndex,5,RUNTIME_CLASS(CGridCellNumeric));
		
		str.Format("%d",m_Retr.m_CalcTIArray[i].POSITION_BYTE_TOO);
		m_Grid.SetItemText(nIndex,6,str);
		m_Grid.SetCellType(nIndex,6,RUNTIME_CLASS(CGridCellNumeric));

		m_Grid.SetCellType(nIndex,7,RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_Grid.GetCell(nIndex, 7);
		strOptions.Add("Нет");	
		strOptions.Add("Да");
		pCell->SetOptions(strOptions);		
		if(m_Retr.m_CalcTIArray[i].DOPKODE_YES_NO == 1)
			pCell->SetCurSel(1);
		else
			pCell->SetCurSel(0);
		strOptions.RemoveAll();

		str.Format("%f",m_Retr.m_CalcTIArray[i].CENA_SHKALI);
		m_Grid.SetItemText(nIndex,8,str);

		str.Format("%f",m_Retr.m_CalcTIArray[i].SMESHENIE);
		m_Grid.SetItemText(nIndex,9,str);

		str.Format("%f",m_Retr.m_CalcTIArray[i].MIN_FIZ);
		m_Grid.SetItemText(nIndex,10,str);

		str.Format("%f",m_Retr.m_CalcTIArray[i].MAX_FIZ);
		m_Grid.SetItemText(nIndex,11,str);

		str.Format("%d",m_Retr.m_CalcTIArray[i].MAX_SHKALA_FIZ);
		m_Grid.SetItemText(nIndex,12,str);
		m_Grid.SetCellType(nIndex,12,RUNTIME_CLASS(CGridCellNumeric));
	}

	//m_Grid.AutoSizeRows();
	m_Grid.AutoSize();
	m_Grid.Refresh();
}
BOOL CRCalcRetrDlg::SaveGrid(void)
{
	CString str;
	m_Retr.m_CalcTIArray.RemoveAll();

	for(int i = 1; i < m_Grid.GetRowCount(); i++)
	{
		CalcTI is101;	

		is101.strCOMMENT = m_Grid.GetItemText(i,0 );	

		str = m_Grid.GetItemText(i,1 );					
				
		if(str == "байтовая")
			is101.TYPE = 2;	
		else if(str == "2 байта в 1")
			is101.TYPE = 4;	
		else if(str == "4 байта в 1")
			is101.TYPE = 6;	
		else if(str == "4 байта в 2")
			is101.TYPE = 7;
		else if(str == "4 байта в 2+1")
			is101.TYPE = 8;
		else
		{
			str = m_Grid.GetItemText(i,1);
			is101.TYPE = atoi(str);
		}

		str = m_Grid.GetItemText(i,2);
		is101.ADDRESS_FROM = atoi(str);

		str = m_Grid.GetItemText(i,3);
		is101.POSITION_BYTE = atoi(str);
		if((is101.POSITION_BYTE>11)||(is101.POSITION_BYTE<0))
		{
			AfxMessageBox("Позиция байта в информационном объекте с которого выполняется ретрансляция: 0..11!");
			return FALSE;
		}	

		str = m_Grid.GetItemText(i,4);
		is101.NUMBER_BYTE = atoi(str);

		str = m_Grid.GetItemText(i,5);
		is101.ADDRESS_TOO = atoi(str);

		str = m_Grid.GetItemText(i,6);
		is101.POSITION_BYTE_TOO = atoi(str);			
		if(is101.POSITION_BYTE_TOO + is101.NUMBER_BYTE > 12)
		{
			AfxMessageBox("(POSITION_BYTE_TOO+NUMBER_BYTE)<=12");
			return FALSE;
		}	

		str = m_Grid.GetItemText(i,7 );					
		if(str == "Да")		
			is101.DOPKODE_YES_NO = 1;					
		else
			is101.DOPKODE_YES_NO = 0;	

		str = m_Grid.GetItemText(i,8);
		is101.CENA_SHKALI = atof(str);

		str = m_Grid.GetItemText(i,9);
		is101.SMESHENIE = atof(str);

		str = m_Grid.GetItemText(i,10);
		is101.MIN_FIZ = atof(str);

		str = m_Grid.GetItemText(i,11);
		is101.MAX_FIZ = atof(str);
			
		str = m_Grid.GetItemText(i,12);
		is101.MAX_SHKALA_FIZ = atoi(str);			

		

		if(((is101.MAX_SHKALA_FIZ>255)&&(is101.NUMBER_BYTE == 1))			
			||(is101.MAX_SHKALA_FIZ<0))
		{
			AfxMessageBox("Размах шкалы: 0..255");
			return FALSE;
		}

		if(((is101.MAX_SHKALA_FIZ>65535)&&(is101.NUMBER_BYTE == 2))			
			||(is101.MAX_SHKALA_FIZ<0))
		{
			AfxMessageBox("Размах шкалы: 0..65535");
			return FALSE;
		}

		if(((is101.MAX_SHKALA_FIZ>4294967295)&&(is101.NUMBER_BYTE == 4))			
			||(is101.MAX_SHKALA_FIZ<0))
		{
			AfxMessageBox("Размах шкалы: 0..4294967295");
			return FALSE;
		}
		
		m_Retr.m_CalcTIArray.Add(is101);				
	}
	
	return TRUE;
}
afx_msg void CRCalcRetrDlg::OnAdd()
{
	if(!SaveGrid())
		return;
	CalcTI mpr;
	m_Retr.m_CalcTIArray.Add(mpr);

	UpdateGrid();
	
	m_Grid.EnsureVisible(m_Grid.GetRowCount()-1,0);
}
afx_msg void CRCalcRetrDlg::OnDel()
{

	if(m_Grid.GetRowCount()==1)
		return;	

	//if(!SaveGrid())
	//	return;


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
		m_Retr.m_CalcTIArray.RemoveAt(arGrigIndexes[j]-1);				
		for(int v = j+1; v < arGrigIndexes.GetSize();v++)
		{
			arGrigIndexes[v]--;
		}
	}	
	
	SaveGrid();	
	UpdateGrid();
}
afx_msg void CRCalcRetrDlg::OnAddDiapason()
{
	if(!SaveGrid())
		return;

	CAddDiapRCalc dlg;	
	dlg.m_Retr = m_Retr;
	if(dlg.DoModal()==IDOK)
	{
		m_Retr = dlg.m_Retr;
		UpdateGrid();
	}
	
}	
BOOL CRCalcRetrDlg::PreTranslateMessage(MSG* pMsg)
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
