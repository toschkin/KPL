// AddIODiapDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "KPLConfig.h"
#include "AddIODiapDlg.h"


// диалоговое окно CAddIODiapDlg

IMPLEMENT_DYNAMIC(CAddIODiapDlg, CDialog)

CAddIODiapDlg::CAddIODiapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddIODiapDlg::IDD, pParent)
	, m_strComment(_T(""))
	, m_strNumByteInObj(_T("1"))
	, m_strASDU(_T("1"))
	, m_strIOA(_T("0"))
	, m_bFastBuf(FALSE)
	, m_strFastBufSize(_T("0"))
	, m_strStartPMZAddr(_T("0"))
	, m_strNaborNum(_T("1"))
	, m_strObjNumInNabor(_T("0"))
{

}

CAddIODiapDlg::~CAddIODiapDlg()
{
}

void CAddIODiapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strComment);
	DDX_Control(pDX, IDC_COMBO1, m_cmbTypeIO);
	DDX_Text(pDX, IDC_EDIT10, m_strNumByteInObj);
	DDX_Text(pDX, IDC_EDIT14, m_strASDU);
	DDX_Text(pDX, IDC_EDIT18, m_strIOA);
	DDX_Control(pDX, IDC_COMBO3, m_cmbNumProcess);
	DDX_Check(pDX, IDC_CHECK1, m_bFastBuf);
	DDX_Text(pDX, IDC_EDIT23, m_strFastBufSize);
	DDX_Text(pDX, IDC_EDIT17, m_strStartPMZAddr);
	DDX_Text(pDX, IDC_EDIT21, m_strNaborNum);
	DDX_Text(pDX, IDC_EDIT19, m_strObjNumInNabor);
}


BEGIN_MESSAGE_MAP(CAddIODiapDlg, CDialog)
	ON_CBN_SELENDOK(IDC_COMBO1, &CAddIODiapDlg::OnCbnSelendokCombo1)
END_MESSAGE_MAP()


// обработчики сообщений CAddIODiapDlg

