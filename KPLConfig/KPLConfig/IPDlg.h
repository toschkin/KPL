#pragma once
#include "afxcmn.h"


// диалоговое окно CIPDlg

class CIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CIPDlg)

public:
	CIPDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CIPDlg();

// Данные диалогового окна
	enum { IDD = IDD_IP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	CIPAddressCtrl m_IP;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
