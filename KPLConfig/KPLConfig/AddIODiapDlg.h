#pragma once
#include "afxwin.h"
#include "KPLConfig.h"

// диалоговое окно CAddIODiapDlg

class CAddIODiapDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddIODiapDlg)

public:
	CAddIODiapDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAddIODiapDlg();

// Данные диалогового окна
	enum { IDD = IDD_IO_DIAP_DIALOG };

	CIniObjectArray m_arrIniObject;
	CStringArray arrMain_Set_ObjectTypes,arrMain_Set_Processes;
	CArray<int,int> arrObjectTypesInt;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CString m_strComment;
	CComboBox m_cmbTypeIO;
	CString m_strNumByteInObj;
	CString m_strASDU;
	CString m_strIOA;
	CComboBox m_cmbNumProcess;
	BOOL m_bFastBuf;
	CString m_strFastBufSize;
	CString m_strStartPMZAddr;
	CString m_strNaborNum;
	CString m_strObjNumInNabor;
	afx_msg void OnCbnSelendokCombo1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
