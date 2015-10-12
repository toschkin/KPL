#pragma once
#include "afxwin.h"


// диалоговое окно CAddDiapRCalc

class CAddDiapRCalc : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapRCalc)

public:
	CAddDiapRCalc(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapRCalc();

	CRetr		m_Retr;
// Данные диалогового окна
	enum { IDD = IDD_CALC_RETR_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	int m_nCount;
	int m_nAddrIOSrc;
	int m_nAddrIODest;
	int m_nPosByteSrc;
	int m_nPosByteDest;
	int m_nBytesNum;
	CComboBox m_cmbTypeRetr;
	float m_fScale;
	float m_fZeroShift;
	float m_fMaxVal;
	float m_fMinVal;
	int m_nRazmax;
	BOOL m_bSign;
	CString m_strComment;
};
