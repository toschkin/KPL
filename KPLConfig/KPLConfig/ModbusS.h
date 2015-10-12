#pragma once

#include "KPLVersion.h"
class CModbusS;
typedef CArray<CModbusS,CModbusS> CModbusSArray;

struct CalcStructureModbusS: public CKPLVersion
{
	int TYPE;
	int ADDRESS_FROM;
	int POSITION_BYTE;
	int POSITION_BIT;
	int NUMBER_BYTE;
	int ADDRESS_TOO;
	int POSITION_BYTE_TOO;
	int POSITION_BIT_TOO;
	int DOPKODE_YES_NO;
	double CENA_SHKALI;
	double SMESHENIE;
	double MIN_FIZ;
	double MAX_FIZ;
	int MAX_SHKALA_FIZ;
	CString strCOMMENT;

	CalcStructureModbusS()
	{		
		TYPE=1;
		ADDRESS_FROM=0;
		POSITION_BYTE=0;
		POSITION_BIT=0;
		NUMBER_BYTE=0;
		ADDRESS_TOO=0;
		POSITION_BYTE_TOO=0;
		POSITION_BIT_TOO=0;
		DOPKODE_YES_NO=0;
		CENA_SHKALI=0.0;
		SMESHENIE=0.0;
		MIN_FIZ=0.0;
		MAX_FIZ=0.0;
		MAX_SHKALA_FIZ=0;
		strCOMMENT=" ";
	}
	CalcStructureModbusS(const CalcStructureModbusS& aCalcStructureModbusS)
	{
		TYPE=aCalcStructureModbusS.TYPE;
		ADDRESS_FROM=aCalcStructureModbusS.ADDRESS_FROM;
		POSITION_BYTE=aCalcStructureModbusS.POSITION_BYTE;
		POSITION_BIT=aCalcStructureModbusS.POSITION_BIT;
		NUMBER_BYTE=aCalcStructureModbusS.NUMBER_BYTE;
		ADDRESS_TOO=aCalcStructureModbusS.ADDRESS_TOO;
		POSITION_BYTE_TOO=aCalcStructureModbusS.POSITION_BYTE_TOO;
		POSITION_BIT_TOO=aCalcStructureModbusS.POSITION_BIT_TOO;
		DOPKODE_YES_NO=aCalcStructureModbusS.DOPKODE_YES_NO;
		CENA_SHKALI=aCalcStructureModbusS.CENA_SHKALI;
		SMESHENIE=aCalcStructureModbusS.SMESHENIE;
		MIN_FIZ=aCalcStructureModbusS.MIN_FIZ;
		MAX_FIZ=aCalcStructureModbusS.MAX_FIZ;
		MAX_SHKALA_FIZ=aCalcStructureModbusS.MAX_SHKALA_FIZ;
		strCOMMENT=aCalcStructureModbusS.strCOMMENT;
	}
	void operator = (const CalcStructureModbusS& aCalcStructureModbusS)
	{
		TYPE=aCalcStructureModbusS.TYPE;
		ADDRESS_FROM=aCalcStructureModbusS.ADDRESS_FROM;
		POSITION_BYTE=aCalcStructureModbusS.POSITION_BYTE;
		POSITION_BIT=aCalcStructureModbusS.POSITION_BIT;
		NUMBER_BYTE=aCalcStructureModbusS.NUMBER_BYTE;
		ADDRESS_TOO=aCalcStructureModbusS.ADDRESS_TOO;
		POSITION_BYTE_TOO=aCalcStructureModbusS.POSITION_BYTE_TOO;
		POSITION_BIT_TOO=aCalcStructureModbusS.POSITION_BIT_TOO;
		DOPKODE_YES_NO=aCalcStructureModbusS.DOPKODE_YES_NO;
		CENA_SHKALI=aCalcStructureModbusS.CENA_SHKALI;
		SMESHENIE=aCalcStructureModbusS.SMESHENIE;
		MIN_FIZ=aCalcStructureModbusS.MIN_FIZ;
		MAX_FIZ=aCalcStructureModbusS.MAX_FIZ;
		MAX_SHKALA_FIZ=aCalcStructureModbusS.MAX_SHKALA_FIZ;
		strCOMMENT=aCalcStructureModbusS.strCOMMENT;
	}
};

