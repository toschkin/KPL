#pragma once

#include "KPLVersion.h"

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

struct IndividualStructureKorund: public CKPLVersion
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
	/*int C_CS_ENABLE;
	int GLOBAL_ASDU;
	int STATUS_ADDRESS_PMZ;
	int STATUS_MASKA;
	int STATUS_TYPE;*/
	CString strCOMMENT;

	IndividualStructureKorund()
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
		/*C_CS_ENABLE=0;
		GLOBAL_ASDU=0;
		STATUS_ADDRESS_PMZ=0;
		STATUS_MASKA=0;
		STATUS_TYPE=0;*/
		strCOMMENT=" ";
	}
	IndividualStructureKorund(const IndividualStructureKorund& aIndividualStructureKorund)
	{
		LINK_ADDRESS=aIndividualStructureKorund.LINK_ADDRESS;
		TYPE_ID=aIndividualStructureKorund.TYPE_ID;
		NUM_BYTE=aIndividualStructureKorund.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructureKorund.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructureKorund.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructureKorund.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructureKorund.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructureKorund.START_IOA;
		AM_IOA=aIndividualStructureKorund.AM_IOA;
		ADDRESS_PMZ=aIndividualStructureKorund.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructureKorund.POZITION_OF_QUALITY_FLAG;

		/*C_CS_ENABLE=aIndividualStructureKorund.C_CS_ENABLE;
		GLOBAL_ASDU=aIndividualStructureKorund.GLOBAL_ASDU;
		STATUS_ADDRESS_PMZ=aIndividualStructureKorund.STATUS_ADDRESS_PMZ;
		STATUS_MASKA=aIndividualStructureKorund.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructureKorund.STATUS_TYPE;*/
		strCOMMENT=aIndividualStructureKorund.strCOMMENT;
	}
	void operator = (const IndividualStructureKorund& aIndividualStructureKorund)
	{
		LINK_ADDRESS=aIndividualStructureKorund.LINK_ADDRESS;
		TYPE_ID=aIndividualStructureKorund.TYPE_ID;
		NUM_BYTE=aIndividualStructureKorund.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructureKorund.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructureKorund.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructureKorund.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructureKorund.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructureKorund.START_IOA;
		AM_IOA=aIndividualStructureKorund.AM_IOA;
		ADDRESS_PMZ=aIndividualStructureKorund.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructureKorund.POZITION_OF_QUALITY_FLAG;

		/*C_CS_ENABLE=aIndividualStructureKorund.C_CS_ENABLE;
		GLOBAL_ASDU=aIndividualStructureKorund.GLOBAL_ASDU;
		STATUS_ADDRESS_PMZ=aIndividualStructureKorund.STATUS_ADDRESS_PMZ;
		STATUS_MASKA=aIndividualStructureKorund.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructureKorund.STATUS_TYPE;*/
		strCOMMENT=aIndividualStructureKorund.strCOMMENT;
	}
};

typedef CArray<IndividualStructureKorund,IndividualStructureKorund> CIndividualStructureKorundArray;

class CIecKorundm;
typedef CArray<CIecKorundm,CIecKorundm> CIecKorundmArray;

class CIecKorundm:public CKPLVersion
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
	//int RES_PORT;

	CIecKorundm(const CIecKorundm& aIecKorundm)
	{
		m_nProcNum=aIecKorundm.m_nProcNum;
		PORT=aIecKorundm.PORT;
		BAUDRATE=aIecKorundm.BAUDRATE;
		STOPBITS=aIecKorundm.STOPBITS;
		PARITY=aIecKorundm.PARITY;
		BYTETIME=aIecKorundm.BYTETIME;
		WAITRESP=aIecKorundm.WAITRESP;
		NEXTMESSAGE=aIecKorundm.NEXTMESSAGE;
		AMOUNTBYTE=aIecKorundm.AMOUNTBYTE;
		FLOWCONTROLL=aIecKorundm.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aIecKorundm.NUMBER_NO_ANSWER;
		ADRES_BADCHANEL=aIecKorundm.ADRES_BADCHANEL;
		NUMBER_OF_DEVICES=aIecKorundm.NUMBER_OF_DEVICES;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES=aIecKorundm.;
		SIZE_LINK=aIecKorundm.SIZE_LINK;
		SIZE_COFT=aIecKorundm.SIZE_COFT;
		SIZE_ASDU=aIecKorundm.SIZE_ASDU;
		SIZE_IOA=aIecKorundm.SIZE_IOA;
		PERIOD_C_IC_NA_1=aIecKorundm.PERIOD_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIecKorundm.PERIOD_C_CS_NA_1;
		TIME_TU_EXPIRE=aIecKorundm.TIME_TU_EXPIRE;
		//RES_PORT=aIecKorundm.RES_PORT;
		m_IndividualStructureKorundArray.RemoveAll();
		for(int i = 0; i < aIecKorundm.m_IndividualStructureKorundArray.GetSize(); i++)
			m_IndividualStructureKorundArray.Add(aIecKorundm.m_IndividualStructureKorundArray[i]);
		//m_TuArray.Copy(aIecKorundm.m_TuArray);
	}
	void operator = (const CIecKorundm& aIecKorundm)
	{
		m_nProcNum=aIecKorundm.m_nProcNum;
		PORT=aIecKorundm.PORT;
		BAUDRATE=aIecKorundm.BAUDRATE;
		STOPBITS=aIecKorundm.STOPBITS;
		PARITY=aIecKorundm.PARITY;
		BYTETIME=aIecKorundm.BYTETIME;
		WAITRESP=aIecKorundm.WAITRESP;
		NEXTMESSAGE=aIecKorundm.NEXTMESSAGE;
		AMOUNTBYTE=aIecKorundm.AMOUNTBYTE;
		FLOWCONTROLL=aIecKorundm.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aIecKorundm.NUMBER_NO_ANSWER;
		ADRES_BADCHANEL=aIecKorundm.ADRES_BADCHANEL;
		NUMBER_OF_DEVICES=aIecKorundm.NUMBER_OF_DEVICES;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES=aIecKorundm.;
		SIZE_LINK=aIecKorundm.SIZE_LINK;
		SIZE_COFT=aIecKorundm.SIZE_COFT;
		SIZE_ASDU=aIecKorundm.SIZE_ASDU;
		SIZE_IOA=aIecKorundm.SIZE_IOA;
		PERIOD_C_IC_NA_1=aIecKorundm.PERIOD_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIecKorundm.PERIOD_C_CS_NA_1;
		TIME_TU_EXPIRE=aIecKorundm.TIME_TU_EXPIRE;
		//RES_PORT=aIecKorundm.RES_PORT;
		m_IndividualStructureKorundArray.RemoveAll();
		for(int i = 0; i < aIecKorundm.m_IndividualStructureKorundArray.GetSize(); i++)
			m_IndividualStructureKorundArray.Add(aIecKorundm.m_IndividualStructureKorundArray[i]);
		//m_TuArray.Copy(aIecKorundm.m_TuArray);
	}

	CIndividualStructureKorundArray m_IndividualStructureKorundArray;
	//CTuArray	m_TuArray;

	CIecKorundm(void);
	~CIecKorundm(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	//BOOL LoadFromTuFile(CString strFile);
};
