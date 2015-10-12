#pragma once

#include "..\GRID\GridCtrl.h"
#include "..\GRID\GridCellNumeric.h"
#include "..\GRID\GridCellCombo.h"
#include "..\GRID\GridCellCheck.h"
#include "Iec104s.h"

// ���������� ���� CIec104sDlg

class CIec104sDlg : public CDialog
{
	DECLARE_DYNAMIC(CIec104sDlg)

public:
	CIec104sDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CIec104sDlg();

	BYTE m_byProcType; //8 - ptp  14 -ptmp
	CStringArray arrMain_Set_ObjectTypes;
	int nProcNum;
	CString strTitle;
	CGridCtrl m_Grid;	
	CIec104s m_Iec104s;
	int m_nStartPMZAddr;
	int m_nEndPMZAddr;
	BOOL ProcessSave(void);
	CRect m_Rect;
// ������ ����������� ����
	enum { IDD = IDD_IEC104S_DIALOG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);	
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRClickGrid(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnPrint(void);
};
