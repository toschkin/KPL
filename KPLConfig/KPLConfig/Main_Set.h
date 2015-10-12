#pragma once

#include "KPLVersion.h"
#define PORT_FREE 0
#define PORT_BUSY 1

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

struct ProcessInfo: public CKPLVersion
{
	int TYPE_PROTOKOL;
	int START_ADDRESS_MAP;
	int AMOUNT_SIGNIFICATE;
	int YESNOLOGALARM;
	int YESNOLOGPROTOKOL;
	CString strCOMMENT;

	ProcessInfo()
	{
		TYPE_PROTOKOL=255;
		START_ADDRESS_MAP=0;
		AMOUNT_SIGNIFICATE=0;
		YESNOLOGALARM=1;
		YESNOLOGPROTOKOL=1;
		strCOMMENT=" ";
	}
	~ProcessInfo()
	{
		TYPE_PROTOKOL=255;
		START_ADDRESS_MAP=0;
		AMOUNT_SIGNIFICATE=0;
		YESNOLOGALARM=1;
		YESNOLOGPROTOKOL=1;
		strCOMMENT=" ";
	}
	ProcessInfo(const ProcessInfo& aProcessInfo)
	{
		TYPE_PROTOKOL=aProcessInfo.TYPE_PROTOKOL;
		START_ADDRESS_MAP=aProcessInfo.START_ADDRESS_MAP;
		AMOUNT_SIGNIFICATE=aProcessInfo.AMOUNT_SIGNIFICATE;
		YESNOLOGALARM=aProcessInfo.YESNOLOGALARM;
		YESNOLOGPROTOKOL=aProcessInfo.YESNOLOGPROTOKOL;		
		strCOMMENT=aProcessInfo.strCOMMENT;
	}
	void operator = (const ProcessInfo& aProcessInfo)
	{
		TYPE_PROTOKOL=aProcessInfo.TYPE_PROTOKOL;
		START_ADDRESS_MAP=aProcessInfo.START_ADDRESS_MAP;
		AMOUNT_SIGNIFICATE=aProcessInfo.AMOUNT_SIGNIFICATE;
		YESNOLOGALARM=aProcessInfo.YESNOLOGALARM;
		YESNOLOGPROTOKOL=aProcessInfo.YESNOLOGPROTOKOL;
		strCOMMENT=aProcessInfo.strCOMMENT;
	}
};

struct IniMask: public CKPLVersion
{
	int ADR_MASKA;
	int MASKAINT;
	int MASKAFLOAT;
	int VALUE_0;
	int TYPE_VALUE;
	int MASKA_VALUE_0;
	CString strCOMMENT;
	IniMask()
	{
		ADR_MASKA=0;
		MASKAINT=0;
		MASKAFLOAT=0;
		VALUE_0=0;
		TYPE_VALUE=0;
		MASKA_VALUE_0=0;
		strCOMMENT=" ";
	}
	IniMask(const IniMask& aIniMask)
	{
		ADR_MASKA=aIniMask.ADR_MASKA;
		MASKAINT=aIniMask.MASKAINT;
		MASKAFLOAT=aIniMask.MASKAFLOAT;
		VALUE_0=aIniMask.VALUE_0;
		TYPE_VALUE=aIniMask.TYPE_VALUE;
		MASKA_VALUE_0=aIniMask.MASKA_VALUE_0;
		strCOMMENT=aIniMask.strCOMMENT;
	}
	void operator = (const IniMask& aIniMask)
	{
		ADR_MASKA=aIniMask.ADR_MASKA;
		MASKAINT=aIniMask.MASKAINT;
		MASKAFLOAT=aIniMask.MASKAFLOAT;
		VALUE_0=aIniMask.VALUE_0;
		TYPE_VALUE=aIniMask.TYPE_VALUE;
		MASKA_VALUE_0=aIniMask.MASKA_VALUE_0;
		strCOMMENT=aIniMask.strCOMMENT;
	}
};

struct IniObject: public CKPLVersion
{
	int TYPE_OBJECT;
	int GENTYPE_OBJECT;
	int START_ADRES_PMZ;
	int NUMBER_OBJECT;
	int NUM_DATE;
	int REAL_ADRES;
	int GEN_NUMBYTE;
	int ADRES_ASDU;
	int YES_NO_FASTBUF;
	int SIZE_FAST_BUF;
	int NUMBER_DIRECT;
	//ver 11
	CString strCOMMENT;

