#pragma once


#include "SPAm.h"
#include "afxwin.h"
// ���������� ���� CAddDiapSPADlg

class CAddDiapSPADlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDiapSPADlg)

public:
	CAddDiapSPADlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CAddDiapSPADlg();

	CIndividualStructureSPAArray m_arrData;
	CStringArray arrMain_Set_ObjectTypes;
// ������ ����������� ����
	enum { IDD = IDD_SPA_DIAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:

	CEdit m_edtComment;
	CComboBox m_cmbTypeInf;
	CEdit m_edtLinkaddr;
	CEdit m_edtChannel;	
	CEdit m_edtStartDataNum;
	CEdit m_edtEndDataNum;
	CEdit m_edtStartAddrPMZ;	
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmbDataCat;
	BOOL m_bStatusEnable;
	CEdit m_edtAddrStatus;
	CEdit m_edtMaskaStatus;
};
