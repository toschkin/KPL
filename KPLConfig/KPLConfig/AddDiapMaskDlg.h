#pragma once
#include "afxwin.h"
#include "KPLProject.h"

// ���������� ���� CAddDiapMaskDlg

class CAddDiapMaskDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapMaskDlg)

public:
	CAddDiapMaskDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CAddDiapMaskDlg();

	IniMask m_IniMask;
	int m_nStartIOA;
	int m_nEndIOA;
// ������ ����������� ����
	enum { IDD = IDD_MASK_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
	
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtIOAStart;
	CEdit m_edtIOAEnd;
	CEdit m_edtMaskInt;
	CEdit m_edtMaskFloat;
	CEdit m_edtZero;
	CEdit m_edtDeadZone;
	BOOL m_bIntVal;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
