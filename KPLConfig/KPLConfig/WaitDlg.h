#pragma once
#include "afxwin.h"


// ���������� ���� CWaitDlg

class CWaitDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitDlg)

public:
	CWaitDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CWaitDlg();

	void SetText(CString strInfo);
// ������ ����������� ����
	enum { IDD = IDD_WAITDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_edtInfo;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
