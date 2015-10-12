#pragma once
#include "KPLVersion.h"
#include "Tu.h"

struct ModbusPribor: public CKPLVersion
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
	CString strCOMMENT;

	ModbusPribor()
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
		strCOMMENT=" ";
	}
	ModbusPribor(const ModbusPribor& aModbusPribor)
	{
		PRIBOR=aModbusPribor.PRIBOR;
		ADRESS=aModbusPribor.ADRESS;
		FUNCTION = aModbusPribor.FUNCTION;
		START_ADRESS=aModbusPribor.START_ADRESS;
		NUMBER=aModbusPribor.NUMBER;
		ADRESS_PMZ=aModbusPribor.ADRESS_PMZ;
		DOP_BYTE1=aModbusPribor.DOP_BYTE1;
		DOP_BYTE2=aModbusPribor.DOP_BYTE2;
		DOP_BYTE3=aModbusPribor.DOP_BYTE3;
		DOP_BYTE4=aModbusPribor.DOP_BYTE4;
		TYPE_STATUS=aModbusPribor.TYPE_STATUS;
		MASKA_STATUS=aModbusPribor.MASKA_STATUS;
		ADRES_STATUS=aModbusPribor.ADRES_STATUS;
		ADRES_4B=aModbusPribor.ADRES_4B;
		strCOMMENT=aModbusPribor.strCOMMENT;
	}
	void operator = (const ModbusPribor& aModbusPribor)
	{
		PRIBOR=aModbusPribor.PRIBOR;
		ADRESS=aModbusPribor.ADRESS;
		FUNCTION = aModbusPribor.FUNCTION;
		START_ADRESS=aModbusPribor.START_ADRESS;
		NUMBER=aModbusPribor.NUMBER;
		ADRESS_PMZ=aModbusPribor.ADRESS_PMZ;
		DOP_BYTE1=aModbusPribor.DOP_BYTE1;
		DOP_BYTE2=aModbusPribor.DOP_BYTE2;
		DOP_BYTE3=aModbusPribor.DOP_BYTE3;
		DOP_BYTE4=aModbusPribor.DOP_BYTE4;
		TYPE_STATUS=aModbusPribor.TYPE_STATUS;
		MASKA_STATUS=aModbusPribor.MASKA_STATUS;
		ADRES_STATUS=aModbusPribor.ADRES_STATUS;
		ADRES_4B=aModbusPribor.ADRES_4B;
		strCOMMENT=aModbusPribor.strCOMMENT;
	}
};

typedef CArray<ModbusPribor,ModbusPribor> CModbusPriborArray;

class CModbusM;
typedef CArray<CModbusM,CModbusM> CModbusMArray;

class CModbusM:public CKPLVersion
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
	int NUMBER_NO_ANSWER;
	int AMOUNTBYTE;	
	int CONTROLPOTOK;
	int MODBUS_TYPE;
	
	CModbusM(const CModbusM& aModbusM)
	{
		m_nProcNum=aModbusM.m_nProcNum;
		PORT=aModbusM.PORT;
		BAUDRATE=aModbusM.BAUDRATE;
		STOPBITS=aModbusM.STOPBITS;
		PARITY=aModbusM.PARITY;
		BYTETIME=aModbusM.BYTETIME;
		WAITRESP=aModbusM.WAITRESP;
		NEXTMESSAGE=aModbusM.NEXTMESSAGE;
		AMOUNTBYTE=aModbusM.AMOUNTBYTE;
		CONTROLPOTOK=aModbusM.CONTROLPOTOK;
		NUMBER_NO_ANSWER=aModbusM.NUMBER_NO_ANSWER;
		MODBUS_TYPE=aModbusM.MODBUS_TYPE;
		
		m_ModbusPriborArray.Copy(aModbusM.m_ModbusPriborArray);
		m_TuArray.Copy(aModbusM.m_TuArray);
	}
	void operator = (const CModbusM& aModbusM)
	{
		m_nProcNum=aModbusM.m_nProcNum;
		PORT=aModbusM.PORT;
		BAUDRATE=aModbusM.BAUDRATE;
		STOPBITS=aModbusM.STOPBITS;
		PARITY=aModbusM.PARITY;
		BYTETIME=aModbusM.BYTETIME;
		WAITRESP=aModbusM.WAITRESP;
		NEXTMESSAGE=aModbusM.NEXTMESSAGE;
		AMOUNTBYTE=aModbusM.AMOUNTBYTE;
		CONTROLPOTOK=aModbusM.CONTROLPOTOK;
		NUMBER_NO_ANSWER=aModbusM.NUMBER_NO_ANSWER;
		MODBUS_TYPE=aModbusM.MODBUS_TYPE;

		m_ModbusPriborArray.Copy(aModbusM.m_ModbusPriborArray);
		m_TuArray.Copy(aModbusM.m_TuArray);
	}
	
	CTuArray	m_TuArray;
	CModbusPriborArray	m_ModbusPriborArray;

	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);


	CModbusM(void);
	~CModbusM(void);
};
