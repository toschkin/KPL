#pragma once

#include "KPLVersion.h"
#include "Tu.h"

#define M_SP_NA_1 0x01 // ТС
#define M_DP_NA_1 0x03 // двойной ТС
#define M_ME_NA_1 0x09 // ТИ нормализов.
#define M_ME_NB_1 0x0B // ТИ масштабированые
#define M_ME_NC_1 0x0D // ShortFloatingPointNumber
#define M_ME_ND_1 0x15 // ТИ нормализов.без описателя качества
#define M_BO_NA_1 0x07 // Bitstring of 32 bit
#define M_ST_NA_1 0x05 // Step Position
#define M_IT_NA_1 0x0F // Integrated totals
#define M_SP_TA_1 0x02 // ТС со временем 24
#define M_DP_TA_1 0x04 // двойной ТС со временем 24
#define M_ME_TA_1 0x0A // ТИ нормализов. со временем 24
#define M_ME_TB_1 0x0C // ТИ масштабированые со временем 24
#define M_ME_TC_1 0x0E // ShortFloatingPointNumber 24
#define M_BO_TA_1 0x08 // Bitstring of 32 bit 24
#define M_ST_TA_1 0x06 // Step Position 24
#define M_IT_TA_1 0x10 // Integrated totals 24
#define M_SP_TB_1 0x1E // ТС со временем 56
#define M_DP_TB_1 0x1F // двойной ТС со временем 56
#define M_ME_TD_1 0x22 // ТИ нормализов. со временем 56
#define M_ME_TE_1 0x23 // ТИ масштабированые со временем 56
#define M_ME_TF_1 0x24 // ShortFloatingPointNumber 56
#define M_BO_TB_1 0x21 // Bitstring of 32 bit 56
#define M_IT_TB_1 0x25 // Integrated totals 56

struct IndividualStructure101: public CKPLVersion
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

	IndividualStructure101()
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
	IndividualStructure101(const IndividualStructure101& aIndividualStructure101)
	{
		LINK_ADDRESS=aIndividualStructure101.LINK_ADDRESS;
		TYPE_ID=aIndividualStructure101.TYPE_ID;
		NUM_BYTE=aIndividualStructure101.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructure101.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructure101.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructure101.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructure101.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructure101.START_IOA;
		AM_IOA=aIndividualStructure101.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure101.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructure101.POZITION_OF_QUALITY_FLAG;

		C_CS_ENABLE=aIndividualStructure101.C_CS_ENABLE;
		GLOBAL_ASDU=aIndividualStructure101.GLOBAL_ASDU;
		STATUS_ADDRESS_PMZ=aIndividualStructure101.STATUS_ADDRESS_PMZ;
		STATUS_MASKA=aIndividualStructure101.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructure101.STATUS_TYPE;
		strCOMMENT=aIndividualStructure101.strCOMMENT;
	}
	void operator = (const IndividualStructure101& aIndividualStructure101)
	{
		LINK_ADDRESS=aIndividualStructure101.LINK_ADDRESS;
		TYPE_ID=aIndividualStructure101.TYPE_ID;
		NUM_BYTE=aIndividualStructure101.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructure101.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructure101.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructure101.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructure101.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructure101.START_IOA;
		AM_IOA=aIndividualStructure101.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure101.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructure101.POZITION_OF_QUALITY_FLAG;
		C_CS_ENABLE=aIndividualStructure101.C_CS_ENABLE;
		GLOBAL_ASDU=aIndividualStructure101.GLOBAL_ASDU;
		STATUS_ADDRESS_PMZ=aIndividualStructure101.STATUS_ADDRESS_PMZ;
		STATUS_MASKA=aIndividualStructure101.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructure101.STATUS_TYPE;
		strCOMMENT=aIndividualStructure101.strCOMMENT;
	}
};

typedef CArray<IndividualStructure101,IndividualStructure101> CIndividualStructure101Array;

