#include "StdAfx.h"
#include "Iec104m.h"

CIec104m::CIec104m(void)
{
	m_nProcNum=0;

	UST_CONNECT_t0=30;
	TEST_APDU_t1=15;
	CONFIRM_t2=10;
	SEND_TEST_t3=20;
	MAX_DELTA_K=12;
	CONFIRM_AFTER_W=8;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=3;
	ADRESS_IP="127.0.0.1";
	SMOLLTIME=0;
	GLOBAL_ASDU=1;	
	PORT=2404;
	C_IС_NA_1_ENABLE=1;
	C_IС_NA_1_WAIT_END_ACT=1;
	C_CS_NA_1_ENABLE=0;
	C_CS_NA_1_WAIT_END_ACT=0;
	PERIOD_C_IC_NA_1=3600;
	TIME_WAIT_C_IC_NA_1=30;
	PERIOD_C_CS_NA_1=3600;
	TIME_WAIT_C_CS_NA_1=30;
	TIME_WAIT_RESP_TEST=10;
	TIME_WAIT_RESP_STOP=5;
	TIME_WAIT_FLAG_BAD=30;	
	RES_ADRESS_IP="127.0.0.1";
	RES_PORT=2404;	
}

CIec104m::~CIec104m(void)
{
	m_nProcNum=0;

	UST_CONNECT_t0=30;
	TEST_APDU_t1=15;
	CONFIRM_t2=10;
	SEND_TEST_t3=20;
	MAX_DELTA_K=12;
	CONFIRM_AFTER_W=8;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=3;
	ADRESS_IP="127.0.0.1";
	SMOLLTIME=0;
	GLOBAL_ASDU=1;	
	PORT=2404;
	C_IС_NA_1_ENABLE=1;
	C_IС_NA_1_WAIT_END_ACT=1;
	C_CS_NA_1_ENABLE=0;
	C_CS_NA_1_WAIT_END_ACT=0;
	PERIOD_C_IC_NA_1=3600;
	TIME_WAIT_C_IC_NA_1=30;
	PERIOD_C_CS_NA_1=3600;
	TIME_WAIT_C_CS_NA_1=30;
	TIME_WAIT_RESP_TEST=10;
	TIME_WAIT_RESP_STOP=5;
	TIME_WAIT_FLAG_BAD=30;	
	RES_ADRESS_IP="127.0.0.1";
	RES_PORT=2404;
}
BOOL CIec104m::SaveToFile(CString strFile)
{ 
	CString strBuf,str;
				
	str.Format("UST_CONNECT_t0=%d\r\n",UST_CONNECT_t0);
	strBuf+=str;
	str.Format("TEST_APDU_t1=%d\r\n",TEST_APDU_t1);
	strBuf+=str;
	str.Format("CONFIRM_t2=%d\r\n",CONFIRM_t2);
	strBuf+=str;
	str.Format("SEND_TEST_t3=%d\r\n",SEND_TEST_t3);
	strBuf+=str;
	str.Format("MAX_DELTA_K=%d\r\n",MAX_DELTA_K);
	strBuf+=str;
	str.Format("CONFIRM_AFTER_W=%d\r\n",CONFIRM_AFTER_W);
	strBuf+=str;	
	str.Format("SIZE_COFT=%d\r\n",2);//SIZE_COFT
	strBuf+=str;
	str.Format("SIZE_ASDU=%d\r\n",2);//SIZE_ASDU
	strBuf+=str;
	str.Format("SIZE_IOA=%d\r\n",3);//SIZE_IOA
	strBuf+=str;			
	
	CStringArray dest;
	Str2Array(ADRESS_IP, &dest, '.');
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
		str.Format("ADRESS_IP=%u\r\n",IP.uIP);
	}
	else
		str.Format("ADRESS_IP=%i\r\n",0);
	strBuf+=str;

	str.Format("SMOLLTIME=%d\r\n",SMOLLTIME);
	strBuf+=str;
	str.Format("GLOBAL_ASDU=%d\r\n",GLOBAL_ASDU);
	strBuf+=str;
	str.Format("PORT=%d\r\n",PORT);
	strBuf+=str;
	str.Format("C_IC_NA_1_ENABLE=%d\r\n",C_IС_NA_1_ENABLE);
	strBuf+=str;
	str.Format("C_IC_NA_1_WAIT_END_ACT=%d\r\n",C_IС_NA_1_WAIT_END_ACT);
	strBuf+=str;
	str.Format("C_CS_NA_1_ENABLE=%d\r\n",C_CS_NA_1_ENABLE);
	strBuf+=str;
	str.Format("C_CS_NA_1_WAIT_END_ACT=%d\r\n",C_CS_NA_1_WAIT_END_ACT);
	strBuf+=str;
	str.Format("PERIOD_C_IC_NA_1=%d\r\n",PERIOD_C_IC_NA_1);
	strBuf+=str;
	str.Format("TIME_WAIT_C_IC_NA_1=%d\r\n",TIME_WAIT_C_IC_NA_1);
	strBuf+=str;
	str.Format("PERIOD_C_CS_NA_1=%d\r\n",PERIOD_C_CS_NA_1);
	strBuf+=str;
	str.Format("TIME_WAIT_C_CS_NA_1=%d\r\n",TIME_WAIT_C_CS_NA_1);
	strBuf+=str;
	str.Format("TIME_WAIT_RESP_TEST=%d\r\n",TEST_APDU_t1);//сделано специально
	strBuf+=str;
	str.Format("TIME_WAIT_RESP_STOP=%d\r\n",TEST_APDU_t1);//сделано специально
	strBuf+=str;
	str.Format("TIME_WAIT_FLAG_BAD=%d\r\n",TIME_WAIT_FLAG_BAD);
	strBuf+=str;
	str.Format("NUMBER_CONFIG_STRUCTURES=%d\r\n\r\n",m_IndividualStructure104Array.GetSize());
	strBuf+=str;
	if(m_nVersion > 11)
	{
		strBuf.TrimRight("\r\n");
		strBuf+="\r\n";
		Str2Array(RES_ADRESS_IP, &dest, '.');
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
			str.Format("RES_ADRESS_IP=%u\r\n",IP.uIP);
		}
		else
			str.Format("RES_ADRESS_IP=%i\r\n",0);
		strBuf+=str;
		str.Format("RES_PORT=%d\r\n\r\n",RES_PORT);
		strBuf+=str;
	}
	
	for(int i =0; i < m_IndividualStructure104Array.GetSize(); i++)
	{
		str.Format("MAKE_STRUCTURE=%d\r\n",i+1);
		strBuf+=str;		
		str.Format("TYPE_ID=%d\r\n",m_IndividualStructure104Array[i].TYPE_ID);
		strBuf+=str;
		str.Format("NUM_BYTE=%d\r\n",m_IndividualStructure104Array[i].NUM_BYTE);
		strBuf+=str;
		str.Format("TYPE_ID_C_IC_NA_1=%d\r\n",m_IndividualStructure104Array[i].TYPE_ID_C_IC_NA_1);
		strBuf+=str;
		str.Format("NUM_BYTE_C_IC_NA_1=%d\r\n",m_IndividualStructure104Array[i].NUM_BYTE_C_IC_NA_1);
		strBuf+=str;
		str.Format("ORIGINATOR_ADDRESS=%d\r\n",m_IndividualStructure104Array[i].ORIGINATOR_ADDRESS);
		strBuf+=str;
		str.Format("COMMON_ADDRESS_ASDU=%d\r\n",m_IndividualStructure104Array[i].COMMON_ADDRESS_ASDU);
		strBuf+=str;
		str.Format("START_IOA=%d\r\n",m_IndividualStructure104Array[i].START_IOA);
		strBuf+=str;
		str.Format("AM_IOA=%d\r\n",m_IndividualStructure104Array[i].AM_IOA);
		strBuf+=str;
		str.Format("ADDRESS_PMZ=%d\r\n",m_IndividualStructure104Array[i].ADDRESS_PMZ);
		strBuf+=str;
		str.Format("POZITION_OF_QUALITY_FLAG=%d\r\n",m_IndividualStructure104Array[i].POZITION_OF_QUALITY_FLAG);
		strBuf+=str;		
		str.Format("STATUS_ADDRESS=%d\r\n",m_IndividualStructure104Array[i].STATUS_ADDRESS);
		strBuf+=str;
		str.Format("STATUS_MASKA=%d\r\n",m_IndividualStructure104Array[i].STATUS_MASKA);
		strBuf+=str;
		str.Format("STATUS_TYPE=%d\r\n",m_IndividualStructure104Array[i].STATUS_TYPE);
		strBuf+=str;
		str.Format("DOP_FLAG=%d\r\n",m_IndividualStructure104Array[i].DOP_FLAG);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_IndividualStructure104Array[i].strCOMMENT);
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
BOOL CIec104m::LoadFromFile(CString strFile)
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

			if(str.Find("UST_CONNECT_T0") != -1)
			{
				str.TrimLeft("UST_CONNECT_T0");
				str.Trim();str.Trim("=");				
				UST_CONNECT_t0 = atoi(str);
			}
			if(str.Find("TEST_APDU_T1") != -1)
			{
				str.TrimLeft("TEST_APDU_T1");
				str.Trim();str.Trim("=");
				TEST_APDU_t1 = atoi(str);
			}
			if(str.Find("CONFIRM_T2") != -1)
			{
				str.TrimLeft("CONFIRM_T2");
				str.Trim();str.Trim("=");
				CONFIRM_t2 = atoi(str);
			}
			if(str.Find("SEND_TEST_T3") != -1)
			{
				str.TrimLeft("SEND_TEST_T3");
				str.Trim();str.Trim("=");
				SEND_TEST_t3 = atoi(str);
			}
			if(str.Find("MAX_DELTA_K") != -1)
			{
				str.TrimLeft("MAX_DELTA_K");
				str.Trim();str.Trim("=");
				MAX_DELTA_K = atoi(str);
			}
			if(str.Find("CONFIRM_AFTER_W") != -1)
			{
				str.TrimLeft("CONFIRM_AFTER_W");
				str.Trim();str.Trim("=");
				CONFIRM_AFTER_W = atoi(str);
			}
			if(str.Find("SIZE_COFT") != -1)
			{
				str.TrimLeft("SIZE_COFT");
				str.Trim();str.Trim("=");
				SIZE_COFT = atoi(str);
			}
			if(str.Find("SIZE_ASDU") != -1)
			{
				str.TrimLeft("SIZE_ASDU");
				str.Trim();str.Trim("=");
				SIZE_ASDU = atoi(str);
			}
			if(str.Find("SIZE_IOA") != -1)
			{
				str.TrimLeft("SIZE_IOA");
				str.Trim();str.Trim("=");
				SIZE_IOA = atoi(str);
			}
			if((str.Find("ADRESS_IP") != -1)&&(str.Find("RES_ADRESS_IP") == -1))
			{
				str.TrimLeft("ADRESS_IP");
				str.Trim();str.Trim("=");

				union 
				{
					__int64 uIP;
					BYTE byIP[8];
				}IP;
				IP.uIP = _atoi64(str);
				
				str.Format("%d.%d.%d.%d",IP.byIP[3],IP.byIP[2],IP.byIP[1],IP.byIP[0]);

				ADRESS_IP = str;
			}
			if(str.Find("SMOLLTIME") != -1)
			{
				str.TrimLeft("SMOLLTIME");
				str.Trim();str.Trim("=");
				SMOLLTIME = atoi(str);
			}
			if(str.Find("GLOBAL_ASDU") != -1)
			{
				str.TrimLeft("GLOBAL_ASDU");
				str.Trim();str.Trim("=");
				GLOBAL_ASDU = atoi(str);
			}
			if((str.Find("PORT") != -1)&&(str.Find("RES_PORT") == -1))
			{
				str.TrimLeft("PORT");
				str.Trim();str.Trim("=");
				PORT = atoi(str);
			}	
			if(str.Find("C_IС_NA_1_ENABLE") != -1)
			{
				str.TrimLeft("C_IС_NA_1_ENABLE");
				str.Trim();str.Trim("=");
				C_IС_NA_1_ENABLE = atoi(str);
			}		
			if(str.Find("C_IС_NA_1_WAIT_END_ACT") != -1)
			{
				str.TrimLeft("C_IС_NA_1_WAIT_END_ACT");
				str.Trim();str.Trim("=");
				C_IС_NA_1_WAIT_END_ACT = atoi(str);
			}		
			if(str.Find("C_CS_NA_1_ENABLE") != -1)
			{
				str.TrimLeft("C_CS_NA_1_ENABLE");
				str.Trim();str.Trim("=");
				C_CS_NA_1_ENABLE = atoi(str);
			}		
			if(str.Find("C_CS_NA_1_WAIT_END_ACT") != -1)
			{
				str.TrimLeft("C_CS_NA_1_WAIT_END_ACT");
				str.Trim();str.Trim("=");
				C_CS_NA_1_WAIT_END_ACT = atoi(str);
			}					
			if(str.Find("PERIOD_C_IC_NA_1") != -1)
			{
				str.TrimLeft("PERIOD_C_IC_NA_1");
				str.Trim();str.Trim("=");
				PERIOD_C_IC_NA_1 = atoi(str);
			}	
			if(str.Find("TIME_WAIT_C_IC_NA_1") != -1)
			{
				str.TrimLeft("TIME_WAIT_C_IC_NA_1");
				str.Trim();str.Trim("=");
				TIME_WAIT_C_IC_NA_1 = atoi(str);
			}	
			if(str.Find("PERIOD_C_CS_NA_1") != -1)
			{
				str.TrimLeft("PERIOD_C_CS_NA_1");
				str.Trim();str.Trim("=");
				PERIOD_C_CS_NA_1 = atoi(str);
			}	
			if(str.Find("TIME_WAIT_C_CS_NA_1") != -1)
			{
				str.TrimLeft("TIME_WAIT_C_CS_NA_1");
				str.Trim();str.Trim("=");
				TIME_WAIT_C_CS_NA_1 = atoi(str);
			}	
			if(str.Find("TIME_WAIT_RESP_TEST") != -1)
			{
				str.TrimLeft("TIME_WAIT_RESP_TEST");
				str.Trim();str.Trim("=");
				TIME_WAIT_RESP_TEST = atoi(str);
			}	
			if(str.Find("TIME_WAIT_RESP_STOP") != -1)
			{
				str.TrimLeft("TIME_WAIT_RESP_STOP");
				str.Trim();str.Trim("=");
				TIME_WAIT_RESP_STOP = atoi(str);
			}
			if(str.Find("TIME_WAIT_FLAG_BAD") != -1)
			{
				str.TrimLeft("TIME_WAIT_FLAG_BAD");
				str.Trim();str.Trim("=");
				TIME_WAIT_FLAG_BAD = atoi(str);
			}	
			if(m_nVersion > 11)
			{
				if(str.Find("RES_ADRESS_IP") != -1)
				{
					str.TrimLeft("RES_ADRESS_IP");
					str.Trim();str.Trim("=");

					union 
					{
						__int64 uIP;
						BYTE byIP[8];
					}IP;
					IP.uIP = _atoi64(str);
					
					str.Format("%d.%d.%d.%d",IP.byIP[3],IP.byIP[2],IP.byIP[1],IP.byIP[0]);

					RES_ADRESS_IP = str;
				}
				if(str.Find("RES_PORT") != -1)
				{
					str.TrimLeft("RES_PORT");
					str.Trim();str.Trim("=");
					RES_PORT = atoi(str);
				}
			}
