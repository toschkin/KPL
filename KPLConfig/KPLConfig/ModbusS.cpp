#include "StdAfx.h"
#include "ModbusS.h"

CModbusS::CModbusS(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=2;
	PARITY=0;
	BYTETIME=10;
	WAITRESP=100;	
	AMOUNTBYTE=8;	
	ADRESS_KP=1;
	CONTROLPOTOK=0;
	MODBUS_TYPE=0;
	START_ADDRESS_TS=0;
	SIZE_TS=0;
	ADDRESS_ALARM_TS=0;
	START_ADDRESS_TI=0;
	SIZE_TI=0;
	ADDRESS_ALARM_TI=0;
}

CModbusS::~CModbusS(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=2;
	PARITY=0;
	BYTETIME=10;
	WAITRESP=100;	
	AMOUNTBYTE=8;	
	ADRESS_KP=1;
	CONTROLPOTOK=0;
	MODBUS_TYPE=0;
	START_ADDRESS_TS=0;
	SIZE_TS=0;
	ADDRESS_ALARM_TS=0;
	START_ADDRESS_TI=0;
	SIZE_TI=0;
	ADDRESS_ALARM_TI=0;

	NEXTMESSAGE=100;
	NUMBER_OF_PRIBOR=1;
	NUMBER_NO_ANSWER=10;

	m_CalcStructureModbusSArray.RemoveAll();
}
BOOL CModbusS::SaveToFile(CString strFile)
{
	CString strBuf,str;
	str.Format("PORT=%d\r\n",PORT);
	strBuf+=str;
	str.Format("BAUDRATE=%d\r\n",BAUDRATE);
	strBuf+=str;
	str.Format("STOPBITS=%d\r\n",STOPBITS);
	strBuf+=str;
	str.Format("PARITY=%d\r\n",PARITY);
	strBuf+=str;
	str.Format("BYTETIME=%d\r\n",BYTETIME);
	strBuf+=str;
	str.Format("WAITRESP=%d\r\n",WAITRESP);
	strBuf+=str;
	str.Format("NEXTMESSAGE=%d\r\n",NEXTMESSAGE);
	strBuf+=str;
	str.Format("NUMBER_OF_PRIBOR=%d\r\n",NUMBER_OF_PRIBOR);
	strBuf+=str;
	str.Format("AMOUNTBYTE=%d\r\n",AMOUNTBYTE);
	strBuf+=str;
	str.Format("CONTROLPOTOK=%d\r\n",CONTROLPOTOK);
	strBuf+=str;		
	str.Format("NUMBER_NO_ANSWER=%d\r\n",NUMBER_NO_ANSWER);
	strBuf+=str;		
	str.Format("MODBUS_TYPE=%d\r\n",MODBUS_TYPE);
	strBuf+=str;	
	str.Format("ADRESS_KP=%d\r\n",ADRESS_KP);
	strBuf+=str;
	str.Format("START_ADDRESS_TS=%d\r\n",START_ADDRESS_TS);
	strBuf+=str;
	str.Format("SIZE_TS=%d\r\n",SIZE_TS);
	strBuf+=str;
	str.Format("ADDRESS_ALARM_TS=%d\r\n",ADDRESS_ALARM_TS);
	strBuf+=str;
	str.Format("START_ADDRESS_TI=%d\r\n",START_ADDRESS_TI);
	strBuf+=str;
	str.Format("SIZE_TI=%d\r\n",SIZE_TI);
	strBuf+=str;
	str.Format("ADDRESS_ALARM_TI=%d\r\n\r\n",ADDRESS_ALARM_TI);
	strBuf+=str;
	//ver 11
	if(m_nVersion > 10)
	{
		strBuf.TrimRight("\r\n");
		strBuf+="\r\n";
		str.Format("NUM_CALCULATE=%d\r\n\r\n",m_CalcStructureModbusSArray.GetSize());
		strBuf+=str;		

		for(int i =0; i < m_CalcStructureModbusSArray.GetSize(); i++)
		{			
			str.Format("NUMBER_CALCULATE=%d\r\n",i+1);
			strBuf+=str;
			str.Format("TYPE=%d\r\n",m_CalcStructureModbusSArray[i].TYPE);
			strBuf+=str;
			str.Format("ADDRESS_FROM=%d\r\n",m_CalcStructureModbusSArray[i].ADDRESS_FROM);
			strBuf+=str;
			str.Format("POSITION_BYTE=%d\r\n",m_CalcStructureModbusSArray[i].POSITION_BYTE);
			strBuf+=str;
			str.Format("POSITION_BIT=%d\r\n",m_CalcStructureModbusSArray[i].POSITION_BIT);
			strBuf+=str;
			str.Format("NUMBER_BYTE=%d\r\n",m_CalcStructureModbusSArray[i].NUMBER_BYTE);
			strBuf+=str;
			str.Format("ADDRESS_TOO=%d\r\n",m_CalcStructureModbusSArray[i].ADDRESS_TOO);
			strBuf+=str;
			str.Format("POSITION_BYTE_TOO=%d\r\n",m_CalcStructureModbusSArray[i].POSITION_BYTE_TOO);
			strBuf+=str;
			str.Format("POSITION_BIT_TOO=%d\r\n",m_CalcStructureModbusSArray[i].POSITION_BIT_TOO);
			strBuf+=str;
			str.Format("DOPKODE_YES_NO=%d\r\n",m_CalcStructureModbusSArray[i].DOPKODE_YES_NO);
			strBuf+=str;
			str.Format("CENA_SHKALI=%f\r\n",m_CalcStructureModbusSArray[i].CENA_SHKALI);
			strBuf+=str;
			str.Format("SMESHENIE=%f\r\n",m_CalcStructureModbusSArray[i].SMESHENIE);
			strBuf+=str;
			str.Format("MIN_FIZ=%f\r\n",m_CalcStructureModbusSArray[i].MIN_FIZ);
			strBuf+=str;
			str.Format("MAX_FIZ=%f\r\n",m_CalcStructureModbusSArray[i].MAX_FIZ);
			strBuf+=str;
			str.Format("MAX_SHKALA_FIZ=%d\r\n",m_CalcStructureModbusSArray[i].MAX_SHKALA_FIZ);
			strBuf+=str;		
			str.Format("//%s\r\n\r\n",m_CalcStructureModbusSArray[i].strCOMMENT);			
			strBuf+=str;					
		}
	}
	
	CFile f;
	try
	{
		f.Open(strFile,CFile::modeCreate|CFile::modeWrite);
		f.Write((void*)strBuf.GetBuffer(),strBuf.GetLength());
		f.Close();		
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CModbusS::LoadFromFile(CString strFile)
{
	CFile f;
	CString strBuf,str;
	try
	{
		if(!f.Open(strFile,CFile::modeRead))
			return FALSE;
		CHAR buffer[4096];
		DWORD dwRead=0;
		// Read in 4096-byte blocks,
		// remember how many bytes were actually read,
		// and try to write that many out. This loop ends
		// when there are no more bytes to read.
		do
		{
			dwRead = f.Read(buffer, 4096);
			if(dwRead > 0)
			{
				int nLen = strBuf.GetLength();
				strBuf+=buffer;
				strBuf.Truncate(nLen+dwRead);
			}
		}
		while (dwRead > 0);
		f.Close();
		//AfxMessageBox(strBuf);
		strBuf.MakeUpper();
		strBuf.Remove(';');
		int nIndex = 0;
		int nProcIndex = -1;
		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			if(str.Find("PORT") != -1)
			{
				str.TrimLeft("PORT");
				str.Trim();str.Trim("=");				
				PORT = atoi(str);
			}
			if(str.Find("BAUDRATE") != -1)
			{
				str.TrimLeft("BAUDRATE");
				str.Trim();str.Trim("=");
				BAUDRATE = atoi(str);
			}
			if(str.Find("STOPBITS") != -1)
			{
				str.TrimLeft("STOPBITS");
				str.Trim();str.Trim("=");
				STOPBITS = atoi(str);
			}
			if(str.Find("PARITY") != -1)
			{
				str.TrimLeft("PARITY");
				str.Trim();str.Trim("=");
				PARITY = atoi(str);
			}
			if(str.Find("BYTETIME") != -1)
			{
				str.TrimLeft("BYTETIME");
				str.Trim();str.Trim("=");
				BYTETIME = atoi(str);
			}
			if(str.Find("WAITRESP") != -1)
			{
				str.TrimLeft("WAITRESP");
				str.Trim();str.Trim("=");
				WAITRESP = atoi(str);
			}
			if(str.Find("ADRESS_KP") != -1)
			{
				str.TrimLeft("ADRESS_KP");
				str.Trim();str.Trim("=");
				ADRESS_KP = atoi(str);
			}
			if(str.Find("NEXTMESSAGE") != -1)
			{
				str.TrimLeft("NEXTMESSAGE");
				str.Trim();str.Trim("=");
				NEXTMESSAGE = atoi(str);
			}
			if(str.Find("NUMBER_OF_PRIBOR") != -1)
			{
				str.TrimLeft("NUMBER_OF_PRIBOR");
				str.Trim();str.Trim("=");
				NUMBER_OF_PRIBOR = atoi(str);
			}
			if(str.Find("NUMBER_NO_ANSWER") != -1)
			{
				str.TrimLeft("NUMBER_NO_ANSWER");
				str.Trim();str.Trim("=");
				NUMBER_NO_ANSWER = atoi(str);
			}
			if(str.Find("AMOUNTBYTE") != -1)
			{
				str.TrimLeft("AMOUNTBYTE");
				str.Trim();str.Trim("=");
				AMOUNTBYTE = atoi(str);
			}
			if(str.Find("CONTROLPOTOK") != -1)
			{
				str.TrimLeft("CONTROLPOTOK");
				str.Trim();str.Trim("=");
				CONTROLPOTOK = atoi(str);
			}			
			if(str.Find("MODBUS_TYPE") != -1)
			{
				str.TrimLeft("MODBUS_TYPE");
				str.Trim();str.Trim("=");
				MODBUS_TYPE = atoi(str);
			}		
			if(str.Find("START_ADDRESS_TS") != -1)
			{
				str.TrimLeft("START_ADDRESS_TS");
				str.Trim();str.Trim("=");
				START_ADDRESS_TS = atoi(str);
			}	
			if(str.Find("SIZE_TS") != -1)
			{
				str.TrimLeft("SIZE_TS");
				str.Trim();str.Trim("=");
				SIZE_TS = atoi(str);
			}
			if(str.Find("ADDRESS_ALARM_TS") != -1)
			{
				str.TrimLeft("ADDRESS_ALARM_TS");
				str.Trim();str.Trim("=");
				ADDRESS_ALARM_TS = atoi(str);
			}
			if(str.Find("START_ADDRESS_TI") != -1)
			{
				str.TrimLeft("START_ADDRESS_TI");
				str.Trim();str.Trim("=");
				START_ADDRESS_TI = atoi(str);
			}
			if(str.Find("SIZE_TI") != -1)
			{
				str.TrimLeft("SIZE_TI");
				str.Trim();str.Trim("=");
				SIZE_TI = atoi(str);
			}
			if(str.Find("ADDRESS_ALARM_TI") != -1)
			{
				str.TrimLeft("ADDRESS_ALARM_TI");
				str.Trim();str.Trim("=");
				ADDRESS_ALARM_TI = atoi(str);
			}	
			if(m_nVersion > 10)
			{
				if(str.Find("NUM_CALCULATE") != -1)
				{
					str.TrimLeft("NUM_CALCULATE");
					str.Trim();str.Trim("=");
					m_CalcStructureModbusSArray.SetSize(atoi(str));
				}								
				if(str.Find("NUMBER_CALCULATE") != -1)
				{
					str.TrimLeft("NUMBER_CALCULATE");
					str.Trim();str.Trim("=");
					if((atoi(str) > 0)&&(atoi(str) <= m_CalcStructureModbusSArray.GetSize()))				
						nProcIndex = atoi(str)-1;								
				}
				if((str.Find("TYPE") != -1)&&(str.Find("MODBUS_TYPE") == -1))
				{
					str.TrimLeft("TYPE");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].TYPE = atoi(str);										
				}
				if(str.Find("ADDRESS_FROM") != -1)
				{
					str.TrimLeft("ADDRESS_FROM");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].ADDRESS_FROM = atoi(str);										
				}
				if((str.Find("POSITION_BYTE") != -1)&&(str.Find("POSITION_BYTE_TOO") == -1))
				{
					str.TrimLeft("POSITION_BYTE");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].POSITION_BYTE = atoi(str);										
				}
				if((str.Find("POSITION_BIT") != -1)&&(str.Find("POSITION_BIT_TOO") == -1))
				{
					str.TrimLeft("POSITION_BIT");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].POSITION_BIT = atoi(str);										
				}
				if(str.Find("NUMBER_BYTE") != -1)
				{
					str.TrimLeft("NUMBER_BYTE");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].NUMBER_BYTE = atoi(str);										
				}
				if(str.Find("ADDRESS_TOO") != -1)
				{
					str.TrimLeft("ADDRESS_TOO");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].ADDRESS_TOO = atoi(str);										
				}
				if(str.Find("POSITION_BYTE_TOO") != -1)
				{
					str.TrimLeft("POSITION_BYTE_TOO");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].POSITION_BYTE_TOO = atoi(str);										
				}
				if(str.Find("POSITION_BIT_TOO") != -1)
				{
					str.TrimLeft("POSITION_BIT_TOO");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].POSITION_BIT_TOO = atoi(str);										
				}
				if(str.Find("DOPKODE_YES_NO") != -1)
				{
					str.TrimLeft("DOPKODE_YES_NO");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].DOPKODE_YES_NO = atoi(str);										
				}
				if(str.Find("CENA_SHKALI") != -1)
				{
					str.TrimLeft("CENA_SHKALI");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].CENA_SHKALI = atof(str);										
				}					
				if(str.Find("SMESHENIE") != -1)
				{
					str.TrimLeft("SMESHENIE");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].SMESHENIE = atof(str);										
				}

				if(str.Find("MIN_FIZ") != -1)
				{
					str.TrimLeft("MIN_FIZ");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].MIN_FIZ = atof(str);										
				}
				if(str.Find("MAX_FIZ") != -1)
				{
					str.TrimLeft("MAX_FIZ");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].MAX_FIZ = atof(str);										
				}
				if(str.Find("MAX_SHKALA_FIZ") != -1)
				{
					str.TrimLeft("MAX_SHKALA_FIZ");
					str.Trim();str.Trim("=");
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].MAX_SHKALA_FIZ = atoi(str);										
				}
				if((str.Find("//") != -1)/*&&(str.Find("//_") == -1)&&(str.Find("//MSK_") == -1)&&(str.Find("//KPL_") == -1)
					&&(str.Find("//VER_") == -1)&&(str.Find("//IO_") == -1)*/)
				{
					str.TrimLeft("//");				
					str.Remove('\n');
					str.Remove('\r');
					if((nProcIndex >= 0)&&(nProcIndex < m_CalcStructureModbusSArray.GetSize()))
						m_CalcStructureModbusSArray[nProcIndex].strCOMMENT = str;														
				}	
			}			
			strBuf.Delete(0,nIndex+1);			
		}while(nIndex != -1);
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}