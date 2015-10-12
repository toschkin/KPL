// AddDiapTUDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapTUDlg.h"


// диалоговое окно CAddDiapTUDlg

IMPLEMENT_DYNAMIC(CAddDiapTUDlg, CDialog)

CAddDiapTUDlg::CAddDiapTUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapTUDlg::IDD, pParent)
{
	m_nProcType = 1;
}

CAddDiapTUDlg::~CAddDiapTUDlg()
{
}

void CAddDiapTUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_edtStartONAddr);
	DDX_Control(pDX, IDC_EDIT3, m_edtStartOFFAddr);
	DDX_Control(pDX, IDC_EDIT8, m_edtTUCount);
	DDX_Control(pDX, IDC_EDIT1, m_edtRTUAddr);
	DDX_Control(pDX, IDC_EDIT4, m_edtStateON);
	DDX_Control(pDX, IDC_EDIT5, m_edtStateOFF);
	DDX_Control(pDX, IDC_EDIT6, m_edtTUClose);
	DDX_Control(pDX, IDC_EDIT7, m_edtTUWaitResp);
	DDX_Control(pDX, IDC_COMBO1, m_cboRTUType);
	DDX_Control(pDX, IDC_COMBO2, m_cboTUType);
	DDX_Control(pDX, IDC_EDIT9, m_edtINF);
	DDX_Control(pDX, IDC_FUN, m_stFUN);
	DDX_Control(pDX, IDC_INF, m_stINF);
	DDX_Control(pDX, IDC_TUOTKL, m_stTUOFF);
	DDX_Control(pDX, IDC_TUVKL, m_stTUON);
	DDX_Control(pDX, IDC_EDIT12, m_edtSelExec);
	DDX_Control(pDX, IDC_INTERVALST, m_stSelExec);
	DDX_Control(pDX, IDC_TIMEOUT_STATIC, m_stTimeout);
	DDX_Control(pDX, IDC_TIMERELE_STATIC, m_stReleTime);
}


