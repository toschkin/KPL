#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "Iec101s.h"

// диалоговое окно CIec101sDlg

class CIec101sDlg : public CDialog
{
	DECLARE_DYNAMIC(CIec101sDlg)

public:
	CIec101sDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CIec101sDlg();

	CStringArray arrMain_Set_ObjectTypes;
	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;	
	CIec101s m_Iec101s;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;
// Данные диалогового окна
	enum { IDD = IDD_IEC101S_DIALOG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnPrint(void);
};
