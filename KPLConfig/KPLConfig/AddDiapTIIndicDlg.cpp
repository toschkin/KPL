// AddDiapTIIndicDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapTIIndicDlg.h"


// диалоговое окно CAddDiapTIIndicDlg

IMPLEMENT_DYNAMIC(CAddDiapTIIndicDlg, CDialog)

CAddDiapTIIndicDlg::CAddDiapTIIndicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapTIIndicDlg::IDD, pParent)
{

}

CAddDiapTIIndicDlg::~CAddDiapTIIndicDlg()
{
}

void CAddDiapTIIndicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtComment);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeInd);	
	DDX_Control(pDX, IDC_COMBO4, m_cmbPKTS);
	DDX_Control(pDX, IDC_EDIT18, m_edtIndStart);
	DDX_Control(pDX, IDC_EDIT19, m_edtIndEnd);
	DDX_Control(pDX, IDC_EDIT17, m_edtPMZStart);
	DDX_Control(pDX, IDC_COMBO5, m_cmbSign);
	DDX_Control(pDX, IDC_EDIT21, m_edtScale);
	DDX_Control(pDX, IDC_EDIT22, m_edtZeroShift);
	DDX_Control(pDX, IDC_EDIT25, m_edtMin);
	DDX_Control(pDX, IDC_EDIT23, m_edtMax);
	DDX_Control(pDX, IDC_COMBO6, m_cmbFormat);
	DDX_Control(pDX, IDC_COMBO7, m_cmbDot);
}


