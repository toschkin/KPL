#include "StdAfx.h"
#include "Retr.h"

BOOL CRetr::SaveToFile(CString strFile)
{
	CString strBuf,str;

	str.Format("NUM_RECIVE_DIRECT=%d\r\n",m_RECIVE_DIRECT.GetSize());
	strBuf+=str;
	str.Format("NUM_TRANSMIT_DIRECT=%d\r\n",NUM_TRANSMIT_DIRECT);
	strBuf+=str;
	str.Format("NUM_RETR_OBJECT=%d\r\n",NUM_RETR_OBJECT);
	strBuf+=str;
	str.Format("NUM_MANY_RETR=%d\r\n",m_ManyRetrArray.GetSize());
	strBuf+=str;
	str.Format("NUM_SINGLE_RETR=%d\r\n",0);
	strBuf+=str;	
	str.Format("NUM_FAST_RETR_OBJECT=%d\r\n\r\n",1000);
	strBuf+=str;

	for(int i =0; i < m_RECIVE_DIRECT.GetSize(); i++)
	{
		str.Format("RECIVE_DIRECT=%d\r\n",i+1);
		strBuf+=str;
		str.Format("KOD_DIRECT=%d\r\n\r\n",m_RECIVE_DIRECT[i]);
		strBuf+=str;		
	}
	strBuf+="\r\n";
	
	for(int i =0; i < m_ManyRetrArray.GetSize(); i++)
	{	
		str.Format("MAKE_MANY_RETR=%d\r\n",i+1);
		strBuf+=str;
		str.Format("PATH_DIRECT=%d\r\n",m_ManyRetrArray[i].PATH_DIRECT);
		strBuf+=str;		
		str.Format("PLACE_OF_PUT=%d\r\n",m_ManyRetrArray[i].PLACE_OF_PUT);
		strBuf+=str;		
		str.Format("START_ADRES_OBJECT=%d\r\n",m_ManyRetrArray[i].START_ADRES_OBJECT);
		strBuf+=str;		
		str.Format("START_ADRES_RETR=%d\r\n",m_ManyRetrArray[i].START_ADRES_RETR);
		strBuf+=str;		
		str.Format("NUM_MANY_RETR_OBJECT=%d\r\n",m_ManyRetrArray[i].NUM_MANY_RETR_OBJECT);
		strBuf+=str;		
		str.Format("FLAG_RETR=%d\r\n",m_ManyRetrArray[i].FLAG_RETR);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_ManyRetrArray[i].strCOMMENT);
		strBuf+=str;	
	}
	strBuf+="\r\n";

	/*for(int i =0; i < m_SingleRetrArray.GetSize(); i++)
	{	
		str.Format("MAKE_SINGLE_RETR=%d\r\n",i+1);
		strBuf+=str;
		str.Format("PATH_DIRECT=%d\r\n",m_SingleRetrArray[i].PATH_DIRECT);
		strBuf+=str;		
		str.Format("PLACE_OF_PUT=%d\r\n",m_SingleRetrArray[i].PLACE_OF_PUT);
		strBuf+=str;		
		str.Format("ADRES_OBJECT=%d\r\n",m_SingleRetrArray[i].ADRES_OBJECT);
		strBuf+=str;		
		str.Format("ADRES_RETR=%d\r\n",m_SingleRetrArray[i].ADRES_RETR);
		strBuf+=str;		
		str.Format("FLAG_RETR=%d\r\n",m_SingleRetrArray[i].FLAG_RETR);
		strBuf+=str;		
	}
	strBuf+="\r\n";	*/

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
BOOL CRetr::LoadFromFile(CString strFile)
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
		int nRecieveIndex = -1;
		int nManyRetrIndex = -1;
		int nMaskIndex = -1;
		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			if(str.Find("NUM_TRANSMIT_DIRECT") != -1)
			{
				str.TrimLeft("NUM_TRANSMIT_DIRECT");
				str.Trim();str.Trim("=");
				NUM_TRANSMIT_DIRECT = atoi(str);
			}
			if(str.Find("NUM_RETR_OBJECT") != -1)
			{
				str.TrimLeft("NUM_RETR_OBJECT");
				str.Trim();str.Trim("=");
				NUM_RETR_OBJECT = atoi(str);
			}			
			if(str.Find("NUM_RECIVE_DIRECT") != -1)
			{
				str.TrimLeft("NUM_RECIVE_DIRECT");
				str.Trim();str.Trim("=");
				m_RECIVE_DIRECT.SetSize(atoi(str));
			}						
			if(str.Find("RECIVE_DIRECT") != -1)
			{
				str.TrimLeft("RECIVE_DIRECT");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_RECIVE_DIRECT.GetSize()))				
					nRecieveIndex = atoi(str)-1;								
			}
			if(str.Find("KOD_DIRECT") != -1)
			{
				str.TrimLeft("KOD_DIRECT");
				str.Trim();str.Trim("=");
				if((nRecieveIndex >= 0)&&(nRecieveIndex < m_RECIVE_DIRECT.GetSize()))
					m_RECIVE_DIRECT[nRecieveIndex] = atoi(str);										
			}

			if((str.Find("NUM_MANY_RETR") != -1)&&(str.Find("NUM_MANY_RETR_OBJECT")==-1))
			{
				str.TrimLeft("NUM_MANY_RETR");
				str.Trim();str.Trim("=");
				m_ManyRetrArray.SetSize(atoi(str));
			}						
			if(str.Find("MAKE_MANY_RETR") != -1)
			{
				str.TrimLeft("MAKE_MANY_RETR");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_ManyRetrArray.GetSize()))				
					nManyRetrIndex = atoi(str)-1;								
			}
			if(str.Find("PATH_DIRECT") != -1)
			{
				str.TrimLeft("PATH_DIRECT");
				str.Trim();str.Trim("=");
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].PATH_DIRECT = atoi(str);										
			}
			if(str.Find("PLACE_OF_PUT") != -1)
			{
				str.TrimLeft("PLACE_OF_PUT");
				str.Trim();str.Trim("=");
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].PLACE_OF_PUT = atoi(str);										
			}
			if(str.Find("START_ADRES_OBJECT") != -1)
			{
				str.TrimLeft("START_ADRES_OBJECT");
				str.Trim();str.Trim("=");
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].START_ADRES_OBJECT = atoi(str);										
			}
			if(str.Find("START_ADRES_RETR") != -1)
			{
				str.TrimLeft("START_ADRES_RETR");
				str.Trim();str.Trim("=");
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].START_ADRES_RETR = atoi(str);										
			}
			if(str.Find("NUM_MANY_RETR_OBJECT") != -1)
			{
				str.TrimLeft("NUM_MANY_RETR_OBJECT");
				str.Trim();str.Trim("=");
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].NUM_MANY_RETR_OBJECT = atoi(str);										
			}
			if(str.Find("FLAG_RETR") != -1)
			{
				str.TrimLeft("FLAG_RETR");
				str.Trim();str.Trim("=");
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].FLAG_RETR = atoi(str);										
			}
			if((str.Find("//") != -1)&&(str.Find("//_") == -1))
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nManyRetrIndex >= 0)&&(nManyRetrIndex < m_ManyRetrArray.GetSize()))
					m_ManyRetrArray[nManyRetrIndex].strCOMMENT = str;														
			}	
			if(str.Find("MAKE_SINGLE_RETR") != -1)
			{
				break;
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

BOOL CRetr::SaveToCalcFile(CString strFile)
{
	CString strBuf,str;

	str.Format("NUM_MACROS_TI=%d\r\n",m_CalcTIArray.GetSize());
	strBuf+=str;
	str.Format("NUM_MACROS_TS=%d\r\n\r\n",m_CalcTSArray.GetSize());
	strBuf+=str;
	
	for(int i =0; i < m_CalcTIArray.GetSize(); i++)
	{	
		str.Format("NUMBER_CALCULATE_TI=%d\r\n",i+1);
		strBuf+=str;
		str.Format("TYPE=%d\r\n",m_CalcTIArray[i].TYPE);
		strBuf+=str;		
		str.Format("ADDRESS_FROM=%d\r\n",m_CalcTIArray[i].ADDRESS_FROM);
		strBuf+=str;		
		str.Format("POSITION_BYTE=%d\r\n",m_CalcTIArray[i].POSITION_BYTE);
		strBuf+=str;		
		str.Format("NUMBER_BYTE=%d\r\n",m_CalcTIArray[i].NUMBER_BYTE);
		strBuf+=str;		
		str.Format("NUMBER_DIRECT=%d\r\n",m_CalcTIArray[i].NUMBER_DIRECT);
		strBuf+=str;		
		str.Format("ADDRESS_TOO=%d\r\n",m_CalcTIArray[i].ADDRESS_TOO);
		strBuf+=str;
		str.Format("POSITION_BYTE_TOO=%d\r\n",m_CalcTIArray[i].POSITION_BYTE_TOO);
		strBuf+=str;		
		str.Format("DOPKODE_YES_NO=%d\r\n",m_CalcTIArray[i].DOPKODE_YES_NO);
		strBuf+=str;		
		str.Format("CENA_SHKALI=%f\r\n",m_CalcTIArray[i].CENA_SHKALI);
		strBuf+=str;		
		str.Format("SMESHENIE=%f\r\n",m_CalcTIArray[i].SMESHENIE);
		strBuf+=str;		
		str.Format("MIN_FIZ=%f\r\n",m_CalcTIArray[i].MIN_FIZ);
		strBuf+=str;		
		str.Format("MAX_FIZ=%f\r\n",m_CalcTIArray[i].MAX_FIZ);
		strBuf+=str;		
		str.Format("MAX_SHKALA_FIZ=%d\r\n",m_CalcTIArray[i].MAX_SHKALA_FIZ);
		strBuf+=str;
		str.Format("//%s\r\n\r\n",m_CalcTIArray[i].strCOMMENT);
		strBuf+=str;	
	}

	/*for(int i =0; i < m_CalcTSArray.GetSize(); i++)
	{	
		str.Format("NUMBER_RETR_TS=%d\r\n",i+1);
		strBuf+=str;
		str.Format("TYPE=%d\r\n",m_CalcTSArray[i].TYPE);
		strBuf+=str;		
		str.Format("ADDRESS_FROM=%d\r\n",m_CalcTSArray[i].ADDRESS_FROM);
		strBuf+=str;		
		str.Format("POSITION_BYTE=%d\r\n",m_CalcTSArray[i].POSITION_BYTE);
		strBuf+=str;		
		str.Format("POSITION_BIT=%d\r\n",m_CalcTSArray[i].POSITION_BIT);
		strBuf+=str;		
		str.Format("NUMBER_BIT=%d\r\n",m_CalcTSArray[i].NUMBER_BIT);
		strBuf+=str;		
		str.Format("NUMBER_DIRECT=%d\r\n",m_CalcTSArray[i].NUMBER_DIRECT);
		strBuf+=str;		
		str.Format("ADDRESS_TOO=%d\r\n",m_CalcTSArray[i].ADDRESS_TOO);
		strBuf+=str;
		str.Format("POSITION_BYTE_TOO=%d\r\n",m_CalcTSArray[i].POSITION_BYTE_TOO);
		strBuf+=str;		
		str.Format("POSITION_BIT_TOO=%d\r\n",m_CalcTSArray[i].POSITION_BIT_TOO);
		strBuf+=str;				
		str.Format("//%s\r\n\r\n",m_CalcTSArray[i].strCOMMENT);
		strBuf+=str;	
	}*/

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
BOOL CRetr::LoadFromCalcFile(CString strFile)
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
		int nRecieveIndex = -1;
		int nCalcTIIndex = -1;
		int nMaskIndex = -1;
		do
		{
			nIndex = strBuf.Find("\n");
			str = strBuf.Left(nIndex+1);
			
			if(str.Find("NUM_MACROS_TI") != -1)
			{
				str.TrimLeft("NUM_MACROS_TI");
				str.Trim();str.Trim("=");
				m_CalcTIArray.SetSize(atoi(str));
			}						
			if(str.Find("NUMBER_CALCULATE_TI") != -1)
			{
				str.TrimLeft("NUMBER_CALCULATE_TI");
				str.Trim();str.Trim("=");
				if((atoi(str) > 0)&&(atoi(str) <= m_CalcTIArray.GetSize()))				
					nCalcTIIndex = atoi(str)-1;								
			}
			if(str.Find("TYPE") != -1)
			{
				str.TrimLeft("TYPE");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].TYPE = atoi(str);										
			}
			if(str.Find("ADDRESS_FROM") != -1)
			{
				str.TrimLeft("ADDRESS_FROM");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].ADDRESS_FROM = atoi(str);										
			}
			if((str.Find("POSITION_BYTE") != -1)&&(str.Find("POSITION_BYTE_TOO") == -1))
			{
				str.TrimLeft("POSITION_BYTE");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].POSITION_BYTE = atoi(str);										
			}
			if(str.Find("NUMBER_BYTE") != -1)
			{
				str.TrimLeft("NUMBER_BYTE");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].NUMBER_BYTE = atoi(str);										
			}
			if(str.Find("NUMBER_DIRECT") != -1)
			{
				str.TrimLeft("NUMBER_DIRECT");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].NUMBER_DIRECT = atoi(str);										
			}
			if(str.Find("ADDRESS_TOO") != -1)
			{
				str.TrimLeft("ADDRESS_TOO");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].ADDRESS_TOO = atoi(str);										
			}
			if(str.Find("POSITION_BYTE_TOO") != -1)
			{
				str.TrimLeft("POSITION_BYTE_TOO");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].POSITION_BYTE_TOO = atoi(str);										
			}			
			if(str.Find("DOPKODE_YES_NO") != -1)
			{
				str.TrimLeft("DOPKODE_YES_NO");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].DOPKODE_YES_NO = atoi(str);										
			}
			if(str.Find("CENA_SHKALI") != -1)
			{
				str.TrimLeft("CENA_SHKALI");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].CENA_SHKALI = atof(str);										
			}
			if(str.Find("SMESHENIE") != -1)
			{
				str.TrimLeft("SMESHENIE");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].SMESHENIE = atof(str);										
			}
			if(str.Find("MIN_FIZ") != -1)
			{
				str.TrimLeft("MIN_FIZ");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].MIN_FIZ = atof(str);										
			}
			if(str.Find("MAX_FIZ") != -1)
			{
				str.TrimLeft("MAX_FIZ");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].MAX_FIZ = atof(str);										
			}
			if(str.Find("MAX_SHKALA_FIZ") != -1)
			{
				str.TrimLeft("MAX_SHKALA_FIZ");
				str.Trim();str.Trim("=");
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].MAX_SHKALA_FIZ = atoi(str);										
			}
			//     for TI //			for TS    //_
			if((str.Find("//") != -1)&&(str.Find("//_") == -1))
			{
				str.TrimLeft("//");				
				str.Remove('\n');
				str.Remove('\r');
				if((nCalcTIIndex >= 0)&&(nCalcTIIndex < m_CalcTIArray.GetSize()))
					m_CalcTIArray[nCalcTIIndex].strCOMMENT = str;														
			}
			if(str.Find("NUMBER_RETR_TS") != -1)
			{
				//пока так чтобы не было косяков, потом реализуем ретранс. ТС
				break;
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