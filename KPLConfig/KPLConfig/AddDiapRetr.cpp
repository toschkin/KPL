// AddDiapRetr.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapRetr.h"


// диалоговое окно CAddDiapRetr

IMPLEMENT_DYNAMIC(CAddDiapRetr, CDialog)

CAddDiapRetr::CAddDiapRetr(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapRetr::IDD, pParent)
	, m_strNumSets(_T(""))
	, m_strStartPMZAddr(_T(""))
	, m_strStartRetrAddr(_T(""))
	, m_srtNumObj(_T(""))
	, m_strComment(_T(""))
{

}

CAddDiapRetr::~CAddDiapRetr()
{
}

void CAddDiapRetr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT10, m_strNumSets);
	DDX_Text(pDX, IDC_EDIT1, m_strStartPMZAddr);
	DDX_Text(pDX, IDC_EDIT2, m_strStartRetrAddr);
	DDX_Text(pDX, IDC_EDIT4, m_srtNumObj);
	DDX_Control(pDX, IDC_COMBO1, m_cmbProcessRetr);
	DDX_Text(pDX, IDC_EDIT11, m_strComment);
}


BEGIN_MESSAGE_MAP(CAddDiapRetr, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapRetr

void CAddDiapRetr::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	UpdateData(TRUE);
	
		
	CManyRetrArray arr;

	int nStartPMZAddr= atoi(m_strStartPMZAddr);
	int nStartRetrAddr= atoi(m_strStartRetrAddr);

	int nCount = atoi(m_strNumSets);

	if(nCount > 0)
	{
		arr.SetSize(nCount);
		int nLastaddrPMZ = nStartPMZAddr;
		int nLastaddrRetr = nStartRetrAddr;

		for(int i = 0; i < arr.GetSize(); i++)
		{
			ManyRetr st;
			st.PATH_DIRECT = m_cmbProcessRetr.GetItemData(m_cmbProcessRetr.GetCurSel());
			st.NUM_MANY_RETR_OBJECT = atoi(m_srtNumObj);
			st.strCOMMENT = m_strComment;
			st.START_ADRES_OBJECT = nLastaddrPMZ;
			nLastaddrPMZ = st.START_ADRES_OBJECT+(st.NUM_MANY_RETR_OBJECT);
			st.START_ADRES_RETR = nLastaddrRetr;
			nLastaddrRetr = st.START_ADRES_RETR+(st.NUM_MANY_RETR_OBJECT);
			arr[i] = st;			
		}
		m_Retr.m_ManyRetrArray.Append(arr);
	}

	CDialog::OnOK();
}

BOOL CAddDiapRetr::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	m_strNumSets ="1";
	m_strStartPMZAddr="0";
	m_strStartRetrAddr="0";
	m_srtNumObj="1";
	m_strComment = " ";
	UpdateData(FALSE);

	CString str;	
	int nInd =-1;
	for(int j = 0; j < m_Main_Set.m_ProcessInfoArray.GetSize();j++)
	{
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 2)
		{
			str.Format("№%d (MODBUS-slave)",j+1);			
			nInd = m_cmbProcessRetr.AddString(str);
			m_cmbProcessRetr.SetItemData(nInd,j+1);
		}
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 4)
		{
			str.Format("№%d (IEC870-5-101-slave)",j+1);
			nInd = m_cmbProcessRetr.AddString(str);
			m_cmbProcessRetr.SetItemData(nInd,j+1);
		}
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 8)
		{
			str.Format("№%d (IEC870-5-104-slave PtP)",j+1);
			nInd = m_cmbProcessRetr.AddString(str);
			m_cmbProcessRetr.SetItemData(nInd,j+1);
		}		
		if(m_Main_Set.m_ProcessInfoArray[j].TYPE_PROTOKOL == 14)
		{
			str.Format("№%d (IEC870-5-104-slave PtMP)",j+1);
			nInd = m_cmbProcessRetr.AddString(str);
			m_cmbProcessRetr.SetItemData(nInd,j+1);
		}		
	}
	m_cmbProcessRetr.SetCurSel(0);

	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
