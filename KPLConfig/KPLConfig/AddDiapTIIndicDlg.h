#pragma once
#include "afxwin.h"


// диалоговое окно CAddDiapTIIndicDlg

class CAddDiapTIIndicDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapTIIndicDlg)

public:
	CAddDiapTIIndicDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapTIIndicDlg();

	CMacrosBUIArray m_MacrosBUIArray;
// Данные диалогового окна
	enum { IDD = IDD_BUI_DIAP_DIALOG };

	CEdit m_edtComment;
	CComboBox m_cmbTypeInd;	
	CComboBox m_cmbPKTS;
	CEdit m_edtIndStart;
	CEdit m_edtIndEnd;
	CEdit m_edtPMZStart;
	CComboBox m_cmbSign;
	CEdit m_edtScale;
	CEdit m_edtZeroShift;
	CEdit m_edtMin;
	CEdit m_edtMax;
	CComboBox m_cmbFormat;
	CComboBox m_cmbDot;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
