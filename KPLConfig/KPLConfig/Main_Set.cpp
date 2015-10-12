#include "StdAfx.h"
#include "Main_Set.h"

CMain_Set::CMain_Set(void)
{
	REAL_SIZE_DIRECT_BUFER=0;
	REAL_NUM_GENFAST_OBJECT=0;
	AMOUNT_OBJECT=0;
	ProcessInfo pi;
	pi.TYPE_PROTOKOL = 9;
	m_ProcessInfoArray.Add(pi);
	pi.TYPE_PROTOKOL = 12;
	m_ProcessInfoArray.Add(pi);
	pi.TYPE_PROTOKOL = 13;
	m_ProcessInfoArray.Add(pi);
	KPLType = "8_PORT";
	m_Ports.SetSize(8);
	MY_IP = "192.168.0.1";
	MY_IP_MASK = "255.255.255.0";
	MY_IP_GW = "192.168.0.0";

	for(int i =0; i < m_Ports.GetSize(); i++)
	{
		m_Ports[i]=PORT_FREE;
	}
}

CMain_Set::~CMain_Set(void)
{
	REAL_SIZE_DIRECT_BUFER=0;
	REAL_NUM_GENFAST_OBJECT=0;	
	AMOUNT_OBJECT=0;	
	m_strPSNAME="";	
	KPLType = "8_PORT";
	MY_IP = "192.168.0.1";
	MY_IP_MASK = "255.255.255.0";
	MY_IP_GW = "192.168.0.0";
	m_Ports.SetSize(8);
	for(int i =0; i < m_Ports.GetSize(); i++)
	{
		m_Ports[i]=PORT_FREE;
	}
	m_IniObjectArray.RemoveAll();
	m_IniMaskArray.RemoveAll();
}

