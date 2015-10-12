#pragma once
#include "KPLVersion.h"
#include "Tu.h"

#define TYPE103_1 1//сообщение с меткой времени
#define TYPE103_2 2// сообщение с меткой времени в относительном формате
#define TYPE103_3 3// измеряемые величины, набор типа 1
#define TYPE103_4 4// измеряемые величины с меткой времени с относительным временем
#define TYPE103_9 9// измеряемые величины, набор типа 2
#define TYPE103_10 10// групповая информация

struct IndividualStructure103: public CKPLVersion
{
	int LINK_ADDRESS;
	int TYPE_ID;
	int NUM_BYTE;
	int TYPE_ID_C_IC_NA_1;
	int NUM_BYTE_C_IC_NA_1;
	int ORIGINATOR_ADDRESS;
	int COMMON_ADDRESS_ASDU;
	int START_IOA;
	int AM_IOA;
	int ADDRESS_PMZ;
	int POZITION_OF_QUALITY_FLAG;
	int C_CS_ENABLE;
	int GLOBAL_ASDU;
	int STATUS_ADDRESS_PMZ;
	int STATUS_MASKA;
	int STATUS_TYPE;
	CString strCOMMENT;


	IndividualStructure103()
	{
		LINK_ADDRESS=1;
		TYPE_ID=1;
		NUM_BYTE=1;
		TYPE_ID_C_IC_NA_1=1;
		NUM_BYTE_C_IC_NA_1=1;
		ORIGINATOR_ADDRESS=0;
		COMMON_ADDRESS_ASDU=1;
		START_IOA=0;
		AM_IOA=0;
		ADDRESS_PMZ=0;
		POZITION_OF_QUALITY_FLAG=0;
		C_CS_ENABLE=0;
		GLOBAL_ASDU=0;
		STATUS_ADDRESS_PMZ=0;
		STATUS_MASKA=0;
		STATUS_TYPE=0;
		strCOMMENT=" ";
	}
	IndividualStructure103(const IndividualStructure103& aIndividualStructure103)
	{
		LINK_ADDRESS=aIndividualStructure103.LINK_ADDRESS;
		TYPE_ID=aIndividualStructure103.TYPE_ID;
		NUM_BYTE=aIndividualStructure103.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructure103.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructure103.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructure103.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructure103.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructure103.START_IOA;
		AM_IOA=aIndividualStructure103.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure103.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructure103.POZITION_OF_QUALITY_FLAG;

		C_CS_ENABLE=aIndividualStructure103.C_CS_ENABLE;
		GLOBAL_ASDU=aIndividualStructure103.GLOBAL_ASDU;
		STATUS_ADDRESS_PMZ=aIndividualStructure103.STATUS_ADDRESS_PMZ;
		STATUS_MASKA=aIndividualStructure103.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructure103.STATUS_TYPE;
		strCOMMENT=aIndividualStructure103.strCOMMENT;
	}
	void operator = (const IndividualStructure103& aIndividualStructure103)
	{
		LINK_ADDRESS=aIndividualStructure103.LINK_ADDRESS;
		TYPE_ID=aIndividualStructure103.TYPE_ID;
		NUM_BYTE=aIndividualStructure103.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructure103.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructure103.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructure103.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructure103.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructure103.START_IOA;
		AM_IOA=aIndividualStructure103.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure103.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructure103.POZITION_OF_QUALITY_FLAG;
		C_CS_ENABLE=aIndividualStructure103.C_CS_ENABLE;
		GLOBAL_ASDU=aIndividualStructure103.GLOBAL_ASDU;
		STATUS_ADDRESS_PMZ=aIndividualStructure103.STATUS_ADDRESS_PMZ;
		STATUS_MASKA=aIndividualStructure103.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructure103.STATUS_TYPE;
		strCOMMENT=aIndividualStructure103.strCOMMENT;
	}
};

typedef CArray<IndividualStructure103,IndividualStructure103> CIndividualStructure103Array;

class CIec103m;
typedef CArray<CIec103m,CIec103m> CIec103mArray;

class CIec103m:public CKPLVersion
{
public:
	int m_nProcNum;

