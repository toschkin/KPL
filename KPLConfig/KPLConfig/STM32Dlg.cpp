// STM32Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "STM32Dlg.h"
#include "GranitDlg.h"
#include "afxdialogex.h"

#define IDM_PRINT1 WM_USER + 420
#define IDM_PRINT2 WM_USER + 421
#define IDM_SETTINGS WM_USER + 422
#define IDM_ADD		WM_USER + 400
#define IDM_DEL		WM_USER + 401
#include "AISTDlg.h"

// диалоговое окно CSTM32Dlg

IMPLEMENT_DYNAMIC(CSTM32Dlg, CDialog)

CSTM32Dlg::CSTM32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSTM32Dlg::IDD, pParent)
{
	nProcNum=0;
	strTitle.Format("Процесс №%d: STM32",nProcNum);
	m_nStartPMZAddr=0;
	m_nEndPMZAddr=0;
	m_Rect = CRect(0,0,0,0);
}

CSTM32Dlg::~CSTM32Dlg()
{
}

void CSTM32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID2, m_GridSTMChannels);	
}


BEGIN_MESSAGE_MAP(CSTM32Dlg, CDialog)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDM_PRINT1, OnPrint1)
	ON_COMMAND(IDM_PRINT2, OnPrint2)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnRClickGrid)
	ON_NOTIFY(NM_RCLICK, IDC_GRID2, OnRClickGrid1)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_ADD, OnAdd)	
	ON_COMMAND(IDM_DEL, OnDel)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID2, OnGridEndEdit1)
END_MESSAGE_MAP()


// обработчики сообщений CSTM32Dlg
afx_msg void CSTM32Dlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{	
	m_Grid.AutoSizeColumns();
	m_Grid.Refresh();
	ProcessSave(TRUE);	
}
afx_msg void CSTM32Dlg::OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult)
{		
	m_GridSTMChannels.AutoSizeColumns();
	m_GridSTMChannels.Refresh();
	ProcessSave(TRUE);	
}

