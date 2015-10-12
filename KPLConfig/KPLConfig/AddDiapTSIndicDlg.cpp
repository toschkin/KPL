// AddDiapTSIndicDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapTSIndicDlg.h"


// диалоговое окно CAddDiapTSIndicDlg

IMPLEMENT_DYNAMIC(CAddDiapTSIndicDlg, CDialog)

CAddDiapTSIndicDlg::CAddDiapTSIndicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapTSIndicDlg::IDD, pParent)
{

}

CAddDiapTSIndicDlg::~CAddDiapTSIndicDlg()
{
}

void CAddDiapTSIndicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtComment);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeInd);
	DDX_Control(pDX, IDC_COMBO2, m_cmbTypeMapboard);
	DDX_Control(pDX, IDC_COMBO4, m_cmbPKTS);
	DDX_Control(pDX, IDC_EDIT18, m_edtIndStart);
	DDX_Control(pDX, IDC_EDIT19, m_edtIndEnd);
	DDX_Control(pDX, IDC_EDIT17, m_edtPMZStart);
	DDX_Control(pDX, IDC_COMBO5, m_cmbByte);
	DDX_Control(pDX, IDC_COMBO6, m_cmbBit);
	DDX_Control(pDX, IDC_COMBO7, m_cmbColourON);
	DDX_Control(pDX, IDC_COMBO8, m_cmbColourOFF);
	DDX_Control(pDX, IDC_EDIT21, m_edtValON);
}


BEGIN_MESSAGE_MAP(CAddDiapTSIndicDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapTSIndicDlg

void CAddDiapTSIndicDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_MacrosBUTSArray.RemoveAll();
	CString str;
	m_edtIndStart.GetWindowText(str);
	int nIndStart	= atoi(str);
	m_edtIndEnd.GetWindowText(str);
	int nIndEnd		= atoi(str);

	m_edtPMZStart.GetWindowText(str);
	int nPMZStart = atoi(str);

	CString strComment;
	m_edtComment.GetWindowText(strComment);

	m_edtValON.GetWindowText(str);
	int nValON = atoi(str);

	if((nIndStart > nIndEnd)||(nIndStart == 0)||(nIndEnd == 0))
	{
		AfxMessageBox("Неверно заданы значения полей № Индикатора");
		return;
	}
	m_MacrosBUTSArray.SetSize((nIndEnd-nIndStart)+1);

	for(int i = 0; i < (int)m_MacrosBUTSArray.GetCount();i++)
	{
		m_MacrosBUTSArray[i].NUMBER_POSITION = nIndStart;
		nIndStart++;
		m_MacrosBUTSArray[i].ADDRESS_PMZ = nPMZStart;
		nPMZStart++;
		m_MacrosBUTSArray[i].ADDRESS_BUTS = m_cmbPKTS.GetItemData(m_cmbPKTS.GetCurSel());
		
		BYTE nTypeInd = (BYTE)m_cmbTypeInd.GetItemData(m_cmbTypeInd.GetCurSel());
		BYTE nTypeMapboard = (BYTE)m_cmbTypeMapboard.GetItemData(m_cmbTypeMapboard.GetCurSel())<<4;
		m_MacrosBUTSArray[i].TYPE = 0;
		m_MacrosBUTSArray[i].TYPE |= nTypeInd;
		m_MacrosBUTSArray[i].TYPE |= nTypeMapboard;

		m_MacrosBUTSArray[i].COLOR_OFF = m_cmbColourOFF.GetItemData(m_cmbColourOFF.GetCurSel());
		m_MacrosBUTSArray[i].COLOR_ON  = m_cmbColourON.GetItemData(m_cmbColourON.GetCurSel());
		m_MacrosBUTSArray[i].POS_BYTE = m_cmbByte.GetItemData(m_cmbByte.GetCurSel());
		m_MacrosBUTSArray[i].POS_BIT = m_cmbBit.GetItemData(m_cmbBit.GetCurSel());
		m_MacrosBUTSArray[i].strCOMMENT = strComment;
		m_MacrosBUTSArray[i].ON_VALUE = nValON;		
	}
	CDialog::OnOK();
}

BOOL CAddDiapTSIndicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int ind = m_cmbTypeInd.AddString("единичный");
	m_cmbTypeInd.SetItemData(ind,2);
	ind = m_cmbTypeInd.AddString("матричный");
	m_cmbTypeInd.SetItemData(ind,3);	
	m_cmbTypeInd.SetCurSel(0);

	ind = m_cmbTypeMapboard.AddString("светлый");
	m_cmbTypeMapboard.SetItemData(ind,0);
	ind = m_cmbTypeMapboard.AddString("тёмный");
	m_cmbTypeMapboard.SetItemData(ind,1);	
	ind = m_cmbTypeMapboard.AddString("полутёмный");
	m_cmbTypeMapboard.SetItemData(ind,2);	
	ind = m_cmbTypeMapboard.AddString("ПНУ");
	m_cmbTypeMapboard.SetItemData(ind,3);	
	ind = m_cmbTypeMapboard.AddString("инв. полутёмный");
	m_cmbTypeMapboard.SetItemData(ind,4);
	m_cmbTypeMapboard.SetCurSel(0);

	CString str;
	for(int i = 1; i < 255;i++)
	{
		str.Format("%d",i);
		m_cmbPKTS.SetItemData(m_cmbPKTS.AddString(str),i);		
	}
	m_cmbPKTS.SetCurSel(0);
	
	m_edtIndStart.SetLimitText(2);
	m_edtIndEnd.SetLimitText(3);

	m_edtIndStart.SetWindowText("1");
	m_edtIndEnd.SetWindowText("64");
	
	m_edtPMZStart.SetWindowText("0");
	m_edtValON.SetWindowText("1");

	for(int i = 0; i < 12;i++)
	{
		str.Format("%d",i);		
		m_cmbByte.SetItemData(m_cmbByte.AddString(str),i);
		if(i < 8)
			m_cmbBit.SetItemData(m_cmbBit.AddString(str),i);
	}
	m_cmbBit.SetCurSel(0);
	m_cmbByte.SetCurSel(0);

	ind = m_cmbColourON.AddString("потушен");
	m_cmbColourON.SetItemData(ind,0);
	ind = m_cmbColourON.AddString("зелёный");
	m_cmbColourON.SetItemData(ind,1);
	ind = m_cmbColourON.AddString("красный");
	m_cmbColourON.SetItemData(ind,2);
	ind = m_cmbColourON.AddString("оранжевый");
	m_cmbColourON.SetItemData(ind,3);
	ind = m_cmbColourON.AddString("красн.-зел.");
	m_cmbColourON.SetItemData(ind,4);
	
	ind = m_cmbColourOFF.AddString("потушен");
	m_cmbColourOFF.SetItemData(ind,0);
	ind = m_cmbColourOFF.AddString("зелёный");
	m_cmbColourOFF.SetItemData(ind,1);
	ind = m_cmbColourOFF.AddString("красный");
	m_cmbColourOFF.SetItemData(ind,2);
	ind = m_cmbColourOFF.AddString("оранжевый");
	m_cmbColourOFF.SetItemData(ind,3);
	ind = m_cmbColourOFF.AddString("красн.-зел.");
	m_cmbColourOFF.SetItemData(ind,4);

	m_cmbColourON.SetCurSel(1);
	m_cmbColourOFF.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
