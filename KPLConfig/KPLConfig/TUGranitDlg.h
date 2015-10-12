#pragma once
#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "STM.h"

// диалоговое окно CTUGranitDlg

class CTUGranitDlg : public CDialog
{
	DECLARE_DYNAMIC(CTUGranitDlg)

public:
	CTUGranitDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CTUGranitDlg();

// Данные диалогового окна
	enum { IDD = IDD_TU_GRANIT_DIALOG };

	CTUGranitArray m_TUGranitArray;
	int m_nChannelNumber;
	CString strTitle;
	CGridCtrl m_Grid;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	CRect m_Rect;
	void UpdateGrid(void);
	BOOL SaveGrid(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);	
	afx_msg void OnAdd();			
	afx_msg void OnDel();	
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);		
	afx_msg void OnPrint(void);
};
