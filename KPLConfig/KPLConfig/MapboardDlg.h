#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "BUI.h"
// диалоговое окно CMapboardDlg

class CMapboardDlg : public CDialog
{
	DECLARE_DYNAMIC(CMapboardDlg)
	
	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;	
	CMapboard m_Mapboard;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;
public:
	CMapboardDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CMapboardDlg();

// Данные диалогового окна
	enum { IDD = IDD_BUI_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnPrint(void);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
};
