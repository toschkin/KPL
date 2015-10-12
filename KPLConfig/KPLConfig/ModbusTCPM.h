#pragma once
#include "KPLVersion.h"
#include "Tu.h"

struct ModbusPriborTCP: public CKPLVersion
{
	int PRIBOR;
	int ADRESS;
	int FUNCTION;
	int START_ADRESS;
	int NUMBER;
	int ADRESS_PMZ;
	int DOP_BYTE1;
	int DOP_BYTE2;
	int DOP_BYTE3;
	int DOP_BYTE4;
	int TYPE_STATUS;
	int MASKA_STATUS;
	int ADRES_STATUS;
	int ADRES_4B;
	CString IP_ADDRESS;
	int PORT;
	CString strCOMMENT;

	ModbusPriborTCP()
	{
		PRIBOR=0;
		ADRESS=1;
		FUNCTION = 2;
		START_ADRESS=0;
		NUMBER=1;
		ADRESS_PMZ=0;
		DOP_BYTE1=0;
		DOP_BYTE2=0;
		DOP_BYTE3=0;
		DOP_BYTE4=0;
		TYPE_STATUS=0;
		MASKA_STATUS=0;
		ADRES_STATUS=0;
		ADRES_4B=0;
		IP_ADDRESS = "127.0.0.1";
		PORT = 502;
		strCOMMENT=" ";
	}
	ModbusPriborTCP(const ModbusPriborTCP& aModbusPriborTCP)
	{
		PRIBOR=aModbusPriborTCP.PRIBOR;
		ADRESS=aModbusPriborTCP.ADRESS;
		FUNCTION = aModbusPriborTCP.FUNCTION;
		START_ADRESS=aModbusPriborTCP.START_ADRESS;
		NUMBER=aModbusPriborTCP.NUMBER;
		ADRESS_PMZ=aModbusPriborTCP.ADRESS_PMZ;
		DOP_BYTE1=aModbusPriborTCP.DOP_BYTE1;
		DOP_BYTE2=aModbusPriborTCP.DOP_BYTE2;
		DOP_BYTE3=aModbusPriborTCP.DOP_BYTE3;
		DOP_BYTE4=aModbusPriborTCP.DOP_BYTE4;
		TYPE_STATUS=aModbusPriborTCP.TYPE_STATUS;
		MASKA_STATUS=aModbusPriborTCP.MASKA_STATUS;
		ADRES_STATUS=aModbusPriborTCP.ADRES_STATUS;
		ADRES_4B=aModbusPriborTCP.ADRES_4B;
		IP_ADDRESS=aModbusPriborTCP.IP_ADDRESS;
		PORT=aModbusPriborTCP.PORT;
		strCOMMENT=aModbusPriborTCP.strCOMMENT;
	}
	void operator = (const ModbusPriborTCP& aModbusPriborTCP)
	{
		PRIBOR=aModbusPriborTCP.PRIBOR;
		ADRESS=aModbusPriborTCP.ADRESS;
		FUNCTION = aModbusPriborTCP.FUNCTION;
		START_ADRESS=aModbusPriborTCP.START_ADRESS;
		NUMBER=aModbusPriborTCP.NUMBER;
		ADRESS_PMZ=aModbusPriborTCP.ADRESS_PMZ;
		DOP_BYTE1=aModbusPriborTCP.DOP_BYTE1;
		DOP_BYTE2=aModbusPriborTCP.DOP_BYTE2;
		DOP_BYTE3=aModbusPriborTCP.DOP_BYTE3;
		DOP_BYTE4=aModbusPriborTCP.DOP_BYTE4;
		TYPE_STATUS=aModbusPriborTCP.TYPE_STATUS;
		MASKA_STATUS=aModbusPriborTCP.MASKA_STATUS;
		ADRES_STATUS=aModbusPriborTCP.ADRES_STATUS;
		ADRES_4B=aModbusPriborTCP.ADRES_4B;
		IP_ADDRESS=aModbusPriborTCP.IP_ADDRESS;
		PORT=aModbusPriborTCP.PORT;
		strCOMMENT=aModbusPriborTCP.strCOMMENT;
	}
};

typedef CArray<ModbusPriborTCP,ModbusPriborTCP> CModbusPriborTCPArray;

class CModbusTCPM;
typedef CArray<CModbusTCPM,CModbusTCPM> CModbusTCPMArray;

class CModbusTCPM:public CKPLVersion
{
public:
	int m_nProcNum;

	int NUMBER_OF_IP;
	int SERVICE;
	int MODBUS_TYPE;
	int SMALL_TIME;		
	int NUMBER_NO_ANSWER;
	int NEXTMESSAGE;	
	
	CModbusTCPM(const CModbusTCPM& aModbusTCPM)
	{
		m_nProcNum=aModbusTCPM.m_nProcNum;
		SERVICE=aModbusTCPM.SERVICE;
		NUMBER_OF_IP=aModbusTCPM.NUMBER_OF_IP;
		SMALL_TIME=aModbusTCPM.SMALL_TIME;		
		NEXTMESSAGE=aModbusTCPM.NEXTMESSAGE;		
		NUMBER_NO_ANSWER=aModbusTCPM.NUMBER_NO_ANSWER;
		MODBUS_TYPE=aModbusTCPM.MODBUS_TYPE;
		
		m_ModbusPriborTCPArray.Copy(aModbusTCPM.m_ModbusPriborTCPArray);
		m_TuArray.Copy(aModbusTCPM.m_TuArray);
	}
	void operator = (const CModbusTCPM& aModbusTCPM)
	{
		m_nProcNum=aModbusTCPM.m_nProcNum;		
		SERVICE=aModbusTCPM.SERVICE;
		NUMBER_OF_IP=aModbusTCPM.NUMBER_OF_IP;
		SMALL_TIME=aModbusTCPM.SMALL_TIME;		
		NEXTMESSAGE=aModbusTCPM.NEXTMESSAGE;		
		NUMBER_NO_ANSWER=aModbusTCPM.NUMBER_NO_ANSWER;
		MODBUS_TYPE=aModbusTCPM.MODBUS_TYPE;

		m_ModbusPriborTCPArray.Copy(aModbusTCPM.m_ModbusPriborTCPArray);
		m_TuArray.Copy(aModbusTCPM.m_TuArray);
	}
	
	CTuArray	m_TuArray;
	CModbusPriborTCPArray	m_ModbusPriborTCPArray;

	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);


	CModbusTCPM(void);
	~CModbusTCPM(void);
};
