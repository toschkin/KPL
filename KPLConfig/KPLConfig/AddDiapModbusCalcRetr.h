#pragma once
#include "afxwin.h"


// диалоговое окно CAddDiapModbusCalcRetr

class CAddDiapModbusCalcRetr : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapModbusCalcRetr)

public:
	CAddDiapModbusCalcRetr(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapModbusCalcRetr();

// Данные диалогового окна
	enum { IDD = IDD_CALC_MODBUS_DIAP_DIALOG };

	CModbusS m_ModbusS;

	int m_nCount;
	int m_nAddrIOSrc;
	int m_nAddrIODest;
	int m_nPosByteSrc;
	int m_nPosByteDest;
	int m_nPosBitSrc;
	int m_nPosBitDest;
	int m_nBytesNum;
	CComboBox m_cmbTypeRetr;
	float m_fScale;
	float m_fZeroShift;
	float m_fMaxVal;
	float m_fMinVal;
	int m_nRazmax;
	BOOL m_bSign;
	CString m_strComment;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CEdit m_edtPosByteSrc;
	CEdit m_edtPosBitSrc;
	CEdit m_edtPosBitDest;
};
