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


class CIec104s;
typedef CArray<CIec104s,CIec104s> CIec104sArray;

class CIec104s:public CKPLVersion
{
public:
	int m_nProcNum;

	int UST_CONNECT_t0;
	int TEST_APDU_t1;
	int CONFIRM_t2;
	int SEND_TEST_t3;
	int MAX_DELTA_K;
	int CONFIRM_AFTER_W;
	int SIZE_LINK;
	int SIZE_COFT;
	int SIZE_ASDU;
	int SIZE_IOA;
	int BIGTIME;
	int SMOLLTIME;
	int GLOBAL_ASDU;
	int ADRESS_LINK;
	CString ADRESS_IP;
	int PORT;
	int SIZE_OBJECT_ARH;
	//ver 13
	CString RES_ADRESS_IP;
		
	CIec104s(const CIec104s& aIec104s)
	{
		m_nProcNum=aIec104s.m_nProcNum;
		UST_CONNECT_t0=aIec104s.UST_CONNECT_t0;
		TEST_APDU_t1=aIec104s.TEST_APDU_t1;
		CONFIRM_t2=aIec104s.CONFIRM_t2;
		SEND_TEST_t3=aIec104s.SEND_TEST_t3;
		MAX_DELTA_K=aIec104s.MAX_DELTA_K;
		CONFIRM_AFTER_W=aIec104s.CONFIRM_AFTER_W;
		BIGTIME=aIec104s.BIGTIME;
		SMOLLTIME=aIec104s.SMOLLTIME;
		GLOBAL_ASDU=aIec104s.GLOBAL_ASDU;
		ADRESS_IP=aIec104s.ADRESS_IP;
		SIZE_LINK=aIec104s.SIZE_LINK;
		ADRESS_LINK=aIec104s.ADRESS_LINK;
		SIZE_COFT=aIec104s.SIZE_COFT;
		SIZE_ASDU=aIec104s.SIZE_ASDU;
		SIZE_IOA=aIec104s.SIZE_IOA;		
		PORT=aIec104s.PORT;
		SIZE_OBJECT_ARH=aIec104s.SIZE_OBJECT_ARH;
		RES_ADRESS_IP=aIec104s.RES_ADRESS_IP;
	}
	void operator = (const CIec104s& aIec104s)
	{
		m_nProcNum=aIec104s.m_nProcNum;
		UST_CONNECT_t0=aIec104s.UST_CONNECT_t0;
		TEST_APDU_t1=aIec104s.TEST_APDU_t1;
		CONFIRM_t2=aIec104s.CONFIRM_t2;
		SEND_TEST_t3=aIec104s.SEND_TEST_t3;
		MAX_DELTA_K=aIec104s.MAX_DELTA_K;
		CONFIRM_AFTER_W=aIec104s.CONFIRM_AFTER_W;
		BIGTIME=aIec104s.BIGTIME;
		SMOLLTIME=aIec104s.SMOLLTIME;
		GLOBAL_ASDU=aIec104s.GLOBAL_ASDU;
		ADRESS_IP=aIec104s.ADRESS_IP;
		SIZE_LINK=aIec104s.SIZE_LINK;
		ADRESS_LINK=aIec104s.ADRESS_LINK;
		SIZE_COFT=aIec104s.SIZE_COFT;
		SIZE_ASDU=aIec104s.SIZE_ASDU;
		SIZE_IOA=aIec104s.SIZE_IOA;	
		PORT=aIec104s.PORT;
		SIZE_OBJECT_ARH=aIec104s.SIZE_OBJECT_ARH;
		RES_ADRESS_IP=aIec104s.RES_ADRESS_IP;
	}

	CIec104s(void);
	~CIec104s(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);	
};
