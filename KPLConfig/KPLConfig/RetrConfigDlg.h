#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "KPLProject.h"
// диалоговое окно CRetrConfigDlg

class CRetrConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CRetrConfigDlg)

public:
	CRetrConfigDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CRetrConfigDlg();

	CRetr m_Retr;
	CMain_Set	m_Main_Set;

	BOOL SaveGrid(void);

	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;	
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	CRect m_Rect;
	void UpdateGrid(void);

// Данные диалогового окна
	enum { IDD = IDD_RETR_DIALOG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();	
	afx_msg void OnAddDiapason();	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPrint(void);
};
