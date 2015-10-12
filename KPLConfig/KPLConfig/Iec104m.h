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

struct IndividualStructure104: public CKPLVersion
{	
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
	int STATUS_ADDRESS;
	int STATUS_MASKA;
	int STATUS_TYPE;
	int DOP_FLAG;
	CString strCOMMENT;

	IndividualStructure104()
	{		
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
		STATUS_ADDRESS=0;
		STATUS_MASKA=0;
		STATUS_TYPE=0;
		DOP_FLAG=0;
		strCOMMENT=" ";
	}
	IndividualStructure104(const IndividualStructure104& aIndividualStructure104)
	{		
		TYPE_ID=aIndividualStructure104.TYPE_ID;
		NUM_BYTE=aIndividualStructure104.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructure104.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructure104.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructure104.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructure104.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructure104.START_IOA;
		AM_IOA=aIndividualStructure104.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure104.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructure104.POZITION_OF_QUALITY_FLAG;
		
		STATUS_ADDRESS=aIndividualStructure104.STATUS_ADDRESS;
		STATUS_MASKA=aIndividualStructure104.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructure104.STATUS_TYPE;
		DOP_FLAG=aIndividualStructure104.DOP_FLAG;
		strCOMMENT=aIndividualStructure104.strCOMMENT;
	}
	void operator = (const IndividualStructure104& aIndividualStructure104)
	{
		TYPE_ID=aIndividualStructure104.TYPE_ID;
		NUM_BYTE=aIndividualStructure104.NUM_BYTE;
		TYPE_ID_C_IC_NA_1=aIndividualStructure104.TYPE_ID_C_IC_NA_1;
		NUM_BYTE_C_IC_NA_1=aIndividualStructure104.NUM_BYTE_C_IC_NA_1;
		ORIGINATOR_ADDRESS=aIndividualStructure104.ORIGINATOR_ADDRESS;
		COMMON_ADDRESS_ASDU=aIndividualStructure104.COMMON_ADDRESS_ASDU;
		START_IOA=aIndividualStructure104.START_IOA;
		AM_IOA=aIndividualStructure104.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure104.ADDRESS_PMZ;
		POZITION_OF_QUALITY_FLAG=aIndividualStructure104.POZITION_OF_QUALITY_FLAG;
		
		STATUS_ADDRESS=aIndividualStructure104.STATUS_ADDRESS;
		STATUS_MASKA=aIndividualStructure104.STATUS_MASKA;
		STATUS_TYPE=aIndividualStructure104.STATUS_TYPE;
		DOP_FLAG=aIndividualStructure104.DOP_FLAG;
		strCOMMENT=aIndividualStructure104.strCOMMENT;
	}
};

typedef CArray<IndividualStructure104,IndividualStructure104> CIndividualStructure104Array;

class CIec104m;
typedef CArray<CIec104m,CIec104m> CIec104mArray;

class CIec104m:public CKPLVersion
{
public:
	int m_nProcNum;

	int UST_CONNECT_t0;
	int TEST_APDU_t1;
	int CONFIRM_t2;
	int SEND_TEST_t3;
	int MAX_DELTA_K;
	int CONFIRM_AFTER_W;
	int SIZE_COFT;
	int SIZE_ASDU;
	int SIZE_IOA;
	CString ADRESS_IP;
	int SMOLLTIME;
	int GLOBAL_ASDU;	
	int PORT;
	int C_IС_NA_1_ENABLE;
	int C_IС_NA_1_WAIT_END_ACT;
	int C_CS_NA_1_ENABLE;
	int C_CS_NA_1_WAIT_END_ACT;
	int PERIOD_C_IC_NA_1;
	int TIME_WAIT_C_IC_NA_1;
	int PERIOD_C_CS_NA_1;
	int TIME_WAIT_C_CS_NA_1;
	int TIME_WAIT_RESP_TEST;
	int TIME_WAIT_RESP_STOP;
	int TIME_WAIT_FLAG_BAD;
	//ver 12
	CString RES_ADRESS_IP;
	int RES_PORT;


