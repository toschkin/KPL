#include "stdafx.h"
#include "STM.h"


CSTM::CSTM(void)
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
	CONTROLPOTOK=0;
	NUMBER_NO_ANSWER=1;	
	TYPE=0;	
	SERVICE=0;	
}

CSTM::~CSTM(void)
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
	CONTROLPOTOK=0;
	NUMBER_NO_ANSWER=1;	
	TYPE=0;	
	SERVICE=0;	
	m_IndividualStructureSTMArray.RemoveAll();	
}
BOOL CSTM::SaveToFile(CString strFile)
{ 
	//процесс stm_mN.ini
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
	str.Format("NUMBER_STRUCT=%d\r\n",m_IndividualStructureSTMArray.GetSize());
	strBuf+=str;
	str.Format("AMOUNTBYTE=%d\r\n",AMOUNTBYTE);
	strBuf+=str;
	str.Format("CONTROLPOTOK=%d\r\n",CONTROLPOTOK);
	strBuf+=str;
	str.Format("NUMBER_NO_ANSWER=%d\r\n",NUMBER_NO_ANSWER);
	strBuf+=str;
	str.Format("TYPE=%d\r\n",TYPE);
	strBuf+=str;
	str.Format("SERVICE=%d\r\n\r\n",SERVICE);
	strBuf+=str;
					
	for(int i =0; i < m_IndividualStructureSTMArray.GetSize(); i++)
	{
		str.Format("MAKE_STRUCT=%d\r\n",i+1);
		strBuf+=str;		
		str.Format("PROTOCOL_TYPE=%d\r\n",m_IndividualStructureSTMArray[i].PROTOCOL_TYPE);
		strBuf+=str;
		str.Format("CHANNEL=%d\r\n",m_IndividualStructureSTMArray[i].CHANNEL);
		strBuf+=str;		
		str.Format("SPEED=%d\r\n",m_IndividualStructureSTMArray[i].SPEED);
		strBuf+=str;
		str.Format("CHANNEL2=%d\r\n", m_IndividualStructureSTMArray[i].CHANNEL2);
		strBuf += str;		
		str.Format("//%s\r\n\r\n",m_IndividualStructureSTMArray[i].strCOMMENT);
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
	
	CString strDirectory;
	strDirectory = strFile;
	int idx = strDirectory.ReverseFind('\\');
	strDirectory.Truncate(idx);	

	for(int i =0; i < m_IndividualStructureSTMArray.GetSize(); i++)
	{	
		if (m_IndividualStructureSTMArray[i].PROTOCOL_TYPE == PROTOCOL_TYPE_GRANIT)
		{
			//каналы гранита granit_mN_cX.ini 
			strBuf = "";
			str.Format("NUMBER_STRUCT=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray.GetSize());
			strBuf += str;
			str.Format("NUMBER_NO_ANSWER=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.NUMBER_NO_ANSWER);
			strBuf += str;
			str.Format("TYPE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.TYPE);
			strBuf += str;
			str.Format("LOG_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.LOG_ENABLE);
			strBuf += str;
			str.Format("ALARM_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.ALARM_ENABLE);
			strBuf += str;
			str.Format("SERVICE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.SERVICE);
			strBuf += str;
			str.Format("MEANDER_VALUE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.MEANDER_VALUE);
			strBuf += str;
			str.Format("INVERT_REQUEST=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.INVERT_REQUEST);
			strBuf += str;
			str.Format("INVERT_RESPONSE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.INVERT_RESPONSE);
			strBuf += str;
			str.Format("C_IC_NA_1_PERIOD=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.C_IC_NA_1_PERIOD);
			strBuf += str;
			str.Format("C_IC_TS_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.C_IC_TS_ENABLE);
			strBuf += str;
			str.Format("C_IC_TIT_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.C_IC_TIT_ENABLE);
			strBuf += str;
			str.Format("C_IC_TII_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.C_IC_TII_ENABLE);
			strBuf += str;
			str.Format("NO_LINK_PERIOD=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.NO_LINK_PERIOD);
			strBuf += str;
			str.Format("TU_RESPONSE_PERIOD=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.TU_RESPONSE_PERIOD);
			strBuf += str;
			str.Format("REQ_RESPONSE_PERIOD=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.REQ_RESPONSE_PERIOD);
			strBuf += str;
			str.Format("MEANDER_PERIOD=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.MEANDER_PERIOD);
			strBuf += str;
			str.Format("ADD_MEANDER_BEFORE_REQ=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.ADD_MEANDER_BEFORE_REQ);
			strBuf += str;
			str.Format("SEND_CONFIRM=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.SEND_CONFIRM);
			strBuf += str;
			str.Format("IC_ON_MEANDER=%d\r\n\r\n", m_IndividualStructureSTMArray[i].m_Granit.IC_ON_MEANDER);
			strBuf += str;

			for (int k = 0; k < m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray.GetSize(); k++)
			{
				str.Format("MAKE_STRUCT=%d\r\n", k + 1);
				strBuf += str;
				str.Format("N_KP=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].N_KP);
				strBuf += str;
				str.Format("PACKET_TYPE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].PACKET_TYPE);
				strBuf += str;
				str.Format("AFB=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].AFB);
				strBuf += str;
				str.Format("INFO_TYPE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].INFO_TYPE);
				strBuf += str;
				str.Format("GROUP_NUMBER=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].GROUP_NUMBER);
				strBuf += str;
				str.Format("NUMBER=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].NUMBER);
				strBuf += str;
				str.Format("ADDRESS_PMZ=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].ADDRESS_PMZ);
				strBuf += str;
				str.Format("DATA_FORMAT=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].DATA_FORMAT);
				strBuf += str;				
				str.Format("//%s\r\n\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_IndividualStructureGranitArray[k].strCOMMENT);
				strBuf += str;
			}
			try
			{
				CString strFileName;
				strFileName.Format("%s\\granit_m%d_c%d.ini", strDirectory, m_nProcNum, m_IndividualStructureSTMArray[i].CHANNEL);
				f.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
				f.Write((void*)strBuf.GetBuffer(), strBuf.GetLength());
				f.Close();
			}
			catch (...)
			{
				return FALSE;
			}
			//TU
			strBuf = "";
			str.Format("NUMBER_OF_TU=%d\r\n\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray.GetSize());
			strBuf += str;

			for (int k = 0; k < m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray.GetSize(); k++)
			{
				str.Format("MAKE_TU=%d\r\n", k + 1);
				strBuf += str;
				str.Format("N_GROUP_2B=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].N_GROUP_2B);
				strBuf += str;
				str.Format("N_KP=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].N_KP);
				strBuf += str;
				str.Format("PACKET_TYPE=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].PACKET_TYPE);
				strBuf += str;
				str.Format("N_OBJECT_ON=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].N_OBJECT_ON);
				strBuf += str;
				str.Format("N_OBJECT_OFF=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].N_OBJECT_OFF);
				strBuf += str;
				str.Format("AFB_ON=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].AFB_ON);
				strBuf += str;
				str.Format("AFB_OFF=%d\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].AFB_OFF);
				strBuf += str;
				str.Format("//%s\r\n\r\n", m_IndividualStructureSTMArray[i].m_Granit.m_TUGranitArray[k].strCOMMENT);
				strBuf += str;

			}
			try
			{
				CString strFileName;
				strFileName.Format("%s\\tu_granit_p%d_c%d.ini", strDirectory, m_nProcNum, m_IndividualStructureSTMArray[i].CHANNEL);
				f.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
				f.Write((void*)strBuf.GetBuffer(), strBuf.GetLength());
				f.Close();
			}
			catch (...)
			{
				return FALSE;
			}
		}

		if (m_IndividualStructureSTMArray[i].PROTOCOL_TYPE == PROTOCOL_TYPE_AIST)
		{
			//каналы гранита aist_mN_cX.ini 
			strBuf = "";
			str.Format("NUMBER_STRUCT=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray.GetSize());
			strBuf += str;			
			str.Format("LOG_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.LOG_ENABLE);
			strBuf += str;
			str.Format("ALARM_ENABLE=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.ALARM_ENABLE);
			strBuf += str;
			str.Format("SERVICE=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.SERVICE);
			strBuf += str;			
			str.Format("NO_LINK_PERIOD=%d\r\n\r\n", m_IndividualStructureSTMArray[i].m_AIST.NO_LINK_PERIOD);
			strBuf += str;
			
			for (int k = 0; k < m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray.GetSize(); k++)
			{
				str.Format("MAKE_STRUCT=%d\r\n", k + 1);
				strBuf += str;				
				str.Format("PACKET_TYPE=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray[k].PACKET_TYPE);
				strBuf += str;
				str.Format("ADDRESS_PARAM=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray[k].ADDRESS_PARAM);
				strBuf += str;				
				str.Format("ADDRESS_PMZ=%d\r\n", m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray[k].ADDRESS_PMZ);
				strBuf += str;
				str.Format("//%s\r\n\r\n", m_IndividualStructureSTMArray[i].m_AIST.m_IndividualStructureAISTArray[k].strCOMMENT);
				strBuf += str;
			}
			try
			{
				CString strFileName;
				strFileName.Format("%s\\aist_m%d_c%d.ini", strDirectory, m_nProcNum, m_IndividualStructureSTMArray[i].CHANNEL);
				f.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
				f.Write((void*)strBuf.GetBuffer(), strBuf.GetLength());
				f.Close();
			}
			catch (...)
			{
				return FALSE;
			}			
		}
	}

	return TRUE;
}

BOOL CSTM::LoadFromFile(CString strFile)
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
			if((str.Find("TYPE") != -1)&&(str.Find("PROTOCOL_TYPE") == -1))
			{
				str.TrimLeft("TYPE");
				str.Trim();str.Trim("=");
				TYPE = atoi(str);
			}
			if(str.Find("SERVICE") != -1)
			{
				str.TrimLeft("SERVICE");
				str.Trim();str.Trim("=");
				SERVICE = atoi(str);
			}
			if(str.Find("NUMBER_STRUCT") != -1)
			{
				str.TrimLeft("NUMBER_STRUCT");
				str.Trim();str.Trim("=");
				m_IndividualStructureSTMArray.SetSize(atoi(str));
			}
						
			if(str.Find("MAKE_STRUCT") != -1)
			{
				str.TrimLeft("MAKE_STRUCT");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_IndividualStructureSTMArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}			
			if(str.Find("PROTOCOL_TYPE") != -1)
			{
				str.TrimLeft("PROTOCOL_TYPE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSTMArray.GetSize()))
					m_IndividualStructureSTMArray[nProcIndex].PROTOCOL_TYPE = atoi(str);										
			}
			if((str.Find("CHANNEL") != -1)&& (str.Find("CHANNEL2") == -1))
			{
				str.TrimLeft("CHANNEL");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSTMArray.GetSize()))
					m_IndividualStructureSTMArray[nProcIndex].CHANNEL = atoi(str);										
			}			
			if(str.Find("SPEED") != -1)
			{
				str.TrimLeft("SPEED");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSTMArray.GetSize()))
					m_IndividualStructureSTMArray[nProcIndex].SPEED = atoi(str);										
			}
			if (str.Find("CHANNEL2") != -1)
			{
				str.TrimLeft("CHANNEL2");
				str.Trim(); str.Trim("=");
				if ((nProcIndex >= 0) && (nProcIndex < m_IndividualStructureSTMArray.GetSize()))
					m_IndividualStructureSTMArray[nProcIndex].CHANNEL2 = atoi(str);
			}
			
			if(str.Find("//") != -1)
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_IndividualStructureSTMArray.GetSize()))
					m_IndividualStructureSTMArray[nProcIndex].strCOMMENT = str;														
			}
			strBuf.Delete(0,nIndex+1);			
		}while(nIndex != -1);
	}
	catch(...)
	{
		return FALSE;
	}
	////////////////////////////////////////////////////
	CString strDirectory;
	strDirectory = strFile;
	int idx = strDirectory.ReverseFind('\\');
	strDirectory.Truncate(idx);	

	for(int i =0; i < m_IndividualStructureSTMArray.GetSize(); i++)
	{		
		if (m_IndividualStructureSTMArray[i].PROTOCOL_TYPE == PROTOCOL_TYPE_GRANIT)
		{
			CString strBuf, str;
			CString strFileName;

			strFileName.Format("%s\\granit_m%d_c%d.ini", strDirectory, m_nProcNum, m_IndividualStructureSTMArray[i].CHANNEL);
			СGranit tmpGranit;
			try
			{
				if (!f.Open(strFileName, CFile::modeRead))
					return FALSE;
				CHAR buffer[4096];
				DWORD dwRead = 0;
				// Read in 4096-byte blocks,
				// remember how many bytes were actually read,
				// and try to write that many out. This loop ends
				// when there are no more bytes to read.
				do
				{
					dwRead = f.Read(buffer, 4096);
					if (dwRead > 0)
					{
						int nLen = strBuf.GetLength();
						strBuf += buffer;
						strBuf.Truncate(nLen + dwRead);
					}
				} while (dwRead > 0);
				f.Close();
				//AfxMessageBox(strBuf);
				strBuf.MakeUpper();
				strBuf.Remove(';');
				int nIndex = 0;
				int nProcIndex = -1;

				do
				{
					nIndex = strBuf.Find("\n");
					str = strBuf.Left(nIndex + 1);

					if (str.Find("NUMBER_STRUCT") != -1)
					{
						str.TrimLeft("NUMBER_STRUCT");
						str.Trim(); str.Trim("=");
						tmpGranit.m_IndividualStructureGranitArray.SetSize(atoi(str));
					}
					if (str.Find("NUMBER_NO_ANSWER") != -1)
					{
						str.TrimLeft("NUMBER_NO_ANSWER");
						str.Trim(); str.Trim("=");
						tmpGranit.NUMBER_NO_ANSWER = atoi(str);
					}
					if ((str.Find("TYPE") != -1) && (str.Find("PACKET_TYPE") == -1) && (str.Find("INFO_TYPE") == -1))
					{
						str.TrimLeft("TYPE");
						str.Trim(); str.Trim("=");
						tmpGranit.TYPE = atoi(str);
					}
					if (str.Find("LOG_ENABLE") != -1)
					{
						str.TrimLeft("LOG_ENABLE");
						str.Trim(); str.Trim("=");
						tmpGranit.LOG_ENABLE = atoi(str);
					}
					if (str.Find("ALARM_ENABLE") != -1)
					{
						str.TrimLeft("ALARM_ENABLE");
						str.Trim(); str.Trim("=");
						tmpGranit.ALARM_ENABLE = atoi(str);
					}
					if (str.Find("SERVICE") != -1)
					{
						str.TrimLeft("SERVICE");
						str.Trim(); str.Trim("=");
						tmpGranit.SERVICE = atoi(str);
					}
					if (str.Find("MEANDER_VALUE") != -1)
					{
						str.TrimLeft("MEANDER_VALUE");
						str.Trim(); str.Trim("=");
						tmpGranit.MEANDER_VALUE = atoi(str);
					}
					if (str.Find("NEXTMESSAGE") != -1)
					{
						str.TrimLeft("NEXTMESSAGE");
						str.Trim(); str.Trim("=");
						tmpGranit.INVERT_REQUEST = atoi(str);
					}
					if (str.Find("INVERT_REQUEST") != -1)
					{
						str.TrimLeft("INVERT_REQUEST");
						str.Trim(); str.Trim("=");
						tmpGranit.INVERT_REQUEST = atoi(str);
					}
					if (str.Find("INVERT_RESPONSE") != -1)
					{
						str.TrimLeft("INVERT_RESPONSE");
						str.Trim(); str.Trim("=");
						tmpGranit.INVERT_RESPONSE = atoi(str);
					}
					if (str.Find("C_IC_NA_1_PERIOD") != -1)
					{
						str.TrimLeft("C_IC_NA_1_PERIOD");
						str.Trim(); str.Trim("=");
						tmpGranit.C_IC_NA_1_PERIOD = atoi(str);
					}
					if (str.Find("C_IC_TS_ENABLE") != -1)
					{
						str.TrimLeft("C_IC_TS_ENABLE");
						str.Trim(); str.Trim("=");
						tmpGranit.C_IC_TS_ENABLE = atoi(str);
					}
					if (str.Find("C_IC_TIT_ENABLE") != -1)
					{
						str.TrimLeft("C_IC_TIT_ENABLE");
						str.Trim(); str.Trim("=");
						tmpGranit.C_IC_TIT_ENABLE = atoi(str);
					}
					if (str.Find("C_IC_TII_ENABLE") != -1)
					{
						str.TrimLeft("C_IC_TII_ENABLE");
						str.Trim(); str.Trim("=");
						tmpGranit.C_IC_TII_ENABLE = atoi(str);
					}
					if (str.Find("NO_LINK_PERIOD") != -1)
					{
						str.TrimLeft("NO_LINK_PERIOD");
						str.Trim(); str.Trim("=");
						tmpGranit.NO_LINK_PERIOD = atoi(str);
					}
					if (str.Find("TU_RESPONSE_PERIOD") != -1)
					{
						str.TrimLeft("TU_RESPONSE_PERIOD");
						str.Trim(); str.Trim("=");
						tmpGranit.TU_RESPONSE_PERIOD = atoi(str);
					}
					if (str.Find("REQ_RESPONSE_PERIOD") != -1)
					{
						str.TrimLeft("REQ_RESPONSE_PERIOD");
						str.Trim(); str.Trim("=");
						tmpGranit.REQ_RESPONSE_PERIOD = atoi(str);
					}
					if (str.Find("MEANDER_PERIOD") != -1)
					{
						str.TrimLeft("MEANDER_PERIOD");
						str.Trim(); str.Trim("=");
						tmpGranit.MEANDER_PERIOD = atoi(str);
					}
					if (str.Find("ADD_MEANDER_BEFORE_REQ") != -1)
					{
						str.TrimLeft("ADD_MEANDER_BEFORE_REQ");
						str.Trim(); str.Trim("=");
						tmpGranit.ADD_MEANDER_BEFORE_REQ = atoi(str);
					}
					if (str.Find("SEND_CONFIRM") != -1)
					{
						str.TrimLeft("SEND_CONFIRM");
						str.Trim(); str.Trim("=");
						tmpGranit.SEND_CONFIRM = atoi(str);
					}
					if (str.Find("IC_ON_MEANDER") != -1)
					{
						str.TrimLeft("IC_ON_MEANDER");
						str.Trim(); str.Trim("=");
						tmpGranit.IC_ON_MEANDER = atoi(str);
					}


					if (str.Find("MAKE_STRUCT") != -1)
					{
						str.TrimLeft("MAKE_STRUCT");
						str.Trim(); str.Trim("=");
						if ((atoi(str) > 0) && (atoi(str) <= tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							nProcIndex = atoi(str) - 1;
					}
					if (str.Find("N_KP") != -1)
					{
						str.TrimLeft("N_KP");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].N_KP = atoi(str);
					}
					if (str.Find("PACKET_TYPE") != -1)
					{
						str.TrimLeft("PACKET_TYPE");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].PACKET_TYPE = atoi(str);
					}
					if (str.Find("AFB") != -1)
					{
						str.TrimLeft("AFB");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].AFB = atoi(str);
					}
					if (str.Find("INFO_TYPE") != -1)
					{
						str.TrimLeft("INFO_TYPE");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].INFO_TYPE = atoi(str);
					}
					if (str.Find("GROUP_NUMBER") != -1)
					{
						str.TrimLeft("GROUP_NUMBER");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].GROUP_NUMBER = atoi(str);
					}
					if ((str.Find("NUMBER") != -1) && (str.Find("GROUP_NUMBER") == -1) && (str.Find("NUMBER_STRUCT") == -1) && (str.Find("NUMBER_NO_ANSWER") == -1))
					{
						str.TrimLeft("NUMBER");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].NUMBER = atoi(str);
					}
					if (str.Find("ADDRESS_PMZ") != -1)
					{
						str.TrimLeft("ADDRESS_PMZ");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].ADDRESS_PMZ = atoi(str);
					}
					if (str.Find("DATA_FORMAT") != -1)
					{
						str.TrimLeft("DATA_FORMAT");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].DATA_FORMAT = atoi(str);
					}					
					if (str.Find("//") != -1)
					{
						str.TrimLeft("//");
						str.Remove('\n');
						str.Remove('\r');
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_IndividualStructureGranitArray.GetSize()))
							tmpGranit.m_IndividualStructureGranitArray[nProcIndex].strCOMMENT = str;
					}
					strBuf.Delete(0, nIndex + 1);
				} while (nIndex != -1);
			}
			catch (...)
			{
				return FALSE;
			}

			strFileName.Format("%s\\tu_granit_p%d_c%d.ini", strDirectory, m_nProcNum, m_IndividualStructureSTMArray[i].CHANNEL);
			try
			{
				if (!f.Open(strFileName, CFile::modeRead))
					return FALSE;
				CHAR buffer[4096];
				DWORD dwRead = 0;
				// Read in 4096-byte blocks,
				// remember how many bytes were actually read,
				// and try to write that many out. This loop ends
				// when there are no more bytes to read.
				do
				{
					dwRead = f.Read(buffer, 4096);
					if (dwRead > 0)
					{
						int nLen = strBuf.GetLength();
						strBuf += buffer;
						strBuf.Truncate(nLen + dwRead);
					}
				} while (dwRead > 0);
				f.Close();
				//AfxMessageBox(strBuf);
				strBuf.MakeUpper();
				strBuf.Remove(';');
				int nIndex = 0;
				int nProcIndex = -1;
				do
				{
					nIndex = strBuf.Find("\n");
					str = strBuf.Left(nIndex + 1);

					if (str.Find("NUMBER_OF_TU") != -1)
					{
						str.TrimLeft("NUMBER_OF_TU");
						str.Trim(); str.Trim("=");
						tmpGranit.m_TUGranitArray.SetSize(atoi(str));
					}

					if (str.Find("MAKE_TU") != -1)
					{
						str.TrimLeft("MAKE_TU");
						str.Trim(); str.Trim("=");
						if ((atoi(str) > 0) && (atoi(str) <= tmpGranit.m_TUGranitArray.GetSize()))
							nProcIndex = atoi(str) - 1;
					}
					if (str.Find("N_GROUP_2B") != -1)
					{
						str.TrimLeft("N_GROUP_2B");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].N_GROUP_2B = atoi(str);
					}
					if (str.Find("N_KP") != -1)
					{
						str.TrimLeft("N_KP");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].N_KP = atoi(str);
					}
					if (str.Find("PACKET_TYPE") != -1)
					{
						str.TrimLeft("PACKET_TYPE");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].PACKET_TYPE = atoi(str);
					}
					if (str.Find("N_OBJECT_ON") != -1)
					{
						str.TrimLeft("N_OBJECT_ON");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].N_OBJECT_ON = atoi(str);
					}
					if (str.Find("N_OBJECT_OFF") != -1)
					{
						str.TrimLeft("N_OBJECT_OFF");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].N_OBJECT_OFF = atoi(str);
					}
					if (str.Find("AFB_ON") != -1)
					{
						str.TrimLeft("AFB_ON");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].AFB_ON = atoi(str);
					}
					if (str.Find("AFB_OFF") != -1)
					{
						str.TrimLeft("AFB_OFF");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].AFB_OFF = atoi(str);
					}
					if (str.Find("//") != -1)
					{
						str.TrimLeft("//");
						str.Remove('\n');
						str.Remove('\r');
						if ((nProcIndex >= 0) && (nProcIndex < tmpGranit.m_TUGranitArray.GetSize()))
							tmpGranit.m_TUGranitArray[nProcIndex].strCOMMENT = str;
					}
					strBuf.Delete(0, nIndex + 1);
				} while (nIndex != -1);
			}
			catch (...)
			{
				return FALSE;
			}
			m_IndividualStructureSTMArray[i].m_Granit = tmpGranit;
		}

		if (m_IndividualStructureSTMArray[i].PROTOCOL_TYPE == PROTOCOL_TYPE_AIST)
		{
			CString strBuf, str;
			CString strFileName;

			strFileName.Format("%s\\aist_m%d_c%d.ini", strDirectory, m_nProcNum, m_IndividualStructureSTMArray[i].CHANNEL);
			СAIST tmpAIST;
			try
			{
				if (!f.Open(strFileName, CFile::modeRead))
					return FALSE;
				CHAR buffer[4096];
				DWORD dwRead = 0;
				// Read in 4096-byte blocks,
				// remember how many bytes were actually read,
				// and try to write that many out. This loop ends
				// when there are no more bytes to read.
				do
				{
					dwRead = f.Read(buffer, 4096);
					if (dwRead > 0)
					{
						int nLen = strBuf.GetLength();
						strBuf += buffer;
						strBuf.Truncate(nLen + dwRead);
					}
				} while (dwRead > 0);
				f.Close();
				//AfxMessageBox(strBuf);
				strBuf.MakeUpper();
				strBuf.Remove(';');
				int nIndex = 0;
				int nProcIndex = -1;

				do
				{
					nIndex = strBuf.Find("\n");
					str = strBuf.Left(nIndex + 1);

					if (str.Find("NUMBER_STRUCT") != -1)
					{
						str.TrimLeft("NUMBER_STRUCT");
						str.Trim(); str.Trim("=");
						tmpAIST.m_IndividualStructureAISTArray.SetSize(atoi(str));
					}
					
					if (str.Find("LOG_ENABLE") != -1)
					{
						str.TrimLeft("LOG_ENABLE");
						str.Trim(); str.Trim("=");
						tmpAIST.LOG_ENABLE = atoi(str);
					}
					if (str.Find("ALARM_ENABLE") != -1)
					{
						str.TrimLeft("ALARM_ENABLE");
						str.Trim(); str.Trim("=");
						tmpAIST.ALARM_ENABLE = atoi(str);
					}
					if (str.Find("SERVICE") != -1)
					{
						str.TrimLeft("SERVICE");
						str.Trim(); str.Trim("=");
						tmpAIST.SERVICE = atoi(str);
					}					
					if (str.Find("NO_LINK_PERIOD") != -1)
					{
						str.TrimLeft("NO_LINK_PERIOD");
						str.Trim(); str.Trim("=");
						tmpAIST.NO_LINK_PERIOD = atoi(str);
					}					


					if (str.Find("MAKE_STRUCT") != -1)
					{
						str.TrimLeft("MAKE_STRUCT");
						str.Trim(); str.Trim("=");
						if ((atoi(str) > 0) && (atoi(str) <= tmpAIST.m_IndividualStructureAISTArray.GetSize()))
							nProcIndex = atoi(str) - 1;
					}					
					if (str.Find("PACKET_TYPE") != -1)
					{
						str.TrimLeft("PACKET_TYPE");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpAIST.m_IndividualStructureAISTArray.GetSize()))
							tmpAIST.m_IndividualStructureAISTArray[nProcIndex].PACKET_TYPE = atoi(str);
					}
					if (str.Find("ADDRESS_PARAM") != -1)
					{
						str.TrimLeft("ADDRESS_PARAM");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpAIST.m_IndividualStructureAISTArray.GetSize()))
							tmpAIST.m_IndividualStructureAISTArray[nProcIndex].ADDRESS_PARAM = atoi(str);
					}					
					if (str.Find("ADDRESS_PMZ") != -1)
					{
						str.TrimLeft("ADDRESS_PMZ");
						str.Trim(); str.Trim("=");
						if ((nProcIndex >= 0) && (nProcIndex < tmpAIST.m_IndividualStructureAISTArray.GetSize()))
							tmpAIST.m_IndividualStructureAISTArray[nProcIndex].ADDRESS_PMZ = atoi(str);
					}
					if (str.Find("//") != -1)
					{
						str.TrimLeft("//");
						str.Remove('\n');
						str.Remove('\r');
						if ((nProcIndex >= 0) && (nProcIndex <  tmpAIST.m_IndividualStructureAISTArray.GetSize()))
							tmpAIST.m_IndividualStructureAISTArray[nProcIndex].strCOMMENT = str;
					}
					strBuf.Delete(0, nIndex + 1);
				} while (nIndex != -1);
			}
			catch (...)
			{
				return FALSE;
			}			
			m_IndividualStructureSTMArray[i].m_AIST = tmpAIST;
		}
	}
	return TRUE;
}