// AddDiapModbusDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddDiapModbusDlg.h"


// диалоговое окно CAddDiapModbusDlg

IMPLEMENT_DYNAMIC(CAddDiapModbusDlg, CDialog)

CAddDiapModbusDlg::CAddDiapModbusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDiapModbusDlg::IDD, pParent)
{

}

CAddDiapModbusDlg::~CAddDiapModbusDlg()
{
}

void CAddDiapModbusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtComment);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypePribor);
	DDX_Control(pDX, IDC_EDIT10, m_edtStartModbusAddr);
	DDX_Control(pDX, IDC_EDIT13, m_edtEndModbusAddr);
	DDX_Control(pDX, IDC_EDIT14, m_edtFunc);
	DDX_Control(pDX, IDC_EDIT15, m_edtStartReg);
	DDX_Control(pDX, IDC_EDIT16, m_edtNumberReg);
	DDX_Control(pDX, IDC_EDIT17, m_edtStartAddrMap);
	DDX_Control(pDX, IDC_EDIT18, m_edtStart2b);
	DDX_Control(pDX, IDC_EDIT19, m_edtNumber2b);
	DDX_Control(pDX, IDC_EDIT20, m_edtStart4b);
	DDX_Control(pDX, IDC_EDIT21, m_edtNumber4b);
	DDX_Control(pDX, IDC_EDIT22, m_edtStartAddrMap4b);
	DDX_Control(pDX, IDC_COMBO3, m_cmbTypeStatus);
	DDX_Control(pDX, IDC_EDIT23, m_edtAddrStatus);
	DDX_Control(pDX, IDC_EDIT24, m_edtMaskStatus);
}


BEGIN_MESSAGE_MAP(CAddDiapModbusDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddDiapModbusDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CAddDiapModbusDlg

void CAddDiapModbusDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnOK();
}