	CIec104m(const CIec104m& aIec104m)
	{
		m_nProcNum=aIec104m.m_nProcNum;
		UST_CONNECT_t0=aIec104m.UST_CONNECT_t0;
		TEST_APDU_t1=aIec104m.TEST_APDU_t1;
		CONFIRM_t2=aIec104m.CONFIRM_t2;
		SEND_TEST_t3=aIec104m.SEND_TEST_t3;
		MAX_DELTA_K=aIec104m.MAX_DELTA_K;
		CONFIRM_AFTER_W=aIec104m.CONFIRM_AFTER_W;
		SIZE_COFT=aIec104m.SIZE_COFT;
		SIZE_ASDU=aIec104m.SIZE_ASDU;
		SIZE_IOA=aIec104m.SIZE_IOA;
		ADRESS_IP=aIec104m.ADRESS_IP;
		SMOLLTIME=aIec104m.SMOLLTIME;
		GLOBAL_ASDU=aIec104m.GLOBAL_ASDU;
		PORT=aIec104m.PORT;
		C_IС_NA_1_ENABLE=aIec104m.C_IС_NA_1_ENABLE;
		C_IС_NA_1_WAIT_END_ACT=aIec104m.C_IС_NA_1_WAIT_END_ACT;
		C_CS_NA_1_ENABLE=aIec104m.C_CS_NA_1_ENABLE;
		C_CS_NA_1_WAIT_END_ACT=aIec104m.C_CS_NA_1_WAIT_END_ACT;
		PERIOD_C_IC_NA_1=aIec104m.PERIOD_C_IC_NA_1;
		TIME_WAIT_C_IC_NA_1=aIec104m.TIME_WAIT_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIec104m.PERIOD_C_CS_NA_1;
		TIME_WAIT_C_CS_NA_1=aIec104m.TIME_WAIT_C_CS_NA_1;
		TIME_WAIT_RESP_TEST=aIec104m.TIME_WAIT_RESP_TEST;
		TIME_WAIT_RESP_STOP=aIec104m.TIME_WAIT_RESP_STOP;
		TIME_WAIT_FLAG_BAD=aIec104m.TIME_WAIT_FLAG_BAD;
		RES_ADRESS_IP=aIec104m.RES_ADRESS_IP;
		RES_PORT=aIec104m.RES_PORT;
				
		m_IndividualStructure104Array.RemoveAll();
		for(int i = 0; i < aIec104m.m_IndividualStructure104Array.GetSize(); i++)
			m_IndividualStructure104Array.Add(aIec104m.m_IndividualStructure104Array[i]);
		m_TuArray.Copy(aIec104m.m_TuArray);
	}
	void operator = (const CIec104m& aIec104m)
	{
		m_nProcNum=aIec104m.m_nProcNum;
		UST_CONNECT_t0=aIec104m.UST_CONNECT_t0;
		TEST_APDU_t1=aIec104m.TEST_APDU_t1;
		CONFIRM_t2=aIec104m.CONFIRM_t2;
		SEND_TEST_t3=aIec104m.SEND_TEST_t3;
		MAX_DELTA_K=aIec104m.MAX_DELTA_K;
		CONFIRM_AFTER_W=aIec104m.CONFIRM_AFTER_W;
		SIZE_COFT=aIec104m.SIZE_COFT;
		SIZE_ASDU=aIec104m.SIZE_ASDU;
		SIZE_IOA=aIec104m.SIZE_IOA;
		ADRESS_IP=aIec104m.ADRESS_IP;
		SMOLLTIME=aIec104m.SMOLLTIME;
		GLOBAL_ASDU=aIec104m.GLOBAL_ASDU;
		PORT=aIec104m.PORT;
		C_IС_NA_1_ENABLE=aIec104m.C_IС_NA_1_ENABLE;
		C_IС_NA_1_WAIT_END_ACT=aIec104m.C_IС_NA_1_WAIT_END_ACT;
		C_CS_NA_1_ENABLE=aIec104m.C_CS_NA_1_ENABLE;
		C_CS_NA_1_WAIT_END_ACT=aIec104m.C_CS_NA_1_WAIT_END_ACT;
		PERIOD_C_IC_NA_1=aIec104m.PERIOD_C_IC_NA_1;
		TIME_WAIT_C_IC_NA_1=aIec104m.TIME_WAIT_C_IC_NA_1;
		PERIOD_C_CS_NA_1=aIec104m.PERIOD_C_CS_NA_1;
		TIME_WAIT_C_CS_NA_1=aIec104m.TIME_WAIT_C_CS_NA_1;
		TIME_WAIT_RESP_TEST=aIec104m.TIME_WAIT_RESP_TEST;
		TIME_WAIT_RESP_STOP=aIec104m.TIME_WAIT_RESP_STOP;
		TIME_WAIT_FLAG_BAD=aIec104m.TIME_WAIT_FLAG_BAD;
		RES_ADRESS_IP=aIec104m.RES_ADRESS_IP;
		RES_PORT=aIec104m.RES_PORT;
				
		m_IndividualStructure104Array.RemoveAll();
		for(int i = 0; i < aIec104m.m_IndividualStructure104Array.GetSize(); i++)
			m_IndividualStructure104Array.Add(aIec104m.m_IndividualStructure104Array[i]);
		m_TuArray.Copy(aIec104m.m_TuArray);
	}

	CIndividualStructure104Array m_IndividualStructure104Array;
	CTuArray	m_TuArray;

	CIec104m(void);
	~CIec104m(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);	
};
