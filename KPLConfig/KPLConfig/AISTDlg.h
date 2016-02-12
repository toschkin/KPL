#pragma once

#include "..\GRID\GridCtrl.h"
#include "..\GRID\GridCellNumeric.h"
#include "..\GRID\GridCellCombo.h"
#include "..\GRID\GridCellCheck.h"
#include "STM.h"


// ���������� ���� CAISTDlg

class CAISTDlg : public CDialog
{
	DECLARE_DYNAMIC(CAISTDlg)

public:
	CAISTDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CAISTDlg();

// ������ ����������� ����
	enum { IDD = IDD_AIST_DIALOG };

	�AIST m_AIST;
	int m_nChannelNumber;
	CString strTitle;
	CGridCtrl m_Grid;
	CGridCtrl m_GridData;
	
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;
	void UpdateDataGrid(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnAdd();	
	//afx_msg void OnAddDiapason();	
	afx_msg void OnDel();	
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnRClickGrid1(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);	
	afx_msg void OnGridEndEdit1(NMHDR *pNotifyStruct, LRESULT* pResult);		
	afx_msg void OnPrint1(void);
	afx_msg void OnPrint2(void);	
};
