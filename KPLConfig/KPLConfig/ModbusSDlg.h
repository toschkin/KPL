#pragma once

#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "ModbusS.h"
#include "afxwin.h"

// диалоговое окно CModbusSDlg

class CModbusSDlg : public CDialog
{
	DECLARE_DYNAMIC(CModbusSDlg)

public:
	CModbusSDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CModbusSDlg();

	CStringArray arrMain_Set_ObjectTypes;
	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;
	CGridCtrl m_GridCalc;
	CModbusS m_ModbusS;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;
	void UpdateCalcGrid(void);
// Данные диалогового окна
	enum { IDD = IDD_MODBUSS_DIALOG };

	void RessizeControls(int cx,int cy);
	void UpdateDataGrid(void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);	
	afx_msg void OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnAdd();	
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnRClickGrid2(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnDel();
	CStatic m_stCalcCap;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPrint1(void);
	afx_msg void OnPrint2(void);
	afx_msg void OnAddDiapason();	
};