class CIec101m;
typedef CArray<CIec101m,CIec101m> CIec101mArray;

class CIec101m:public CKPLVersion
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
	int RES_PORT;

	CIec101m(const CIec101m& aIec101m)
	{
		m_nProcNum=aIec101m.m_nProcNum;
		PORT=aIec101m.PORT;
		BAUDRATE=aIec101m.BAUDRATE;
		STOPBITS=aIec101m.STOPBITS;
		PARITY=aIec101m.PARITY;
		BYTETIME=aIec101m.BYTETIME;
		WAITRESP=aIec101m.WAITRESP;
		NEXTMESSAGE=aIec101m.NEXTMESSAGE;
		AMOUNTBYTE=aIec101m.AMOUNTBYTE;
		FLOWCONTROLL=aIec101m.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aIec101m.NUMBER_NO_ANSWER;
		ADRES_BADCHANEL=aIec101m.ADRES_BADCHANEL;
		NUMBER_OF_DEVICES=aIec101m.NUMBER_OF_DEVICES;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES=aIec101m.;
		SIZE_LINK=aIec101m.SIZE_LINK;
		SIZE_COFT=aIec101m.SIZE_COFT;
		SIZE_ASDU=aIec101m.SIZE_ASDU;
		SIZE_IOA=aIec101m.SIZE_IOA;
		PERIOD_C_IC_NA_1=aIec101m.PERIOD_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIec101m.PERIOD_C_CS_NA_1;
		TIME_TU_EXPIRE=aIec101m.TIME_TU_EXPIRE;
		RES_PORT=aIec101m.RES_PORT;
		m_IndividualStructure101Array.RemoveAll();
		for(int i = 0; i < aIec101m.m_IndividualStructure101Array.GetSize(); i++)
			m_IndividualStructure101Array.Add(aIec101m.m_IndividualStructure101Array[i]);
		m_TuArray.Copy(aIec101m.m_TuArray);
	}
	void operator = (const CIec101m& aIec101m)
	{
		m_nProcNum=aIec101m.m_nProcNum;
		PORT=aIec101m.PORT;
		BAUDRATE=aIec101m.BAUDRATE;
		STOPBITS=aIec101m.STOPBITS;
		PARITY=aIec101m.PARITY;
		BYTETIME=aIec101m.BYTETIME;
		WAITRESP=aIec101m.WAITRESP;
		NEXTMESSAGE=aIec101m.NEXTMESSAGE;
		AMOUNTBYTE=aIec101m.AMOUNTBYTE;
		FLOWCONTROLL=aIec101m.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aIec101m.NUMBER_NO_ANSWER;
		ADRES_BADCHANEL=aIec101m.ADRES_BADCHANEL;
		NUMBER_OF_DEVICES=aIec101m.NUMBER_OF_DEVICES;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES=aIec101m.;
		SIZE_LINK=aIec101m.SIZE_LINK;
		SIZE_COFT=aIec101m.SIZE_COFT;
		SIZE_ASDU=aIec101m.SIZE_ASDU;
		SIZE_IOA=aIec101m.SIZE_IOA;
		PERIOD_C_IC_NA_1=aIec101m.PERIOD_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIec101m.PERIOD_C_CS_NA_1;
		TIME_TU_EXPIRE=aIec101m.TIME_TU_EXPIRE;
		RES_PORT=aIec101m.RES_PORT;
		m_IndividualStructure101Array.RemoveAll();
		for(int i = 0; i < aIec101m.m_IndividualStructure101Array.GetSize(); i++)
			m_IndividualStructure101Array.Add(aIec101m.m_IndividualStructure101Array[i]);
		m_TuArray.Copy(aIec101m.m_TuArray);
	}

	CIndividualStructure101Array m_IndividualStructure101Array;
	CTuArray	m_TuArray;

	CIec101m(void);
	~CIec101m(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);
};