BOOL CAddIODiapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_arrIniObject.RemoveAll();
	// TODO:  Добавить дополнительную инициализацию
	m_cmbTypeIO.ResetContent();
	
	//CIniObjectArray m_arrIniObject;
	//CStringArray arrMain_Set_ObjectTypes,arrMain_Set_Processes;

	for(int i = 0; i < arrMain_Set_ObjectTypes.GetSize(); i++)
	{
		int nInd = m_cmbTypeIO.AddString(arrMain_Set_ObjectTypes[i]);
		m_cmbTypeIO.SetItemData(nInd,arrObjectTypesInt[i]);		
	}
	m_cmbTypeIO.SetWindowText("0");

	for(int j = 0; j < arrMain_Set_Processes.GetSize(); j++)
	{
		int nInd = m_cmbNumProcess.AddString(arrMain_Set_Processes[j]);
		m_cmbNumProcess.SetItemData(nInd,(DWORD)atoi(arrMain_Set_Processes[j]));		
	}
	m_cmbNumProcess.SetCurSel(0);
	

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CAddIODiapDlg::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	UpdateData(TRUE);	

	if(m_strNaborNum.IsEmpty() || m_strNumByteInObj.IsEmpty() || m_strASDU.IsEmpty() 
		|| m_strIOA.IsEmpty() ||m_strFastBufSize.IsEmpty() ||m_strStartPMZAddr.IsEmpty() ||m_strObjNumInNabor.IsEmpty())
	{
		AfxMessageBox("Не задано одно из полей!");
		return;
	}

	int nNaborNum = atoi(m_strNaborNum);
	int nObjNumInNabor = atoi(m_strObjNumInNabor);

	

	if(nNaborNum <= 0)
		CDialog::OnCancel();

	CString str;
	/*
	, m_strStartPMZAddr(_T("0"))
	
	, m_strObjNumInNabor(_T("0"))*/

	//CIniObjectArray m_arrIniObject
	for(int i = 0; i < nNaborNum; i++)
	{
		IniObject iniobj;
		iniobj.strCOMMENT = m_strComment;
		iniobj.NUM_DATE = atoi(m_strNumByteInObj);
		iniobj.ADRES_ASDU = atoi(m_strASDU);
		iniobj.REAL_ADRES = atoi(m_strIOA);
		if(m_bFastBuf)
			iniobj.YES_NO_FASTBUF = 1;
		iniobj.SIZE_FAST_BUF = atoi(m_strFastBufSize);
		iniobj.NUMBER_DIRECT = m_cmbNumProcess.GetItemData(m_cmbNumProcess.GetCurSel());		
		iniobj.NUMBER_OBJECT = atoi(m_strObjNumInNabor);

		int nStartPMZ = atoi(m_strStartPMZAddr);

		iniobj.START_ADRES_PMZ = nStartPMZ + i*iniobj.NUMBER_OBJECT;

		m_cmbTypeIO.GetWindowText(str);
		for(int l = 0; l < arrMain_Set_ObjectTypes.GetSize();l++)					
		{
			if(str == arrMain_Set_ObjectTypes[l])
			{
				iniobj.TYPE_OBJECT = arrObjectTypesInt[l];
				break;
			}
		}
		if(iniobj.TYPE_OBJECT==0)
			iniobj.TYPE_OBJECT = atoi(str);

		if((iniobj.TYPE_OBJECT == M_SP_NA_1)||(iniobj.TYPE_OBJECT == M_SP_TA_1)||(iniobj.TYPE_OBJECT == M_SP_TB_1))
		{
				iniobj.GENTYPE_OBJECT=M_SP_NA_1;
				iniobj.GEN_NUMBYTE = 1;
		}
		else if((iniobj.TYPE_OBJECT == M_DP_NA_1)||(iniobj.TYPE_OBJECT == M_DP_TA_1)||(iniobj.TYPE_OBJECT == M_DP_TB_1))
		{
				iniobj.GENTYPE_OBJECT=M_DP_NA_1;
				iniobj.GEN_NUMBYTE=1;
		}
		else if((iniobj.TYPE_OBJECT == M_ME_NA_1)||(iniobj.TYPE_OBJECT == M_ME_TA_1)||(iniobj.TYPE_OBJECT == M_ME_TD_1))
		{
				iniobj.GENTYPE_OBJECT=M_ME_NA_1;
				iniobj.GEN_NUMBYTE=3;
		}
		else if((iniobj.TYPE_OBJECT == M_ME_NB_1)||(iniobj.TYPE_OBJECT == M_ME_TB_1)||(iniobj.TYPE_OBJECT == M_ME_TE_1))
		{
				iniobj.GENTYPE_OBJECT=M_ME_NB_1;
				iniobj.GEN_NUMBYTE=3;
		}
		else if((iniobj.TYPE_OBJECT == M_ME_NC_1)||(iniobj.TYPE_OBJECT == M_ME_TC_1)||(iniobj.TYPE_OBJECT == M_ME_TF_1))
		{
				iniobj.GENTYPE_OBJECT=M_ME_NC_1;
				iniobj.GEN_NUMBYTE=5;
		}
		else if((iniobj.TYPE_OBJECT == M_ME_ND_1))
		{
				iniobj.GENTYPE_OBJECT=M_ME_ND_1;
				iniobj.GEN_NUMBYTE=2;
		}
		else if((iniobj.TYPE_OBJECT == M_BO_NA_1)||(iniobj.TYPE_OBJECT == M_BO_TA_1)||(iniobj.TYPE_OBJECT == M_BO_TB_1))
		{
				iniobj.GENTYPE_OBJECT=M_BO_NA_1;
				iniobj.GEN_NUMBYTE=5;
		}
		else
		{
			iniobj.GENTYPE_OBJECT = iniobj.TYPE_OBJECT;
			iniobj.GEN_NUMBYTE = iniobj.NUM_DATE;
		}
		m_arrIniObject.Add(iniobj);
	}

	CDialog::OnOK();
}