BEGIN_MESSAGE_MAP(CAddDiapTUDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapTUDlg

BOOL CAddDiapTUDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtStartONAddr.SetWindowTextA("0");
	m_edtStartOFFAddr.SetWindowTextA("0");
	m_edtTUCount.SetWindowTextA("1");	
	m_edtTUClose.SetWindowTextA("1");
	m_edtTUWaitResp.SetWindowTextA("1");
	m_edtRTUAddr.SetWindowTextA("1");
	m_edtSelExec.SetWindowTextA("10");
	
	if(m_nProcType == PROT_SPA)
	{
		m_cboTUType.AddString("1-I-input data");
		m_cboTUType.AddString("2-O-output data");	
		m_cboTUType.AddString("3-S-setting value");
		m_cboTUType.AddString("4-V-variable");
		m_cboTUType.AddString("5-M-memory data");
		m_cboTUType.AddString("6-C-condition of slave status");
		m_cboTUType.AddString("7-F-slave identification");//0		
		m_cboTUType.AddString("8-T-time");
		m_cboTUType.AddString("9-D-date and time");
		m_cboTUType.AddString("10-last events");
		m_cboTUType.AddString("11-B-backup events");
		m_cboTUType.AddString("12-A-alarms valid");
		m_cboTUType.SetCurSel(1);

		m_edtINF.ShowWindow(SW_HIDE);
		m_stFUN.ShowWindow(SW_HIDE);
		m_stINF.ShowWindow(SW_HIDE);		
		m_edtTUWaitResp.ShowWindow(SW_HIDE);
		m_cboRTUType.ShowWindow(SW_HIDE);		
		m_edtSelExec.ShowWindow(SW_HIDE);
		m_stSelExec.ShowWindow(SW_HIDE);
		m_stTimeout.ShowWindow(SW_HIDE);
		m_stReleTime.SetWindowTextA("Номер канала");

		m_edtStateON.SetWindowTextA("1");
		m_edtStateOFF.SetWindowTextA("0");
	}

	if(m_nProcType == PROT_MODBUS)
	{
		m_cboTUType.AddString("Force Single Coil(5)");		
		m_cboTUType.AddString("Preset Single Reg(6)");				
		m_cboTUType.SetItemData(0,5);		
		m_cboTUType.SetItemData(1,6);		
		m_cboTUType.SetCurSel(0);
		
		m_cboRTUType.AddString("Внутр.модули ТУ(MODBUS)");	
		m_cboRTUType.AddString("Внешнее устройство ТУ");			
		m_cboRTUType.SetItemData(0,1);
		m_cboRTUType.SetItemData(1,2);
		m_cboRTUType.SetCurSel(0);
		
		m_edtINF.ShowWindow(SW_HIDE);
		m_stFUN.ShowWindow(SW_HIDE);
		m_stINF.ShowWindow(SW_HIDE);
		
		m_edtStateON.SetWindowTextA("65280");
		m_edtStateOFF.SetWindowTextA("0");
		m_edtTUCount.SetWindowTextA("32");
		m_edtTUClose.SetWindowTextA("255");
		m_edtTUWaitResp.SetWindowTextA("1000");

		m_stSelExec.SetWindowTextA("Интервал между командами(мкс)");
		m_edtSelExec.SetWindowTextA("3");
	}
	if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
	{		
		m_cboTUType.AddString("C_SC_NA(45)");
		m_cboTUType.AddString("C_DC_NA(46)");		
		m_cboTUType.SetItemData(0,45);
		m_cboTUType.SetItemData(1,46);		
		m_cboTUType.SetCurSel(0);

		m_cboRTUType.AddString("Одноступенчатое ТУ(IEC101)");			
		m_cboRTUType.AddString("Двуступенчатое ТУ(IEC101)");			
		m_cboRTUType.SetItemData(0,2);
		m_cboRTUType.SetItemData(1,3);
		m_cboRTUType.SetCurSel(0);

		m_stTUON.SetWindowText("Нач. адрес ТУ:");
		m_stTUOFF.ShowWindow(SW_HIDE);
		m_edtStartOFFAddr.ShowWindow(SW_HIDE);

		m_edtINF.ShowWindow(SW_HIDE);
		m_stFUN.ShowWindow(SW_HIDE);
		m_stINF.ShowWindow(SW_HIDE);

		m_edtStateON.SetWindowTextA("1");
		m_edtStateOFF.SetWindowTextA("0");
	}
	if(m_nProcType == PROT_IEC103)
	{
		m_cboTUType.AddString("DCO(20)");		
		m_cboTUType.SetItemData(0,20);		
		m_cboTUType.SetCurSel(0);

		m_cboRTUType.AddString("Одноступенчатое ТУ(IEC101)");					
		m_cboRTUType.SetItemData(0,2);		
		m_cboRTUType.SetCurSel(0);
		
		m_stTUON.SetWindowText("Нач. адрес ТУ:");
		m_stTUOFF.ShowWindow(SW_HIDE);
		m_edtStartOFFAddr.ShowWindow(SW_HIDE);
		m_edtINF.SetWindowTextA("1");

		m_edtStateON.SetWindowTextA("2");
		m_edtStateOFF.SetWindowTextA("1");
	}
	
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDiapTUDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	CString str;
	m_edtTUCount.GetWindowTextA(str);
	int nCount = atoi(str);

	
	if(((nCount <= 0)||(nCount > 1000))&&(m_nProcType != PROT_IEC103))
	{
		AfxMessageBox("Количество ТУ 1..1000");
		return;
	}
	if(((nCount <= 0)||(nCount > 255))&&(m_nProcType == PROT_IEC103))
	{
		AfxMessageBox("Количество ТУ 1..255");
		return;
	}
	m_TuArray.SetSize(nCount);

	m_edtRTUAddr.GetWindowTextA(str);
	int nRTUAddr = atoi(str);

	int nStartONAddr = 0;
	int nStartOFFAddr = 0;
	if(m_nProcType == PROT_SPA)
	{
		m_edtStartONAddr.GetWindowTextA(str);
		nStartONAddr = atoi(str);

		m_edtStartOFFAddr.GetWindowTextA(str);
		nStartOFFAddr = atoi(str);
	}

	if(m_nProcType == PROT_MODBUS)
	{
		m_edtStartONAddr.GetWindowTextA(str);
		nStartONAddr = atoi(str);

		m_edtStartOFFAddr.GetWindowTextA(str);
		nStartOFFAddr = atoi(str);
	}
	if((m_nProcType == PROT_IEC101)||(m_nProcType == PROT_IEC104))
	{
		m_edtStartONAddr.GetWindowTextA(str);
		nStartOFFAddr = nStartONAddr = atoi(str);		 
	}
	if(m_nProcType == PROT_IEC103)
	{
		BYTE FUN = 0;
		BYTE INF = 0;			
		m_edtStartONAddr.GetWindowTextA(str);
		if((atoi(str)>255)||(atoi(str)<0))
		{
			AfxMessageBox("Нач.Адрес ТУ (FUN): 0..255!");
			return;
		}
		FUN = (BYTE)atoi(str);

		m_edtINF.GetWindowTextA(str);
		if((atoi(str)>255)||(atoi(str)<0))
		{
			AfxMessageBox("Нач.Адрес ТУ (INF): 0..255!");
			return;
		}
		INF = (BYTE)atoi(str);			
		nStartOFFAddr = nStartONAddr = MAKEWORD(INF,FUN);			

		if(INF + nCount > 255)
		{
			str.Format("При данном Нач.Адресе ТУ (INF) количество ТУ должн быть не более: %d!",255-INF);
			AfxMessageBox(str);
			return;
		}
	}

	m_edtStateON.GetWindowTextA(str);
	int nStateON = atoi(str);

	m_edtStateOFF.GetWindowTextA(str);
	int nStateOFF = atoi(str);

	m_edtTUClose.GetWindowTextA(str);
	int nTUClose = atoi(str);

	m_edtTUWaitResp.GetWindowTextA(str);
	int nTUWaitResp = atoi(str);

	int nRTUType = m_cboRTUType.GetItemData(m_cboRTUType.GetCurSel());		

	int nTUFunction = 0;
	if(m_nProcType == PROT_SPA)
		nTUFunction = m_cboTUType.GetCurSel()+1;
	else
		nTUFunction = m_cboTUType.GetItemData(m_cboTUType.GetCurSel());

	m_edtSelExec.GetWindowTextA(str);
	int nSelExec = atoi(str);

	

	for(int i = 0; i < nCount; i++)
	{
		m_TuArray[i].ADRESS = nRTUAddr;
		m_TuArray[i].REGTU_ON = nStartONAddr+i;
		m_TuArray[i].REGTU_OFF = nStartOFFAddr+i;
		m_TuArray[i].DATATU_ON = nStateON;
		m_TuArray[i].DATATU_OFF = nStateOFF;
		if(m_nProcType == PROT_SPA)
			m_TuArray[i].IEC_ASDU = nTUClose;
		else
			m_TuArray[i].TU_CLOSER = nTUClose;
		m_TuArray[i].WAIT_RESP_TU = nTUWaitResp;
		m_TuArray[i].FUNCTION = nTUFunction;
		m_TuArray[i].TYPE_PRIBOR = nRTUType;
		m_TuArray[i].TIMER_SEL_EXEC = nSelExec;
	}

	CDialog::OnOK();
}

BOOL CAddDiapTUDlg::PreTranslateMessage(MSG* pMsg)
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
