// AddDiapIECDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapIECDlg.h"


// ���������� ���� CAddDiapIECDlg

IMPLEMENT_DYNAMIC(CAddDiapIECDlg, CDialog)

CAddDiapIECDlg::CAddDiapIECDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapIECDlg::IDD, pParent)
{
	m_byProtocolType = TYPE_IEC101;
}

CAddDiapIECDlg::~CAddDiapIECDlg()
{
}

void CAddDiapIECDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtComment);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeInf);
	DDX_Control(pDX, IDC_EDIT10, m_edtLinkaddr);
	DDX_Control(pDX, IDC_EDIT14, m_edtASDUAddr);
	DDX_Control(pDX, IDC_EDIT23, m_edtOriginatorAddr);
	DDX_Control(pDX, IDC_EDIT18, m_edtStartIOA);
	DDX_Control(pDX, IDC_EDIT19, m_edtEndIOA);
	DDX_Control(pDX, IDC_EDIT17, m_edtStartAddrPMZ);
}


BEGIN_MESSAGE_MAP(CAddDiapIECDlg, CDialog)
END_MESSAGE_MAP()


// ����������� ��������� CAddDiapIECDlg

BOOL CAddDiapIECDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	arrMain_Set_ObjectTypes.RemoveAll();
	m_arr101.RemoveAll();
	m_arr104.RemoveAll();

	m_edtLinkaddr.SetWindowText("1");
	m_edtASDUAddr.SetWindowText("1");
	m_edtOriginatorAddr.SetWindowText("0");
	m_edtStartIOA.SetWindowText("0");
	m_edtEndIOA.SetWindowText("0");
	m_edtStartAddrPMZ.SetWindowText("0");

	if(m_byProtocolType == TYPE_IEC104)
	{
		m_edtLinkaddr.EnableWindow(FALSE);
		arrMain_Set_ObjectTypes.Add("1: ��������� ��");//M_SP_NA_1
		arrMain_Set_ObjectTypes.Add("2: ��������� �� � �������� ��");//M_SP_TA_1
		arrMain_Set_ObjectTypes.Add("30:��������� �� � ������� ��");//M_SP_TB_1
		arrMain_Set_ObjectTypes.Add("3: ������� ��");//M_DP_NA_1
		arrMain_Set_ObjectTypes.Add("4: ������� �� � �������� ��");//M_DP_TA_1
		arrMain_Set_ObjectTypes.Add("31:������� �� � ������� ��");//M_DP_TB_1
		arrMain_Set_ObjectTypes.Add("9: �� ���.���");//M_ME_NA_1
		arrMain_Set_ObjectTypes.Add("10:�� ���.��� � �������� ��");//M_ME_TA_1
		arrMain_Set_ObjectTypes.Add("34:�� ���.��� � ������� ��");//M_ME_TD_1
		arrMain_Set_ObjectTypes.Add("21:�� ���.��� ��� ����� ��������");//M_ME_ND_1
		arrMain_Set_ObjectTypes.Add("11:�� �������.");//M_ME_NB_1
		arrMain_Set_ObjectTypes.Add("12:�� �������. � �������� ��");//M_ME_TB_1
		arrMain_Set_ObjectTypes.Add("35:�� �������. � ������� ��");//M_ME_TE_1
		arrMain_Set_ObjectTypes.Add("13:�� ����.�����");//M_ME_NC_1
		arrMain_Set_ObjectTypes.Add("14:�� ����.����� � �������� ��");//M_ME_TC_1
		arrMain_Set_ObjectTypes.Add("36:�� ����.����� � ������� ��");//M_ME_TF_1
		arrMain_Set_ObjectTypes.Add("7: ������ 32 ����");//M_BO_NA_1
		arrMain_Set_ObjectTypes.Add("8: ������ 32 ���� � �������� ��");//M_BO_TA_1
		arrMain_Set_ObjectTypes.Add("33:������ 32 ���� � ������� ��");//M_BO_TB_1
	}
	else if(m_byProtocolType == TYPE_IEC101)
	{
		m_edtLinkaddr.EnableWindow(TRUE);

		arrMain_Set_ObjectTypes.Add("1: ��������� ��");//M_SP_NA_1
		arrMain_Set_ObjectTypes.Add("2: ��������� �� � �������� ��");//M_SP_TA_1
		arrMain_Set_ObjectTypes.Add("30:��������� �� � ������� ��");//M_SP_TB_1
		arrMain_Set_ObjectTypes.Add("3: ������� ��");//M_DP_NA_1
		arrMain_Set_ObjectTypes.Add("4: ������� �� � �������� ��");//M_DP_TA_1
		arrMain_Set_ObjectTypes.Add("31:������� �� � ������� ��");//M_DP_TB_1
		arrMain_Set_ObjectTypes.Add("9: �� ���.���");//M_ME_NA_1
		arrMain_Set_ObjectTypes.Add("10:�� ���.��� � �������� ��");//M_ME_TA_1
		arrMain_Set_ObjectTypes.Add("34:�� ���.��� � ������� ��");//M_ME_TD_1
		arrMain_Set_ObjectTypes.Add("21:�� ���.��� ��� ����� ��������");//M_ME_ND_1
		arrMain_Set_ObjectTypes.Add("11:�� �������.");//M_ME_NB_1
		arrMain_Set_ObjectTypes.Add("12:�� �������. � �������� ��");//M_ME_TB_1
		arrMain_Set_ObjectTypes.Add("35:�� �������. � ������� ��");//M_ME_TE_1
		arrMain_Set_ObjectTypes.Add("13:�� ����.�����");//M_ME_NC_1
		arrMain_Set_ObjectTypes.Add("14:�� ����.����� � �������� ��");//M_ME_TC_1
		arrMain_Set_ObjectTypes.Add("36:�� ����.����� � ������� ��");//M_ME_TF_1
		arrMain_Set_ObjectTypes.Add("7: ������ 32 ����");//M_BO_NA_1
		arrMain_Set_ObjectTypes.Add("8: ������ 32 ���� � �������� ��");//M_BO_TA_1
		arrMain_Set_ObjectTypes.Add("33:������ 32 ���� � ������� ��");//M_BO_TB_1
	}	

	for(int i = 0; i < (int)arrMain_Set_ObjectTypes.GetCount(); i++)
	{
		m_cmbTypeInf.AddString(arrMain_Set_ObjectTypes[i]);
	}

	m_cmbTypeInf.SetCurSel(0);


	// TODO:  �������� �������������� �������������

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

