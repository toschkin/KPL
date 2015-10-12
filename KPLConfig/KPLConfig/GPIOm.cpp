#include "StdAfx.h"
#include "GPIOm.h"

CGPIOm::CGPIOm(void)
{
	m_nProcNum=0;
	SERVICE=0;		
	BUTTONS_ENABLE=0;// включение -1  /отключение -0 кнопок на GP17-GP14
	BUTTONS_DELAY=1000;//=1000 задержка чтения на дребезг контактов кнопок
	TS_DELAY=1000;
}

CGPIOm::~CGPIOm(void)
{
	m_nProcNum=0;
	SERVICE=0;
	BUTTONS_ENABLE=0;// включение -1  /отключение -0 кнопок на GP17-GP14
	BUTTONS_DELAY=1000;//=1000 задержка чтения на дребезг контактов кнопок
	TS_DELAY=1000;
	m_IndividualStructureGPIOArray.RemoveAll();
	m_TuArray.RemoveAll();
}
BOOL CGPIOm::SaveToFile(CString strFile)
{ 
	CString strBuf,str;
	
	str.Format("NUMBER_OF_INDIVIDUAL_STRUCTURES=%d\r\n",m_IndividualStructureGPIOArray.GetSize());
	strBuf+=str;
	str.Format("SERVICE=%d\r\n\r\n",SERVICE);
	strBuf+=str;
	if(m_nVersion > 15)
	{
		strBuf.TrimRight("\r\n");
		strBuf+="\r\n";
		str.Format("BUTTONS_ENABLE=%d\r\n",BUTTONS_ENABLE);
		strBuf+=str;
		str.Format("BUTTONS_DELAY=%d\r\n",BUTTONS_DELAY);
		strBuf+=str;
		str.Format("TS_DELAY=%d\r\n\r\n",TS_DELAY);
		strBuf+=str;
	}
	for(int i =0; i < m_IndividualStructureGPIOArray.GetSize(); i++)
	{
		str.Format("MAKE_DEVICE=%d\r\n",i+1);
		strBuf+=str;
		str.Format("CHANNEL_NUM=%d\r\n",m_IndividualStructureGPIOArray[i].CHANNEL_NUM);
		strBuf+=str;
		str.Format("ADDRESS_PMZ=%d\r\n",m_IndividualStructureGPIOArray[i].ADDRESS_PMZ);
		strBuf+=str;		
		str.Format("//%s\r\n\r\n",m_IndividualStructureGPIOArray[i].strCOMMENT);
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
BOOL CGPIOm::LoadFromFile(CString strFile)
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
			if(str.Find("SERVICE") != -1)
			{
				str.TrimLeft("SERVICE");
				str.Trim();str.Trim("=");
				SERVICE = atoi(str);
			}		
			if(m_nVersion > 15)
			{
				if(str.Find("BUTTONS_ENABLE") != -1)
				{
					str.TrimLeft("BUTTONS_ENABLE");
					str.Trim();str.Trim("=");
					BUTTONS_ENABLE = atoi(str);
				}
				if(str.Find("BUTTONS_DELAY") != -1)
				{
					str.TrimLeft("BUTTONS_DELAY");
					str.Trim();str.Trim("=");
					BUTTONS_DELAY = atoi(str);
				}
				if(str.Find("TS_DELAY") != -1)
				{
					str.TrimLeft("TS_DELAY");
					str.Trim();str.Trim("=");
					TS_DELAY = atoi(str);
				}				
			}
			if(str.Find("NUMBER_OF_INDIVIDUAL_STRUCTURES") != -1)
			{
				str.TrimLeft("NUMBER_OF_INDIVIDUAL_STRUCTURES");
				str.Trim();str.Trim("=");
				m_IndividualStructureGPIOArray.SetSize(atoi(str));
			}
						
			if(str.Find("MAKE_DEVICE") != -1)
			{
				str.TrimLeft("MAKE_DEVICE");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IndividualStructureGPIOArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}
			if(str.Find("CHANNEL_NUM") != -1)
			{
				str.TrimLeft("CHANNEL_NUM");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPIOArray.GetSize()))
					m_IndividualStructureGPIOArray[nProcIndex].CHANNEL_NUM = atoi(str);										
			}			
			if(str.Find("ADDRESS_PMZ") != -1)
			{
				str.TrimLeft("ADDRESS_PMZ");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPIOArray.GetSize()))
					m_IndividualStructureGPIOArray[nProcIndex].ADDRESS_PMZ = atoi(str);										
			}						
			if(str.Find("//") != -1)
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureGPIOArray.GetSize()))
					m_IndividualStructureGPIOArray[nProcIndex].strCOMMENT = str;														
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
BOOL CGPIOm::SaveToTuFile(CString strFile)
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
BOOL CGPIOm::LoadFromTuFile(CString strFile)
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