#pragma once
#include "afxwin.h"


// диалоговое окно CWaitDlg

class CWaitDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitDlg)

public:
	CWaitDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CWaitDlg();

	void SetText(CString strInfo);
// Данные диалогового окна
	enum { IDD = IDD_WAITDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_edtInfo;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