void CAddDiapIECDlg::OnOK()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	
	if((m_byProtocolType == TYPE_IEC104)||(m_byProtocolType == TYPE_IEC101))
	{
		IndividualStructure104 template104;
		IndividualStructure101 template101;	
		CString str;
		m_cmbTypeInf.GetWindowText(str);		
		if(str == arrMain_Set_ObjectTypes[0])
		{
			template104.TYPE_ID = M_SP_NA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[1])
		{
			template104.TYPE_ID = M_SP_TA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[2])
		{
			template104.TYPE_ID = M_SP_TB_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[3])
		{
			template104.TYPE_ID = M_DP_NA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[4])
		{
			template104.TYPE_ID = M_DP_TA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[5])
		{
			template104.TYPE_ID = M_DP_TB_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[6])
		{
			template104.TYPE_ID = M_ME_NA_1;	
		}
		else if(str == arrMain_Set_ObjectTypes[7])
		{
			template104.TYPE_ID = M_ME_TA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[8])
		{
			template104.TYPE_ID = M_ME_TD_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[9])
		{
			template104.TYPE_ID = M_ME_ND_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[10])
		{
			template104.TYPE_ID = M_ME_NB_1;	
		}
		else if(str == arrMain_Set_ObjectTypes[11])
		{
			template104.TYPE_ID = M_ME_TB_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[12])
		{
			template104.TYPE_ID = M_ME_TE_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[13])
		{
			template104.TYPE_ID = M_ME_NC_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[14])
		{
			template104.TYPE_ID = M_ME_TC_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[15])
		{
			template104.TYPE_ID = M_ME_TF_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[16])
		{
			template104.TYPE_ID = M_BO_NA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[17])
		{
			template104.TYPE_ID = M_BO_TA_1;		
		}
		else if(str == arrMain_Set_ObjectTypes[18])
		{
			template104.TYPE_ID = M_BO_TB_1;	
		}
				
		template101.TYPE_ID = template104.TYPE_ID;
		
		m_edtComment.GetWindowText(str);
		template101.strCOMMENT = template104.strCOMMENT = str;

		m_edtASDUAddr.GetWindowText(str);
		template101.COMMON_ADDRESS_ASDU = template104.COMMON_ADDRESS_ASDU = atoi(str);
		
		m_edtOriginatorAddr.GetWindowText(str);
		template101.ORIGINATOR_ADDRESS = template104.ORIGINATOR_ADDRESS = atoi(str);
		
		template101.AM_IOA = template104.AM_IOA = 1;
		
		DWORD nStartIOA,nEndIOA,nStartPMZ;

		m_edtStartIOA.GetWindowText(str);
		nStartIOA = atoi(str);

		m_edtEndIOA.GetWindowText(str);
		nEndIOA = atoi(str);

		m_edtStartAddrPMZ.GetWindowText(str);
		nStartPMZ = atoi(str);

		if(nStartIOA > nEndIOA)
		{
			AfxMessageBox("���.����� IOA \"c\" > \"��\"");
			return;
		}

		m_edtLinkaddr.GetWindowText(str);
		template101.LINK_ADDRESS = atoi(str);

		int k = 0;
		for(DWORD i = nStartIOA; i < nEndIOA+1; i++)
		{
			template104.START_IOA = template101.START_IOA = i;
			template104.ADDRESS_PMZ = template101.ADDRESS_PMZ = nStartPMZ+k;
			if(m_byProtocolType == TYPE_IEC104)
				m_arr104.Add(template104);
			else
				m_arr101.Add(template101);
			k++;
		}
	}	
	CDialog::OnOK();
}

BOOL CAddDiapIECDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
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
