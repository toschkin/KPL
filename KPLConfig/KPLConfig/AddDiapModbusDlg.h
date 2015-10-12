#pragma once


// диалоговое окно CAddDiapModbusDlg

#include "ModbusM.h"
#include "afxwin.h"
class CAddDiapModbusDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapModbusDlg)

public:
	CAddDiapModbusDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapModbusDlg();

	CModbusPriborArray m_PriborArray;

// Данные диалогового окна
	enum { IDD = IDD_MODBUS_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CEdit m_edtComment;
	CComboBox m_cmbTypePribor;
	CEdit m_edtStartModbusAddr;
	CEdit m_edtEndModbusAddr;
	CEdit m_edtFunc;
	CEdit m_edtStartReg;
	CEdit m_edtNumberReg;
	CEdit m_edtStartAddrMap;
	CEdit m_edtStart2b;
	CEdit m_edtNumber2b;
	CEdit m_edtStart4b;
	CEdit m_edtNumber4b;
	CEdit m_edtStartAddrMap4b;
	CComboBox m_cmbTypeStatus;
	CEdit m_edtAddrStatus;
	CEdit m_edtMaskStatus;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
