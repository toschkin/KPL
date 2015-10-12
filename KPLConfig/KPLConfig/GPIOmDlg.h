#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "GPIOm.h"
#include "afxwin.h"

// диалоговое окно CGPIOmDlg

class CGPIOmDlg : public CDialog
{
	DECLARE_DYNAMIC(CGPIOmDlg)

public:
	CGPIOmDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CGPIOmDlg();


// Данные диалогового окна
	enum { IDD = IDD_GPIO_DIALOG };

	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;

	CGPIOm m_GPIOm;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;

	void UpdateDataGrid(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bService;

	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();		
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);		
	//afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);		
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	afx_msg void OnPrint1(void);	
protected:
	virtual void OnOK();
public:
	BOOL m_bButtonsEnable;
	CEdit m_edtDrebezgButton;
	CEdit m_edtDrebezgTS;
	CButton m_chkButtonsEnable;
};