BOOL CSTM32Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	strTitle.Format("Процесс №%d: STM32",nProcNum);
	this->SetWindowTextA(strTitle);	
	this->GetWindowRect(&m_Rect);

	//m_Rect
	
	CStringArray aOptions;

	m_Grid.SetColumnCount(2);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetRowCount(12);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetItemText(0,0,"Параметр");
	m_Grid.SetItemText(0,1,"Значение");
	m_Grid.EnableSelection(0);
		
	CString str;
	m_Grid.SetItemText(1,0,"COM-порт");	
	m_Grid.SetCellType(1, 1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(2,0,"Скорость, бод");		
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
	m_Grid.SetCellType(3,1, RUNTIME_CLASS(CGridCellNumeric));

	m_Grid.SetItemText(4,0,"Количество стоповых бит");	
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
	aOptions.RemoveAll();

	m_Grid.SetItemText(6,0,"Контроль потока");	
	m_Grid.SetCellType(6,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(6, 1);
	aOptions.Add("нет");
	aOptions.Add("аппаратный");
	aOptions.Add("программный");	
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	aOptions.RemoveAll();

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_LEFT|DT_WORDBREAK;									
	Item.row = 7;
	Item.col = 0;							
	Item.strText = "Таймаут ответа\r\nподчиненного в квантах\r\n(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(7,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 8;
	Item.col = 0;							
	Item.strText = "Пауза между байтами\r\nв квантах\r\n(1квант = 10 мс.)";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(8,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 9;
	Item.col = 0;							
	Item.strText = "Интервал между запросами\r\nв квантах\r\n(мс.)";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(9,1, RUNTIME_CLASS(CGridCellNumeric));

	Item.row = 10;
	Item.col = 0;							
	Item.strText = "Количество ошибок для\r\nгенерации \"недостоверности\"";
	m_Grid.SetItem(&Item);	
	m_Grid.SetCellType(10,1, RUNTIME_CLASS(CGridCellNumeric));	

	m_Grid.SetItemText(11,0,"Вывод на консоль");	
	m_Grid.SetCellType(11,1, RUNTIME_CLASS(CGridCellCombo));
	pCell = (CGridCellCombo*) m_Grid.GetCell(11, 1);
	aOptions.Add("Нет");
	aOptions.Add("Да");
	pCell->SetOptions(aOptions);		
	pCell->SetStyle(CBS_DROPDOWNLIST);	
	aOptions.RemoveAll();
	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,60);
	m_Grid.Refresh();

	m_GridSTMChannels.SetColumnCount(4);
	//m_GridSTMChannels.SetFixedColumnCount(1);
	m_GridSTMChannels.SetRowCount(1);
	m_GridSTMChannels.SetFixedRowCount(1);	
	m_GridSTMChannels.EnableTitleTips(0);
	//m_GridSTMChannels.SetColumnResize(0);
	//m_GridSTMChannels.EnableSelection(0);

	m_GridSTMChannels.SetItemText(0,0,"№ канала");
	m_GridSTMChannels.SetItemText(0,1,"Протокол");
	m_GridSTMChannels.SetItemText(0,2,"Скорость");
	m_GridSTMChannels.SetItemText(0,3,"Комментарий");	

	UpdateChannelsGrid();
	UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CSTM32Dlg::UpdateGrid()
{
	CString str;
	str.Format("%d",m_STM.PORT+1);
	m_Grid.SetItemText(1,1,str);
	str.Format("%d",m_STM.BAUDRATE);
	m_Grid.SetItemText(2,1,str);
	str.Format("%d",m_STM.AMOUNTBYTE);
	m_Grid.SetItemText(3,1,str);str.Format("%d",m_STM.STOPBITS);
	m_Grid.SetItemText(4,1,str);
	if((m_STM.PARITY!=1)&&(m_STM.PARITY!=2))
		m_Grid.SetItemText(5,1,"NONE");
	if(m_STM.PARITY==1)
		m_Grid.SetItemText(5,1,"EVEN");
	if(m_STM.PARITY==2)
		m_Grid.SetItemText(5,1,"ODD");
	if((m_STM.CONTROLPOTOK!=1)&&(m_STM.CONTROLPOTOK!=2))
		m_Grid.SetItemText(6,1,"нет");
	if(m_STM.CONTROLPOTOK==1)
		m_Grid.SetItemText(6,1,"аппаратный");
	if(m_STM.CONTROLPOTOK==2)
		m_Grid.SetItemText(6,1,"программный");
	str.Format("%d",m_STM.WAITRESP);
	m_Grid.SetItemText(7,1,str);
	str.Format("%d",m_STM.BYTETIME);
	m_Grid.SetItemText(8,1,str);
	str.Format("%d",m_STM.NEXTMESSAGE);
	m_Grid.SetItemText(9,1,str);
	str.Format("%d",m_STM.NUMBER_NO_ANSWER);
	m_Grid.SetItemText(10,1,str);
	if(m_STM.SERVICE==0)
		m_Grid.SetItemText(11,1,"Нет");	
	else
		m_Grid.SetItemText(11,1,"Да");	
	m_Grid.AutoSize();
	m_Grid.SetColumnWidth(1,60);
	m_Grid.Refresh();
}

void CSTM32Dlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	if(ProcessSave(FALSE)==FALSE)
		return;
	CDialog::OnOK();
}


void CSTM32Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if((m_Rect.Width()>0) && (m_Rect.Height()>0))
	{
		lpMMI->ptMinTrackSize.x = (long)m_Rect.Width();
		lpMMI->ptMinTrackSize.y = (long)m_Rect.Height();
	}
}


