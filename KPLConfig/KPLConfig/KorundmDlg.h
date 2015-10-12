#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "Korundm.h"

// диалоговое окно CKorundmDlg

class CKorundmDlg : public CDialog
{
	DECLARE_DYNAMIC(CKorundmDlg)

public:
	CKorundmDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CKorundmDlg();

	CStringArray arrMain_Set_ObjectTypes;
	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;
	CGridCtrl m_GridData;
	CGridCtrl m_GridKP;
	CIecKorundm m_Korundm;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;
// Данные диалогового окна
	enum { IDD = IDD_KORUNDM_DIALOG };

	void UpdateDataGrid(void);
	void UpdateKPGrid(void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();	
	afx_msg void OnAddDiap();	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedCancel2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnRClickGrid3(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnPrint1(void);
	afx_msg void OnPrint2(void);
	afx_msg void OnPrint3(void);
};
