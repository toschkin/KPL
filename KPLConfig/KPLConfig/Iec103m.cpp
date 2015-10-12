#include "StdAfx.h"
#include "Iec103m.h"

CIec103m::CIec103m(void)
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
	ADRES_BADCHANEL=0;
	NUMBER_OF_DEVICES=1;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES=0;
	SIZE_LINK=1;
	SIZE_COFT=1;
	SIZE_ASDU=1;
	SIZE_IOA=2;
	PERIOD_C_IC_NA_1=60;
	PERIOD_C_CS_NA_1=60;
	TIME_TU_EXPIRE=0;	
}

CIec103m::~CIec103m(void)
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
	ADRES_BADCHANEL=0;
	NUMBER_OF_DEVICES=0;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES=0;
	SIZE_LINK=1;
	SIZE_COFT=2;
	SIZE_ASDU=2;
	SIZE_IOA=2;
	PERIOD_C_IC_NA_1=60;
	PERIOD_C_CS_NA_1=60;
	TIME_TU_EXPIRE=10;
	m_IndividualStructure103Array.RemoveAll();
	m_TuArray.RemoveAll();
}
BOOL CIec103m::SaveToFile(CString strFile)
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
	str.Format("ADRES_BADCHANEL=%d\r\n",ADRES_BADCHANEL);
	strBuf+=str;
	str.Format("NUMBER_OF_DEVICES=%d\r\n",NUMBER_OF_DEVICES);
	strBuf+=str;
	str.Format("NUMBER_OF_INDIVIDUAL_STRUCTURES=%d\r\n",m_IndividualStructure103Array.GetSize());
	strBuf+=str;
	str.Format("SIZE_LINK=%d\r\n",1/*SIZE_LINK*/);
	strBuf+=str;
	str.Format("SIZE_COFT=%d\r\n",1/*SIZE_COFT*/);
	strBuf+=str;
	str.Format("SIZE_ASDU=%d\r\n",1/*SIZE_ASDU*/);
	strBuf+=str;
	str.Format("SIZE_IOA=%d\r\n",2/*SIZE_IOA*/);
	strBuf+=str;
	str.Format("PERIOD_C_IC_NA_1=%d\r\n",PERIOD_C_IC_NA_1);
	strBuf+=str;
	str.Format("PERIOD_C_CS_NA_1=%d\r\n",PERIOD_C_CS_NA_1);
	strBuf+=str;
	str.Format("TIME_TU_EXPIRE=%d\r\n\r\n",TIME_TU_EXPIRE);
	strBuf+=str;		
	
	for(int i =0; i < m_IndividualStructure103Array.GetSize(); i++)
	{
		str.Format("MAKE_DEVICE=%d\r\n",i+1);
		strBuf+=str;
		str.Format("LINK_ADDRESS=%d\r\n",m_IndividualStructure103Array[i].LINK_ADDRESS);
		strBuf+=str;
		str.Format("TYPE_ID=%d\r\n",m_IndividualStructure103Array[i].TYPE_ID);
		strBuf+=str;
		str.Format("NUM_BYTE=%d\r\n",m_IndividualStructure103Array[i].NUM_BYTE);
		strBuf+=str;
		str.Format("TYPE_ID_C_IC_NA_1=%d\r\n",m_IndividualStructure103Array[i].TYPE_ID_C_IC_NA_1);
		strBuf+=str;
		str.Format("NUM_BYTE_C_IC_NA_1=%d\r\n",m_IndividualStructure103Array[i].NUM_BYTE_C_IC_NA_1);
		strBuf+=str;
		str.Format("ORIGINATOR_ADDRESS=%d\r\n",m_IndividualStructure103Array[i].ORIGINATOR_ADDRESS);
		strBuf+=str;
		str.Format("COMMON_ADDRESS_ASDU=%d\r\n",m_IndividualStructure103Array[i].COMMON_ADDRESS_ASDU);
		strBuf+=str;
		str.Format("START_IOA=%d\r\n",m_IndividualStructure103Array[i].START_IOA);
		strBuf+=str;
		str.Format("AM_IOA=%d\r\n",m_IndividualStructure103Array[i].AM_IOA);
		strBuf+=str;
		str.Format("ADDRESS_PMZ=%d\r\n",m_IndividualStructure103Array[i].ADDRESS_PMZ);
		strBuf+=str;
		str.Format("POZITION_OF_QUALITY_FLAG=%d\r\n",m_IndividualStructure103Array[i].POZITION_OF_QUALITY_FLAG);
		strBuf+=str;
		str.Format("C_CS_ENABLE=%d\r\n",m_IndividualStructure103Array[i].C_CS_ENABLE);
		strBuf+=str;
		str.Format("GLOBAL_ASDU=%d\r\n",m_IndividualStructure103Array[i].GLOBAL_ASDU);
		strBuf+=str;
		str.Format("STATUS_ADDRESS_PMZ=%d\r\n",m_IndividualStructure103Array[i].STATUS_ADDRESS_PMZ);
		strBuf+=str;
		str.Format("STATUS_MASKA=%d\r\n",m_IndividualStructure103Array[i].STATUS_MASKA);
		strBuf+=str;
		str.Format("STATUS_TYPE=%d\r\n",m_IndividualStructure103Array[i].STATUS_TYPE);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_IndividualStructure103Array[i].strCOMMENT);
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
BOOL CIec103m::LoadFromFile(CString strFile)
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
			if(str.Find("ADRES_BADCHANEL") != -1)
			{
				str.TrimLeft("ADRES_BADCHANEL");
				str.Trim();str.Trim("=");
				ADRES_BADCHANEL = atoi(str);
			}
			if(str.Find("NUMBER_OF_DEVICES") != -1)
			{
				str.TrimLeft("NUMBER_OF_DEVICES");
				str.Trim();str.Trim("=");
				NUMBER_OF_DEVICES = atoi(str);
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
			if(str.Find("PERIOD_C_IC_NA_1") != -1)
			{
				str.TrimLeft("PERIOD_C_IC_NA_1");
				str.Trim();str.Trim("=");
				PERIOD_C_IC_NA_1 = atoi(str);
			}
			if(str.Find("PERIOD_C_CS_NA_1") != -1)
			{
				str.TrimLeft("PERIOD_C_CS_NA_1");
				str.Trim();str.Trim("=");
				PERIOD_C_CS_NA_1 = atoi(str);
			}
			if(str.Find("TIME_TU_EXPIRE") != -1)
			{
				str.TrimLeft("TIME_TU_EXPIRE");
				str.Trim();str.Trim("=");
				TIME_TU_EXPIRE = atoi(str);
			}
			if(str.Find("NUMBER_OF_INDIVIDUAL_STRUCTURES") != -1)
			{
				str.TrimLeft("NUMBER_OF_INDIVIDUAL_STRUCTURES");
				str.Trim();str.Trim("=");
				m_IndividualStructure103Array.SetSize(atoi(str));
			}
			
			
			if(str.Find("MAKE_DEVICE") != -1)
			{
				str.TrimLeft("MAKE_DEVICE");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IndividualStructure103Array.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}
			if(str.Find("LINK_ADDRESS") != -1)
			{
				str.TrimLeft("LINK_ADDRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].LINK_ADDRESS = atoi(str);										
			}
			if((str.Find("TYPE_ID") != -1)&&(str.Find("TYPE_ID_C_IC_NA_1") == -1))
			{
				str.TrimLeft("TYPE_ID");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].TYPE_ID = atoi(str);										
			}
			if((str.Find("NUM_BYTE") != -1)&&(str.Find("NUM_BYTE_C_IC_NA_1") == -1))
			{
				str.TrimLeft("NUM_BYTE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].NUM_BYTE = atoi(str);										
			}
			if(str.Find("TYPE_ID_C_IC_NA_1") != -1)
			{
				str.TrimLeft("TYPE_ID_C_IC_NA_1");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].TYPE_ID_C_IC_NA_1 = atoi(str);										
			}
			if(str.Find("NUM_BYTE_C_IC_NA_1") != -1)
			{
				str.TrimLeft("NUM_BYTE_C_IC_NA_1");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].NUM_BYTE_C_IC_NA_1 = atoi(str);										
			}
			if(str.Find("ORIGINATOR_ADDRESS") != -1)
			{
				str.TrimLeft("ORIGINATOR_ADDRESS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].ORIGINATOR_ADDRESS = atoi(str);										
			}
			if(str.Find("COMMON_ADDRESS_ASDU") != -1)
			{
				str.TrimLeft("COMMON_ADDRESS_ASDU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].COMMON_ADDRESS_ASDU = atoi(str);										
			}
			if(str.Find("START_IOA") != -1)
			{
				str.TrimLeft("START_IOA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].START_IOA = atoi(str);										
			}
			if(str.Find("AM_IOA") != -1)
			{
				str.TrimLeft("AM_IOA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].AM_IOA = atoi(str);										
			}
			if((str.Find("ADDRESS_PMZ") != -1)&&(str.Find("STATUS_ADDRESS_PMZ") == -1))
			{
				str.TrimLeft("ADDRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].ADDRESS_PMZ = atoi(str);										
			}
			if(str.Find("POZITION_OF_QUALITY_FLAG") != -1)
			{
				str.TrimLeft("POZITION_OF_QUALITY_FLAG");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].POZITION_OF_QUALITY_FLAG = atoi(str);										
			}
			if(str.Find("C_CS_ENABLE") != -1)
			{
				str.TrimLeft("C_CS_ENABLE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].C_CS_ENABLE = atoi(str);										
			}
			if(str.Find("GLOBAL_ASDU") != -1)
			{
				str.TrimLeft("GLOBAL_ASDU");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].GLOBAL_ASDU = atoi(str);										
			}
			if(str.Find("STATUS_ADDRESS_PMZ") != -1)
			{
				str.TrimLeft("STATUS_ADDRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].STATUS_ADDRESS_PMZ = atoi(str);
			}
			if(str.Find("STATUS_MASKA") != -1)
			{
				str.TrimLeft("STATUS_MASKA");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].STATUS_MASKA = atoi(str);
			}
			if(str.Find("STATUS_TYPE") != -1)
			{
				str.TrimLeft("STATUS_TYPE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].STATUS_TYPE = atoi(str);
			}	
			if(str.Find("//") != -1)
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructure103Array.GetSize()))
					m_IndividualStructure103Array[nProcIndex].strCOMMENT = str;														
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
BOOL CIec103m::SaveToTuFile(CString strFile)
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
BOOL CIec103m::LoadFromTuFile(CString strFile)
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