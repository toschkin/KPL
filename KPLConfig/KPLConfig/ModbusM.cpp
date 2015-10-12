#include "StdAfx.h"
#include "ModbusM.h"

CModbusM::CModbusM(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=2;
	PARITY=0;
	BYTETIME=10;
	WAITRESP=100;
	NEXTMESSAGE=10;
	AMOUNTBYTE=8;	
	NUMBER_NO_ANSWER=1;
	CONTROLPOTOK=0;
	MODBUS_TYPE=0;
}

CModbusM::~CModbusM(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=2;
	PARITY=0;
	BYTETIME=10;
	WAITRESP=100;
	NEXTMESSAGE=10;
	AMOUNTBYTE=8;	
	NUMBER_NO_ANSWER=1;
	CONTROLPOTOK=0;
	MODBUS_TYPE=0;
	m_ModbusPriborArray.RemoveAll();
	m_TuArray.RemoveAll();
}
BOOL CModbusM::SaveToFile(CString strFile)
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
	str.Format("NUMBER_OF_PRIBOR=%d\r\n",m_ModbusPriborArray.GetSize());
	strBuf+=str;
	str.Format("AMOUNTBYTE=%d\r\n",AMOUNTBYTE);
	strBuf+=str;
	str.Format("CONTROLPOTOK=%d\r\n",CONTROLPOTOK);
	strBuf+=str;
	str.Format("NUMBER_NO_ANSWER=%d\r\n",NUMBER_NO_ANSWER);
	strBuf+=str;
	str.Format("MODBUS_TYPE=%d\r\n\r\n",MODBUS_TYPE);
	strBuf+=str;	
	
	for(int i =0; i < m_ModbusPriborArray.GetSize(); i++)
	{
		str.Format("MAKE_PRIBOR=%d\r\n",i+1);
		strBuf+=str;		
		str.Format("PRIBOR=%d\r\n",m_ModbusPriborArray[i].PRIBOR);
		strBuf+=str;
		str.Format("ADRESS=%d\r\n",m_ModbusPriborArray[i].ADRESS);
		strBuf+=str;		
		str.Format("FUNCTION=%d\r\n",m_ModbusPriborArray[i].FUNCTION);
		strBuf+=str;
		str.Format("START_ADRESS=%d\r\n",m_ModbusPriborArray[i].START_ADRESS);
		strBuf+=str;
		str.Format("NUMBER=%d\r\n",m_ModbusPriborArray[i].NUMBER);
		strBuf+=str;
		str.Format("ADRESS_PMZ=%d\r\n",m_ModbusPriborArray[i].ADRESS_PMZ);
		strBuf+=str;
		str.Format("DOP_BYTE1=%d\r\n",m_ModbusPriborArray[i].DOP_BYTE1);
		strBuf+=str;
		str.Format("DOP_BYTE2=%d\r\n",m_ModbusPriborArray[i].DOP_BYTE2);
		strBuf+=str;
		str.Format("DOP_BYTE3=%d\r\n",m_ModbusPriborArray[i].DOP_BYTE3);
		strBuf+=str;
		str.Format("DOP_BYTE4=%d\r\n",m_ModbusPriborArray[i].DOP_BYTE4);
		strBuf+=str;
		str.Format("TYPE_STATUS=%d\r\n",m_ModbusPriborArray[i].TYPE_STATUS);
		strBuf+=str;
		str.Format("MASKA_STATUS=%d\r\n",m_ModbusPriborArray[i].MASKA_STATUS);
		strBuf+=str;
		str.Format("ADRES_STATUS=%d\r\n",m_ModbusPriborArray[i].ADRES_STATUS);
		strBuf+=str;
		str.Format("ADRES_4B=%d\r\n",m_ModbusPriborArray[i].ADRES_4B);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_ModbusPriborArray[i].strCOMMENT);
		strBuf+=str;
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
BOOL CModbusM::LoadFromFile(CString strFile)
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
			if(str.Find("NEXTMESSAGE") != -1)
			{
				str.TrimLeft("NEXTMESSAGE");
				str.Trim();str.Trim("=");
				NEXTMESSAGE = atoi(str);
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
			if(str.Find("NUMBER_NO_ANSWER") != -1)
			{
				str.TrimLeft("NUMBER_NO_ANSWER");
				str.Trim();str.Trim("=");
				NUMBER_NO_ANSWER = atoi(str);
			}
			if(str.Find("MODBUS_TYPE") != -1)
			{
				str.TrimLeft("MODBUS_TYPE");
				str.Trim();str.Trim("=");
				MODBUS_TYPE = atoi(str);
			}			
			if(str.Find("NUMBER_OF_PRIBOR") != -1)
			{
				str.TrimLeft("NUMBER_OF_PRIBOR");
				str.Trim();str.Trim("=");
				m_ModbusPriborArray.SetSize(atoi(str));
			}
			
			
			if(str.Find("MAKE_PRIBOR") != -1)
			{
				str.TrimLeft("MAKE_PRIBOR");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_ModbusPriborArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}
			if((str.Find("//") != -1)&&(str.Find("//_") == -1))
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].strCOMMENT = str;														
			}
			if((str.Find("PRIBOR") != -1)&&(str.Find("MAKE_PRIBOR") == -1)&&(str.Find("NUMBER_OF_PRIBOR") == -1))
			{
				str.TrimLeft("PRIBOR");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].PRIBOR = atoi(str);										
			}			
			if((str.Find("ADRESS") != -1)&&(str.Find("START_ADRESS") == -1)&&(str.Find("ADRESS_PMZ") == -1))
			{
				str.TrimLeft("ADRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].ADRESS = atoi(str);										
			}
			if(str.Find("FUNCTION") != -1)
			{
				str.TrimLeft("FUNCTION");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].FUNCTION = atoi(str);										
			}		
			if(str.Find("START_ADRESS") != -1)
			{
				str.TrimLeft("START_ADRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].START_ADRESS = atoi(str);										
			}
			if(str.Find("ADRESS_PMZ") != -1)
			{
				str.TrimLeft("ADRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].ADRESS_PMZ = atoi(str);										
			}
			if((str.Find("NUMBER") != -1)&&(str.Find("NUMBER_NO_ANSWER") == -1)&&(str.Find("NUMBER_OF_PRIBOR") == -1))
			{
				str.TrimLeft("NUMBER");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].NUMBER = atoi(str);										
			}
			if(str.Find("DOP_BYTE1") != -1)
			{
				str.TrimLeft("DOP_BYTE1");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].DOP_BYTE1 = atoi(str);										
			}
			if(str.Find("DOP_BYTE2") != -1)
			{
				str.TrimLeft("DOP_BYTE2");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].DOP_BYTE2 = atoi(str);										
			}
			if(str.Find("DOP_BYTE3") != -1)
			{
				str.TrimLeft("DOP_BYTE3");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].DOP_BYTE3 = atoi(str);										
			}
			if(str.Find("DOP_BYTE4") != -1)
			{
				str.TrimLeft("DOP_BYTE4");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].DOP_BYTE4 = atoi(str);										
			}
			if(str.Find("TYPE_STATUS") != -1)
			{
				str.TrimLeft("TYPE_STATUS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].TYPE_STATUS= atoi(str);										
			}
			if(str.Find("MASKA_STATUS") != -1)
			{
				str.TrimLeft("MASKA_STATUS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].MASKA_STATUS= atoi(str);										
			}
			if(str.Find("ADRES_STATUS") != -1)
			{
				str.TrimLeft("ADRES_STATUS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].ADRES_STATUS= atoi(str);										
			}
			if(str.Find("ADRES_4B") != -1)
			{
				str.TrimLeft("ADRES_4B");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ModbusPriborArray.GetSize()))
					m_ModbusPriborArray[nProcIndex].ADRES_4B= atoi(str);										
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
BOOL CModbusM::SaveToTuFile(CString strFile)
{

	CString strBuf,str;	

	if(m_TuArray.GetSize()<=0)
	{
		str.Format("WAIT_RESP_TU=%d\r\n",0);
		strBuf+=str;
		str.Format("NUMBER_OF_TU=%d\r\n\r\n",0);
		strBuf+=str;			
	}
	else
	{
		str.Format("WAIT_RESP_TU=%d\r\n",m_TuArray[0].WAIT_RESP_TU);
		strBuf+=str;
		str.Format("NUMBER_OF_TU=%d\r\n\r\n",m_TuArray.GetSize());
		strBuf+=str;
	}
	
	for(int i =0; i < m_TuArray.GetSize(); i++)
	{
		str.Format("MAKE_TU=%d\r\n",i+1);
		strBuf+=str;		
		str.Format("TYPE_PRIBOR=%d\r\n",m_TuArray[i].TYPE_PRIBOR);
		strBuf+=str;		
		str.Format("ADRESS=%d\r\n",m_TuArray[i].ADRESS);
		strBuf+=str;
		str.Format("FUNCTION=%d\r\n",m_TuArray[i].FUNCTION);
		strBuf+=str;					
		str.Format("REGTU_ON=%d\r\n",m_TuArray[i].REGTU_ON);
		strBuf+=str;
		str.Format("REGTU_OFF=%d\r\n",m_TuArray[i].REGTU_OFF);
		strBuf+=str;
		str.Format("DATATU_ON=%d\r\n",m_TuArray[i].DATATU_ON);
		strBuf+=str;		
		str.Format("DATATU_OFF=%d\r\n",m_TuArray[i].DATATU_OFF);
		strBuf+=str;
		str.Format("TU_CLOSER=%d\r\n",m_TuArray[i].TU_CLOSER);
		strBuf+=str;		
		str.Format("IEC_ASDU=%d\r\n",m_TuArray[i].IEC_ASDU);
		strBuf+=str;
		str.Format("TU_ACT_TRM_ENABLE=%d\r\n",m_TuArray[i].TU_ACT_TRM_ENABLE);
		strBuf+=str;
		str.Format("TIMER_SEL_EXEC=%d\r\n",m_TuArray[i].TIMER_SEL_EXEC);
		strBuf+=str;
		str.Format("TIMER_ACT_TRM=%d\r\n",m_TuArray[i].TIMER_ACT_TRM);
		strBuf+=str;		
		str.Format("ADDRESS_TS=%d\r\n",m_TuArray[i].ADDRESS_TS);
		strBuf+=str;		
		str.Format("TS_ON=%d\r\n",m_TuArray[i].TS_ON);
		strBuf+=str;		
		str.Format("TS_OFF=%d\r\n",m_TuArray[i].TS_OFF);
		strBuf+=str;		
		str.Format("ADDRESS_DAMAGE_TU=%d\r\n",m_TuArray[i].ADDRESS_DAMAGE_TU);
		strBuf+=str;		
		str.Format("MASKA_DAMAGE_TU=%d\r\n",m_TuArray[i].MASKA_DAMAGE_TU);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_TuArray[i].strCOMMENT);
		strBuf+=str;
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
BOOL CModbusM::LoadFromTuFile(CString strFile)
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
		int nIndex = 0;
		int nProcIndex = -1;
		strBuf.Remove(';');
		int nWaitRespTU = 0;
		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			
			if(str.Find("NUMBER_OF_TU") != -1)
			{
				str.TrimLeft("NUMBER_OF_TU");
				str.Trim();str.Trim("=");
				m_TuArray.SetSize(atoi(str));
			}
						
			if(str.Find("MAKE_TU") != -1)
			{
				str.TrimLeft("MAKE_TU");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_TuArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}			
			if(str.Find("WAIT_RESP_TU") != -1)
			{
				str.TrimLeft("WAIT_RESP_TU");
				str.Trim();str.Trim("=");
				//if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					nWaitRespTU = atoi(str);										
			}
			if(str.Find("TU_CLOSER") != -1)
			{
				str.TrimLeft("TU_CLOSER");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TU_CLOSER = atoi(str);										
			}
			if(str.Find("DATATU_OFF") != -1)
			{
				str.TrimLeft("DATATU_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].DATATU_OFF = atoi(str);										
			}
			if(str.Find("DATATU_ON") != -1)
			{
				str.TrimLeft("DATATU_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].DATATU_ON = atoi(str);										
			}
			if(str.Find("REGTU_OFF") != -1)
			{
				str.TrimLeft("REGTU_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].REGTU_OFF = atoi(str);										
			}
			if(str.Find("REGTU_ON") != -1)
			{
				str.TrimLeft("REGTU_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].REGTU_ON = atoi(str);										
			}
			if(str.Find("FUNCTION") != -1)
			{
				str.TrimLeft("FUNCTION");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].FUNCTION = atoi(str);										
			}		
			if((str.Find("ADRESS") != -1)&&(str.Find("ADDRESS_TS") == -1)&&(str.Find("ADDRESS_DAMAGE_TU") == -1))
			{
				str.TrimLeft("ADRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].ADRESS = atoi(str);										
			}
			if(str.Find("TYPE_PRIBOR") != -1)
			{
				str.TrimLeft("TYPE_PRIBOR");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TYPE_PRIBOR = atoi(str);										
			}
			if(str.Find("IEC_ASDU") != -1)
			{
				str.TrimLeft("IEC_ASDU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].IEC_ASDU = atoi(str);										
			}
			if(str.Find("TU_ACT_TRM_ENABLE") != -1)
			{
				str.TrimLeft("TU_ACT_TRM_ENABLE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TU_ACT_TRM_ENABLE = atoi(str);										
			}
			if(str.Find("TIMER_SEL_EXEC") != -1)
			{
				str.TrimLeft("TIMER_SEL_EXEC");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TIMER_SEL_EXEC = atoi(str);										
			}
			if(str.Find("TIMER_ACT_TRM") != -1)
			{
				str.TrimLeft("TIMER_ACT_TRM");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TIMER_ACT_TRM = atoi(str);										
			}	
			if(str.Find("ADDRESS_TS") != -1)
			{
				str.TrimLeft("ADDRESS_TS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].ADDRESS_TS = atoi(str);										
			}	
			if(str.Find("TS_ON") != -1)
			{
				str.TrimLeft("TS_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TS_ON = atoi(str);										
			}	
			if(str.Find("TS_OFF") != -1)
			{
				str.TrimLeft("TS_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TS_OFF = atoi(str);										
			}	
			if(str.Find("ADDRESS_DAMAGE_TU") != -1)
			{
				str.TrimLeft("ADDRESS_DAMAGE_TU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].ADDRESS_DAMAGE_TU = atoi(str);										
			}
			if(str.Find("MASKA_DAMAGE_TU") != -1)
			{
				str.TrimLeft("MASKA_DAMAGE_TU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].MASKA_DAMAGE_TU = atoi(str);										
			}
			if((str.Find("//") != -1)&&(str.Find("//_") == -1))
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].strCOMMENT = str;														
			}
			strBuf.Delete(0,nIndex+1);			
		}while(nIndex != -1);

		for(int i = 0; i < m_TuArray.GetSize(); i++)
			m_TuArray[i].WAIT_RESP_TU = nWaitRespTU;
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}
/*BOOL CModbusM::SaveToTuFile(CString strFile)
{
	if(m_TuArray.GetSize()<=0)
		return TRUE;

	CString strBuf,str;	

	str.Format("NUMBER_OF_TU=%d\r\n\r\n",m_TuArray.GetSize());
	strBuf+=str;
	
	for(int i =0; i < m_TuArray.GetSize(); i++)
	{
		str.Format("MAKE_TU=%d\r\n",i+1);
		strBuf+=str;
		str.Format("ADRESS=%d\r\n",m_TuArray[i].ADRESS);
		strBuf+=str;
		str.Format("DATATU_OFF=%d\r\n",m_TuArray[i].DATATU_OFF);
		strBuf+=str;
		str.Format("DATATU_ON=%d\r\n",m_TuArray[i].DATATU_ON);
		strBuf+=str;
		str.Format("FUNCTION=%d\r\n",m_TuArray[i].FUNCTION);
		strBuf+=str;
		str.Format("REGTU_OFF=%d\r\n",m_TuArray[i].REGTU_OFF);
		strBuf+=str;
		str.Format("REGTU_ON=%d\r\n",m_TuArray[i].REGTU_ON);
		strBuf+=str;
		str.Format("TU_CLOSER=%d\r\n",m_TuArray[i].TU_CLOSER);
		strBuf+=str;
		str.Format("TYPE_PRIBOR=%d\r\n",m_TuArray[i].TYPE_PRIBOR);
		strBuf+=str;
		str.Format("WAIT_RESP_TU=%d\r\n",m_TuArray[i].WAIT_RESP_TU);
		strBuf+=str;
		str.Format("IEC_ASDU=%d\r\n",m_TuArray[i].IEC_ASDU);
		strBuf+=str;
		str.Format("TU_ACT_TRM_ENABLE=%d\r\n",m_TuArray[i].TU_ACT_TRM_ENABLE);
		strBuf+=str;
		str.Format("TIMER_SEL_EXEC=%d\r\n",m_TuArray[i].TIMER_SEL_EXEC);
		strBuf+=str;
		str.Format("TIMER_ACT_TRM=%d\r\n",m_TuArray[i].TIMER_ACT_TRM);
		strBuf+=str;		
		str.Format("ADDRESS_TS=%d\r\n",m_TuArray[i].ADDRESS_TS);
		strBuf+=str;		
		str.Format("TS_ON=%d\r\n",m_TuArray[i].TS_ON);
		strBuf+=str;		
		str.Format("TS_OFF=%d\r\n\r\n",m_TuArray[i].TS_OFF);
		strBuf+=str;		
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
BOOL CModbusM::LoadFromTuFile(CString strFile)
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
		int nIndex = 0;
		int nProcIndex = -1;
		strBuf.Remove(';');
		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			
			if(str.Find("NUMBER_OF_TU") != -1)
			{
				str.TrimLeft("NUMBER_OF_TU");
				str.Trim();str.Trim("=");
				m_TuArray.SetSize(atoi(str));
			}
						
			if(str.Find("MAKE_TU") != -1)
			{
				str.TrimLeft("MAKE_TU");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_TuArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}			
			if(str.Find("WAIT_RESP_TU") != -1)
			{
				str.TrimLeft("WAIT_RESP_TU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].WAIT_RESP_TU = atoi(str);										
			}
			if(str.Find("TU_CLOSER") != -1)
			{
				str.TrimLeft("TU_CLOSER");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TU_CLOSER = atoi(str);										
			}
			if(str.Find("DATATU_OFF") != -1)
			{
				str.TrimLeft("DATATU_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].DATATU_OFF = atoi(str);										
			}
			if(str.Find("DATATU_ON") != -1)
			{
				str.TrimLeft("DATATU_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].DATATU_ON = atoi(str);										
			}
			if(str.Find("REGTU_OFF") != -1)
			{
				str.TrimLeft("REGTU_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].REGTU_OFF = atoi(str);										
			}
			if(str.Find("REGTU_ON") != -1)
			{
				str.TrimLeft("REGTU_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].REGTU_ON = atoi(str);										
			}
			if(str.Find("FUNCTION") != -1)
			{
				str.TrimLeft("FUNCTION");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].FUNCTION = atoi(str);										
			}		
			if((str.Find("ADRESS") != -1)&&(str.Find("ADDRESS_TS") == -1))
			{
				str.TrimLeft("ADRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].ADRESS = atoi(str);										
			}
			if(str.Find("TYPE_PRIBOR") != -1)
			{
				str.TrimLeft("TYPE_PRIBOR");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TYPE_PRIBOR = atoi(str);										
			}
			if(str.Find("IEC_ASDU") != -1)
			{
				str.TrimLeft("IEC_ASDU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].IEC_ASDU = atoi(str);										
			}
			if(str.Find("TU_ACT_TRM_ENABLE") != -1)
			{
				str.TrimLeft("TU_ACT_TRM_ENABLE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TU_ACT_TRM_ENABLE = atoi(str);										
			}
			if(str.Find("TIMER_SEL_EXEC") != -1)
			{
				str.TrimLeft("TIMER_SEL_EXEC");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TIMER_SEL_EXEC = atoi(str);										
			}
			if(str.Find("TIMER_ACT_TRM") != -1)
			{
				str.TrimLeft("TIMER_ACT_TRM");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TIMER_ACT_TRM = atoi(str);										
			}	
			if(str.Find("ADDRESS_TS") != -1)
			{
				str.TrimLeft("ADDRESS_TS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].ADDRESS_TS = atoi(str);										
			}	
			if(str.Find("TS_ON") != -1)
			{
				str.TrimLeft("TS_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TS_ON = atoi(str);										
			}	
			if(str.Find("TS_OFF") != -1)
			{
				str.TrimLeft("TS_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TS_OFF = atoi(str);										
			}	
			strBuf.Delete(0,nIndex+1);			
		}while(nIndex != -1);
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}*/
/*BOOL CModbusM::SaveToTuFile(CString strFile)
{
	if(m_TuArray.GetSize()<=0)
		return TRUE;

	CString strBuf,str;	

	str.Format("NUMBER_OF_TU=%d\r\n\r\n",m_TuArray.GetSize());
	strBuf+=str;
	
	for(int i =0; i < m_TuArray.GetSize(); i++)
	{
		str.Format("MAKE_TU=%d\r\n",i+1);
		strBuf+=str;
		str.Format("ADRESS=%d\r\n",m_TuArray[i].ADRESS);
		strBuf+=str;
		str.Format("DATATU_OFF=%d\r\n",m_TuArray[i].DATATU_OFF);
		strBuf+=str;
		str.Format("DATATU_ON=%d\r\n",m_TuArray[i].DATATU_ON);
		strBuf+=str;
		str.Format("FUNCTION=%d\r\n",m_TuArray[i].FUNCTION);
		strBuf+=str;
		str.Format("REGTU_OFF=%d\r\n",m_TuArray[i].REGTU_OFF);
		strBuf+=str;
		str.Format("REGTU_ON=%d\r\n",m_TuArray[i].REGTU_ON);
		strBuf+=str;
		str.Format("TU_CLOSER=%d\r\n",m_TuArray[i].TU_CLOSER);
		strBuf+=str;
		str.Format("TYPE_PRIBOR=%d\r\n",m_TuArray[i].TYPE_PRIBOR);
		strBuf+=str;
		str.Format("WAIT_RESP_TU=%d\r\n\r\n",m_TuArray[i].WAIT_RESP_TU);
		strBuf+=str;		
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
BOOL CModbusM::LoadFromTuFile(CString strFile)
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
		int nIndex = 0;
		int nProcIndex = -1;
		strBuf.Remove(';');
		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			
			if(str.Find("NUMBER_OF_TU") != -1)
			{
				str.TrimLeft("NUMBER_OF_TU");
				str.Trim();str.Trim("=");
				m_TuArray.SetSize(atoi(str));
			}
						
			if(str.Find("MAKE_TU") != -1)
			{
				str.TrimLeft("MAKE_TU");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_TuArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}			
			if(str.Find("WAIT_RESP_TU") != -1)
			{
				str.TrimLeft("WAIT_RESP_TU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].WAIT_RESP_TU = atoi(str);										
			}
			if(str.Find("TU_CLOSER") != -1)
			{
				str.TrimLeft("TU_CLOSER");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TU_CLOSER = atoi(str);										
			}
			if(str.Find("DATATU_OFF") != -1)
			{
				str.TrimLeft("DATATU_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].DATATU_OFF = atoi(str);										
			}
			if(str.Find("DATATU_ON") != -1)
			{
				str.TrimLeft("DATATU_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].DATATU_ON = atoi(str);										
			}
			if(str.Find("REGTU_OFF") != -1)
			{
				str.TrimLeft("REGTU_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].REGTU_OFF = atoi(str);										
			}
			if(str.Find("REGTU_ON") != -1)
			{
				str.TrimLeft("REGTU_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].REGTU_ON = atoi(str);										
			}
			if(str.Find("FUNCTION") != -1)
			{
				str.TrimLeft("FUNCTION");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].FUNCTION = atoi(str);										
			}
			if(str.Find("ADRESS") != -1)
			{
				str.TrimLeft("ADRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].ADRESS = atoi(str);										
			}
			if(str.Find("TYPE_PRIBOR") != -1)
			{
				str.TrimLeft("TYPE_PRIBOR");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_TuArray.GetSize()))
					m_TuArray[nProcIndex].TYPE_PRIBOR = atoi(str);										
			}
			
			strBuf.Delete(0,nIndex+1);			
		}while(nIndex != -1);
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}*/