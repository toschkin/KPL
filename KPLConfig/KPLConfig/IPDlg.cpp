// IPDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "IPDlg.h"


// ���������� ���� CIPDlg

IMPLEMENT_DYNAMIC(CIPDlg, CDialog)

CIPDlg::CIPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPDlg::IDD, pParent)
{
	m_strIP="0.0.0.0";
}

CIPDlg::~CIPDlg()
{
}

void CIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP);
}


BEGIN_MESSAGE_MAP(CIPDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CIPDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� CIPDlg

void CIPDlg::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString str;
	m_IP.GetWindowText(str);
	WritePrivateProfileString("FTP","IP", str, "KPL.INI");
	m_strIP = str;

	OnOK();
}

BOOL CIPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������
	char szName[2560];
	GetPrivateProfileString("FTP","IP", "0.0.0.0", szName, 2560, "KPL.INI");
	m_IP.SetWindowText(szName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

BOOL CIPDlg::PreTranslateMessage(MSG* pMsg)
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
