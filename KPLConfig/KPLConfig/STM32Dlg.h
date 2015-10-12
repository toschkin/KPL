#pragma once

#include "..\GRID\GridCtrl.h"
#include "..\GRID\GridCellNumeric.h"
#include "..\GRID\GridCellCombo.h"
#include "..\GRID\GridCellCheck.h"
#include "STM.h"
// диалоговое окно CSTM32Dlg

class CSTM32Dlg : public CDialog
{
	DECLARE_DYNAMIC(CSTM32Dlg)

public:
	CSTM32Dlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CSTM32Dlg();

	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;
	CGridCtrl m_GridSTMChannels;
	CSTM m_STM;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(BOOL bSilent);
	CRect m_Rect;
	void UpdateChannelsGrid(void);
	void UpdateGrid(void);
// Данные диалогового окна
	enum { IDD = IDD_STM32_DIALOG };
		
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAdd();	
	afx_msg void OnDel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnPrint1(void);
	afx_msg void OnPrint2(void);
	afx_msg void OnSettings(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);	
	afx_msg void OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult);
};
