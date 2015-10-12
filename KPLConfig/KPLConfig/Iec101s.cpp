#include "StdAfx.h"
#include "Iec101s.h"

CIec101s::CIec101s(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=1;
	PARITY=1;
	BYTETIME=10;
	WAITRESP=100;	
	AMOUNTBYTE=8;
	FLOWCONTROLL=0;
	GLOBAL_ASDU=1;
	ADRESS_LINK=1;
	SIZE_LINK=1;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=2;	
	NEXTMESSAGE = 100;
	CHECK_BAD_CHANEL=10;
	RES_PORT=0;
	SIZE_OBJECT_ARH=1000;
}

CIec101s::~CIec101s(void)
{
	m_nProcNum=0;
	PORT=0;
	BAUDRATE=9600;
	STOPBITS=1;
	PARITY=1;
	BYTETIME=10;
	WAITRESP=100;	
	AMOUNTBYTE=8;
	FLOWCONTROLL=0;
	GLOBAL_ASDU=1;
	ADRESS_LINK=1;
	SIZE_LINK=1;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=2;	
	NEXTMESSAGE = 100;
	CHECK_BAD_CHANEL=10;
	RES_PORT=0;
	SIZE_OBJECT_ARH=1000;
}
BOOL CIec101s::SaveToFile(CString strFile)
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
	str.Format("AMOUNTBYTE=%d\r\n",AMOUNTBYTE);
	strBuf+=str;
	str.Format("CONTROLPOTOK=%d\r\n",FLOWCONTROLL);
	strBuf+=str;
	str.Format("BYTETIME=%d\r\n",BYTETIME);
	strBuf+=str;	
	str.Format("WAITRESP=%d\r\n",WAITRESP);
	strBuf+=str;
	str.Format("NEXTMESSAGE=%d\r\n",NEXTMESSAGE);
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
	str.Format("GLOBAL_ASDU=%d\r\n",GLOBAL_ASDU);
	strBuf+=str;
	str.Format("CHECK_BAD_CHANEL=%d\r\n",CHECK_BAD_CHANEL);
	strBuf+=str;
	str.Format("RES_PORT=%d\r\n",RES_PORT);
	strBuf+=str;
	str.Format("SIZE_OBJECT_ARH=%d\r\n",SIZE_OBJECT_ARH);
	strBuf+=str;
	
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
BOOL CIec101s::LoadFromFile(CString strFile)
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
				FLOWCONTROLL = atoi(str);
			}			
			if(str.Find("GLOBAL_ASDU") != -1)
			{
				str.TrimLeft("GLOBAL_ASDU");
				str.Trim();str.Trim("=");
				GLOBAL_ASDU = atoi(str);
			}
			if(str.Find("ADRESS_LINK") != -1)
			{
				str.TrimLeft("ADRESS_LINK");
				str.Trim();str.Trim("=");
				ADRESS_LINK = atoi(str);
			}
			if(str.Find("SIZE_LINK") != -1)
			{
				str.TrimLeft("SIZE_LINK");
				str.Trim();str.Trim("=");
				SIZE_LINK = atoi(str);
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
			if(str.Find("NEXTMESSAGE") != -1)
			{
				str.TrimLeft("NEXTMESSAGE");
				str.Trim();str.Trim("=");
				NEXTMESSAGE = atoi(str);
			}			
			if(str.Find("CHECK_BAD_CHANEL") != -1)
			{
				str.TrimLeft("CHECK_BAD_CHANEL");
				str.Trim();str.Trim("=");
				CHECK_BAD_CHANEL = atoi(str);
			}			
			if(str.Find("RES_PORT") != -1)
			{
				str.TrimLeft("RES_PORT");
				str.Trim();str.Trim("=");
				RES_PORT = atoi(str);
			}			
			if(str.Find("SIZE_OBJECT_ARH") != -1)
			{
				str.TrimLeft("SIZE_OBJECT_ARH");
				str.Trim();str.Trim("=");
				SIZE_OBJECT_ARH = atoi(str);
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