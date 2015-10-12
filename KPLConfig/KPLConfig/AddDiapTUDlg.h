#pragma once
#include "afxwin.h"
#include "Iec101m.h"

#define PROT_MODBUS	1
#define PROT_IEC101	3
#define PROT_IEC103	5
#define PROT_IEC104	7
#define PROT_SPA	17
#define PROT_MODBUSTCP	19


// диалоговое окно CAddDiapTUDlg

class CAddDiapTUDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapTUDlg)

public:
	CAddDiapTUDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddDiapTUDlg();

	BYTE m_nProcType;
	CTuArray m_TuArray;
// Данные диалогового окна
	enum { IDD = IDD_TU_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtStartONAddr;
	CEdit m_edtStartOFFAddr;
	CEdit m_edtTUCount;
	CEdit m_edtRTUAddr;
	CEdit m_edtStateON;
	CEdit m_edtStateOFF;
	CEdit m_edtTUClose;
	CEdit m_edtTUWaitResp;
	CComboBox m_cboRTUType;
	CComboBox m_cboTUType;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CEdit m_edtINF;
	CStatic m_stFUN;
	CStatic m_stINF;
	CStatic m_stTUOFF;
	CStatic m_stTUON;
	CEdit m_edtSelExec;
	CStatic m_stSelExec;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_stTimeout;
	CStatic m_stReleTime;
};
