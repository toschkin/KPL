#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "Iec101m.h"
// диалоговое окно CTuConfigTUDlg

class CTuConfigTUDlg : public CDialog
{
	DECLARE_DYNAMIC(CTuConfigTUDlg)

public:
	CTuConfigTUDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CTuConfigTUDlg();
	
	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;
	CTuArray m_TuArray;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	CRect m_Rect;
	void UpdateGrid(void);

	BOOL SaveGrid(void);

	BYTE m_nProcType;

// Данные диалогового окна
	enum { IDD = IDD_TU_DIALOG };
	
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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPrint(void);
};