BOOL CSTM32Dlg::PreTranslateMessage(MSG* pMsg)
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
afx_msg void CSTM32Dlg::OnSettings(void)
{
	CCellID cell = m_GridSTMChannels.GetFocusCell();	
	if(cell.row > 0)
	{		
		if (m_STM.m_IndividualStructureSTMArray[cell.row - 1].PROTOCOL_TYPE == PROTOCOL_TYPE_GRANIT)
		{
			CGranitDlg dlg;
			dlg.m_Granit = m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_Granit;
			dlg.m_nStartPMZAddr = m_nStartPMZAddr;
			dlg.m_nEndPMZAddr = m_nEndPMZAddr;
			dlg.m_nChannelNumber = m_STM.m_IndividualStructureSTMArray[cell.row - 1].CHANNEL;
			if (dlg.DoModal() == IDOK)
			{
				m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_Granit = dlg.m_Granit;
				//тут подсчитаем колво инф. объектов
				int nTotalAmount = 0;

				for (int i = 0; i < m_STM.m_IndividualStructureSTMArray.GetSize(); i++)
				{
					for (int k = 0; k < m_STM.m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray.GetSize(); k++)
					{
						nTotalAmount += m_STM.m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].NUMBER;
					}
				}
				if (nTotalAmount > m_nEndPMZAddr + 1)
				{
					CString str;
					str.Format("%d > %d !", nTotalAmount, m_nEndPMZAddr + 1);
					AfxMessageBox("Суммарное кол-во инф. объектов настроенных в каналах больше выделенного количества для данного процесса:" + str);
					//return FALSE;
				}
			}
		}
		if (m_STM.m_IndividualStructureSTMArray[cell.row - 1].PROTOCOL_TYPE == PROTOCOL_TYPE_AIST)
		{
			//CAISTDlg
			CAISTDlg dlg;
			dlg.m_AIST = m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_AIST;
			dlg.m_nStartPMZAddr = m_nStartPMZAddr;
			dlg.m_nEndPMZAddr = m_nEndPMZAddr;
			dlg.m_nChannelNumber = m_STM.m_IndividualStructureSTMArray[cell.row - 1].CHANNEL;
			if (dlg.DoModal() == IDOK)
			{
				m_STM.m_IndividualStructureSTMArray[cell.row - 1].m_AIST = dlg.m_AIST;
				//тут подсчитаем колво инф. объектов
				int nTotalAmount = 0;

				for (int i = 0; i < m_STM.m_IndividualStructureSTMArray.GetSize(); i++)
				{
					for (int k = 0; k < m_STM.m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray.GetSize(); k++)
					{
						nTotalAmount++;
					}
				}
				if (nTotalAmount > m_nEndPMZAddr + 1)
				{
					CString str;
					str.Format("%d > %d !", nTotalAmount, m_nEndPMZAddr + 1);
					AfxMessageBox("Суммарное кол-во инф. объектов настроенных в каналах больше выделенного количества для данного процесса:" + str);
					//return FALSE;
				}
			}
		}
	}
}
afx_msg void CSTM32Dlg::OnPrint1(void)
{
	m_Grid.Print();
}

afx_msg void CSTM32Dlg::OnPrint2(void)
{
	m_GridSTMChannels.Print();
}

afx_msg void CSTM32Dlg::OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
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
afx_msg void CSTM32Dlg::OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;

	CMenu MenuRButton;
	MenuRButton.CreatePopupMenu();						
	MenuRButton.AppendMenu(MF_STRING, IDM_ADD, "Добавить канал");		
	MenuRButton.AppendMenu(MF_STRING, IDM_DEL, "Удалить канал");
	MenuRButton.AppendMenu(MF_STRING, IDM_SETTINGS, "Настройка канала...");	
	MenuRButton.AppendMenu(MF_SEPARATOR);
	MenuRButton.AppendMenu(MF_STRING, IDM_PRINT2, "Печать...");	
	POINT point;
	GetCursorPos(&point);
	MenuRButton.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	MenuRButton.DestroyMenu();
				
}
afx_msg void CSTM32Dlg::OnAdd()
{
	ProcessSave(TRUE);

	if(m_STM.m_IndividualStructureSTMArray.GetCount()==4)
	{
		AfxMessageBox("Допустимо не более 4-х каналов!");
		return;
	}
	CCellID cell = m_GridSTMChannels.GetFocusCell();
	IndividualStructureSTM mpr;
	if((cell.row > 0)&&(m_STM.m_IndividualStructureSTMArray.GetCount() > 1))
	{									
		m_STM.m_IndividualStructureSTMArray.InsertAt(cell.row,mpr);		
		UpdateChannelsGrid();
		return;
	}
	if((cell.row == m_STM.m_IndividualStructureSTMArray.GetCount())
		||(cell.row == -1))
	{									
		m_STM.m_IndividualStructureSTMArray.Add(mpr);												
		UpdateChannelsGrid();
		return;
	}	
}
afx_msg void CSTM32Dlg::OnDel()
{	
	if(m_GridSTMChannels.GetRowCount()==1)
		return;

	ProcessSave(TRUE);
	CCellID pCell = m_GridSTMChannels.GetFocusCell();
	
	if((pCell.row > 0)&&(pCell.col >= 0))
	{
		m_STM.m_IndividualStructureSTMArray.RemoveAt(pCell.row-1);		
		UpdateChannelsGrid();
	}
}