/////////////////////////////////////			
			if(str.Find("NUMBER_CONFIG_STRUCTURES") != -1)
			{
				str.TrimLeft("NUMBER_CONFIG_STRUCTURES");
				str.Trim();str.Trim("=");
				m_IndividualStructure104Array.SetSize(atoi(str));
			}						
			if(str.Find("MAKE_STRUCTURE") != -1)
			{
				str.TrimLeft("MAKE_STRUCTURE");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IndividualStructure104Array.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}			
			if((str.Find("TYPE_ID") != -1)&&(str.Find("TYPE_ID_C_IC_NA_1") == -1))
			{
				str.TrimLeft("TYPE_ID");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].TYPE_ID = atoi(str);										
			}
			if((str.Find("NUM_BYTE") != -1)&&(str.Find("NUM_BYTE_C_IC_NA_1") == -1))
			{
				str.TrimLeft("NUM_BYTE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].NUM_BYTE = atoi(str);										
			}
			if(str.Find("TYPE_ID_C_IC_NA_1") != -1)
			{
				str.TrimLeft("TYPE_ID_C_IC_NA_1");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].TYPE_ID_C_IC_NA_1 = atoi(str);										
			}
			if(str.Find("NUM_BYTE_C_IC_NA_1") != -1)
			{
				str.TrimLeft("NUM_BYTE_C_IC_NA_1");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].NUM_BYTE_C_IC_NA_1 = atoi(str);										
			}
			if(str.Find("ORIGINATOR_ADDRESS") != -1)
			{
				str.TrimLeft("ORIGINATOR_ADDRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].ORIGINATOR_ADDRESS = atoi(str);										
			}
			if(str.Find("COMMON_ADDRESS_ASDU") != -1)
			{
				str.TrimLeft("COMMON_ADDRESS_ASDU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].COMMON_ADDRESS_ASDU = atoi(str);										
			}
			if(str.Find("START_IOA") != -1)
			{
				str.TrimLeft("START_IOA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].START_IOA = atoi(str);										
			}
			if(str.Find("AM_IOA") != -1)
			{
				str.TrimLeft("AM_IOA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].AM_IOA = atoi(str);										
			}
			if(str.Find("ADDRESS_PMZ") != -1)
			{
				str.TrimLeft("ADDRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].ADDRESS_PMZ = atoi(str);										
			}
			if(str.Find("POZITION_OF_QUALITY_FLAG") != -1)
			{
				str.TrimLeft("POZITION_OF_QUALITY_FLAG");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].POZITION_OF_QUALITY_FLAG = atoi(str);										
			}
			
			if(str.Find("STATUS_ADDRESS") != -1)
			{
				str.TrimLeft("STATUS_ADDRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].STATUS_ADDRESS = atoi(str);
			}
			if(str.Find("STATUS_MASKA") != -1)
			{
				str.TrimLeft("STATUS_MASKA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].STATUS_MASKA = atoi(str);
			}
			if(str.Find("STATUS_TYPE") != -1)
			{
				str.TrimLeft("STATUS_TYPE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].STATUS_TYPE = atoi(str);
			}			
			if(str.Find("DOP_FLAG") != -1)
			{
				str.TrimLeft("DOP_FLAG");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].DOP_FLAG = atoi(str);
			}			
			if(str.Find("//") != -1)
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure104Array.GetSize()))
					m_IndividualStructure104Array[nProcIndex].strCOMMENT = str;														
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
BOOL CIec104m::SaveToTuFile(CString strFile)
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
BOOL CIec104m::LoadFromTuFile(CString strFile)
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