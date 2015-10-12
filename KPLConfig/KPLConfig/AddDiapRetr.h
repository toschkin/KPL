#pragma once
#include "afxwin.h"


// диалоговое окно CAddDiapRetr

class CAddDiapRetr : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapRetr)

public:
	CAddDiapRetr(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapRetr();

	CRetr		m_Retr;
	CMain_Set	m_Main_Set;
// Данные диалогового окна
	enum { IDD = IDD_RETR_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CString m_strNumSets;
	CString m_strStartPMZAddr;
	CString m_strStartRetrAddr;
	CString m_srtNumObj;
	CComboBox m_cmbProcessRetr;
	CString m_strComment;
};