void CSTM32Dlg::UpdateChannelsGrid(void)
{
	CString str;
	CStringArray strOptions;
	m_GridSTMChannels.DeleteNonFixedRows();

	for(int i = 0; i < m_STM.m_IndividualStructureSTMArray.GetSize(); i++)
	{
		int nIndex = m_GridSTMChannels.InsertRow(NULL);
		int nCol = 0;
			
		strOptions.Add("1");
		strOptions.Add("2");	
		strOptions.Add("3");
		strOptions.Add("4");		
		m_GridSTMChannels.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		CGridCellCombo* pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		pCell->SetCurSel(m_STM.m_IndividualStructureSTMArray[i].CHANNEL-1);
		strOptions.RemoveAll();		
		nCol++;

		strOptions.Add("Гранит");
		strOptions.Add("AИСТ(мастер)");
		m_GridSTMChannels.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		
		pCell->SetCurSel(m_STM.m_IndividualStructureSTMArray[i].PROTOCOL_TYPE-1);
		
		strOptions.RemoveAll();		
		nCol++;

		strOptions.Add("600");
		strOptions.Add("200");	
		strOptions.Add("300");
		strOptions.Add("100");		
		m_GridSTMChannels.SetCellType(nIndex,nCol, RUNTIME_CLASS(CGridCellCombo));
		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(nIndex,nCol);				
		pCell->SetOptions(strOptions);		
		pCell->SetStyle(CBS_DROPDOWNLIST); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE				
		if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 1)		
			pCell->SetCurSel(0);
		else if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 2)
			pCell->SetCurSel(1);
		else if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 3)
			pCell->SetCurSel(2);
		else if(m_STM.m_IndividualStructureSTMArray[i].SPEED == 6)
			pCell->SetCurSel(3);				
		strOptions.RemoveAll();		
		nCol++;

		m_GridSTMChannels.SetItemText(nIndex,nCol,m_STM.m_IndividualStructureSTMArray[i].strCOMMENT);
		nCol++;		
	}

	m_GridSTMChannels.AutoSize();	
	m_GridSTMChannels.Refresh();
}
BOOL CSTM32Dlg::ProcessSave(BOOL bSilent)
{	
	// TODO: добавьте специализированный код или вызов базового класса
	CString str;
		
	str = m_Grid.GetItemText(1,1);
	if((atoi(str)<=0)||(atoi(str)>255))
	{
		if(!bSilent)
		{
			AfxMessageBox("Неверно задан СОМ-порт!");
			return FALSE;
		}
	}
	if(((CKPLConfigApp*)(AfxGetApp()))->m_KPLProject.IsPortDuplicated(atoi(str)-1,nProcNum))
	{
		if(!bSilent)
		{
			AfxMessageBox("Данный СОМ-порт занят под другую задачу!");
			return FALSE;
		}
	}
	m_STM.PORT = atoi(str)-1;

	str = m_Grid.GetItemText(2,1);
	m_STM.BAUDRATE = atoi(str);

	str = m_Grid.GetItemText(3,1);
	m_STM.AMOUNTBYTE = atoi(str);
	if((m_STM.AMOUNTBYTE > 8)||(m_STM.AMOUNTBYTE < 5))
	{
		if(!bSilent)
		{
			AfxMessageBox("Количество бит в байте 5..8!");			
			return FALSE;	
		}
	}
	str = m_Grid.GetItemText(4,1);
	m_STM.STOPBITS = atoi(str);

	str = m_Grid.GetItemText(5,1);
	if(str == "NONE")
		m_STM.PARITY = 0;
	if(str == "EVEN")
		m_STM.PARITY = 1;
	if(str == "ODD")
		m_STM.PARITY = 2;

	str = m_Grid.GetItemText(6,1);
	if(str == "нет")
		m_STM.CONTROLPOTOK = 0;
	if(str == "аппаратный")
		m_STM.CONTROLPOTOK = 1;
	if(str == "программный")
		m_STM.CONTROLPOTOK = 2;

	str = m_Grid.GetItemText(7,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		if(!bSilent)
		{
			AfxMessageBox("Таймаут ответа подчиненного в квантах 1..3000!");
			return FALSE;
		}
	}
	m_STM.WAITRESP = atoi(str);

	str = m_Grid.GetItemText(8,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		if(!bSilent)
		{
			AfxMessageBox("Пауза между байтами в квантах 1..3000!");
			return FALSE;
		}
	}
	m_STM.BYTETIME = atoi(str);

	str = m_Grid.GetItemText(9,1);
	if((atoi(str)<=0)||(atoi(str)>3000))
	{
		if(!bSilent)
		{
			AfxMessageBox("Интервал между запросами в миллисекундах 1..3000!");
			return FALSE;
		}
	}
	m_STM.NEXTMESSAGE = atoi(str);
	
	str = m_Grid.GetItemText(10,1);
	if((atoi(str)<0)||(atoi(str)>50))
	{
		if(!bSilent)
		{
			AfxMessageBox("Количество ошибок для генерации \"недостоверности\" 0..50!");
			return FALSE;
		}
	}
	m_STM.NUMBER_NO_ANSWER = atoi(str);
	
	str = m_Grid.GetItemText(11,1);
	if(str=="Нет")
		m_STM.SERVICE=0;
	else
		m_STM.SERVICE=1;
		
	for(int i = 1; i < m_GridSTMChannels.GetRowCount(); i++)
	{		
		int nCol = 0;
		IndividualStructureSTM tmp;		

		CGridCellCombo* pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(i,nCol++);									
		tmp.CHANNEL = pCell->GetCurSel()+1;

		for(int j = 0; j < m_STM.m_IndividualStructureSTMArray.GetSize();j++)
		{
			if((tmp.CHANNEL == m_STM.m_IndividualStructureSTMArray[j].CHANNEL)
				&&(i-1!=j))
			{
				if(!bSilent)
				{
					AfxMessageBox("Недопустимо два одинаковых номера канала!");
					return FALSE;
				}
			}
		}
		m_STM.m_IndividualStructureSTMArray[i-1].CHANNEL = tmp.CHANNEL;

		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(i,nCol++);									
		m_STM.m_IndividualStructureSTMArray[i-1].PROTOCOL_TYPE = pCell->GetCurSel()+1;

		pCell = (CGridCellCombo*) m_GridSTMChannels.GetCell(i,nCol++);
		if(pCell->GetCurSel() == 0)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 1;
		else if(pCell->GetCurSel() == 1)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 2;
		else if(pCell->GetCurSel() == 2)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 3;
		else if(pCell->GetCurSel() == 3)
			m_STM.m_IndividualStructureSTMArray[i-1].SPEED = 6;

		m_STM.m_IndividualStructureSTMArray[i-1].strCOMMENT = m_GridSTMChannels.GetItemText(i,nCol++);				
	}	
	return TRUE;
}