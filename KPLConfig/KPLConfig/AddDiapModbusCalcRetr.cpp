// AddDiapModbusCalcRetr.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapModbusCalcRetr.h"


// диалоговое окно CAddDiapModbusCalcRetr

IMPLEMENT_DYNAMIC(CAddDiapModbusCalcRetr, CDialog)

CAddDiapModbusCalcRetr::CAddDiapModbusCalcRetr(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapModbusCalcRetr::IDD, pParent)
	, m_nCount(0)
	, m_nAddrIOSrc(0)
	, m_nAddrIODest(0)
	, m_nPosByteSrc(0)
	, m_nPosByteDest(0)
	, m_nPosBitSrc(0)
	, m_nPosBitDest(0)
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

CAddDiapModbusCalcRetr::~CAddDiapModbusCalcRetr()
{
}

void CAddDiapModbusCalcRetr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT10, m_nCount);
	DDX_Text(pDX, IDC_EDIT1, m_nAddrIOSrc);
	DDX_Text(pDX, IDC_EDIT2, m_nAddrIODest);
	DDX_Text(pDX, IDC_EDIT3, m_nPosByteSrc);
	DDX_Text(pDX, IDC_EDIT5, m_nPosByteDest);
	DDX_Text(pDX, IDC_EDIT19, m_nPosBitSrc);
	DDX_Text(pDX, IDC_EDIT12, m_nPosBitDest);
	DDX_Text(pDX, IDC_EDIT4, m_nBytesNum);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeRetr);
	DDX_Text(pDX, IDC_EDIT7, m_fScale);
	DDX_Text(pDX, IDC_EDIT8, m_fZeroShift);
	DDX_Text(pDX, IDC_EDIT25, m_fMaxVal);
	DDX_Text(pDX, IDC_EDIT9, m_fMinVal);
	DDX_Text(pDX, IDC_EDIT17, m_nRazmax);
	DDX_Check(pDX, IDC_CHECK1, m_bSign);
	DDX_Text(pDX, IDC_EDIT11, m_strComment);
	DDX_Control(pDX, IDC_EDIT3, m_edtPosByteSrc);
	DDX_Control(pDX, IDC_EDIT19, m_edtPosBitSrc);
	DDX_Control(pDX, IDC_EDIT12, m_edtPosBitDest);
}


BEGIN_MESSAGE_MAP(CAddDiapModbusCalcRetr, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapModbusCalcRetr

BOOL CAddDiapModbusCalcRetr::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	m_nCount = 1;
	m_nAddrIOSrc=0;
	m_nAddrIODest=0;
	m_nPosByteSrc=0;
	m_nPosByteDest=0;
	m_nBytesNum=1;
	m_fScale = 1.0;
	m_fZeroShift = 0.0;
	m_fMaxVal = 0.0;
	m_fMinVal = 0.0;
	m_nRazmax = 255;
	m_bSign = TRUE;
	m_strComment = " ";
	UpdateData(FALSE);
	
	int nInd = -1;
	nInd = m_cmbTypeRetr.AddString("битовая");
	m_cmbTypeRetr.SetItemData(nInd,1);
	nInd = m_cmbTypeRetr.AddString("байтовая");
	m_cmbTypeRetr.SetItemData(nInd,2);
	nInd = m_cmbTypeRetr.AddString("2 байта в 1");
	m_cmbTypeRetr.SetItemData(nInd,4);
	nInd = m_cmbTypeRetr.AddString("4 байта в 1");
	m_cmbTypeRetr.SetItemData(nInd,6);

	m_cmbTypeRetr.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDiapModbusCalcRetr::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	UpdateData(TRUE);
	CalcStructureModbusSArray arr;

	if(m_nCount > 0)
	{
		arr.SetSize(m_nCount);
		int nLastaddrSrc  = m_nAddrIOSrc;
		int nLastaddrDest = m_nAddrIODest;

		for(int i = 0; i < arr.GetSize(); i++)
		{			
			CalcStructureModbusS st;
			
			
			if(m_cmbTypeRetr.GetCurSel() != -1)
				st.TYPE = m_cmbTypeRetr.GetItemData(m_cmbTypeRetr.GetCurSel());
			else
			{
				CString str;
				m_cmbTypeRetr.GetWindowText(str);
				st.TYPE = atoi(str);
			}
			st.POSITION_BIT = m_nPosBitSrc;
			st.POSITION_BIT_TOO = m_nPosBitDest;
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
		m_ModbusS.m_CalcStructureModbusSArray.Append(arr);
	}

	CDialog::OnOK();
}
