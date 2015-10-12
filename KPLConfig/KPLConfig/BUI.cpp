#include "StdAfx.h"
#include "BUI.h"

CMapboard::CMapboard(void)
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
	NUMBER_NO_ANSWER=0;
	NUMBER_BUTS=0;
	NUMBER_BUI=0;
	START_ADDRESS_BUTS=1;
	START_ADDRESS_BUI=1;
	OPROS_STATUS=1;
	TIMER_AUTO_KVIT_TS=10;
	TIMER_AUTO_KVIT_TI=10;
}

CMapboard::~CMapboard(void)
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
	NUMBER_NO_ANSWER=0;
	
	NUMBER_BUTS=0;
	NUMBER_BUI=0;
	START_ADDRESS_BUTS=1;
	START_ADDRESS_BUI=1;
	OPROS_STATUS=1;
	m_MacrosBUIArray.RemoveAll();
	m_MacrosBUTSArray.RemoveAll();
	TIMER_AUTO_KVIT_TS=10;
	TIMER_AUTO_KVIT_TI=10;
}
BOOL CMapboard::SaveToFile(CString strFile)
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
	str.Format("CONTROLPOTOK=%d\r\n",CONTROLPOTOK);
	strBuf+=str;
	str.Format("NUMBER_NO_ANSWER=%d\r\n",NUMBER_NO_ANSWER);
	strBuf+=str;
	str.Format("NUMBER_BUTS=%d\r\n",NUMBER_BUTS);
	strBuf+=str;
	str.Format("NUMBER_BUI=%d\r\n",NUMBER_BUI);
	strBuf+=str;	
	str.Format("START_ADDRESS_BUTS=%d\r\n",START_ADDRESS_BUTS);
	strBuf+=str;
	str.Format("START_ADDRESS_BUI=%d\r\n",START_ADDRESS_BUI);
	strBuf+=str;
	str.Format("OPROS_STATUS=%d\r\n",OPROS_STATUS);
	strBuf+=str;
	str.Format("NUMBER_MACROS_TS=%d\r\n",m_MacrosBUTSArray.GetSize());
	strBuf+=str;
	str.Format("NUMBER_MACROS_TI=%d\r\n",m_MacrosBUIArray.GetSize());
	strBuf+=str;
	str.Format("NUMBER_SUM_TI=%d\r\n",0);
	strBuf+=str;
	str.Format("TIMER_AUTO_KVIT_TS=%d\r\n",TIMER_AUTO_KVIT_TS);
	strBuf+=str;
	str.Format("TIMER_AUTO_KVIT_TI=%d\r\n\r\n",TIMER_AUTO_KVIT_TI);
	strBuf+=str;
	
	for(int i =0; i < m_MacrosBUTSArray.GetSize(); i++)
	{
		str.Format("NUMBER_MACROS_BUTS=%d\r\n",i+1);
		strBuf+=str;
		str.Format("TYPE_BUTS=%d\r\n",m_MacrosBUTSArray[i].TYPE);
		strBuf+=str;
		str.Format("ADDRESS_BUTS=%d\r\n",m_MacrosBUTSArray[i].ADDRESS_BUTS);
		strBuf+=str;
		str.Format("NUMBER_POSITION_BUTS=%d\r\n",m_MacrosBUTSArray[i].NUMBER_POSITION);
		strBuf+=str;
		str.Format("POSITION_DOUBLE_BUTS=%d\r\n",m_MacrosBUTSArray[i].POSITION_DOUBLE);
		strBuf+=str;
		str.Format("ADDRESS_PMZ_BUTS=%d\r\n",m_MacrosBUTSArray[i].ADDRESS_PMZ);
		strBuf+=str;
		str.Format("POS_BYTE=%d\r\n",m_MacrosBUTSArray[i].POS_BYTE);
		strBuf+=str;
		str.Format("POS_BIT=%d\r\n",m_MacrosBUTSArray[i].POS_BIT);
		strBuf+=str;
		str.Format("COLOR_ON=%d\r\n",m_MacrosBUTSArray[i].COLOR_ON);
		strBuf+=str;
		str.Format("COLOR_OFF=%d\r\n",m_MacrosBUTSArray[i].COLOR_OFF);
		strBuf+=str;
		str.Format("ON_VALUE=%d\r\n",m_MacrosBUTSArray[i].ON_VALUE);
		strBuf+=str;		
		str.Format("//_%s\r\n\r\n",m_MacrosBUTSArray[i].strCOMMENT);
		strBuf+=str;
	}

	for(int i =0; i < m_MacrosBUIArray.GetSize(); i++)
	{
		str.Format("NUMBER_MACROS_BUI=%d\r\n",i+1);
		strBuf+=str;
		str.Format("TYPE_BUI=%d\r\n",m_MacrosBUIArray[i].TYPE);
		strBuf+=str;
		str.Format("ADDRESS_BUI=%d\r\n",m_MacrosBUIArray[i].ADDRESS_BUI);
		strBuf+=str;
		str.Format("NUMBER_POSITION_BUI=%d\r\n",m_MacrosBUIArray[i].NUMBER_POSITION);
		strBuf+=str;
		str.Format("POSITION_DOUBLE_BUI=%d\r\n",m_MacrosBUIArray[i].POSITION_DOUBLE);
		strBuf+=str;
		str.Format("ADDRESS_PMZ_BUI=%d\r\n",m_MacrosBUIArray[i].ADDRESS_PMZ);
		strBuf+=str;
		str.Format("ZNAK=%d\r\n",m_MacrosBUIArray[i].ZNAK);
		strBuf+=str;
		str.Format("CENA_SHKALI=%f\r\n",m_MacrosBUIArray[i].CENA_SHKALI);
		strBuf+=str;
		str.Format("SMESHENIE=%f\r\n",m_MacrosBUIArray[i].SMESHENIE);
		strBuf+=str;
		str.Format("MIN=%f\r\n",m_MacrosBUIArray[i].MIN);
		strBuf+=str;		
		str.Format("MAX=%f\r\n",m_MacrosBUIArray[i].MAX);
		strBuf+=str;
		str.Format("DOP_FLAG=%d\r\n",m_MacrosBUIArray[i].DOP_FLAG);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_MacrosBUIArray[i].strCOMMENT);
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
BOOL CMapboard::LoadFromFile(CString strFile)
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
				/*int ;//=5 - количество панелей ѕ “—
	int ;//=5 - количество панелей ѕ “»
	int ;//=1- стартовый адрес панели ѕ “— (адрес 0- запрещЄнный)
	int ;//=10 Ч стартовый адрес панели ѕ “» (адрес 0- запрещЄнный)
	int ;//=1 Ч врем€ опроса статусов прибора, если 0- опрос не производитс€, 1 квант Ч 1 секунда
	//=12 Ч количество макросов дл€ дл€ вывода информации на ѕ “—
	//NUMBER_MACROS_TI=12 Ч количество макросов дл€ выдачи на ѕ “»
	//NUMBER_SUM_TI=0 Ч количество макросов описывающие суммарные “»
	int ;//=10 Ч врем€ автоквитировани€ дл€ панелей ѕ “—,1 квант Ч 1 секунда
	int ;/*/

			if(str.Find("NUMBER_BUTS") != -1)
			{
				str.TrimLeft("NUMBER_BUTS");
				str.Trim();str.Trim("=");
				NUMBER_BUTS = atoi(str);
			}
			if(str.Find("NUMBER_BUI") != -1)
			{
				str.TrimLeft("NUMBER_BUI");
				str.Trim();str.Trim("=");
				NUMBER_BUI = atoi(str);
			}
			if(str.Find("START_ADDRESS_BUTS") != -1)
			{
				str.TrimLeft("START_ADDRESS_BUTS");
				str.Trim();str.Trim("=");
				START_ADDRESS_BUTS = atoi(str);
			}
			if(str.Find("START_ADDRESS_BUI") != -1)
			{
				str.TrimLeft("START_ADDRESS_BUI");
				str.Trim();str.Trim("=");
				START_ADDRESS_BUI = atoi(str);
			}
			if(str.Find("OPROS_STATUS") != -1)
			{
				str.TrimLeft("OPROS_STATUS");
				str.Trim();str.Trim("=");
				OPROS_STATUS = atoi(str);
			}
			if(str.Find("TIMER_AUTO_KVIT_TS") != -1)
			{
				str.TrimLeft("TIMER_AUTO_KVIT_TS");
				str.Trim();str.Trim("=");
				TIMER_AUTO_KVIT_TS = atoi(str);
			}
			if(str.Find("TIMER_AUTO_KVIT_TI") != -1)
			{
				str.TrimLeft("TIMER_AUTO_KVIT_TI");
				str.Trim();str.Trim("=");
				TIMER_AUTO_KVIT_TI = atoi(str);
			}
			if(str.Find("TIMER_AUTO_KVIT_TS") != -1)
			{
				str.TrimLeft("TIMER_AUTO_KVIT_TS");
				str.Trim();str.Trim("=");
				TIMER_AUTO_KVIT_TS = atoi(str);
			}
		
			if(str.Find("NUMBER_MACROS_TS") != -1)
			{
				str.TrimLeft("NUMBER_MACROS_TS");
				str.Trim();str.Trim("=");
				m_MacrosBUTSArray.SetSize(atoi(str));
			}
			if(str.Find("NUMBER_MACROS_TI") != -1)
			{
				str.TrimLeft("NUMBER_MACROS_TI");
				str.Trim();str.Trim("=");
				m_MacrosBUIArray.SetSize(atoi(str));
			}

			if(str.Find("NUMBER_MACROS_BUTS") != -1)
			{
				str.TrimLeft("NUMBER_MACROS_BUTS");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_MacrosBUTSArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}	
			if(str.Find("TYPE_BUTS") != -1)
			{
				str.TrimLeft("TYPE_BUTS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].TYPE = atoi(str);										
			}
			if(str.Find("ADDRESS_BUTS") != -1)
			{
				str.TrimLeft("ADDRESS_BUTS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].ADDRESS_BUTS = atoi(str);										
			}
			if(str.Find("NUMBER_POSITION_BUTS") != -1)
			{
				str.TrimLeft("NUMBER_POSITION_BUTS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].NUMBER_POSITION = atoi(str);										
			}
			if(str.Find("POSITION_DOUBLE_BUTS") != -1)
			{
				str.TrimLeft("POSITION_DOUBLE_BUTS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].POSITION_DOUBLE = atoi(str);										
			}
			if(str.Find("ADDRESS_PMZ_BUTS") != -1)
			{
				str.TrimLeft("ADDRESS_PMZ_BUTS");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].ADDRESS_PMZ = atoi(str);										
			}
			if(str.Find("POS_BYTE") != -1)
			{
				str.TrimLeft("POS_BYTE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].POS_BYTE = atoi(str);										
			}
			if(str.Find("POS_BIT") != -1)
			{
				str.TrimLeft("POS_BIT");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].POS_BIT = atoi(str);										
			}
			if(str.Find("COLOR_ON") != -1)
			{
				str.TrimLeft("COLOR_ON");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].COLOR_ON = atoi(str);										
			}
			if(str.Find("COLOR_OFF") != -1)
			{
				str.TrimLeft("COLOR_OFF");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].COLOR_OFF = atoi(str);										
			}
			if(str.Find("ON_VALUE") != -1)
			{
				str.TrimLeft("ON_VALUE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].ON_VALUE = atoi(str);										
			}	
			if(str.Find("//_") != -1)
			{
				str.TrimLeft("//_");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUTSArray.GetSize()))
					m_MacrosBUTSArray[nProcIndex].strCOMMENT = str;														
			}
			//BUI
			if(str.Find("NUMBER_MACROS_BUI") != -1)
			{
				str.TrimLeft("NUMBER_MACROS_BUI");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_MacrosBUIArray.GetSize()))				
					nProcIndex = atoi(str)-1;								
			}	
			if(str.Find("TYPE_BUI") != -1)
			{
				str.TrimLeft("TYPE_BUI");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].TYPE = atoi(str);										
			}
			if(str.Find("ADDRESS_BUI") != -1)
			{
				str.TrimLeft("ADDRESS_BUI");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].ADDRESS_BUI = atoi(str);										
			}
			if(str.Find("NUMBER_POSITION_BUI") != -1)
			{
				str.TrimLeft("NUMBER_POSITION_BUI");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].NUMBER_POSITION = atoi(str);										
			}
			if(str.Find("POSITION_DOUBLE_BUI") != -1)
			{
				str.TrimLeft("POSITION_DOUBLE_BUI");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].POSITION_DOUBLE = atoi(str);										
			}
			if(str.Find("ADDRESS_PMZ_BUI") != -1)
			{
				str.TrimLeft("ADDRESS_PMZ_BUI");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].ADDRESS_PMZ = atoi(str);										
			}		
			if(str.Find("ZNAK") != -1)
			{
				str.TrimLeft("ZNAK");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].ZNAK = atoi(str);										
			}
			if(str.Find("CENA_SHKALI") != -1)
			{
				str.TrimLeft("CENA_SHKALI");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].CENA_SHKALI = atof(str);										
			}
			if(str.Find("SMESHENIE") != -1)
			{
				str.TrimLeft("SMESHENIE");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].SMESHENIE = atof(str);										
			}
			if(str.Find("MIN") != -1)
			{
				str.TrimLeft("MIN");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].MIN = atof(str);										
			}
			if(str.Find("MAX") != -1)
			{
				str.TrimLeft("MAX");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].MAX = atof(str);										
			}	
			if(str.Find("DOP_FLAG") != -1)
			{
				str.TrimLeft("DOP_FLAG");
				str.Trim();str.Trim("=");
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].DOP_FLAG = atoi(str);										
			}
			if(str.Find("//") != -1)
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nProcIndex >= 0)&&(nProcIndex < m_MacrosBUIArray.GetSize()))
					m_MacrosBUIArray[nProcIndex].strCOMMENT = str;														
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