#include "StdAfx.h"
#include "GPSTime.h"

CGPSTime::CGPSTime(void)
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
	
	TYPE_OF_GPS=1;
	PERIOD_C_CS_NA_1=60;
	SERVICE=0;
	SUMMER_TIME_ON=0;
	GMT_CORRECTION=3;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES
	ENABLE_SCRIPT=1;
	SYNC_FROM=1;
	GPS_SYNC_ATTEMPT_TIME=1;
	NTP_SERVER_IP="127.0.0.1";
	NTP_LOG=1;
	m_IndividualStructureGPSArray.SetSize(2);	
}

CGPSTime::~CGPSTime(void)
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
	
	TYPE_OF_GPS=1;
	PERIOD_C_CS_NA_1=60;
	SERVICE=0;
	SUMMER_TIME_ON=0;
	GMT_CORRECTION=3;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES
	ENABLE_SCRIPT=1;
	SYNC_FROM=1;
	GPS_SYNC_ATTEMPT_TIME=1;
	NTP_SERVER_IP="127.0.0.1";
	NTP_LOG=1;
	m_IndividualStructureGPSArray.RemoveAll();
	m_IndividualStructureGPSArray.SetSize(2);
}
BOOL CGPSTime::SaveToFile(CString strFile)
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
	str.Format("TYPE_OF_GPS=%d\r\n",TYPE_OF_GPS);
	strBuf+=str;
	str.Format("PERIOD_C_CS_NA_1=%d\r\n",PERIOD_C_CS_NA_1);
	strBuf+=str;
	str.Format("SERVICE=%d\r\n",SERVICE);
	strBuf+=str;
	str.Format("SUMMER_TIME_ON=%d\r\n",SUMMER_TIME_ON);
	strBuf+=str;
	str.Format("GMT_CORRECTION=%d\r\n",GMT_CORRECTION);
	strBuf+=str;
	str.Format("NUMBER_OF_INDIVIDUAL_STRUCTURES=%d\r\n",m_IndividualStructureGPSArray.GetSize());
	strBuf+=str;
	str.Format("ENABLE_SCRIPT=%d\r\n",ENABLE_SCRIPT);
	strBuf+=str;
	str.Format("SYNC_FROM=%d\r\n",SYNC_FROM);
	strBuf+=str;
	str.Format("GPS_SYNC_ATTEMPT_TIME=%d\r\n\r\n",GPS_SYNC_ATTEMPT_TIME);
	strBuf+=str;

	if(m_nVersion > 19)
	{
		strBuf.TrimRight("\r\n");
		strBuf+="\r\n";
		CStringArray dest;
		Str2Array(NTP_SERVER_IP, &dest, '.');
		if(dest.GetSize()==4)
		{
			union 
			{
				UINT uIP;
				BYTE byIP[4];
			}IP;
			IP.byIP[0] = (BYTE)atoi(dest[3]);
			IP.byIP[1] = (BYTE)atoi(dest[2]);
			IP.byIP[2] = (BYTE)atoi(dest[1]);
			IP.byIP[3] = (BYTE)atoi(dest[0]);		
			str.Format("NTP_SERVER_IP=%u\r\n",IP.uIP);
		}
		else
			str.Format("NTP_SERVER_IP=%i\r\n",0);

		CString strMainIP = str;
		strBuf+=str;

		str.Format("NTP_LOG=%d\r\n\r\n",NTP_LOG);
		strBuf+=str;
	}
			
	for(int i =0; i < m_IndividualStructureGPSArray.GetSize(); i++)
	{
		str.Format("MAKE_DEVICE=%d\r\n",i+1);
		strBuf+=str;		
		str.Format("TYPE_ID=%d\r\n",m_IndividualStructureGPSArray[i].TYPE_ID);
		strBuf+=str;
		str.Format("NUM_BYTE=%d\r\n",m_IndividualStructureGPSArray[i].NUM_BYTE);
		strBuf+=str;		
		str.Format("AM_IOA=%d\r\n",m_IndividualStructureGPSArray[i].AM_IOA);
		strBuf+=str;
		str.Format("ADDRESS_PMZ=%d\r\n\r\n",m_IndividualStructureGPSArray[i].ADDRESS_PMZ);
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

BOOL CGPSTime::LoadFromFile(CString strFile)
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
			if(str.Find("TYPE_OF_GPS") != -1)
			{
				str.TrimLeft("TYPE_OF_GPS");
				str.Trim();str.Trim("=");
				TYPE_OF_GPS = atoi(str);
			}
			if(str.Find("PERIOD_C_CS_NA_1") != -1)
			{
				str.TrimLeft("PERIOD_C_CS_NA_1");
				str.Trim();str.Trim("=");
				PERIOD_C_CS_NA_1 = atoi(str);
			}
			if(str.Find("SERVICE") != -1)
			{
				str.TrimLeft("SERVICE");
				str.Trim();str.Trim("=");
				SERVICE = atoi(str);
			}
			if(str.Find("SUMMER_TIME_ON") != -1)
			{
				str.TrimLeft("SUMMER_TIME_ON");
				str.Trim();str.Trim("=");
				SUMMER_TIME_ON = atoi(str);
			}
			if(str.Find("GMT_CORRECTION") != -1)
			{
				str.TrimLeft("GMT_CORRECTION");
				str.Trim();str.Trim("=");
				GMT_CORRECTION = atoi(str);
			}
			if(str.Find("ENABLE_SCRIPT") != -1)
			{
				str.TrimLeft("ENABLE_SCRIPT");
				str.Trim();str.Trim("=");
				ENABLE_SCRIPT = atoi(str);
			}
			if(str.Find("SYNC_FROM") != -1)
			{
				str.TrimLeft("SYNC_FROM");
				str.Trim();str.Trim("=");
				SYNC_FROM = atoi(str);
			}
			if(str.Find("GPS_SYNC_ATTEMPT_TIME") != -1)
			{
				str.TrimLeft("GPS_SYNC_ATTEMPT_TIME");
				str.Trim();str.Trim("=");
				GPS_SYNC_ATTEMPT_TIME = atoi(str);
			}
			if(m_nVersion > 19)
			{
				if(str.Find("NTP_SERVER_IP") != -1)
				{
					str.TrimLeft("NTP_SERVER_IP");
					str.Trim();str.Trim("=");

					union 
					{
						__int64 uIP;
						BYTE byIP[8];
					}IP;
					IP.uIP = _atoi64(str);
				
					str.Format("%d.%d.%d.%d",IP.byIP[3],IP.byIP[2],IP.byIP[1],IP.byIP[0]);

					NTP_SERVER_IP = str;
				}	
				if(str.Find("NTP_LOG") != -1)
				{
					str.TrimLeft("NTP_LOG");
					str.Trim();str.Trim("=");
					NTP_LOG = atoi(str);
				}
			}
			if(str.Find("NUMBER_OF_INDIVIDUAL_STRUCTURES") != -1)
			{
				str.TrimLeft("NUMBER_OF_INDIVIDUAL_STRUCTURES");
				str.Trim();str.Trim("=");
				m_IndividualStructureGPSArray.SetSize(atoi(str));
			}
						
			if(str.Find("MAKE_DEVICE") != -1)
			{
				str.TrimLeft("MAKE_DEVICE");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IndividualStructureGPSArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}			
			if(str.Find("TYPE_ID") != -1)
			{
				str.TrimLeft("TYPE_ID");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPSArray.GetSize()))
					m_IndividualStructureGPSArray[nProcIndex].TYPE_ID = atoi(str);										
			}
			if(str.Find("NUM_BYTE") != -1)
			{
				str.TrimLeft("NUM_BYTE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPSArray.GetSize()))
					m_IndividualStructureGPSArray[nProcIndex].NUM_BYTE = atoi(str);										
			}			
			if(str.Find("AM_IOA") != -1)
			{
				str.TrimLeft("AM_IOA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPSArray.GetSize()))
					m_IndividualStructureGPSArray[nProcIndex].AM_IOA = atoi(str);										
			}
			if((str.Find("ADDRESS_PMZ") != -1)&&(str.Find("STATUS_ADDRESS_PMZ") == -1))
			{
				str.TrimLeft("ADDRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPSArray.GetSize()))
					m_IndividualStructureGPSArray[nProcIndex].ADDRESS_PMZ = atoi(str);										
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
/*BOOL CGPSTime::SaveToScriptFile(CString strFile)
{
	CString strBuf;	
	strBuf.Format("/usr/sbin/ntpdate %s >> /home/ntpdate.log 2>&1\r\nhwclock -s >> /home/ntpdate.log",ADRESS_IP_NTP);			
		
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
BOOL CGPSTime::LoadFromScriptFile(CString strFile)
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

		int idx1 = strBuf.Find("/usr/sbin/ntpdate ",0);
		int idx2 = strBuf.Find(" >>",0);

		if((idx1!=-1)&&(idx2!=-1)&&(idx2 > idx1+18))
		{
			ADRESS_IP_NTP = strBuf.Mid(idx1+18,idx2-(idx1+18));			
		}		
	}
	catch(...)
	{
		return FALSE;
	}

	return TRUE;
}*/