void CAddIODiapDlg::OnCbnSelendokCombo1()
{
	UpdateData(TRUE);
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_cmbTypeIO.GetLBText(m_cmbTypeIO.GetCurSel(),str);

	if(str == arrMain_Set_ObjectTypes[0])
	{
		//pItem->iRow,pItem->iColumn,M_SP_NA_1);
		m_strNumByteInObj = _T("1");
	}
	else if(str == arrMain_Set_ObjectTypes[1])
	{
		//pItem->iRow,pItem->iColumn,M_SP_TA_1);
		m_strNumByteInObj = _T("4");
	}
	else if(str == arrMain_Set_ObjectTypes[2])
	{
		//pItem->iRow,pItem->iColumn,M_SP_TB_1);
		m_strNumByteInObj = _T("8");
	}
	else if(str == arrMain_Set_ObjectTypes[3])
	{
		//pItem->iRow,pItem->iColumn,M_DP_NA_1);
		m_strNumByteInObj = _T("1");
	}
	else if(str == arrMain_Set_ObjectTypes[4])
	{
		//pItem->iRow,pItem->iColumn,M_DP_TA_1);
		m_strNumByteInObj = _T("4");
	}
	else if(str == arrMain_Set_ObjectTypes[5])
	{
		//pItem->iRow,pItem->iColumn,M_DP_TB_1);
		m_strNumByteInObj = _T("8");
	}
	else if(str == arrMain_Set_ObjectTypes[6])
	{
		//pItem->iRow,pItem->iColumn,M_ME_NA_1);
		m_strNumByteInObj = _T("3");
	}
	else if(str == arrMain_Set_ObjectTypes[7])
	{
		//pItem->iRow,pItem->iColumn,M_ME_TA_1);
		m_strNumByteInObj = _T("6");
	}
	else if(str == arrMain_Set_ObjectTypes[8])
	{
		m_strNumByteInObj = _T("10");
		//pItem->iRow,pItem->iColumn,M_ME_TD_1);
	}
	else if(str == arrMain_Set_ObjectTypes[9])
	{
		//pItem->iRow,pItem->iColumn,M_ME_ND_1);
		m_strNumByteInObj = _T("2");
	}
	else if(str == arrMain_Set_ObjectTypes[10])
	{
		//pItem->iRow,pItem->iColumn,M_ME_NB_1);
		m_strNumByteInObj = _T("3");
	}
	else if(str == arrMain_Set_ObjectTypes[11])
	{
		//pItem->iRow,pItem->iColumn,M_ME_TB_1);
		m_strNumByteInObj = _T("6");
	}
	else if(str == arrMain_Set_ObjectTypes[12])
	{
		//pItem->iRow,pItem->iColumn,M_ME_TE_1);
		m_strNumByteInObj = _T("10");
	}
	else if(str == arrMain_Set_ObjectTypes[13])
	{
		//pItem->iRow,pItem->iColumn,M_ME_NC_1);
		m_strNumByteInObj = _T("5");
	}
	else if(str == arrMain_Set_ObjectTypes[14])
	{
		//pItem->iRow,pItem->iColumn,M_ME_TC_1);
		m_strNumByteInObj = _T("8");
	}
	else if(str == arrMain_Set_ObjectTypes[15])
	{
		//pItem->iRow,pItem->iColumn,M_ME_TF_1);
		m_strNumByteInObj = _T("12");
	}
	else if(str == arrMain_Set_ObjectTypes[16])
	{
		//pItem->iRow,pItem->iColumn,M_BO_NA_1);
		m_strNumByteInObj = _T("5");
	}
	else if(str == arrMain_Set_ObjectTypes[17])
	{
		//pItem->iRow,pItem->iColumn,M_BO_TA_1);
		m_strNumByteInObj = _T("8");
	}
	else if(str == arrMain_Set_ObjectTypes[18])
	{
		//pItem->iRow,pItem->iColumn,M_BO_TB_1);
		m_strNumByteInObj = _T("12");
	}
	
	UpdateData(FALSE);
}

BOOL CAddIODiapDlg::PreTranslateMessage(MSG* pMsg)
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
