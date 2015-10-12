#pragma once
#include "..\..\GRID\GridCtrl.h"
#include "..\..\GRID\GridCellNumeric.h"
#include "..\..\GRID\GridCellCombo.h"
#include "..\..\GRID\GridCellCheck.h"
#include "GPSTime.h"

// диалоговое окно CGPSConfigDlg

class CGPSConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CGPSConfigDlg)

public:

	CGridCtrl m_Grid;
	CGPSTime m_GPSTime;

	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	
	CGPSConfigDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CGPSConfigDlg();

// Данные диалогового окна
	enum { IDD = IDD_GPS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();	
public:
	virtual BOOL OnInitDialog();	
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnPrint(void);
};
