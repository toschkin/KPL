#pragma once
#include "afxwin.h"
#include "KPLConfig.h"

#define TYPE_IEC101 0
#define TYPE_IEC104 1
#define TYPE_IEC103 2

// ���������� ���� CAddDiapIECDlg

class CAddDiapIECDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapIECDlg)

public:
	CAddDiapIECDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CAddDiapIECDlg();

	BYTE m_byProtocolType;
	CIndividualStructure101Array m_arr101;
	CIndividualStructure104Array m_arr104;
	CStringArray arrMain_Set_ObjectTypes;
// ������ ����������� ����
	enum { IDD = IDD_IEC_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtComment;
	CComboBox m_cmbTypeInf;
	CEdit m_edtLinkaddr;
	CEdit m_edtASDUAddr;
	CEdit m_edtOriginatorAddr;
	CEdit m_edtStartIOA;
	CEdit m_edtEndIOA;
	CEdit m_edtStartAddrPMZ;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
