#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "WaitDlg.h"
#define TYPE_ALARM	1
#define TYPE_LOG	2
// диалоговое окно CGetFilesDlg

class CGetFilesDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetFilesDlg)

public:

	CWaitDlg m_WaitDlg;

	CGetFilesDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CGetFilesDlg();

	CFtpConnection* m_pFtpConn;
	CString m_strFtpLog;
	CString m_strFtpAlarm;

	CString m_strLogPath;
	CString m_strAlarmPath;

	BYTE m_byTypeDlg;
	CGridCtrl m_GridDisk;	
	CGridCtrl m_GridKPL;	
	void UpdateDiskGrid(void);
	void UpdateKPLGrid(void);
// Данные диалогового окна
	enum { IDD = IDD_FILEGETDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnGridDblClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
