
// KPLConfigDlg.h : файл заголовка
//

#pragma once
#include "afxcmn.h"

#include "..\GRID\GridCtrl.h"
#include "..\GRID\GridCellNumeric.h"
#include "..\GRID\GridCellCombo.h"
#include "..\GRID\GridCellCheck.h"


#include "KPLConfig.h"

#include "Iec101mDlg.h"
#include "Iec103mDlg.h"
#include "ModbusMDlg.h"
#include "Iec104sDlg.h"
#include "Iec101sDlg.h"
#include "Iec104mDlg.h"
#include "ModbusSDlg.h"
#include "RetrConfigDlg.h"
#include "AddDiapMaskDlg.h"
#include "AddIODiapDlg.h"
#include "ClientSocket.h"
#include "WaitDlg.h"
#include "GPSConfigDlg.h"
#include "KorundmDlg.h"
#include "GPIOmDlg.h"
#include "SPAmDlg.h"
#include "MapboardDlg.h"
#include "STM32Dlg.h"
#include "afxwin.h"


#define SERVICE_COMMAND_EXIT_APP	1
#define SERVICE_COMMAND_STOP_SOFT	2

// диалоговое окно CKPLConfigDlg
class CKPLConfigDlg : public CDialog
{
// Создание
public:
	CKPLConfigDlg(CWnd* pParent = NULL);	// стандартный конструктор

	CString m_strLastProjectPath;
// Данные диалогового окна
	enum { IDD = IDD_KPLCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

	CWaitDlg m_WaitDlg;

	CArray<int,int> arrObjectTypesInt;
	CStringArray arrMain_Set_ProcessesTypes;
	CStringArray arrMain_Set_ObjectTypes;	
	BOOL RebootOnTelnet(CString strHost);
	BOOL ChangeFileOptionsOnTelnet(CString strHost);
	CClientSocket * m_pTelnetSocket;

	void ChangeTab(int tab);
	BOOL SaveTab(int tab);
	CGridCtrl m_Grid;
	int m_nOldTab;
	CString m_strFtpUser;
	CString m_strFtpPassword;
	CString m_strFtpSite;
	CString m_strFtpHome;
	CString m_strFtpLog;
	CString m_strFtpAlarm;	
	BOOL SendAndCheckServiceCommandFile(CFtpConnection* pFtpConn,CString strFtp,int nCommand,int nTimeout=5000);
	

	CString m_strLogPath;
	CString m_strAlarmPath;

	CAddDiapMaskDlg m_AddDiapMaskDlg;
	CAddIODiapDlg m_AddIODiapDlg;

	void UpdateCombo(void);	

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_MainTab;
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnAdd();
	afx_msg void OnAddDiapason();	
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDel();
	afx_msg void OnSave();
	afx_msg void OnOpen();
	afx_msg void OnDetail();
	afx_msg void OnCopy();	
	
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	afx_msg void OnPrint();
	afx_msg void OnSaveToKsri();
	afx_msg void OnOpenFtp();
	afx_msg void OnUploadfw();
	afx_msg void OnDownloadfw();
	afx_msg void OnAlarm();
	afx_msg void OnLog();
	afx_msg void On32794();
	afx_msg void OnTelnet();
	CComboBox m_cmbVersion;
	afx_msg void OnCbnSelendokComboversion();
	afx_msg void OnStopkplsoft();
};
