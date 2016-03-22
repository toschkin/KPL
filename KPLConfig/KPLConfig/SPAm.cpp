#include "StdAfx.h"
#include "SPAm.h"

CSPAm::CSPAm(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=1;
	PARITY=1;
	BYTETIME=10;
	WAITRESP=100;
	NEXTMESSAGE=10;
	AMOUNTBYTE=8;
	FLOWCONTROLL=0;
	NUMBER_NO_ANSWER=1;
	NUMBER_OF_DEVICES=1;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES=0;
	SERVICE=1;	
	RES_PORT=1;
}

CSPAm::~CSPAm(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=1;
	PARITY=1;
	BYTETIME=10;
	WAITRESP=100;
	NEXTMESSAGE=10;
	AMOUNTBYTE=8;
	FLOWCONTROLL=0;
	NUMBER_NO_ANSWER=1;
	NUMBER_OF_DEVICES=1;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES=0;
	SERVICE=1;	
	RES_PORT=1;
	m_IndividualStructureSPAArray.RemoveAll();
	m_TuArray.RemoveAll();
}
BOOL CSPAm::SaveToFile(CString strFile)
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
	str.Format("AMOUNTBYTE=%d\r\n",AMOUNTBYTE);
	strBuf+=str;
	str.Format("FLOWCONTROLL=%d\r\n",FLOWCONTROLL);
	strBuf+=str;
	str.Format("NUMBER_NO_ANSWER=%d\r\n",NUMBER_NO_ANSWER);
	strBuf+=str;
	str.Format("NUMBER_OF_DEVICES=%d\r\n",NUMBER_OF_DEVICES);
	strBuf+=str;
	str.Format("NUMBER_OF_INDIVIDUAL_STRUCTURES=%d\r\n",m_IndividualStructureSPAArray.GetSize());
	strBuf+=str;
	str.Format("SERVICE=%d\r\n",SERVICE);
	strBuf+=str;	
	str.Format("RES_PORT=%d\r\n\r\n",RES_PORT);
	strBuf+=str;		

	for(int i =0; i < m_IndividualStructureSPAArray.GetSize(); i++)
	{		
		str.Format("MAKE_DEVICE=%d\r\n",i+1);
		strBuf+=str;
		str.Format("SLAVE_ADDRESS=%d\r\n",m_IndividualStructureSPAArray[i].SLAVE_ADDRESS);
		strBuf+=str;
		str.Format("CHANNEL_NUM=%d\r\n",m_IndividualStructureSPAArray[i].CHANNEL_NUM);
		strBuf+=str;
		str.Format("TYPE_ID=%d\r\n",m_IndividualStructureSPAArray[i].TYPE_ID);
		strBuf+=str;
		str.Format("DATA_CAT=%d\r\n",m_IndividualStructureSPAArray[i].DATA_CAT);
		strBuf+=str;
		str.Format("DATA_NUM=%d\r\n",m_IndividualStructureSPAArray[i].DATA_NUM);
		strBuf+=str;
		str.Format("ADDRESS_PMZ=%d\r\n",m_IndividualStructureSPAArray[i].ADDRESS_PMZ);
		strBuf+=str;
		str.Format("TYPE_STATUS=%d\r\n",m_IndividualStructureSPAArray[i].TYPE_STATUS);
		strBuf+=str;
		str.Format("MASKA_STATUS=%d\r\n",m_IndividualStructureSPAArray[i].MASKA_STATUS);
		strBuf+=str;
		str.Format("ADRES_STATUS=%d\r\n",m_IndividualStructureSPAArray[i].ADRES_STATUS);
		strBuf+=str;			
		str.Format("//%s\r\n\r\n",m_IndividualStructureSPAArray[i].strCOMMENT);
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
BOOL CSPAm::LoadFromFile(CString strFile)
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
			if((str.Find("PORT") != -1)&&(str.Find("RES_PORT") == -1))
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
			if(str.Find("FLOWCONTROLL") != -1)
			{
				str.TrimLeft("FLOWCONTROLL");
				str.Trim();str.Trim("=");
				FLOWCONTROLL = atoi(str);
			}
			if(str.Find("NUMBER_NO_ANSWER") != -1)
			{
				str.TrimLeft("NUMBER_NO_ANSWER");
				str.Trim();str.Trim("=");
				NUMBER_NO_ANSWER = atoi(str);
			}			
			if(str.Find("NUMBER_OF_DEVICES") != -1)
			{
				str.TrimLeft("NUMBER_OF_DEVICES");
				str.Trim();str.Trim("=");
				NUMBER_OF_DEVICES = atoi(str);
			}
			
			if(str.Find("SERVICE") != -1)
			{
				str.TrimLeft("SERVICE");
				str.Trim();str.Trim("=");
				SERVICE = atoi(str);
			}
			if(str.Find("RES_PORT") != -1)
			{
				str.TrimLeft("RES_PORT");
				str.Trim();str.Trim("=");
				RES_PORT = atoi(str);
			}			
			if(str.Find("NUMBER_OF_INDIVIDUAL_STRUCTURES") != -1)
			{
				str.TrimLeft("NUMBER_OF_INDIVIDUAL_STRUCTURES");
				str.Trim();str.Trim("=");
				m_IndividualStructureSPAArray.SetSize(atoi(str));
			}		
			if(str.Find("MAKE_DEVICE") != -1)
			{
				str.TrimLeft("MAKE_DEVICE");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IndividualStructureSPAArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}
			if(str.Find("SLAVE_ADDRESS") != -1)
			{
				str.TrimLeft("SLAVE_ADDRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].SLAVE_ADDRESS = atoi(str);										
			}
			if(str.Find("CHANNEL_NUM") != -1)
			{
				str.TrimLeft("CHANNEL_NUM");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].CHANNEL_NUM = atoi(str);										
			}
			if(str.Find("TYPE_ID") != -1)
			{
				str.TrimLeft("TYPE_ID");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].TYPE_ID = atoi(str);										
			}
			if(str.Find("DATA_CAT") != -1)
			{
				str.TrimLeft("DATA_CAT");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].DATA_CAT = atoi(str);										
			}
			if(str.Find("DATA_NUM") != -1)
			{
				str.TrimLeft("DATA_NUM");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].DATA_NUM = atoi(str);										
			}
			if(str.Find("ADDRESS_PMZ") != -1)
			{
				str.TrimLeft("ADDRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].ADDRESS_PMZ = atoi(str);										
			}
			if(str.Find("TYPE_STATUS") != -1)
			{
				str.TrimLeft("TYPE_STATUS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].TYPE_STATUS = atoi(str);										
			}
			if(str.Find("MASKA_STATUS") != -1)
			{
				str.TrimLeft("MASKA_STATUS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].MASKA_STATUS = atoi(str);										
			}
			if(str.Find("ADRES_STATUS") != -1)
			{
				str.TrimLeft("ADRES_STATUS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].ADRES_STATUS = atoi(str);										
			}					
			if(str.Find("//") != -1)
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSPAArray.GetSize()))
					m_IndividualStructureSPAArray[nProcIndex].strCOMMENT = str;														
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
BOOL CSPAm::SaveToTuFile(CString strFile)
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
BOOL CSPAm::LoadFromTuFile(CString strFile)
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
				//	m_TuArray[nProcIndex].WAIT_RESP_TU = atoi(str);										
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
			if((str.Find("//") != -1)/*&&(str.Find("//_") == -1)*/)
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