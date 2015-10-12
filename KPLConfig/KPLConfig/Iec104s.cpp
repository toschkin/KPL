#include "StdAfx.h"
#include "Iec104s.h"


CIec104s::CIec104s(void)
{
	m_nProcNum=0;
	UST_CONNECT_t0=30;
	TEST_APDU_t1=15;
	CONFIRM_t2=10;
	SEND_TEST_t3=20;
	MAX_DELTA_K=12;
	CONFIRM_AFTER_W=8;
	BIGTIME=700;
	SMOLLTIME=10;
	GLOBAL_ASDU=1;
	ADRESS_IP="127.0.0.1";
	//not changed
	SIZE_LINK=0;
	ADRESS_LINK=0;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=3;		
	PORT=2404;
	SIZE_OBJECT_ARH=1000;
	RES_ADRESS_IP="127.0.0.1";
}

CIec104s::~CIec104s(void)
{
	m_nProcNum=0;
	UST_CONNECT_t0=30;
	TEST_APDU_t1=15;
	CONFIRM_t2=10;
	SEND_TEST_t3=20;
	MAX_DELTA_K=12;
	CONFIRM_AFTER_W=8;
	BIGTIME=700;
	SMOLLTIME=10;
	GLOBAL_ASDU=1;
	ADRESS_IP="127.0.0.1";
	//not changed
	SIZE_LINK=0;
	ADRESS_LINK=0;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=3;		
	PORT=2404;
	SIZE_OBJECT_ARH=1000;
	RES_ADRESS_IP="127.0.0.1";
}
BOOL CIec104s::SaveToFile(CString strFile)
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
	str.Format("SIZE_LINK=%d\r\n",SIZE_LINK);
	strBuf+=str;
	str.Format("SIZE_COFT=%d\r\n",SIZE_COFT);
	strBuf+=str;
	str.Format("SIZE_ASDU=%d\r\n",SIZE_ASDU);
	strBuf+=str;
	str.Format("SIZE_IOA=%d\r\n",SIZE_IOA);
	strBuf+=str;
	str.Format("ADRESS_LINK=%d\r\n",ADRESS_LINK);
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

	CString strMainIP = str;
	strBuf+=str;
	
	str.Format("BIGTIME=%d\r\n",BIGTIME);
	strBuf+=str;
	str.Format("SMOLLTIME=%d\r\n",SMOLLTIME);
	strBuf+=str;
	str.Format("GLOBAL_ASDU=%d\r\n",GLOBAL_ASDU);
	strBuf+=str;
	str.Format("PORT=%d\r\n",PORT);
	strBuf+=str;
	str.Format("SIZE_OBJECT_ARH=%d\r\n",SIZE_OBJECT_ARH);
	strBuf+=str;
	if(m_nVersion > 12)
	{
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
			str = strMainIP;
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
BOOL CIec104s::LoadFromFile(CString strFile)
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
			if(str.Find("BIGTIME") != -1)
			{
				str.TrimLeft("BIGTIME");
				str.Trim();str.Trim("=");
				BIGTIME = atoi(str);
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
			if(str.Find("PORT") != -1)
			{
				str.TrimLeft("PORT");
				str.Trim();str.Trim("=");
				PORT = atoi(str);
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
			if(str.Find("SIZE_OBJECT_ARH") != -1)
			{
				str.TrimLeft("SIZE_OBJECT_ARH");
				str.Trim();str.Trim("=");
				SIZE_OBJECT_ARH = atoi(str);
			}			
			if(m_nVersion > 12)
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