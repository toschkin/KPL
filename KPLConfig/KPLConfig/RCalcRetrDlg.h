#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"

#include "Retr.h"

// диалоговое окно CRCalcRetrDlg

class CRCalcRetrDlg : public CDialog
{
	DECLARE_DYNAMIC(CRCalcRetrDlg)

public:
	CRCalcRetrDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CRCalcRetrDlg();

	CRetr m_Retr;
	CGridCtrl m_Grid;
	CRect m_Rect;
	void UpdateGrid(void);
	BOOL SaveGrid(void);

// Данные диалогового окна
	enum { IDD = IDD_RETRCALC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnAdd();	
	afx_msg void OnAddDiapason();	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDel();
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPrint(void);
};