BOOL CAddDiapModbusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	m_PriborArray.SetSize(1);

	/*DDX_Control(pDX, IDC_EDIT1, );
	DDX_Control(pDX, IDC_COMBO1, );
	DDX_Control(pDX, IDC_EDIT10, );
	DDX_Control(pDX, IDC_EDIT13, );
	DDX_Control(pDX, IDC_EDIT14, );
	DDX_Control(pDX, IDC_EDIT15, );
	DDX_Control(pDX, IDC_EDIT16, );
	DDX_Control(pDX, IDC_EDIT17, );
	DDX_Control(pDX, IDC_EDIT18, );
	DDX_Control(pDX, IDC_EDIT19, );
	DDX_Control(pDX, IDC_EDIT20, );
	DDX_Control(pDX, IDC_EDIT21, );
	DDX_Control(pDX, IDC_EDIT22, );
	DDX_Control(pDX, IDC_COMBO3, );
	DDX_Control(pDX, IDC_EDIT23, );
	DDX_Control(pDX, IDC_EDIT24, );*/
	

	CStringArray strOptions;
	CArray<DWORD,DWORD> arrData;
	strOptions.Add("SATEC");
	arrData.Add(1);
	strOptions.Add("МТЕ");	
	arrData.Add(2);	
	strOptions.Add("МТЕ(2-х байтный)");
	arrData.Add(7);
	strOptions.Add("ТС-32");
	arrData.Add(4);
	strOptions.Add("ТУ-32");
	arrData.Add(5);
	strOptions.Add("ТИ-16");
	arrData.Add(6);
	strOptions.Add("Внешний");//0		
	arrData.Add(0);
	strOptions.Add("SATEC TC");
	arrData.Add(8);

	for(int i = 0; i < strOptions.GetSize(); i++)
	{
		int ind = m_cmbTypePribor.AddString(strOptions[i]);
		m_cmbTypePribor.SetItemData(ind,arrData[i]);
	}
	m_cmbTypePribor.SetCurSel(0);

	strOptions.RemoveAll();
	arrData.RemoveAll();

	strOptions.Add("нет");
	arrData.Add(0);
	strOptions.Add("в посылке");
	arrData.Add(1);
	strOptions.Add("в карте памяти");
	arrData.Add(2);
	
	for(int i = 0; i < strOptions.GetSize(); i++)
	{
		int ind = m_cmbTypeStatus.AddString(strOptions[i]);
		m_cmbTypeStatus.SetItemData(ind,arrData[i]);
	}
	m_cmbTypeStatus.SetCurSel(0);

	CString str;
	m_edtComment.SetWindowText(m_PriborArray[0].strCOMMENT);
	str.Format("%d",m_PriborArray[0].ADRESS);
	m_edtStartModbusAddr.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].ADRESS);
	m_edtEndModbusAddr.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].FUNCTION);
	m_edtFunc.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].START_ADRESS);
	m_edtStartReg.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].NUMBER);
	m_edtNumberReg.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].ADRESS_PMZ);
	m_edtStartAddrMap.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].DOP_BYTE1);
	m_edtStart2b.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].DOP_BYTE2);
	m_edtNumber2b.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].DOP_BYTE3);
	m_edtStart4b.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].DOP_BYTE4);
	m_edtNumber4b.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].ADRES_4B);
	m_edtStartAddrMap4b.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].ADRES_STATUS);
	m_edtAddrStatus.SetWindowText(str);
	str.Format("%d",m_PriborArray[0].MASKA_STATUS);
	m_edtMaskStatus.SetWindowText(str);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddDiapModbusDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_PriborArray.RemoveAll();

	CString str;
	UINT low = 0;
	UINT high = 0;
	
	m_edtStartModbusAddr.GetWindowText(str);
	low = (UINT)atoi(str);
	m_edtEndModbusAddr.GetWindowText(str);
	high = (UINT)atoi(str);

	if((low > high)||(low > 255)||(high > 255))
	{
		AfxMessageBox("Неверный диапазон адресов приборов!");
		return;
	}
	m_PriborArray.SetSize((high-low)+1);

	for(int i = 0; i < m_PriborArray.GetSize(); i++)
	{
		m_PriborArray[i].ADRESS = low+i;
		m_edtComment.GetWindowText(str);
		m_PriborArray[i].strCOMMENT = str;
		m_edtFunc.GetWindowText(str);	
		m_PriborArray[i].FUNCTION = atoi(str);
		m_edtStartReg.GetWindowText(str);
		m_PriborArray[i].START_ADRESS = atoi(str);			
		m_edtNumberReg.GetWindowText(str);	
		m_PriborArray[i].NUMBER = atoi(str);			
		m_edtStartAddrMap.GetWindowText(str);
		m_PriborArray[i].ADRESS_PMZ = atoi(str);			
		m_edtStart2b.GetWindowText(str);
		m_PriborArray[i].DOP_BYTE1 = atoi(str);			
		m_edtNumber2b.GetWindowText(str);
		m_PriborArray[i].DOP_BYTE2 = atoi(str);			
		m_edtStart4b.GetWindowText(str);
		m_PriborArray[i].DOP_BYTE3 = atoi(str);			
		m_edtNumber4b.GetWindowText(str);
		m_PriborArray[i].DOP_BYTE4 = atoi(str);			
		m_edtStartAddrMap4b.GetWindowText(str);
		m_PriborArray[i].ADRES_4B = atoi(str);			
		m_edtAddrStatus.GetWindowText(str);
		m_PriborArray[i].ADRES_STATUS = atoi(str);			
		m_edtMaskStatus.GetWindowText(str);
		m_PriborArray[i].MASKA_STATUS = atoi(str);
		m_PriborArray[i].PRIBOR = m_cmbTypePribor.GetItemData(m_cmbTypePribor.GetCurSel());
		m_PriborArray[i].TYPE_STATUS = m_cmbTypeStatus.GetItemData(m_cmbTypeStatus.GetCurSel());
	}

	CDialog::OnOK();
}



BOOL CAddDiapModbusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	if( pMsg->message == WM_KEYDOWN )
    {
        if(pMsg->wParam == VK_RETURN
            || pMsg->wParam == VK_ESCAPE )
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return TRUE;                    // DO NOT process further
        }
    }	
	return CDialog::PreTranslateMessage(pMsg);
}
