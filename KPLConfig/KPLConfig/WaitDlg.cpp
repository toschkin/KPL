// WaitDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "WaitDlg.h"


// диалоговое окно CWaitDlg

IMPLEMENT_DYNAMIC(CWaitDlg, CDialog)

CWaitDlg::CWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDlg::IDD, pParent)
{

}

CWaitDlg::~CWaitDlg()
{
}

void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtInfo);
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialog)
END_MESSAGE_MAP()

void CWaitDlg::SetText(CString strInfo)
{
	m_edtInfo.HideCaret();
	m_edtInfo.SetWindowText(strInfo);
	m_edtInfo.HideCaret();
	UpdateWindow();
}
// обработчики сообщений CWaitDlg

BOOL CWaitDlg::PreTranslateMessage(MSG* pMsg)
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