BOOL CMain_Set::SaveToFile(CString strFile)
{	
	CString strBuf,str;
	str.Format("//VER_%d\r\n",m_nVersion);
	strBuf+=str;		
	str.Format("NUM_DIRECT=%d\r\n",m_ProcessInfoArray.GetSize());
	strBuf+=str;
	str.Format("REAL_SIZE_DIRECT_BUFER=%d\r\n",REAL_SIZE_DIRECT_BUFER);
	strBuf+=str;
	str.Format("REAL_NUM_GENFAST_OBJECT=%d\r\n",REAL_NUM_GENFAST_OBJECT);
	strBuf+=str;
	str.Format("AMOUNT_OBJECT=%d\r\n",AMOUNT_OBJECT);
	strBuf+=str;	
	str.Format("AMOUNT_INIOBJECT=%d\r\n",m_IniObjectArray.GetSize());
	strBuf+=str;
	str.Format("AMOUNT_INI_MASKA=%d\r\n",m_IniMaskArray.GetSize());
	strBuf+=str;

	if(m_nVersion > 19)
	{
		CStringArray dest;
		Str2Array(MY_IP, &dest, '.');
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
			str.Format("MY_IP=%u\r\n",IP.uIP);
		}
		else
			str.Format("MY_IP=%i\r\n",0);
		strBuf+=str;

		Str2Array(MY_IP_MASK, &dest, '.');
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
			str.Format("MY_IP_MASK=%u\r\n",IP.uIP);
		}
		else
			str.Format("MY_IP_MASK=%i\r\n",0);
		strBuf+=str;

		Str2Array(MY_IP_GW, &dest, '.');
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
			str.Format("MY_IP_GW=%u\r\n",IP.uIP);
		}
		else
			str.Format("MY_IP_GW=%i\r\n",0);
		strBuf+=str;
	}

	str.Format("//KPL_%s\r\n",KPLType);
	strBuf+=str;		
	str.Format("//_%s\r\n\r\n",m_strPSNAME);
	strBuf+=str;	
	
	
	for(int i =0; i < m_ProcessInfoArray.GetSize(); i++)
	{
		str.Format("MAKE_DIRECT=%d\r\n",i+1);
		strBuf+=str;
		str.Format("TYPE_PROTOKOL=%d\r\n",m_ProcessInfoArray[i].TYPE_PROTOKOL);
		strBuf+=str;
		str.Format("START_ADDRESS_MAP=%d\r\n",m_ProcessInfoArray[i].START_ADDRESS_MAP);
		strBuf+=str;
		str.Format("AMOUNT_SIGNIFICATE=%d\r\n",m_ProcessInfoArray[i].AMOUNT_SIGNIFICATE);
		strBuf+=str;
		str.Format("YESNOLOGALARM=%d\r\n",m_ProcessInfoArray[i].YESNOLOGALARM);
		strBuf+=str;
		str.Format("YESNOLOGPROTOKOL=%d\r\n",m_ProcessInfoArray[i].YESNOLOGPROTOKOL);
		strBuf+=str;	
		str.Format("//%s\r\n\r\n",m_ProcessInfoArray[i].strCOMMENT);
		strBuf+=str;			
	}
	for(int i =0; i < m_IniObjectArray.GetSize(); i++)
	{
		str.Format("NUMBER_INIOBJECT=%d\r\n",i+1);
		strBuf+=str;
		str.Format("TYPE_OBJECT=%d\r\n",m_IniObjectArray[i].TYPE_OBJECT);
		strBuf+=str;
		str.Format("GENTYPE_OBJECT=%d\r\n",m_IniObjectArray[i].GENTYPE_OBJECT);
		strBuf+=str;
		str.Format("START_ADRES_PMZ=%d\r\n",m_IniObjectArray[i].START_ADRES_PMZ);
		strBuf+=str;
		str.Format("NUMBER_OBJECT=%d\r\n",m_IniObjectArray[i].NUMBER_OBJECT);
		strBuf+=str;
		str.Format("NUM_DATE=%d\r\n",m_IniObjectArray[i].NUM_DATE);
		strBuf+=str;
		str.Format("REAL_ADRES=%d\r\n",m_IniObjectArray[i].REAL_ADRES);
		strBuf+=str;
		str.Format("GEN_NUMBYTE=%d\r\n",m_IniObjectArray[i].GEN_NUMBYTE);
		strBuf+=str;
		str.Format("ADRES_ASDU=%d\r\n",m_IniObjectArray[i].ADRES_ASDU);
		strBuf+=str;
		str.Format("YES_NO_FASTBUF=%d\r\n",m_IniObjectArray[i].YES_NO_FASTBUF);
		strBuf+=str;
		str.Format("SIZE_FAST_BUF=%d\r\n",m_IniObjectArray[i].SIZE_FAST_BUF);
		strBuf+=str;
		str.Format("NUMBER_DIRECT=%d\r\n\r\n",m_IniObjectArray[i].NUMBER_DIRECT);
		strBuf+=str;
		if(m_nVersion > 10)
		{
			strBuf.TrimRight("\r\n");
			strBuf+="\r\n";
			str.Format("//IO_%s\r\n\r\n",m_IniObjectArray[i].strCOMMENT);
			strBuf+=str;		
		}
	}
	for(int i =0; i < m_IniMaskArray.GetSize(); i++)
	{
		str.Format("NUMBER_MASKA=%d\r\n",i+1);
		strBuf+=str;
		str.Format("ADRES_MASKA=%d\r\n",m_IniMaskArray[i].ADR_MASKA);
		strBuf+=str;
		str.Format("MASKAINT=%d\r\n",m_IniMaskArray[i].MASKAINT);
		strBuf+=str;
		str.Format("MASKAFLOAT=%d\r\n",m_IniMaskArray[i].MASKAFLOAT);
		strBuf+=str;
		str.Format("VALUE_0=%d\r\n",m_IniMaskArray[i].VALUE_0);
		strBuf+=str;
		str.Format("TYPE_VALUE=%d\r\n",m_IniMaskArray[i].TYPE_VALUE);
		strBuf+=str;
		str.Format("MASKA_VALUE_0=%d\r\n",m_IniMaskArray[i].MASKA_VALUE_0);
		strBuf+=str;				
		str.Format("//MSK_%s\r\n\r\n",m_IniMaskArray[i].strCOMMENT);
		strBuf+=str;
	}
	CFile f;
	try
	{		
		if(!f.Open(strFile,CFile::modeCreate|CFile::modeWrite))
			return FALSE;

		f.Write((void*)strBuf.GetBuffer(),strBuf.GetLength());
		f.Close();		
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}
int  CMain_Set::GetVersion(CString strContent)
{
	CString strKey;
	for(int i = 0; i < m_arrVersions.GetSize(); i++)
	{
		strKey.Format("//VER_%d",m_arrVersions[i]);
		if(strContent.Find(strKey)!=-1)
		{
			return m_arrVersions[i];
		}
	}
	return m_arrVersions[0];
}
BOOL CMain_Set::LoadFromFile(CString strFile)
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
		int nIniObjIndex = -1;
		int nMaskIndex = -1;
		
		m_nVersion = GetVersion(strBuf);

		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			if(str.Find("REAL_SIZE_DIRECT_BUFER") != -1)
			{
				str.TrimLeft("REAL_SIZE_DIRECT_BUFER");
				str.Trim();str.Trim("=");
				REAL_SIZE_DIRECT_BUFER = atoi(str);
			}
			if(str.Find("REAL_NUM_GENFAST_OBJECT") != -1)
			{
				str.TrimLeft("REAL_NUM_GENFAST_OBJECT");
				str.Trim();str.Trim("=");
				REAL_NUM_GENFAST_OBJECT = atoi(str);
			}		
			if(str.Find("AMOUNT_OBJECT") != -1)
			{
				str.TrimLeft("AMOUNT_OBJECT");
				str.Trim();str.Trim("=");
				AMOUNT_OBJECT = atoi(str);
			}
			if(str.Find("NUM_DIRECT") != -1)
			{
				str.TrimLeft("NUM_DIRECT");
				str.Trim();str.Trim("=");
				m_ProcessInfoArray.SetSize(atoi(str));
			}
			if(str.Find("AMOUNT_INIOBJECT") != -1)
			{
				str.TrimLeft("AMOUNT_INIOBJECT");
				str.Trim();str.Trim("=");
				m_IniObjectArray.SetSize(atoi(str));
			}
			if(str.Find("AMOUNT_INI_MASKA") != -1)
			{
				str.TrimLeft("AMOUNT_INI_MASKA");
				str.Trim();str.Trim("=");
				m_IniMaskArray.SetSize(atoi(str));
			}
			if((str.Find("MY_IP") != -1)&&(str.Find("MY_IP_MASK") == -1)&&(str.Find("MY_IP_GW") == -1))
			{
				str.TrimLeft("MY_IP");
				str.Trim();str.Trim("=");

				union 
				{
					__int64 uIP;
					BYTE byIP[8];
				}IP;
				IP.uIP = _atoi64(str);
				
				str.Format("%d.%d.%d.%d",IP.byIP[3],IP.byIP[2],IP.byIP[1],IP.byIP[0]);

				MY_IP = str;
			}	

			if(str.Find("MY_IP_MASK") != -1)
			{
				str.TrimLeft("MY_IP_MASK");
				str.Trim();str.Trim("=");

				union 
				{
					__int64 uIP;
					BYTE byIP[8];
				}IP;
				IP.uIP = _atoi64(str);
				
				str.Format("%d.%d.%d.%d",IP.byIP[3],IP.byIP[2],IP.byIP[1],IP.byIP[0]);

				MY_IP_MASK = str;
			}	

			if(str.Find("MY_IP_GW") != -1)
			{
				str.TrimLeft("MY_IP_GW");
				str.Trim();str.Trim("=");

				union 
				{
					__int64 uIP;
					BYTE byIP[8];
				}IP;
				IP.uIP = _atoi64(str);
				
				str.Format("%d.%d.%d.%d",IP.byIP[3],IP.byIP[2],IP.byIP[1],IP.byIP[0]);

				MY_IP_GW = str;
			}	

			if(str.Find("//KPL_") != -1)
			{
				str.TrimLeft("//KPL_");				
				str.Remove('\n');
				str.Remove('\r');
				KPLType=str;				
				str.Replace("_PORT","");
				if(atoi(str) > 0)
				{
					m_Ports.SetSize(atoi(str));
					for(int i =0; i < m_Ports.GetSize(); i++)
					{
						m_Ports[i]=PORT_FREE;
					}
				}
				else
				{
					m_Ports.SetSize(8);
					for(int i =0; i < m_Ports.GetSize(); i++)
					{
						m_Ports[i]=PORT_FREE;
					}
				}
			}				
			if(str.Find("//_") != -1)
			{
				str.TrimLeft("//_");				
				str.Remove('\n');
				str.Remove('\r');
				m_strPSNAME=str;				
			}				
			
			if(str.Find("MAKE_DIRECT") != -1)
			{
				str.TrimLeft("MAKE_DIRECT");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_ProcessInfoArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}
			if(str.Find("TYPE_PROTOKOL") != -1)
			{
				str.TrimLeft("TYPE_PROTOKOL");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ProcessInfoArray.GetSize()))
					m_ProcessInfoArray[nProcIndex].TYPE_PROTOKOL = atoi(str);										
			}
			if(str.Find("START_ADDRESS_MAP") != -1)
			{
				str.TrimLeft("START_ADDRESS_MAP");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ProcessInfoArray.GetSize()))
					m_ProcessInfoArray[nProcIndex].START_ADDRESS_MAP = atoi(str);										
			}
			if(str.Find("AMOUNT_SIGNIFICATE") != -1)
			{
				str.TrimLeft("AMOUNT_SIGNIFICATE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ProcessInfoArray.GetSize()))
					m_ProcessInfoArray[nProcIndex].AMOUNT_SIGNIFICATE = atoi(str);										
			}

			if(str.Find("YESNOLOGALARM") != -1)
			{
				str.TrimLeft("YESNOLOGALARM");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ProcessInfoArray.GetSize()))
					m_ProcessInfoArray[nProcIndex].YESNOLOGALARM = atoi(str);														
			}
			if(str.Find("YESNOLOGPROTOKOL") != -1)
			{
				str.TrimLeft("YESNOLOGPROTOKOL");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_ProcessInfoArray.GetSize()))
					m_ProcessInfoArray[nProcIndex].YESNOLOGPROTOKOL = atoi(str);														
			}									
			if((str.Find("//") != -1)&&(str.Find("//_") == -1)&&(str.Find("//MSK_") == -1)&&(str.Find("//KPL_") == -1)
				&&(str.Find("//VER_") == -1)&&(str.Find("//IO_") == -1))
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_ProcessInfoArray.GetSize()))
					m_ProcessInfoArray[nProcIndex].strCOMMENT = str;														
			}					
			if(str.Find("NUMBER_INIOBJECT") != -1)
			{
				str.TrimLeft("NUMBER_INIOBJECT");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IniObjectArray.GetSize()))				
					nIniObjIndex = atoi(str)-1;								
			}
			if((str.Find("GENTYPE_OBJECT") == -1)&&(str.Find("TYPE_OBJECT") != -1))
			{
				str.TrimLeft("TYPE_OBJECT");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].TYPE_OBJECT = atoi(str);										
			}
			if(str.Find("GENTYPE_OBJECT") != -1)
			{
				str.TrimLeft("GENTYPE_OBJECT");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].GENTYPE_OBJECT = atoi(str);										
			}
			if(str.Find("START_ADRES_PMZ") != -1)
			{
				str.TrimLeft("START_ADRES_PMZ");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].START_ADRES_PMZ = atoi(str);										
			}
			if(str.Find("NUMBER_OBJECT") != -1)
			{
				str.TrimLeft("NUMBER_OBJECT");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].NUMBER_OBJECT = atoi(str);										
			}
			if(str.Find("NUM_DATE") != -1)
			{
				str.TrimLeft("NUM_DATE");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].NUM_DATE = atoi(str);										
			}
			if(str.Find("REAL_ADRES") != -1)
			{
				str.TrimLeft("REAL_ADRES");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].REAL_ADRES = atoi(str);										
			}
			if(str.Find("GEN_NUMBYTE") != -1)
			{
				str.TrimLeft("GEN_NUMBYTE");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].GEN_NUMBYTE = atoi(str);										
			}
			if(str.Find("ADRES_ASDU") != -1)
			{
				str.TrimLeft("ADRES_ASDU");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].ADRES_ASDU = atoi(str);										
			}
			if(str.Find("YES_NO_FASTBUF") != -1)
			{
				str.TrimLeft("YES_NO_FASTBUF");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].YES_NO_FASTBUF = atoi(str);										
			}
			if(str.Find("SIZE_FAST_BUF") != -1)
			{
				str.TrimLeft("SIZE_FAST_BUF");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].SIZE_FAST_BUF = atoi(str);										
			}
			if(str.Find("NUMBER_DIRECT") != -1)
			{
				str.TrimLeft("NUMBER_DIRECT");
				str.Trim();str.Trim("=");
				if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
					m_IniObjectArray[nIniObjIndex].NUMBER_DIRECT = atoi(str);										
			}	
			if(m_nVersion > 10)
			{
				if(str.Find("//IO_") != -1)
				{
					str.TrimLeft("//IO_");				
					str.Remove('\n');
					str.Remove('\r');
					if((nIniObjIndex >= 0)&&(nIniObjIndex < m_IniObjectArray.GetSize()))
						m_IniObjectArray[nIniObjIndex].strCOMMENT = str;														
				}
			}			
			if(str.Find("NUMBER_MASKA") != -1)
			{
				str.TrimLeft("NUMBER_MASKA");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IniMaskArray.GetSize()))				
					nMaskIndex = atoi(str)-1;								
			}
			if(str.Find("ADRES_MASKA") != -1)
			{
				str.TrimLeft("ADRES_MASKA");
				str.Trim();str.Trim("=");
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].ADR_MASKA = atoi(str);										
			}
			if(str.Find("MASKAINT") != -1)
			{
				str.TrimLeft("MASKAINT");
				str.Trim();str.Trim("=");
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].MASKAINT = atoi(str);										
			}
			if(str.Find("MASKAFLOAT") != -1)
			{
				str.TrimLeft("MASKAFLOAT");
				str.Trim();str.Trim("=");
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].MASKAFLOAT = atoi(str);										
			}

			if(str.Find("VALUE_0") != -1)
			{
				str.TrimLeft("VALUE_0");
				str.Trim();str.Trim("=");
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].VALUE_0 = atoi(str);										
			}
			if(str.Find("TYPE_VALUE") != -1)
			{
				str.TrimLeft("TYPE_VALUE");
				str.Trim();str.Trim("=");
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].TYPE_VALUE = atoi(str);										
			}
			if(str.Find("MASKA_VALUE_0") != -1)
			{
				str.TrimLeft("MASKA_VALUE_0");
				str.Trim();str.Trim("=");
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].MASKA_VALUE_0 = atoi(str);										
			}
			if(str.Find("//MSK_") != -1)
			{
				str.TrimLeft("//MSK_");				
				str.Remove('\n');
				str.Remove('\r');
				if((nMaskIndex >= 0)&&(nMaskIndex < m_IniMaskArray.GetSize()))
					m_IniMaskArray[nMaskIndex].strCOMMENT = str;														
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
