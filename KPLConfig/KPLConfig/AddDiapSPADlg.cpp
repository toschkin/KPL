// AddDiapSPADlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapSPADlg.h"


// диалоговое окно CAddDiapSPADlg

IMPLEMENT_DYNAMIC(CAddDiapSPADlg, CDialog)

CAddDiapSPADlg::CAddDiapSPADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapSPADlg::IDD, pParent)
	, m_bStatusEnable(FALSE)
{

}

CAddDiapSPADlg::~CAddDiapSPADlg()
{
}

void CAddDiapSPADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtComment);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeInf);
	DDX_Control(pDX, IDC_EDIT10, m_edtLinkaddr);
	DDX_Control(pDX, IDC_EDIT14, m_edtChannel);	
	DDX_Control(pDX, IDC_EDIT18, m_edtStartDataNum);
	DDX_Control(pDX, IDC_EDIT19, m_edtEndDataNum);
	DDX_Control(pDX, IDC_EDIT17, m_edtStartAddrPMZ);
	DDX_Control(pDX, IDC_COMBO4, m_cmbDataCat);
	DDX_Check(pDX, IDC_CHECK1, m_bStatusEnable);
	DDX_Control(pDX, IDC_EDIT23, m_edtAddrStatus);
	DDX_Control(pDX, IDC_EDIT24, m_edtMaskaStatus);
}


BEGIN_MESSAGE_MAP(CAddDiapSPADlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapSPADlg
BOOL CAddDiapSPADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	arrMain_Set_ObjectTypes.RemoveAll();	
	m_arrData.RemoveAll();
	
	m_edtLinkaddr.SetWindowText("1");
	m_edtChannel.SetWindowText("1");	
	m_edtStartDataNum.SetWindowText("0");	
	m_edtEndDataNum.SetWindowText("0");
	m_edtStartAddrPMZ.SetWindowText("0");
		
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
	
	for(int i = 0; i < (int)arrMain_Set_ObjectTypes.GetCount(); i++)
	{
		m_cmbTypeInf.AddString(arrMain_Set_ObjectTypes[i]);
	}

	m_cmbTypeInf.SetCurSel(0);

	m_cmbDataCat.AddString("1-I-input data");
	m_cmbDataCat.AddString("2-O-output data");	
	m_cmbDataCat.AddString("3-S-setting value");
	m_cmbDataCat.AddString("4-V-variable");
	m_cmbDataCat.AddString("5-M-memory data");
	m_cmbDataCat.AddString("6-C-condition of slave status");
	m_cmbDataCat.AddString("7-F-slave identification");//0		
	m_cmbDataCat.AddString("8-T-time");
	m_cmbDataCat.AddString("9-D-date and time");
	m_cmbDataCat.AddString("10-last events");
	m_cmbDataCat.AddString("11-B-backup events");
	m_cmbDataCat.AddString("12-A-alarms valid");
	m_cmbDataCat.SetCurSel(0);
	
	
	m_edtAddrStatus.SetWindowText("0");
	m_edtMaskaStatus.SetWindowText("65535");

	// TODO:  Добавить дополнительную инициализацию

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDiapSPADlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	
	
	IndividualStructureSPA templateSPA;

	CString str;
	m_cmbTypeInf.GetWindowText(str);		
	if(str == arrMain_Set_ObjectTypes[0])
	{
		templateSPA.TYPE_ID = M_SP_NA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[1])
	{
		templateSPA.TYPE_ID = M_SP_TA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[2])
	{
		templateSPA.TYPE_ID = M_SP_TB_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[3])
	{
		templateSPA.TYPE_ID = M_DP_NA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[4])
	{
		templateSPA.TYPE_ID = M_DP_TA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[5])
	{
		templateSPA.TYPE_ID = M_DP_TB_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[6])
	{
		templateSPA.TYPE_ID = M_ME_NA_1;	
	}
	else if(str == arrMain_Set_ObjectTypes[7])
	{
		templateSPA.TYPE_ID = M_ME_TA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[8])
	{
		templateSPA.TYPE_ID = M_ME_TD_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[9])
	{
		templateSPA.TYPE_ID = M_ME_ND_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[10])
	{
		templateSPA.TYPE_ID = M_ME_NB_1;	
	}
	else if(str == arrMain_Set_ObjectTypes[11])
	{
		templateSPA.TYPE_ID = M_ME_TB_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[12])
	{
		templateSPA.TYPE_ID = M_ME_TE_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[13])
	{
		templateSPA.TYPE_ID = M_ME_NC_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[14])
	{
		templateSPA.TYPE_ID = M_ME_TC_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[15])
	{
		templateSPA.TYPE_ID = M_ME_TF_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[16])
	{
		templateSPA.TYPE_ID = M_BO_NA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[17])
	{
		templateSPA.TYPE_ID = M_BO_TA_1;		
	}
	else if(str == arrMain_Set_ObjectTypes[18])
	{
		templateSPA.TYPE_ID = M_BO_TB_1;	
	}						
	
	m_edtComment.GetWindowText(str);
	templateSPA.strCOMMENT = str;

	m_edtChannel.GetWindowText(str);
	templateSPA.CHANNEL_NUM = atoi(str);

	m_edtLinkaddr.GetWindowText(str);
	templateSPA.SLAVE_ADDRESS = atoi(str);
	
	templateSPA.DATA_CAT = m_cmbDataCat.GetCurSel()+1;
	
	UpdateData();
	if(m_bStatusEnable)
		templateSPA.TYPE_STATUS = 2;
	else
		templateSPA.TYPE_STATUS = 0;

	m_edtAddrStatus.GetWindowText(str);
	templateSPA.ADRES_STATUS = atoi(str);

	m_edtMaskaStatus.GetWindowText(str);
	templateSPA.MASKA_STATUS = atoi(str);	
	
	DWORD nStartIOA,nEndIOA,nStartPMZ;

	m_edtStartDataNum.GetWindowText(str);
	nStartIOA = atoi(str);

	m_edtEndDataNum.GetWindowText(str);
	nEndIOA = atoi(str);

	m_edtStartAddrPMZ.GetWindowText(str);
	nStartPMZ = atoi(str);

	if(nStartIOA > nEndIOA)
	{
		AfxMessageBox("Номер данных \"c\" > \"по\"");
		return;
	}		

	int k = 0;
	for(DWORD i = nStartIOA; i < nEndIOA+1; i++)
	{
		templateSPA.DATA_NUM = i;
		templateSPA.ADDRESS_PMZ = nStartPMZ+k;			
		m_arrData.Add(templateSPA);			
		k++;
	}
	
	CDialog::OnOK();
}

BOOL CAddDiapSPADlg::PreTranslateMessage(MSG* pMsg)
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
