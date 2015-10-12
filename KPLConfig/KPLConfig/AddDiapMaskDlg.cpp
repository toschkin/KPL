// AddDiapMaskDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapMaskDlg.h"


// диалоговое окно CAddDiapMaskDlg

IMPLEMENT_DYNAMIC(CAddDiapMaskDlg, CDialog)

CAddDiapMaskDlg::CAddDiapMaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapMaskDlg::IDD, pParent)
	, m_bIntVal(FALSE)
{	
	m_nStartIOA=0;
	m_nEndIOA=0;
}

CAddDiapMaskDlg::~CAddDiapMaskDlg()
{
}

void CAddDiapMaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtIOAStart);
	DDX_Control(pDX, IDC_EDIT10, m_edtIOAEnd);
	DDX_Control(pDX, IDC_EDIT2, m_edtMaskInt);
	DDX_Control(pDX, IDC_EDIT4, m_edtMaskFloat);
	DDX_Control(pDX, IDC_EDIT5, m_edtZero);
	DDX_Control(pDX, IDC_EDIT11, m_edtDeadZone);
	DDX_Check(pDX, IDC_CHECK1, m_bIntVal);
}


BEGIN_MESSAGE_MAP(CAddDiapMaskDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapMaskDlg

BOOL CAddDiapMaskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	CString str;
	str.Format("%d",m_nStartIOA);
	m_edtIOAStart.SetWindowText(str);

	str.Format("%d",m_nEndIOA);
	m_edtIOAEnd.SetWindowText(str);

	str.Format("%d",m_IniMask.MASKAINT);
	m_edtMaskInt.SetWindowText(str);

	str.Format("%d",m_IniMask.MASKAFLOAT);
	m_edtMaskFloat.SetWindowText(str);

	str.Format("%d",m_IniMask.VALUE_0);
	m_edtZero.SetWindowText(str);

	str.Format("%d",m_IniMask.MASKA_VALUE_0);
	m_edtDeadZone.SetWindowText(str);

	m_bIntVal = m_IniMask.TYPE_VALUE;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDiapMaskDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	UpdateData(TRUE);

	CString str;

	m_edtIOAStart.GetWindowText(str);
	m_nStartIOA = atoi(str);

	m_edtIOAEnd.GetWindowText(str);
	m_nEndIOA = atoi(str);

	m_edtMaskInt.GetWindowText(str);
	m_IniMask.MASKAINT = atoi(str);

	m_edtMaskFloat.GetWindowText(str);
	m_IniMask.MASKAFLOAT = atoi(str);

	m_edtZero.GetWindowText(str);
	m_IniMask.VALUE_0 = atoi(str);

	m_edtDeadZone.GetWindowText(str);
	m_IniMask.MASKA_VALUE_0 = atoi(str);

	m_IniMask.TYPE_VALUE = m_bIntVal;
	
	CDialog::OnOK();
}

BOOL CAddDiapMaskDlg::PreTranslateMessage(MSG* pMsg)
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
