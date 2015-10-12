#include "StdAfx.h"
#include "KPLProject.h"
#include "FileManip.h"

CKPLProject::CKPLProject(void)
{	
}

CKPLProject::~CKPLProject(void)
{
	m_Iec104mArray.RemoveAll();
	m_Iec101mArray.RemoveAll();
	m_Iec103mArray.RemoveAll();
	m_ModbusMArray.RemoveAll();
	m_ModbusSArray.RemoveAll();
	m_Iec104sArray.RemoveAll();
	m_Iec101sArray.RemoveAll();
	m_IecKorundmArray.RemoveAll();
	m_GPIOmArray.RemoveAll();
	m_MapboardArray.RemoveAll();
	m_SPAmArray.RemoveAll();
	m_ModbusTCPMArray.RemoveAll();
	m_STMArray.RemoveAll();
}
BOOL CKPLProject::IsPortDuplicated(int nPort,int nProcNum)
{
	for(int j = 0; j < m_Iec101mArray.GetSize(); j++)
	{
		if((m_Iec101mArray[j].m_nProcNum != nProcNum)&&((m_Iec101mArray[j].PORT == nPort)||(m_Iec101mArray[j].RES_PORT == nPort)))
			return TRUE;
	}
	for(int j = 0; j < m_Iec101sArray.GetSize(); j++)
	{
		if((m_Iec101sArray[j].m_nProcNum != nProcNum)&&((m_Iec101sArray[j].PORT == nPort)||(m_Iec101sArray[j].RES_PORT == nPort)))
			return TRUE;
	}
	for(int j = 0; j < m_ModbusMArray.GetSize(); j++)
	{
		if((m_ModbusMArray[j].m_nProcNum != nProcNum)&&(m_ModbusMArray[j].PORT == nPort))
			return TRUE;
	}
	for(int j = 0; j < m_ModbusSArray.GetSize(); j++)
	{
		if((m_ModbusSArray[j].m_nProcNum != nProcNum)&&(m_ModbusSArray[j].PORT == nPort))
			return TRUE;
	}
	for(int j = 0; j < m_Iec103mArray.GetSize(); j++)
	{
		if((m_Iec103mArray[j].m_nProcNum != nProcNum)&&(m_Iec103mArray[j].PORT == nPort))
			return TRUE;
	}
	for(int j = 0; j < m_IecKorundmArray.GetSize(); j++)
	{
		if((m_IecKorundmArray[j].m_nProcNum != nProcNum)&&(m_IecKorundmArray[j].PORT == nPort))
			return TRUE;
	}	
	for(int j = 0; j < m_MapboardArray.GetSize(); j++)
	{
		if((m_MapboardArray[j].m_nProcNum != nProcNum)&&(m_MapboardArray[j].PORT == nPort))
			return TRUE;
	}		
	for(int j = 0; j < m_SPAmArray.GetSize(); j++)
	{
		if((m_SPAmArray[j].m_nProcNum != nProcNum)&&(m_SPAmArray[j].PORT == nPort))
			return TRUE;
	}		
	for(int j = 0; j < m_STMArray.GetSize(); j++)
	{
		if((m_STMArray[j].m_nProcNum != nProcNum)&&(m_STMArray[j].PORT == nPort))
			return TRUE;
	}			
	if((m_GPSTime.PORT == nPort)&&(nProcNum != -1))
		return TRUE;
	
	
	
	return FALSE;
}
void FileSaveErrorMessage(CString sFile)
{
	CString sMess;
	sMess.Format("Ошибка при сохранении файла:\r\n%s",sFile);
	AfxMessageBox(sMess);
}
BOOL CKPLProject::SaveProject(CString strDirectory,CString strFTPSite,CFtpConnection* pFtpConn)
{
		
	CString sFile="main_set.ini";	
	sFile = strDirectory+sFile;
	if(m_Main_Set.SaveToFile(sFile)!=TRUE)
	{	
		
		return FALSE;
	}	
	sFile = "retr.ini";
	sFile = strDirectory+sFile;
	if(m_Retr.SaveToFile(sFile)!=TRUE)	
	{
		FileSaveErrorMessage(sFile);
		return FALSE;
	}
	if(m_nVersion > 13)
	{
		sFile.Replace("retr.ini","retrcalc.ini");
		if(m_Retr.SaveToCalcFile(sFile)!=TRUE)	
		{
			FileSaveErrorMessage(sFile);
			return FALSE;		
		}
	}

	sFile = "GPS_time3.ini";
	sFile = strDirectory+sFile;
	if(m_GPSTime.SaveToFile(sFile)!=TRUE)	
	{
		FileSaveErrorMessage(sFile);
		return FALSE;
	}
	/*if(m_GPSTime.SYNC_FROM == 4)
	{
		sFile = "ntpdate.sh";
		sFile = strDirectory+sFile;
		if(m_GPSTime.SaveToScriptFile(sFile)!=TRUE)
		{
			FileSaveErrorMessage(sFile);
			return FALSE;
		}
	}*/
		
	if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
	{
		/*if(!pFtpConn->RemoveDirectory(strFTPSite))
		{
		//	return FALSE;
		}
		if(!pFtpConn->CreateDirectory(strFTPSite))
		{
		//	return FALSE;
		}*/
		
		
		CString sFile="main_set.ini";	
		sFile = strDirectory+sFile;

		CString sFTPFile=strFTPSite+"/main_set.ini";
		if(!pFtpConn->PutFile(sFile,sFTPFile))
		{
			FileSaveErrorMessage(sFTPFile);
			return FALSE;
		}
		sFile = "retr.ini";
		sFile = strDirectory+sFile;
		
		sFTPFile=strFTPSite+"/retr.ini";		
		if(!pFtpConn->PutFile(sFile,sFTPFile))
		{
			FileSaveErrorMessage(sFTPFile);
			return FALSE;	
		}
		if(m_nVersion > 13)
		{
			sFTPFile.Replace("retr.ini","retrcalc.ini");
			sFile.Replace("retr.ini","retrcalc.ini");
			if(!pFtpConn->PutFile(sFile,sFTPFile))
				return FALSE;	
		}

		sFile = "GPS_time3.ini";
		sFile = strDirectory+sFile;
		
		sFTPFile=strFTPSite+"/GPS_time3.ini";		
		if(!pFtpConn->PutFile(sFile,sFTPFile))
		{
			FileSaveErrorMessage(sFTPFile);
			return FALSE;	
		}
		/*if(m_GPSTime.SYNC_FROM == 4)
		{
			sFile = "ntpdate.sh";
			sFile = strDirectory+sFile;
			sFTPFile=strFTPSite+"/ntpdate.sh";
			if(!pFtpConn->PutFile(sFile,sFTPFile))
			{
				FileSaveErrorMessage(sFTPFile);
				return FALSE;
			}			
		}*/
	}	
	
	

	for(int i = 0; i < m_Main_Set.m_ProcessInfoArray.GetSize(); i++)
	{				
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 21)
		{			
			for(int j = 0; j < m_STMArray.GetSize(); j++)
			{				
				if(m_STMArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;					
					
					strIec101mPath.Format("%sstm_m%d.ini",strDirectory,i+1);
					
					if(m_STMArray[j].SaveToFile(strIec101mPath)!=TRUE)	
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;					
					}
					
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						//тупо пробую заливать все что толдько может быть игноря ошибки
						//так же надо и с аистом будет делать
						for(int k=0;k<4;k++)
						{				
							CString strTuPath;	
							CString strGranitPath;	
							strTuPath.Format("%stu_granit_p%d_c%d.ini",strDirectory,i+1,k+1);
							strGranitPath.Format("%sgranit_m%d_c%d.ini",strDirectory,i+1,k+1);

							sFTPFile.Format("%s/granit_m%d_c%d.ini",strFTPSite,i+1,k+1);														
							pFtpConn->PutFile(strGranitPath,sFTPFile);
							
							sFTPFile.Format("%s/tu_granit_p%d_c%d.ini",strFTPSite,i+1,k+1);						
							pFtpConn->PutFile(strTuPath,sFTPFile);
						}
						sFTPFile.Format("%s/stm_m%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}

		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 16)
		{			
			for(int j = 0; j < m_GPIOmArray.GetSize(); j++)
			{				
				if(m_GPIOmArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;
					CString strIec101mTuPath;				
					strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec101mPath.Format("%sGPIO%d.ini",strDirectory,i+1);
					
					if(m_GPIOmArray[j].SaveToFile(strIec101mPath)!=TRUE)	
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;					
					}
					if(m_GPIOmArray[j].SaveToTuFile(strIec101mTuPath)!=TRUE)
					{
						FileSaveErrorMessage(strIec101mTuPath);
						return FALSE;
					}
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);						
						pFtpConn->PutFile(strIec101mTuPath,sFTPFile);
						
						sFTPFile.Format("%s/GPIO%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}	
		
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 19)
		{
			for(int j = 0; j < m_ModbusTCPMArray.GetSize(); j++)
			{
				if(m_ModbusTCPMArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;
					CString strIec101mTuPath;				
					strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec101mPath.Format("%smodbus_tcp_m%d.ini",strDirectory,i+1);
					
					if(m_ModbusTCPMArray[j].SaveToFile(strIec101mPath)!=TRUE)		
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;					
					}
					if(m_ModbusTCPMArray[j].SaveToTuFile(strIec101mTuPath)!=TRUE)
					{
						FileSaveErrorMessage(strIec101mTuPath);
						return FALSE;
					}
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);						
						pFtpConn->PutFile(strIec101mTuPath,sFTPFile);
						/*if(!pFtpConn->PutFile(strIec101mTuPath,sFTPFile))
							return FALSE;*/
						sFTPFile.Format("%s/modbus_tcp_m%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 3)
		{
			for(int j = 0; j < m_Iec101mArray.GetSize(); j++)
			{
				if(m_Iec101mArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;
					CString strIec101mTuPath;				
					strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec101mPath.Format("%siec101m%d.ini",strDirectory,i+1);
					
					if(m_Iec101mArray[j].SaveToFile(strIec101mPath)!=TRUE)	
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;					
					}
					if(m_Iec101mArray[j].SaveToTuFile(strIec101mTuPath)!=TRUE)
					{
						FileSaveErrorMessage(strIec101mTuPath);
						return FALSE;
					}

					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);						
						pFtpConn->PutFile(strIec101mTuPath,sFTPFile);
						/*if(!pFtpConn->PutFile(strIec101mTuPath,sFTPFile))
							return FALSE;*/
						sFTPFile.Format("%s/iec101m%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}		
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 5)
		{
			for(int j = 0; j < m_Iec103mArray.GetSize(); j++)
			{
				if(m_Iec103mArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec103mPath;
					CString strIec103mTuPath;				
					strIec103mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec103mPath.Format("%siec103m%d.ini",strDirectory,i+1);
					
					if(m_Iec103mArray[j].SaveToFile(strIec103mPath)!=TRUE)	
					{
						FileSaveErrorMessage(strIec103mPath);
						return FALSE;					
					}
					if(m_Iec103mArray[j].SaveToTuFile(strIec103mTuPath)!=TRUE)
					{
						FileSaveErrorMessage(strIec103mTuPath);
						return FALSE;
					}
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);						
						pFtpConn->PutFile(strIec103mTuPath,sFTPFile);
						/*if(!pFtpConn->PutFile(strIec103mTuPath,sFTPFile))
							return FALSE;*/
						sFTPFile.Format("%s/iec103m%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec103mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 1)
		{
			for(int j = 0; j < m_ModbusMArray.GetSize(); j++)
			{
				if(m_ModbusMArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;
					CString strIec101mTuPath;				
					strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec101mPath.Format("%smodm%d.ini",strDirectory,i+1);

					if(m_ModbusMArray[j].SaveToFile(strIec101mPath)!=TRUE)		
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;					
					}
					
					if(m_ModbusMArray[j].SaveToTuFile(strIec101mTuPath)!=TRUE)
					{
						FileSaveErrorMessage(strIec101mTuPath);
						return FALSE;
					}
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);	
						pFtpConn->PutFile(strIec101mTuPath,sFTPFile);
						/*if(!pFtpConn->PutFile(strIec101mTuPath,sFTPFile))
							return FALSE;*/
						sFTPFile.Format("%s/modm%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}	
					}
					break;
				}
			}
		}		
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 2)
		{
			for(int j = 0; j < m_ModbusSArray.GetSize(); j++)
			{
				if(m_ModbusSArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;									
					strIec101mPath.Format("%smods%d.ini",strDirectory,i+1);
					if(m_ModbusSArray[j].SaveToFile(strIec101mPath)!=TRUE)	
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;	
					}
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{			
						CString sFTPFile;
						sFTPFile.Format("%s/mods%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}		
					}
					break;
				}
			}
		}		
		if((m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 8)
			||(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 14))
		{
			for(int j = 0; j < m_Iec104sArray.GetSize(); j++)
			{
				if(m_Iec104sArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;					
					strIec101mPath.Format("%siec104s%d.ini",strDirectory,i+1);

					if(m_Iec104sArray[j].SaveToFile(strIec101mPath)!=TRUE)		
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;		
					}
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{			
						CString sFTPFile;
						sFTPFile.Format("%s/iec104s%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}	
					}
					break;
				}
			}
		}		
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 4)
		{
			for(int j = 0; j < m_Iec101sArray.GetSize(); j++)
			{
				if(m_Iec101sArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;					
					strIec101mPath.Format("%siec101s%d.ini",strDirectory,i+1);

					if(m_Iec101sArray[j].SaveToFile(strIec101mPath)!=TRUE)					
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;	
					}	
					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{			
						CString sFTPFile;
						sFTPFile.Format("%s/iec101s%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 18)
		{
			for(int j = 0; j < m_MapboardArray.GetSize(); j++)
			{
				if(m_MapboardArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec101mPath;									
					strIec101mPath.Format("%sshit%d.ini",strDirectory,i+1);
					if(m_MapboardArray[j].SaveToFile(strIec101mPath)!=TRUE)					
					{
						FileSaveErrorMessage(strIec101mPath);
						return FALSE;	
					}	

					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{			
						CString sFTPFile;
						sFTPFile.Format("%s/shit%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec101mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}	
					}
					break;
				}
			}
		}
		//m_Iec104mArray
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 7)
		{
			for(int j = 0; j < m_Iec104mArray.GetSize(); j++)
			{
				if(m_Iec104mArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec104mPath;
					CString strIec104mTuPath;				
					strIec104mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec104mPath.Format("%siec104m%d.ini",strDirectory,i+1);
					
					if(m_Iec104mArray[j].SaveToFile(strIec104mPath)!=TRUE)					
					{
							FileSaveErrorMessage(strIec104mPath);
							return FALSE;	
					}					
					
					if(m_Iec104mArray[j].SaveToTuFile(strIec104mTuPath)!=TRUE)
					{
							FileSaveErrorMessage(strIec104mTuPath);
							return FALSE;	
					}

					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);						
						pFtpConn->PutFile(strIec104mTuPath,sFTPFile);
						/*if(!pFtpConn->PutFile(strIec104mTuPath,sFTPFile))
							return FALSE;*/
						sFTPFile.Format("%s/iec104m%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec104mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}
					}
					break;
				}
			}
		}
		//m_SPAmArray
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 17)
		{
			for(int j = 0; j < m_SPAmArray.GetSize(); j++)
			{
				if(m_SPAmArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIec104mPath;
					CString strIec104mTuPath;				
					strIec104mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIec104mPath.Format("%sSPAm%d.ini",strDirectory,i+1);
					
					if(m_SPAmArray[j].SaveToFile(strIec104mPath)!=TRUE)					
					{
							FileSaveErrorMessage(strIec104mPath);
							return FALSE;	
					}					
					
					if(m_SPAmArray[j].SaveToTuFile(strIec104mTuPath)!=TRUE)
					{
							FileSaveErrorMessage(strIec104mTuPath);
							return FALSE;	
					}

					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);						
						pFtpConn->PutFile(strIec104mTuPath,sFTPFile);
						/*if(!pFtpConn->PutFile(strIec104mTuPath,sFTPFile))
							return FALSE;*/
						sFTPFile.Format("%s/SPAm%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIec104mPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}	
					}
					break;
				}
			}
		}		
		//m_IecKorundmArray
		if(m_Main_Set.m_ProcessInfoArray[i].TYPE_PROTOKOL == 15)
		{
			for(int j = 0; j < m_IecKorundmArray.GetSize(); j++)
			{
				if(m_IecKorundmArray[j].m_nProcNum == i+1)
				{
					//CString str=dlg.GetPathName();
					CString strIecKorundmPath;
					CString strIec104mTuPath;				
					strIec104mTuPath.Format("%stu%d.ini",strDirectory,i+1);					
					strIecKorundmPath.Format("%sKorundm%d.ini",strDirectory,i+1);
					
					if(m_IecKorundmArray[j].SaveToFile(strIecKorundmPath)!=TRUE)					
					{
							FileSaveErrorMessage(strIecKorundmPath);
							return FALSE;	
					}					
					
					if(m_IecKorundmArray[j].SaveToTuFile(strIec104mTuPath)!=TRUE)
					{
							FileSaveErrorMessage(strIec104mTuPath);
							return FALSE;	
					}	

					if((!strFTPSite.IsEmpty())&&(pFtpConn!=NULL))
					{
						CString sFTPFile;
						sFTPFile.Format("%s/tu%d.ini",strFTPSite,i+1);												
						pFtpConn->PutFile(strIec104mTuPath,sFTPFile);
						
						sFTPFile.Format("%s/Korundm%d.ini",strFTPSite,i+1);						
						if(!pFtpConn->PutFile(strIecKorundmPath,sFTPFile))
						{
							FileSaveErrorMessage(sFTPFile);
							return FALSE;	
						}	
					}
					break;
				}
			}
		}
	}
	return TRUE;
}
void CKPLProject::RenumerateChannels(int nFrom,BOOL bDelete)
{
	if(bDelete)
	{
		for(int i = 0; i < m_Iec101mArray.GetSize(); i++)
		{
			if(m_Iec101mArray[i].m_nProcNum > nFrom)
			{							
				m_Iec101mArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_Iec103mArray.GetSize(); i++)
		{
			if(m_Iec103mArray[i].m_nProcNum > nFrom)
			{							
				m_Iec103mArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_Iec101sArray.GetSize(); i++)
		{
			if(m_Iec101sArray[i].m_nProcNum > nFrom)
			{							
				m_Iec101sArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_Iec104sArray.GetSize(); i++)
		{
			if(m_Iec104sArray[i].m_nProcNum > nFrom)
			{							
				m_Iec104sArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_ModbusMArray.GetSize(); i++)
		{
			if(m_ModbusMArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusMArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_ModbusSArray.GetSize(); i++)
		{
			if(m_ModbusSArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusSArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_Iec104mArray.GetSize(); i++)
		{
			if(m_Iec104mArray[i].m_nProcNum > nFrom)
			{							
				m_Iec104mArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_IecKorundmArray.GetSize(); i++)
		{
			if(m_IecKorundmArray[i].m_nProcNum > nFrom)
			{							
				m_IecKorundmArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_MapboardArray.GetSize(); i++)
		{
			if(m_MapboardArray[i].m_nProcNum > nFrom)
			{							
				m_MapboardArray[i].m_nProcNum--;
			}					
		}		
		for(int i = 0; i < m_SPAmArray.GetSize(); i++)
		{
			if(m_SPAmArray[i].m_nProcNum > nFrom)
			{							
				m_SPAmArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_GPIOmArray.GetSize(); i++)
		{
			if(m_GPIOmArray[i].m_nProcNum > nFrom)
			{							
				m_GPIOmArray[i].m_nProcNum--;
			}					
		}	
		for(int i = 0; i < m_ModbusTCPMArray.GetSize(); i++)
		{
			if(m_ModbusTCPMArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusTCPMArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_ModbusTCPMArray.GetSize(); i++)
		{
			if(m_ModbusTCPMArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusTCPMArray[i].m_nProcNum--;
			}					
		}
		for(int i = 0; i < m_STMArray.GetSize(); i++)
		{
			if(m_STMArray[i].m_nProcNum > nFrom)
			{							
				m_STMArray[i].m_nProcNum--;
			}					
		}
		
		for(int i = 0; i < m_Main_Set.m_IniObjectArray.GetSize(); i++)
		{
			if(m_Main_Set.m_IniObjectArray[i].NUMBER_DIRECT > nFrom)
			{							
				m_Main_Set.m_IniObjectArray[i].NUMBER_DIRECT--;
			}					
		}
		for(int i = 0; i < m_Retr.m_ManyRetrArray.GetSize(); i++)
		{
			if(m_Retr.m_ManyRetrArray[i].PATH_DIRECT > nFrom)
			{							
				m_Retr.m_ManyRetrArray[i].PATH_DIRECT--;
			}					
		}		
	}
	else//Add
	{
		for(int i = 0; i < m_Iec101mArray.GetSize(); i++)
		{
			if(m_Iec101mArray[i].m_nProcNum > nFrom)
			{							
				m_Iec101mArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_Iec104mArray.GetSize(); i++)
		{
			if(m_Iec104mArray[i].m_nProcNum > nFrom)
			{							
				m_Iec104mArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_Iec103mArray.GetSize(); i++)
		{
			if(m_Iec103mArray[i].m_nProcNum > nFrom)
			{							
				m_Iec103mArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_Iec101sArray.GetSize(); i++)
		{
			if(m_Iec101sArray[i].m_nProcNum > nFrom)
			{							
				m_Iec101sArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_Iec104sArray.GetSize(); i++)
		{
			if(m_Iec104sArray[i].m_nProcNum > nFrom)
			{							
				m_Iec104sArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_ModbusMArray.GetSize(); i++)
		{
			if(m_ModbusMArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusMArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_ModbusSArray.GetSize(); i++)
		{
			if(m_ModbusSArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusSArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_IecKorundmArray.GetSize(); i++)
		{
			if(m_IecKorundmArray[i].m_nProcNum > nFrom)
			{							
				m_IecKorundmArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_MapboardArray.GetSize(); i++)
		{
			if(m_MapboardArray[i].m_nProcNum > nFrom)
			{							
				m_MapboardArray[i].m_nProcNum++;
			}					
		}		
		for(int i = 0; i < m_GPIOmArray.GetSize(); i++)
		{
			if(m_GPIOmArray[i].m_nProcNum > nFrom)
			{							
				m_GPIOmArray[i].m_nProcNum++;
			}					
		}	
		for(int i = 0; i < m_SPAmArray.GetSize(); i++)
		{
			if(m_SPAmArray[i].m_nProcNum > nFrom)
			{							
				m_SPAmArray[i].m_nProcNum++;
			}					
		}	
		for(int i = 0; i < m_ModbusTCPMArray.GetSize(); i++)
		{
			if(m_ModbusTCPMArray[i].m_nProcNum > nFrom)
			{							
				m_ModbusTCPMArray[i].m_nProcNum++;
			}					
		}
		for(int i = 0; i < m_STMArray.GetSize(); i++)
		{
			if(m_STMArray[i].m_nProcNum > nFrom)
			{							
				m_STMArray[i].m_nProcNum++;
			}					
		}		
		for(int i = 0; i < m_Main_Set.m_IniObjectArray.GetSize(); i++)
		{
			if(m_Main_Set.m_IniObjectArray[i].NUMBER_DIRECT > nFrom)
			{							
				m_Main_Set.m_IniObjectArray[i].NUMBER_DIRECT++;
			}					
		}
		for(int i = 0; i < m_Retr.m_ManyRetrArray.GetSize(); i++)
		{
			if(m_Retr.m_ManyRetrArray[i].PATH_DIRECT > nFrom)
			{							
				m_Retr.m_ManyRetrArray[i].PATH_DIRECT++;				
			}					
		}
	}
}
BOOL CKPLProject::LoadProject(CString strDirectory)
{		
	CMain_Set tmp;
	CRetr		tmpRetr;
	CGPSTime	tmpGPSTime;
	CIec101mArray arrtmpIec101;
	CIec104mArray arrtmpIec104;
	CIec103mArray arrtmpIec103;
	CModbusMArray arrtmpModbusM;
	CModbusSArray arrtmpModbusS;
	CIec104sArray arrtmpIec104s;
	CIec101sArray arrtmpIec101s;	
	CIecKorundmArray arrtmpIecKorundm;	
	CGPIOmArray		arrtmpGPIOmArray;
	CMapboardArray	arrtmpMapboardArray;
	CSPAmArray		arrtmpSPAmArray;
	CModbusTCPMArray	arrtmpModbusTCPMArray;
	CSTMArray	arrtmpSTMArray;

	CString sFile="main_set.ini";

	sFile = strDirectory+sFile;

	if(tmp.LoadFromFile(sFile))
	{
		sFile = strDirectory+"retr.ini";
		if(!tmpRetr.LoadFromFile(sFile))
			return FALSE;

		if(m_nVersion > 13)
		{
			sFile.Replace("retr.ini","retrcalc.ini");
			if(tmpRetr.LoadFromCalcFile(sFile)!=TRUE)	
				return FALSE;		
		}

		BOOL bNewConfig = TRUE;
		sFile = strDirectory+"GPS_time3.ini";
		if(!tmpGPSTime.LoadFromFile(sFile))
		{
			bNewConfig = FALSE;
			AfxMessageBox("Не удалось загрузить настройки задачи синхронизации времени!\r\nВозможно у Вас старая версия настроек.\r\nЕсли это так, то никаких дополнительных действий не нужно.\r\nВ противном случае проверьте файл настроек синхронизации,он должен называться: GPS_time3.ini");
		}
		/*if(tmpGPSTime.SYNC_FROM == 4)
		{
			sFile = strDirectory+"ntpdate.sh";
			if(!tmpGPSTime.LoadFromScriptFile(sFile))
			{				
				AfxMessageBox("Не удалось загрузить ntpdate.sh!)");
			}
		}*/

		//protocol files load
		for(int i = 0; i < tmp.m_ProcessInfoArray.GetSize(); i++)
		{				
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 21)//stm
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;				
			
				strIec101mPath.Format("%sstm_m%d.ini",strDirectory,i+1);
				CSTM tmp2;
				tmp2.m_nProcNum = i+1;					
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					arrtmpSTMArray.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}	
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 16)//gpio
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%sGPIO%d.ini",strDirectory,i+1);
				CGPIOm tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					tmp2.LoadFromTuFile(strIec101mTuPath);
					arrtmpGPIOmArray.Add(tmp2);

				}
				else
				{														
					return FALSE;
				}
			}				
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 19)//ModbusTCPM
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%smodbus_tcp_m%d.ini",strDirectory,i+1);
				CModbusTCPM tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					tmp2.LoadFromTuFile(strIec101mTuPath);
					arrtmpModbusTCPMArray.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 3)//101m
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%siec101m%d.ini",strDirectory,i+1);
				CIec101m tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					tmp2.LoadFromTuFile(strIec101mTuPath);
					arrtmpIec101.Add(tmp2);

				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 17)//SPAm
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%sSPAm%d.ini",strDirectory,i+1);
				CSPAm tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					tmp2.LoadFromTuFile(strIec101mTuPath);
					arrtmpSPAmArray.Add(tmp2);

				}
				else
				{														
					return FALSE;
				}
			}			
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 15)//Korund
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				//CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				//strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%sKorundm%d.ini",strDirectory,i+1);
				CIecKorundm tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					arrtmpIecKorundm.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 18)//shit
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				//CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				//strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%sshit%d.ini",strDirectory,i+1);
				CMapboard tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					arrtmpMapboardArray.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 7)//104m
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%siec104m%d.ini",strDirectory,i+1);
				CIec104m tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					tmp2.LoadFromTuFile(strIec101mTuPath);
					arrtmpIec104.Add(tmp2);

				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 5)//103m
			{
				//CString str=dlg.GetPathName();
				CString strIec103mPath;
				CString strIec103mTuPath;
				//str.TrimRight("main_set.ini");
				strIec103mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec103mPath.Format("%siec103m%d.ini",strDirectory,i+1);
				CIec103m tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec103mPath))
				{					
					tmp2.LoadFromTuFile(strIec103mTuPath);
					arrtmpIec103.Add(tmp2);

				}
				else
				{														
					return FALSE;
				}
			}
			if((tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 8)
				||(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 14))//104s
			{				
				CString strIec101mPath;											
				strIec101mPath.Format("%siec104s%d.ini",strDirectory,i+1);
				CIec104s tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{								
					arrtmpIec104s.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 4)//101s
			{				
				CString strIec101mPath;											
				strIec101mPath.Format("%siec101s%d.ini",strDirectory,i+1);
				CIec101s tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{								
					arrtmpIec101s.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}
			//
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 1)//modbus m
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;
				CString strIec101mTuPath;
				//str.TrimRight("main_set.ini");
				strIec101mTuPath.Format("%stu%d.ini",strDirectory,i+1);
				strIec101mPath.Format("%smodm%d.ini",strDirectory,i+1);
				CModbusM tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{					
					tmp2.LoadFromTuFile(strIec101mTuPath);
					arrtmpModbusM.Add(tmp2);

				}
				else
				{														
					return FALSE;
				}
			}
			if(tmp.m_ProcessInfoArray[i].TYPE_PROTOKOL == 2)//modbus s
			{
				//CString str=dlg.GetPathName();
				CString strIec101mPath;				
				strIec101mPath.Format("%smods%d.ini",strDirectory,i+1);
				CModbusS tmp2;
				tmp2.m_nProcNum = i+1;
				if(tmp2.LoadFromFile(strIec101mPath))
				{							
					arrtmpModbusS.Add(tmp2);
				}
				else
				{														
					return FALSE;
				}
			}
		}
		//alles gut!
		/*if(bNewConfig == FALSE)
		{
			m_Main_Set.m_ProcessInfoArray.InsertAt(
		}*/
		m_Main_Set = tmp;//.LoadFromFile(sFile);
		m_Retr = tmpRetr;
		m_GPSTime = tmpGPSTime;
		if(m_Retr.m_RECIVE_DIRECT.GetSize()!= m_Main_Set.m_ProcessInfoArray.GetSize())
			m_Retr.m_RECIVE_DIRECT.SetSize(m_Main_Set.m_ProcessInfoArray.GetSize());
		m_Iec101mArray.Copy(arrtmpIec101);
		m_Iec104mArray.Copy(arrtmpIec104);
		m_Iec103mArray.Copy(arrtmpIec103);
		m_ModbusMArray.Copy(arrtmpModbusM);
		m_ModbusSArray.Copy(arrtmpModbusS);
		m_Iec104sArray.Copy(arrtmpIec104s);
		m_Iec101sArray.Copy(arrtmpIec101s);
		m_IecKorundmArray.Copy(arrtmpIecKorundm);
		m_GPIOmArray.Copy(arrtmpGPIOmArray);		
		m_MapboardArray.Copy(arrtmpMapboardArray);
		m_SPAmArray.Copy(arrtmpSPAmArray);
		m_ModbusTCPMArray.Copy(arrtmpModbusTCPMArray);
		m_STMArray.Copy(arrtmpSTMArray);		
				
		for(int i = 0; i < m_Main_Set.m_Ports.GetSize(); i++)
		{
			if((i == m_GPSTime.PORT)&&(m_GPSTime.SYNC_FROM > 1))
				m_Main_Set.m_Ports[i] = PORT_BUSY;
			for(int j = 0; j < m_Iec101mArray.GetSize(); j++)
			{
				if((i == m_Iec101mArray[j].PORT)||(i == m_Iec101mArray[j].RES_PORT))
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}
			for(int j = 0; j < m_Iec103mArray.GetSize(); j++)
			{
				if(i == m_Iec103mArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}
			for(int j = 0; j < m_ModbusMArray.GetSize(); j++)
			{
				if(i == m_ModbusMArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}
			for(int j = 0; j < m_ModbusSArray.GetSize(); j++)
			{
				if(i == m_ModbusSArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}
			for(int j = 0; j < m_Iec101sArray.GetSize(); j++)
			{
				if((i == m_Iec101sArray[j].PORT)||(i == m_Iec101sArray[j].RES_PORT))
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}
			for(int j = 0; j < m_IecKorundmArray.GetSize(); j++)
			{
				if(i == m_IecKorundmArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}
			for(int j = 0; j < m_MapboardArray.GetSize(); j++)
			{
				if(i == m_MapboardArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}			
			for(int j = 0; j < m_SPAmArray.GetSize(); j++)
			{
				if(i == m_SPAmArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}		
			for(int j = 0; j < m_STMArray.GetSize(); j++)
			{
				if(i == m_STMArray[j].PORT)
					m_Main_Set.m_Ports[i] = PORT_BUSY;
			}								
		}		
	}
	else
		return FALSE;
	
	return TRUE;
}
BOOL LoadProjectFTP(CString strFTPSite,CFtpConnection* pFtpConn = NULL)
{
	return TRUE;
}