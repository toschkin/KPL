#pragma once

#include "KPLVersion.h"
#include "Tu.h"

struct IndividualStructureGPIO: public CKPLVersion
{
	int CHANNEL_NUM;
	int ADDRESS_PMZ;
	CString strCOMMENT;

	IndividualStructureGPIO()
	{
		CHANNEL_NUM=0;
		ADDRESS_PMZ=0;
		strCOMMENT=" ";
	}
	IndividualStructureGPIO(const IndividualStructureGPIO& aIndividualStructureGPIO)
	{
		CHANNEL_NUM=aIndividualStructureGPIO.CHANNEL_NUM;
		ADDRESS_PMZ=aIndividualStructureGPIO.ADDRESS_PMZ;		
		strCOMMENT=aIndividualStructureGPIO.strCOMMENT;
	}
	void operator = (const IndividualStructureGPIO& aIndividualStructureGPIO)
	{	
		CHANNEL_NUM=aIndividualStructureGPIO.CHANNEL_NUM;
		ADDRESS_PMZ=aIndividualStructureGPIO.ADDRESS_PMZ;		
		strCOMMENT=aIndividualStructureGPIO.strCOMMENT;
	}
};

typedef CArray<IndividualStructureGPIO,IndividualStructureGPIO> CIndividualStructureGPIOArray;

class CGPIOm;
typedef CArray<CGPIOm,CGPIOm> CGPIOmArray;

class CGPIOm:public CKPLVersion
{
public:
	int m_nProcNum;

	int SERVICE;
	int BUTTONS_ENABLE;// включение -1  /отключение -0 кнопок на GP17-GP14
	int BUTTONS_DELAY;//=1000 задержка чтения на дребезг контактов кнопок
	int TS_DELAY;///=1000 задержка чтения на дребезг контактов ТС
	
	CGPIOm(const CGPIOm& aGPIOm)
	{
		m_nProcNum=aGPIOm.m_nProcNum;
		SERVICE=aGPIOm.SERVICE;
		BUTTONS_ENABLE=aGPIOm.BUTTONS_ENABLE;// включение -1  /отключение -0 кнопок на GP17-GP14
		BUTTONS_DELAY=aGPIOm.BUTTONS_DELAY;//=1000 задержка чтения на дребезг контактов кнопок
		TS_DELAY=aGPIOm.TS_DELAY;
		m_IndividualStructureGPIOArray.RemoveAll();
		for(int i = 0; i < aGPIOm.m_IndividualStructureGPIOArray.GetSize(); i++)
			m_IndividualStructureGPIOArray.Add(aGPIOm.m_IndividualStructureGPIOArray[i]);
		m_TuArray.Copy(aGPIOm.m_TuArray);
	}
	void operator = (const CGPIOm& aGPIOm)
	{
		m_nProcNum=aGPIOm.m_nProcNum;
		SERVICE=aGPIOm.SERVICE;
		BUTTONS_ENABLE=aGPIOm.BUTTONS_ENABLE;// включение -1  /отключение -0 кнопок на GP17-GP14
		BUTTONS_DELAY=aGPIOm.BUTTONS_DELAY;//=1000 задержка чтения на дребезг контактов кнопок
		TS_DELAY=aGPIOm.TS_DELAY;
		m_IndividualStructureGPIOArray.RemoveAll();
		for(int i = 0; i < aGPIOm.m_IndividualStructureGPIOArray.GetSize(); i++)
			m_IndividualStructureGPIOArray.Add(aGPIOm.m_IndividualStructureGPIOArray[i]);
		m_TuArray.Copy(aGPIOm.m_TuArray);
	}

	CIndividualStructureGPIOArray m_IndividualStructureGPIOArray;
	CTuArray	m_TuArray;

	CGPIOm(void);
	~CGPIOm(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);
};