typedef CArray<CalcStructureModbusS,CalcStructureModbusS> CalcStructureModbusSArray;



class CModbusS:public CKPLVersion
{
public:
	int m_nProcNum;

	int PORT;
	int BAUDRATE;
	int STOPBITS;
	int PARITY;
	int BYTETIME;
	int WAITRESP;	
	int AMOUNTBYTE;	
	int CONTROLPOTOK;
	int MODBUS_TYPE;
	int ADRESS_KP;	
	int START_ADDRESS_TS;
	int SIZE_TS;
	int ADDRESS_ALARM_TS;
	int START_ADDRESS_TI;
	int SIZE_TI;
	int ADDRESS_ALARM_TI;
	//reserve
	int NEXTMESSAGE;
	int NUMBER_OF_PRIBOR;
	int NUMBER_NO_ANSWER;
	//ver 11
	CalcStructureModbusSArray m_CalcStructureModbusSArray;
	
	CModbusS(const CModbusS& aModbusS)
	{
		m_nProcNum=aModbusS.m_nProcNum;
		PORT=aModbusS.PORT;
		BAUDRATE=aModbusS.BAUDRATE;
		STOPBITS=aModbusS.STOPBITS;
		PARITY=aModbusS.PARITY;
		BYTETIME=aModbusS.BYTETIME;
		WAITRESP=aModbusS.WAITRESP;
		ADRESS_KP=aModbusS.ADRESS_KP;
		AMOUNTBYTE=aModbusS.AMOUNTBYTE;
		CONTROLPOTOK=aModbusS.CONTROLPOTOK;		
		MODBUS_TYPE=aModbusS.MODBUS_TYPE;	
		START_ADDRESS_TS=aModbusS.START_ADDRESS_TS;
		SIZE_TS=aModbusS.SIZE_TS;
		ADDRESS_ALARM_TS=aModbusS.ADDRESS_ALARM_TS;
		START_ADDRESS_TI=aModbusS.START_ADDRESS_TI;
		SIZE_TI=aModbusS.SIZE_TI;
		ADDRESS_ALARM_TI=aModbusS.ADDRESS_ALARM_TI;
		NEXTMESSAGE=aModbusS.NEXTMESSAGE;
		NUMBER_OF_PRIBOR=aModbusS.NUMBER_OF_PRIBOR;
		NUMBER_NO_ANSWER=aModbusS.NUMBER_NO_ANSWER;
		//ver 11
		m_CalcStructureModbusSArray.Copy(aModbusS.m_CalcStructureModbusSArray);
	}
	void operator = (const CModbusS& aModbusS)
	{
		m_nProcNum=aModbusS.m_nProcNum;
		PORT=aModbusS.PORT;
		BAUDRATE=aModbusS.BAUDRATE;
		STOPBITS=aModbusS.STOPBITS;
		PARITY=aModbusS.PARITY;
		BYTETIME=aModbusS.BYTETIME;
		WAITRESP=aModbusS.WAITRESP;
		ADRESS_KP=aModbusS.ADRESS_KP;
		AMOUNTBYTE=aModbusS.AMOUNTBYTE;
		CONTROLPOTOK=aModbusS.CONTROLPOTOK;		
		MODBUS_TYPE=aModbusS.MODBUS_TYPE;	
		START_ADDRESS_TS=aModbusS.START_ADDRESS_TS;
		SIZE_TS=aModbusS.SIZE_TS;
		ADDRESS_ALARM_TS=aModbusS.ADDRESS_ALARM_TS;
		START_ADDRESS_TI=aModbusS.START_ADDRESS_TI;
		SIZE_TI=aModbusS.SIZE_TI;
		ADDRESS_ALARM_TI=aModbusS.ADDRESS_ALARM_TI;
		NEXTMESSAGE=aModbusS.NEXTMESSAGE;
		NUMBER_OF_PRIBOR=aModbusS.NUMBER_OF_PRIBOR;
		NUMBER_NO_ANSWER=aModbusS.NUMBER_NO_ANSWER;
		//ver 11
		m_CalcStructureModbusSArray.Copy(aModbusS.m_CalcStructureModbusSArray);
	}

	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);	

	CModbusS(void);
	~CModbusS(void);
};
