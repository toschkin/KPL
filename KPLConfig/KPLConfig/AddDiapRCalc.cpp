// AddDiapRCalc.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapRCalc.h"

// диалоговое окно CAddDiapRCalc

IMPLEMENT_DYNAMIC(CAddDiapRCalc, CDialog)

CAddDiapRCalc::CAddDiapRCalc(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapRCalc::IDD, pParent)
	, m_nCount(0)
	, m_nAddrIOSrc(0)
	, m_nAddrIODest(0)
	, m_nPosByteSrc(0)
	, m_nPosByteDest(0)
	, m_nBytesNum(0)
	, m_fScale(0)
	, m_fZeroShift(0)
	, m_fMaxVal(0)
	, m_fMinVal(0)
	, m_nRazmax(0)
	, m_bSign(FALSE)
	, m_strComment(_T(""))
{

}

CAddDiapRCalc::~CAddDiapRCalc()
{
}

void CAddDiapRCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT10, m_nCount);
	DDX_Text(pDX, IDC_EDIT1, m_nAddrIOSrc);
	DDX_Text(pDX, IDC_EDIT2, m_nAddrIODest);
	DDX_Text(pDX, IDC_EDIT3, m_nPosByteSrc);
	DDX_Text(pDX, IDC_EDIT5, m_nPosByteDest);
	DDX_Text(pDX, IDC_EDIT4, m_nBytesNum);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeRetr);
	DDX_Text(pDX, IDC_EDIT7, m_fScale);
	DDX_Text(pDX, IDC_EDIT8, m_fZeroShift);
	DDX_Text(pDX, IDC_EDIT25, m_fMaxVal);
	DDX_Text(pDX, IDC_EDIT9, m_fMinVal);
	DDX_Text(pDX, IDC_EDIT17, m_nRazmax);
	DDX_Check(pDX, IDC_CHECK1, m_bSign);
	DDX_Text(pDX, IDC_EDIT11, m_strComment);
}


BEGIN_MESSAGE_MAP(CAddDiapRCalc, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapRCalc

void CAddDiapRCalc::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	UpdateData(TRUE);
	CCalcTIArray arr;

	/*
	m_nAddrIOSrc=0;
	m_nAddrIODest=0;
	m_nPosByteSrc=0;
	m_nPosByteDest=0;
	m_nBytesNum=1;
	*/

	if(m_nCount > 0)
	{
		arr.SetSize(m_nCount);
		int nLastaddrSrc  = m_nAddrIOSrc;
		int nLastaddrDest = m_nAddrIODest;

		/*if(m_nAddrIOSrc + m_nBytesNum*m_nCount > m_nAddrIODest)
		{
				AfxMessageBox("Неверно заданы максимум и минимум физю величины!");
				return;
		}*/

		for(int i = 0; i < arr.GetSize(); i++)
		{			
			CalcTI st;
			
			
			if(m_cmbTypeRetr.GetCurSel() != -1)
				st.TYPE = m_cmbTypeRetr.GetItemData(m_cmbTypeRetr.GetCurSel());
			else
			{
				CString str;
				m_cmbTypeRetr.GetWindowText(str);
				st.TYPE = atoi(str);
			}
			st.POSITION_BYTE = m_nPosByteSrc;
			st.POSITION_BYTE_TOO = m_nPosByteDest;
			st.CENA_SHKALI = m_fScale;
			st.DOPKODE_YES_NO = m_bSign;
			st.MAX_FIZ = m_fMaxVal;
			st.MIN_FIZ = m_fMinVal;
			if((int)m_fMaxVal < (int)m_fMinVal)
			{
				AfxMessageBox("Неверно заданы максимум и минимум физ. величины!");
				return;
			}
			st.MAX_SHKALA_FIZ = m_nRazmax;
			st.SMESHENIE = m_fZeroShift;			
			st.strCOMMENT = m_strComment;
			st.NUMBER_BYTE = m_nBytesNum;

			st.ADDRESS_FROM = nLastaddrSrc;
			nLastaddrSrc = st.ADDRESS_FROM+(st.NUMBER_BYTE);
			st.ADDRESS_TOO = nLastaddrDest;
			nLastaddrDest = st.ADDRESS_TOO+(st.NUMBER_BYTE);
			arr[i] = st;			
		}
		m_Retr.m_CalcTIArray.Append(arr);
	}

	CDialog::OnOK();
}

BOOL CAddDiapRCalc::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	m_nCount = 1;
	m_nAddrIOSrc=0;
	m_nAddrIODest=0;
	m_nPosByteSrc=0;
	m_nPosByteDest=0;
	m_nBytesNum=1;
	//CComboBox m_cmbTypeRetr;
	m_fScale = 1.0;
	m_fZeroShift = 0.0;
	m_fMaxVal = 0.0;
	m_fMinVal = 0.0;
	m_nRazmax = 255;
	m_bSign = TRUE;
	m_strComment = " ";
	UpdateData(FALSE);
	
	int nInd = -1;
	nInd = m_cmbTypeRetr.AddString("байтовая");
	m_cmbTypeRetr.SetItemData(nInd,2);
	nInd = m_cmbTypeRetr.AddString("2 байта в 1");
	m_cmbTypeRetr.SetItemData(nInd,4);
	nInd = m_cmbTypeRetr.AddString("4 байта в 1");
	m_cmbTypeRetr.SetItemData(nInd,6);
	nInd = m_cmbTypeRetr.AddString("4 байта в 2");
	m_cmbTypeRetr.SetItemData(nInd,7);
	nInd = m_cmbTypeRetr.AddString("4 байта в 2+1");
	m_cmbTypeRetr.SetItemData(nInd,8);

	m_cmbTypeRetr.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
