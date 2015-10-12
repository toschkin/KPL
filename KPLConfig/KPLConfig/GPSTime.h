#pragma once
#include "KPLVersion.h"
struct IndividualStructureGPS: public CKPLVersion
{	
	int TYPE_ID;
	int NUM_BYTE;
	int AM_IOA;
	int ADDRESS_PMZ;
	

	IndividualStructureGPS()
	{		
		TYPE_ID=1;
		NUM_BYTE=1;		
		AM_IOA=0;
		ADDRESS_PMZ=0;		
	}
	IndividualStructureGPS(const IndividualStructureGPS& aIndividualStructure101)
	{		
		TYPE_ID=aIndividualStructure101.TYPE_ID;
		NUM_BYTE=aIndividualStructure101.NUM_BYTE;		
		AM_IOA=aIndividualStructure101.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure101.ADDRESS_PMZ;		
	}
	void operator = (const IndividualStructureGPS& aIndividualStructure101)
	{
		TYPE_ID=aIndividualStructure101.TYPE_ID;
		NUM_BYTE=aIndividualStructure101.NUM_BYTE;		
		AM_IOA=aIndividualStructure101.AM_IOA;
		ADDRESS_PMZ=aIndividualStructure101.ADDRESS_PMZ;
	}
};
typedef CArray<IndividualStructureGPS,IndividualStructureGPS> CIndividualStructureGPSArray;

class CGPSTime:public CKPLVersion
{
public:
	int m_nProcNum;

	CGPSTime(void);
	~CGPSTime(void);

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

	int TYPE_OF_GPS;
	int PERIOD_C_CS_NA_1;
	int SERVICE;
	int SUMMER_TIME_ON;
	int GMT_CORRECTION;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES
	int ENABLE_SCRIPT;
	int SYNC_FROM;
	int GPS_SYNC_ATTEMPT_TIME;
	CString NTP_SERVER_IP;
	int NTP_LOG;

	CGPSTime(const CGPSTime& aIec101m)
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
		
		TYPE_OF_GPS=aIec101m.TYPE_OF_GPS;
		PERIOD_C_CS_NA_1=aIec101m.PERIOD_C_CS_NA_1;
		SERVICE=aIec101m.SERVICE;
		SUMMER_TIME_ON=aIec101m.SUMMER_TIME_ON;
		GMT_CORRECTION=aIec101m.GMT_CORRECTION;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES
		ENABLE_SCRIPT=aIec101m.ENABLE_SCRIPT;
		SYNC_FROM=aIec101m.SYNC_FROM;
		GPS_SYNC_ATTEMPT_TIME=aIec101m.GPS_SYNC_ATTEMPT_TIME;
		NTP_SERVER_IP=aIec101m.NTP_SERVER_IP;
		NTP_LOG=aIec101m.NTP_LOG;

		m_IndividualStructureGPSArray.RemoveAll();
		for(int i = 0; i < aIec101m.m_IndividualStructureGPSArray.GetSize(); i++)
			m_IndividualStructureGPSArray.Add(aIec101m.m_IndividualStructureGPSArray[i]);
		
	}
	void operator = (const CGPSTime& aIec101m)
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
		
		TYPE_OF_GPS=aIec101m.TYPE_OF_GPS;
		PERIOD_C_CS_NA_1=aIec101m.PERIOD_C_CS_NA_1;
		SERVICE=aIec101m.SERVICE;
		SUMMER_TIME_ON=aIec101m.SUMMER_TIME_ON;
		GMT_CORRECTION=aIec101m.GMT_CORRECTION;
		//NUMBER_OF_INDIVIDUAL_STRUCTURES
		ENABLE_SCRIPT=aIec101m.ENABLE_SCRIPT;
		SYNC_FROM=aIec101m.SYNC_FROM;
		GPS_SYNC_ATTEMPT_TIME=aIec101m.GPS_SYNC_ATTEMPT_TIME;
		NTP_SERVER_IP=aIec101m.NTP_SERVER_IP;
		NTP_LOG=aIec101m.NTP_LOG;

		m_IndividualStructureGPSArray.RemoveAll();
		for(int i = 0; i < aIec101m.m_IndividualStructureGPSArray.GetSize(); i++)
			m_IndividualStructureGPSArray.Add(aIec101m.m_IndividualStructureGPSArray[i]);

	}

	CIndividualStructureGPSArray m_IndividualStructureGPSArray;	

	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);

	//BOOL SaveToScriptFile(CString strFile);
	//BOOL LoadFromScriptFile(CString strFile);
};