BEGIN_MESSAGE_MAP(CAddDiapTIIndicDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapTIIndicDlg

BOOL CAddDiapTIIndicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	int ind = m_cmbTypeInd.AddString("сегментный");
	m_cmbTypeInd.SetItemData(ind,4);	
	m_cmbTypeInd.SetCurSel(0);

	m_cmbFormat.SetItemData(m_cmbFormat.AddString("прямой код"),0);	
	m_cmbFormat.SetItemData(m_cmbFormat.AddString("дополн. код"),1);	
	m_cmbFormat.SetItemData(m_cmbFormat.AddString("КОМПАС"),2);	
	m_cmbFormat.SetCurSel(0);


	m_cmbDot.SetItemData(m_cmbDot.AddString("нет"),0);	
	m_cmbDot.SetItemData(m_cmbDot.AddString("есть"),1);
	m_cmbDot.SetCurSel(0);

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
	m_edtIndEnd.SetWindowText("32");
	m_edtPMZStart.SetWindowText("0");

	m_edtScale.SetWindowText("1.0");
	m_edtZeroShift.SetWindowText("0.0");
	m_edtMin.SetWindowText("0.0");
	m_edtMax.SetWindowText("0.0");
	
	m_cmbSign.SetItemData(m_cmbSign.AddString("_"),0x3A);	
	m_cmbSign.SetItemData(m_cmbSign.AddString("/\\"),0x3C);
	m_cmbSign.SetItemData(m_cmbSign.AddString("\\/"),0x3D);
	m_cmbSign.SetItemData(m_cmbSign.AddString(">"),0x3E);
	m_cmbSign.SetItemData(m_cmbSign.AddString("<"),0x3F);	
	m_cmbSign.SetItemData(m_cmbSign.AddString("+"),0x5C);
	m_cmbSign.SetItemData(m_cmbSign.AddString("-"),0x5D);				
	m_cmbSign.SetItemData(m_cmbSign.AddString("A"),0x41);
	m_cmbSign.SetItemData(m_cmbSign.AddString("B"),0x42);
	m_cmbSign.SetItemData(m_cmbSign.AddString("C"),0x43);
	m_cmbSign.SetItemData(m_cmbSign.AddString("D"),0x44);
	m_cmbSign.SetItemData(m_cmbSign.AddString("E"),0x45);
	m_cmbSign.SetItemData(m_cmbSign.AddString("F"),0x46);
	m_cmbSign.SetItemData(m_cmbSign.AddString("G"),0x47);
	m_cmbSign.SetItemData(m_cmbSign.AddString("H"),0x48);
	m_cmbSign.SetItemData(m_cmbSign.AddString("I"),0x49);
	m_cmbSign.SetItemData(m_cmbSign.AddString("J"),0x4A);
	m_cmbSign.SetItemData(m_cmbSign.AddString("K"),0x4B);
	m_cmbSign.SetItemData(m_cmbSign.AddString("L"),0x4C);
	m_cmbSign.SetItemData(m_cmbSign.AddString("M"),0x4D);
	m_cmbSign.SetItemData(m_cmbSign.AddString("N"),0x4E);
	m_cmbSign.SetItemData(m_cmbSign.AddString("O"),0x4F);
	m_cmbSign.SetItemData(m_cmbSign.AddString("P"),0x50);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Q"),0x51);
	m_cmbSign.SetItemData(m_cmbSign.AddString("R"),0x52);
	m_cmbSign.SetItemData(m_cmbSign.AddString("S"),0x53);
	m_cmbSign.SetItemData(m_cmbSign.AddString("T"),0x54);
	m_cmbSign.SetItemData(m_cmbSign.AddString("U"),0x55);
	m_cmbSign.SetItemData(m_cmbSign.AddString("V"),0x56);
	m_cmbSign.SetItemData(m_cmbSign.AddString("W"),0x57);
	m_cmbSign.SetItemData(m_cmbSign.AddString("X"),0x58);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Y"),0x59);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Z"),0x5A);				
	m_cmbSign.SetItemData(m_cmbSign.AddString("А"),0x80);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Б"),0x81);
	m_cmbSign.SetItemData(m_cmbSign.AddString("В"),0x82);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Г"),0x83);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Д"),0x84);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Е"),0x85);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ж"),0x86);
	m_cmbSign.SetItemData(m_cmbSign.AddString("З"),0x87);
	m_cmbSign.SetItemData(m_cmbSign.AddString("И"),0x88);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Й"),0x89);
	m_cmbSign.SetItemData(m_cmbSign.AddString("К"),0x8A);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Л"),0x8B);
	m_cmbSign.SetItemData(m_cmbSign.AddString("М"),0x8C);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Н"),0x8D);
	m_cmbSign.SetItemData(m_cmbSign.AddString("О"),0x8E);
	m_cmbSign.SetItemData(m_cmbSign.AddString("П"),0x8F);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Р"),0x90);
	m_cmbSign.SetItemData(m_cmbSign.AddString("С"),0x91);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Т"),0x92);
	m_cmbSign.SetItemData(m_cmbSign.AddString("У"),0x93);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ф"),0x94);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Х"),0x95);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ц"),0x96);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ч"),0x97);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ш"),0x98);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Щ"),0x99);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ъ"),0x9A);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ы"),0x9B);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ь"),0x9C);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Э"),0x9D);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Ю"),0x9E);
	m_cmbSign.SetItemData(m_cmbSign.AddString("Я"),0x9F);	
	m_cmbSign.SetCurSel(5);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDiapTIIndicDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_MacrosBUIArray.RemoveAll();
	CString str;
	m_edtIndStart.GetWindowText(str);
	int nIndStart	= atoi(str);
	m_edtIndEnd.GetWindowText(str);
	int nIndEnd		= atoi(str);

	m_edtPMZStart.GetWindowText(str);
	int nPMZStart = atoi(str);

	CString strComment;
	m_edtComment.GetWindowText(strComment);

	m_edtScale.GetWindowText(str);
	double Scale = atof(str);
	m_edtZeroShift.GetWindowText(str);
	double ZSH = atof(str);
	m_edtMin.GetWindowText(str);
	double Min = atof(str);
	m_edtMax.GetWindowText(str);
	double Max = atof(str);

	int nFormat = m_cmbFormat.GetItemData(m_cmbFormat.GetCurSel());		
	int nDot = m_cmbDot.GetItemData(m_cmbDot.GetCurSel());			

	if((nIndStart > nIndEnd)||(nIndStart == 0)||(nIndEnd == 0))
	{
		AfxMessageBox("Неверно заданы значения полей № Индикатора");
		return;
	}
	m_MacrosBUIArray.SetSize((nIndEnd-nIndStart)+1);

	for(int i = 0; i < (int)m_MacrosBUIArray.GetCount();i++)
	{
		m_MacrosBUIArray[i].NUMBER_POSITION = nIndStart;
		nIndStart++;
		m_MacrosBUIArray[i].ADDRESS_PMZ = nPMZStart;
		nPMZStart++;
		m_MacrosBUIArray[i].ADDRESS_BUI = m_cmbPKTS.GetItemData(m_cmbPKTS.GetCurSel());		
		m_MacrosBUIArray[i].TYPE = (BYTE)m_cmbTypeInd.GetItemData(m_cmbTypeInd.GetCurSel());
		m_MacrosBUIArray[i].strCOMMENT = strComment;
		m_MacrosBUIArray[i].CENA_SHKALI = Scale;
		m_MacrosBUIArray[i].SMESHENIE = ZSH;
		m_MacrosBUIArray[i].MIN = Min;
		m_MacrosBUIArray[i].MAX = Max;
		m_MacrosBUIArray[i].ZNAK = m_cmbSign.GetItemData(m_cmbSign.GetCurSel());
		m_MacrosBUIArray[i].DOP_FLAG = (nDot<<2)|nFormat;
	}
	CDialog::OnOK();
}