	int PORT;
	int BAUDRATE;
	int STOPBITS;
	int PARITY;
	int BYTETIME;
	int WAITRESP;
	int NEXTMESSAGE;
	int AMOUNTBYTE;
	int FLOWCONTROLL;
	int NUMBER_NO_ANSWER;
	int ADRES_BADCHANEL;
	int NUMBER_OF_DEVICES;
	//int NUMBER_OF_INDIVIDUAL_STRUCTURES;
	int SIZE_LINK;
	int SIZE_COFT;
	int SIZE_ASDU;
	int SIZE_IOA;
	int PERIOD_C_IC_NA_1;
	int PERIOD_C_CS_NA_1;
	int TIME_TU_EXPIRE;

	CIec103m(const CIec103m& aIec103m)
	{
		m_nProcNum=aIec103m.m_nProcNum;
		PORT=aIec103m.PORT;
		BAUDRATE=aIec103m.BAUDRATE;
		STOPBITS=aIec103m.STOPBITS;
		PARITY=aIec103m.PARITY;
		BYTETIME=aIec103m.BYTETIME;
		WAITRESP=aIec103m.WAITRESP;
		NEXTMESSAGE=aIec103m.NEXTMESSAGE;
		AMOUNTBYTE=aIec103m.AMOUNTBYTE;
		FLOWCONTROLL=aIec103m.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aIec103m.NUMBER_NO_ANSWER;
		ADRES_BADCHANEL=aIec103m.ADRES_BADCHANEL;
		NUMBER_OF_DEVICES=aIec103m.NUMBER_OF_DEVICES;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES=aIec103m.;
		SIZE_LINK=aIec103m.SIZE_LINK;
		SIZE_COFT=aIec103m.SIZE_COFT;
		SIZE_ASDU=aIec103m.SIZE_ASDU;
		SIZE_IOA=aIec103m.SIZE_IOA;
		PERIOD_C_IC_NA_1=aIec103m.PERIOD_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIec103m.PERIOD_C_CS_NA_1;
		TIME_TU_EXPIRE=aIec103m.TIME_TU_EXPIRE;
		m_IndividualStructure103Array.RemoveAll();
		for(int i = 0; i < aIec103m.m_IndividualStructure103Array.GetSize(); i++)
			m_IndividualStructure103Array.Add(aIec103m.m_IndividualStructure103Array[i]);
		m_TuArray.Copy(aIec103m.m_TuArray);
	}
	void operator = (const CIec103m& aIec103m)
	{
		m_nProcNum=aIec103m.m_nProcNum;
		PORT=aIec103m.PORT;
		BAUDRATE=aIec103m.BAUDRATE;
		STOPBITS=aIec103m.STOPBITS;
		PARITY=aIec103m.PARITY;
		BYTETIME=aIec103m.BYTETIME;
		WAITRESP=aIec103m.WAITRESP;
		NEXTMESSAGE=aIec103m.NEXTMESSAGE;
		AMOUNTBYTE=aIec103m.AMOUNTBYTE;
		FLOWCONTROLL=aIec103m.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aIec103m.NUMBER_NO_ANSWER;
		ADRES_BADCHANEL=aIec103m.ADRES_BADCHANEL;
		NUMBER_OF_DEVICES=aIec103m.NUMBER_OF_DEVICES;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES=aIec103m.;
		SIZE_LINK=aIec103m.SIZE_LINK;
		SIZE_COFT=aIec103m.SIZE_COFT;
		SIZE_ASDU=aIec103m.SIZE_ASDU;
		SIZE_IOA=aIec103m.SIZE_IOA;
		PERIOD_C_IC_NA_1=aIec103m.PERIOD_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIec103m.PERIOD_C_CS_NA_1;
		TIME_TU_EXPIRE=aIec103m.TIME_TU_EXPIRE;
		m_IndividualStructure103Array.RemoveAll();
		for(int i = 0; i < aIec103m.m_IndividualStructure103Array.GetSize(); i++)
			m_IndividualStructure103Array.Add(aIec103m.m_IndividualStructure103Array[i]);
		m_TuArray.Copy(aIec103m.m_TuArray);
	}

	CIndividualStructure103Array m_IndividualStructure103Array;
	CTuArray	m_TuArray;

	CIec103m(void);
	~CIec103m(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);
};
