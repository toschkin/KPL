#pragma once

#include "Main_Set.h"
#include "Iec101m.h"
#include "Iec103m.h"
#include "Iec104m.h"
#include "ModbusM.h"
#include "ModbusTCPM.h"
#include "Iec101s.h"
#include "Iec104s.h"
#include "ModbusS.h"
#include "Korundm.h"
#include "Retr.h"
#include "GPSTime.h"
#include "KPLVersion.h"
#include "GPIOm.h"
#include "BUI.h"
#include "SPAm.h"
#include "STM.h"

class CKPLProject : public CKPLVersion
{
public:	
	CMain_Set		m_Main_Set;
	CRetr			m_Retr;
	CGPSTime		m_GPSTime;
	CIec101mArray	m_Iec101mArray;
	CIec104mArray	m_Iec104mArray;
	CIec103mArray	m_Iec103mArray;
	CModbusMArray	m_ModbusMArray;
	CIec104sArray	m_Iec104sArray;
	CIec101sArray	m_Iec101sArray;
	CModbusSArray	m_ModbusSArray;
	CIecKorundmArray	m_IecKorundmArray;
	CGPIOmArray		m_GPIOmArray;
	CMapboardArray	m_MapboardArray;
	CSPAmArray		m_SPAmArray;
	CModbusTCPMArray	m_ModbusTCPMArray;
	CSTMArray m_STMArray;

	

	void operator = (const CKPLProject& aKPLProject)
	{
		m_Main_Set = aKPLProject.m_Main_Set;
		m_Retr = aKPLProject.m_Retr;
		m_GPSTime = aKPLProject.m_GPSTime;
		m_Iec101mArray.Copy(aKPLProject.m_Iec101mArray);
		m_Iec104mArray.Copy(aKPLProject.m_Iec104mArray);
		m_Iec103mArray.Copy(aKPLProject.m_Iec103mArray);
		m_ModbusMArray.Copy(aKPLProject.m_ModbusMArray);
		m_Iec104sArray.Copy(aKPLProject.m_Iec104sArray);
		m_Iec101sArray.Copy(aKPLProject.m_Iec101sArray);
		m_ModbusSArray.Copy(aKPLProject.m_ModbusSArray);		
		m_IecKorundmArray.Copy(aKPLProject.m_IecKorundmArray);		
		m_GPIOmArray.Copy(aKPLProject.m_GPIOmArray);		
		m_MapboardArray.Copy(aKPLProject.m_MapboardArray);
		m_SPAmArray.Copy(aKPLProject.m_SPAmArray);
		m_ModbusTCPMArray.Copy(aKPLProject.m_ModbusTCPMArray);
		m_STMArray.Copy(aKPLProject.m_STMArray);
	}

	BOOL SaveProject(CString strDirectory,CString strFTPSite,CFtpConnection* pFtpConn = NULL);
	BOOL LoadProject(CString strDirectory);
	BOOL LoadProjectFTP(CString strFTPSite,CFtpConnection* pFtpConn = NULL);

	BOOL IsPortDuplicated(int nPort,int nProcNum);

	void RenumerateChannels(int nFrom,BOOL bDelete=TRUE);

	CKPLProject(void);
	~CKPLProject(void);
};
