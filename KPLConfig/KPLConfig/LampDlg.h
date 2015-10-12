#pragma once

#define IND_TS 100
#define IND_TI 101

#include "BUI.h"
#include "..\GRID\GridCtrl.h"
#include "..\GRID\GridCellNumeric.h"
#include "..\GRID\GridCellCombo.h"
#include "..\GRID\GridCellCheck.h"

// диалоговое окно CLampDlg

class CLampDlg : public CDialog
{
	DECLARE_DYNAMIC(CLampDlg)

public:
	CLampDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CLampDlg();

	BYTE m_byTypeInd;
	CString strTitle;
	CGridCtrl m_Grid;	
	CMapboard m_Mapboard;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	void DrawGrid(void);
	CRect m_Rect;
// Данные диалогового окна
	enum { IDD = IDD_LAMP_DIALOG };

	void DrawRowTS(int nRow);
	void DrawRowTI(int nRow);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnPrint(void);
	afx_msg void OnAdd();	
	afx_msg void OnAddDiap();		
	afx_msg void OnDel();
};