	IniObject()
	{
		TYPE_OBJECT=0;
		GENTYPE_OBJECT=0;
		START_ADRES_PMZ=0;
		NUMBER_OBJECT=0;
		NUM_DATE=1;
		REAL_ADRES=0;
		GEN_NUMBYTE=1;
		ADRES_ASDU=1;
		YES_NO_FASTBUF=0;
		SIZE_FAST_BUF=0;
		NUMBER_DIRECT=0;
		strCOMMENT=" ";
	}
	IniObject(const IniObject& aIniObject)
	{
		TYPE_OBJECT=aIniObject.TYPE_OBJECT;
		GENTYPE_OBJECT=aIniObject.GENTYPE_OBJECT;
		START_ADRES_PMZ=aIniObject.START_ADRES_PMZ;
		NUMBER_OBJECT=aIniObject.NUMBER_OBJECT;
		NUM_DATE=aIniObject.NUM_DATE;
		REAL_ADRES=aIniObject.REAL_ADRES;
		GEN_NUMBYTE=aIniObject.GEN_NUMBYTE;
		ADRES_ASDU=aIniObject.ADRES_ASDU;
		YES_NO_FASTBUF=aIniObject.YES_NO_FASTBUF;
		SIZE_FAST_BUF=aIniObject.SIZE_FAST_BUF;
		NUMBER_DIRECT=aIniObject.NUMBER_DIRECT;
		strCOMMENT=aIniObject.strCOMMENT;
	}
	void operator = (const IniObject& aIniObject)
	{
		TYPE_OBJECT=aIniObject.TYPE_OBJECT;
		GENTYPE_OBJECT=aIniObject.GENTYPE_OBJECT;
		START_ADRES_PMZ=aIniObject.START_ADRES_PMZ;
		NUMBER_OBJECT=aIniObject.NUMBER_OBJECT;
		NUM_DATE=aIniObject.NUM_DATE;
		REAL_ADRES=aIniObject.REAL_ADRES;
		GEN_NUMBYTE=aIniObject.GEN_NUMBYTE;
		ADRES_ASDU=aIniObject.ADRES_ASDU;
		YES_NO_FASTBUF=aIniObject.YES_NO_FASTBUF;
		SIZE_FAST_BUF=aIniObject.SIZE_FAST_BUF;
		NUMBER_DIRECT=aIniObject.NUMBER_DIRECT;
		strCOMMENT=aIniObject.strCOMMENT;
	}
};

typedef CArray<ProcessInfo,ProcessInfo> CProcessInfoArray;
typedef CArray<IniObject,IniObject> CIniObjectArray;
typedef CArray<IniMask,IniMask> CIniMaskArray;



class CMain_Set: public CKPLVersion
{
public:
	CMain_Set(void);
	~CMain_Set(void);

	int REAL_SIZE_DIRECT_BUFER;
	int REAL_NUM_GENFAST_OBJECT;	
	int AMOUNT_OBJECT;	
	CString m_strPSNAME;
	CString MY_IP;
	CString MY_IP_MASK;
	CString MY_IP_GW;
	CString KPLType;//KPL_8_port(4,12)
	CArray<int,int> m_Ports;
	
	CProcessInfoArray m_ProcessInfoArray;
	CIniObjectArray   m_IniObjectArray;
	CIniMaskArray	  m_IniMaskArray;

	void operator = (const CMain_Set& aMain_Set)
	{
		REAL_SIZE_DIRECT_BUFER=aMain_Set.REAL_SIZE_DIRECT_BUFER;
		REAL_NUM_GENFAST_OBJECT=aMain_Set.REAL_NUM_GENFAST_OBJECT;
		m_strPSNAME=aMain_Set.m_strPSNAME;
		
		MY_IP=aMain_Set.MY_IP;
		MY_IP_MASK=aMain_Set.MY_IP_MASK;
		MY_IP_GW=aMain_Set.MY_IP_GW;		

		KPLType=aMain_Set.KPLType;

		AMOUNT_OBJECT=aMain_Set.AMOUNT_OBJECT;
		m_ProcessInfoArray.Copy(aMain_Set.m_ProcessInfoArray);
		m_IniObjectArray.Copy(aMain_Set.m_IniObjectArray);
		m_IniMaskArray.Copy(aMain_Set.m_IniMaskArray);
		m_Ports.Copy(aMain_Set.m_Ports);
	}


	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	int  GetVersion(CString strContent);
};
