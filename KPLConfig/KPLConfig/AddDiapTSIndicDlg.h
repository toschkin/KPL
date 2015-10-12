#pragma once
#include "afxwin.h"


// диалоговое окно CAddDiapTSIndicDlg

class CAddDiapTSIndicDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapTSIndicDlg)

public:
	CAddDiapTSIndicDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapTSIndicDlg();

// Данные диалогового окна
	enum { IDD = IDD_BUTS_DIAP_DIALOG };

	CMacrosBUTSArray m_MacrosBUTSArray;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CEdit m_edtComment;
	CComboBox m_cmbTypeInd;
	CComboBox m_cmbTypeMapboard;
	CComboBox m_cmbPKTS;
	CEdit m_edtIndStart;
	CEdit m_edtIndEnd;
	CEdit m_edtPMZStart;
	CComboBox m_cmbByte;
	CComboBox m_cmbBit;
	CComboBox m_cmbColourON;
	CComboBox m_cmbColourOFF;
	CEdit m_edtValON;
};
