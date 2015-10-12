#pragma once
#include "kplversion.h"

struct TUGranit: public CKPLVersion
{	
	int N_GROUP_2B;
	int N_KP;
	int PACKET_TYPE;
	int N_OBJECT_ON;
	int N_OBJECT_OFF;
	int AFB_ON;
	int AFB_OFF;
	CString strCOMMENT;

	TUGranit()
	{	
		N_GROUP_2B=64;
		N_KP=1;		
		PACKET_TYPE=1;		
		N_OBJECT_ON=1;	
		N_OBJECT_OFF=1;
		AFB_ON=0;
		AFB_OFF=0;
	}	
	TUGranit(const TUGranit& aTU101)
	{		
		N_GROUP_2B=aTU101.N_GROUP_2B;
		N_KP=aTU101.N_KP;		
		PACKET_TYPE=aTU101.PACKET_TYPE;
		N_OBJECT_ON=aTU101.N_OBJECT_ON;
		N_OBJECT_OFF=aTU101.N_OBJECT_OFF;
		AFB_ON=aTU101.AFB_ON;
		AFB_OFF=aTU101.AFB_OFF;	
		strCOMMENT=aTU101.strCOMMENT;	
	}
	void operator = (const TUGranit& aTU101)
	{
		N_GROUP_2B=aTU101.N_GROUP_2B;
		N_KP=aTU101.N_KP;		
		PACKET_TYPE=aTU101.PACKET_TYPE;
		N_OBJECT_ON=aTU101.N_OBJECT_ON;
		N_OBJECT_OFF=aTU101.N_OBJECT_OFF;
		AFB_ON=aTU101.AFB_ON;
		AFB_OFF=aTU101.AFB_OFF;	
		strCOMMENT=aTU101.strCOMMENT;	
	}
};
typedef CArray<TUGranit,TUGranit> CTUGranitArray;

struct IndividualStructureGranit: public CKPLVersion
{	
	int N_KP;//=1- ����� ��, 0 - 256
	int PACKET_TYPE;/*=4 ��� ���������� ������ � ������� 4- ��� �� �� ��� 
	����� ����� ����� 4 ��� ����� ���� ������ �����? *
	��� ��� � ����� ������ ��� 4� ������  � ������������ ���*/
	int AFB;//=2 � ����� ��������������� �����, 0 -16
	int INFO_TYPE;//=2 � ��� ���������� 2- �� 3, 6, 7-��� 4 -���
	int GROUP_NUMBER;//=0- ����� ������ , 0-16
	int NUMBER;//=64 ���������� ������ ������ �� ������� 64-�� , 16- ��� ��� ���
	int ADDRESS_PMZ;//=0 ����� � ��� � �������� ����������� �������
	CString strCOMMENT;//granit � ���� ����������� � �����

	IndividualStructureGranit()
	{	
		N_KP=1;
		PACKET_TYPE=4;
		AFB=0;		
		INFO_TYPE=2;	
		GROUP_NUMBER=0;
		NUMBER=64;
		ADDRESS_PMZ=0;
	}	
	IndividualStructureGranit(const IndividualStructureGranit& aIndividualStructure101)
	{		
		N_KP=aIndividualStructure101.N_KP;
		PACKET_TYPE=aIndividualStructure101.PACKET_TYPE;		
		AFB=aIndividualStructure101.AFB;
		INFO_TYPE=aIndividualStructure101.INFO_TYPE;
		GROUP_NUMBER=aIndividualStructure101.GROUP_NUMBER;
		NUMBER=aIndividualStructure101.NUMBER;
		ADDRESS_PMZ=aIndividualStructure101.ADDRESS_PMZ;
		strCOMMENT=aIndividualStructure101.strCOMMENT;	
	}
	void operator = (const IndividualStructureGranit& aIndividualStructure101)
	{
		N_KP=aIndividualStructure101.N_KP;
		PACKET_TYPE=aIndividualStructure101.PACKET_TYPE;		
		AFB=aIndividualStructure101.AFB;
		INFO_TYPE=aIndividualStructure101.INFO_TYPE;
		GROUP_NUMBER=aIndividualStructure101.GROUP_NUMBER;
		NUMBER=aIndividualStructure101.NUMBER;
		ADDRESS_PMZ=aIndividualStructure101.ADDRESS_PMZ;
		strCOMMENT=aIndividualStructure101.strCOMMENT;	
	}
};
typedef CArray<IndividualStructureGranit,IndividualStructureGranit> CIndividualStructureGranitArray;

struct �Granit: public CKPLVersion
{		
	int NUMBER_NO_ANSWER;/*=3 � ���������� �� ������� ��� �������� ��������. ����� ���������� � ������� ����� ��� � ������ �����-�� �������� �������� ����. ����� ������������?  
	���������� ��������, ��� ������ �� ��, ����� �������� ������������ ������������� ����� ������.*/
	int TYPE;/*=1 ��� ��������� 1- ������ �� ������� 2 - ��� ������� ����� �������������*/
	int LOG_ENABLE;/*=1 � ����� ��� ������ 0 - ��� 1- ��*/
	int ALARM_ENABLE;/*=1 � ����� ��� ������ 0 - ��� 1-��*/
	int SERVICE;/*=1 - ��������� ���� 0 � ��� 1 � �������� ��� ������ � �������*/
	int MEANDER_VALUE;/*=21765 � �������� ������� ��� ������ 0�55 05 hex (12 ��� 010101010101) ��� 05 - ������� ���� 55 - ������� ���� ��� ������������ ������� � ����� (����� ���� ������� ������ ��������)*/
	int INVERT_REQUEST;/*=0 �������������� ������� ������� 0- ��� , 1- ��*/
	int INVERT_RESPONSE;/*=0 �������������� �������� ������� 0- ��� , 1- ��*/
	int C_IC_NA_1_PERIOD;/*=0 ������ ����� �������� ���������� ���� ������ �������� ���� ������, ���*/
	int C_IC_TS_ENABLE;/*=1 ����� ������ �� 0- ��� , 1- ��*/
	int C_IC_TIT_ENABLE;/*=1 ����� ������ �� 0- ��� , 1- ��*/
	int C_IC_TII_ENABLE;/*=0 (������) ����� ������ ��� 0- ��� , 1- ��*/
	int NO_LINK_PERIOD;/*=60 - ������ ���������� �� ����� �������� ������������ ���� ���� ����� �������������, ���*/
	int TU_RESPONSE_PERIOD;/*=30 - ������ �������� ������������� ������� �� ����� �������� ����� ���������� ���� �� �� ������� , ���*/
	int REQ_RESPONSE_PERIOD;/*=5 - ������ �������� ������ ����� �������, ���*/
	int MEANDER_PERIOD;/*=1500 - ������ ������� �������� , ���� ���*/
	int ADD_MEANDER_BEFORE_REQ;/*=0 - ���������� ������� ����� �������� ������� 0- ��� 1 -��*/
	int SEND_CONFIRM;/*=1 - �������� ������������� ������ ������ ��, ��, ��� 0- ��� 1- ��*/
	int IC_ON_MEANDER;/*=1 - �������� ��������� ������ ������ ����� ��������� ������� �� �� 0- ��� 1 -��*/

	CIndividualStructureGranitArray m_IndividualStructureGranitArray;
	CTUGranitArray	m_TUGranitArray;

	�Granit()
	{			
		NUMBER_NO_ANSWER=3;
		TYPE=1;		
		LOG_ENABLE=1;
		ALARM_ENABLE=1;
		SERVICE=1;
		MEANDER_VALUE=21765;
		INVERT_REQUEST=0;
		INVERT_RESPONSE=0;
		C_IC_NA_1_PERIOD=0;
		C_IC_TS_ENABLE=1;
		C_IC_TIT_ENABLE=1;
		C_IC_TII_ENABLE=0;
		NO_LINK_PERIOD=60;
		TU_RESPONSE_PERIOD=30;
		REQ_RESPONSE_PERIOD=5;
		MEANDER_PERIOD=1500;
		ADD_MEANDER_BEFORE_REQ=0;
		SEND_CONFIRM=1;
		IC_ON_MEANDER=1;
	}
	~�Granit()
	{		
		NUMBER_NO_ANSWER=3;
		TYPE=1;		
		LOG_ENABLE=1;
		ALARM_ENABLE=1;
		SERVICE=1;
		MEANDER_VALUE=21765;
		INVERT_REQUEST=0;
		INVERT_RESPONSE=0;
		C_IC_NA_1_PERIOD=0;
		C_IC_TS_ENABLE=1;
		C_IC_TIT_ENABLE=1;
		C_IC_TII_ENABLE=0;
		NO_LINK_PERIOD=60;
		TU_RESPONSE_PERIOD=30;
		REQ_RESPONSE_PERIOD=5;
		MEANDER_PERIOD=1500;
		ADD_MEANDER_BEFORE_REQ=0;
		SEND_CONFIRM=1;
		IC_ON_MEANDER=1;
		m_IndividualStructureGranitArray.RemoveAll();
		m_TUGranitArray.RemoveAll();
	}
	�Granit(const �Granit& aIndividualStructure101)
	{		
		NUMBER_NO_ANSWER=aIndividualStructure101.NUMBER_NO_ANSWER;//3;
		TYPE=aIndividualStructure101.TYPE;//1;		
		LOG_ENABLE=aIndividualStructure101.LOG_ENABLE;//1;
		ALARM_ENABLE=aIndividualStructure101.ALARM_ENABLE;//1;
		SERVICE=aIndividualStructure101.SERVICE;//1;
		MEANDER_VALUE=aIndividualStructure101.MEANDER_VALUE;//21765;
		INVERT_REQUEST=aIndividualStructure101.INVERT_REQUEST;//0;
		INVERT_RESPONSE=aIndividualStructure101.INVERT_RESPONSE;//0;
		C_IC_NA_1_PERIOD=aIndividualStructure101.C_IC_NA_1_PERIOD;//0;
		C_IC_TS_ENABLE=aIndividualStructure101.C_IC_TS_ENABLE;//1;
		C_IC_TIT_ENABLE=aIndividualStructure101.C_IC_TIT_ENABLE;//1;
		C_IC_TII_ENABLE=aIndividualStructure101.C_IC_TII_ENABLE;//0;
		NO_LINK_PERIOD=aIndividualStructure101.NO_LINK_PERIOD;//60;
		TU_RESPONSE_PERIOD=aIndividualStructure101.TU_RESPONSE_PERIOD;//30;
		REQ_RESPONSE_PERIOD=aIndividualStructure101.REQ_RESPONSE_PERIOD;//5;
		MEANDER_PERIOD=aIndividualStructure101.MEANDER_PERIOD;//1500;
		ADD_MEANDER_BEFORE_REQ=aIndividualStructure101.ADD_MEANDER_BEFORE_REQ;//0;
		SEND_CONFIRM=aIndividualStructure101.SEND_CONFIRM;//1;
		IC_ON_MEANDER=aIndividualStructure101.IC_ON_MEANDER;//1;
		m_IndividualStructureGranitArray.Copy(aIndividualStructure101.m_IndividualStructureGranitArray);
		m_TUGranitArray.Copy(aIndividualStructure101.m_TUGranitArray);
	}
	void operator = (const �Granit& aIndividualStructure101)
	{
		NUMBER_NO_ANSWER=aIndividualStructure101.NUMBER_NO_ANSWER;//3;
		TYPE=aIndividualStructure101.TYPE;//1;		
		LOG_ENABLE=aIndividualStructure101.LOG_ENABLE;//1;
		ALARM_ENABLE=aIndividualStructure101.ALARM_ENABLE;//1;
		SERVICE=aIndividualStructure101.SERVICE;//1;
		MEANDER_VALUE=aIndividualStructure101.MEANDER_VALUE;//21765;
		INVERT_REQUEST=aIndividualStructure101.INVERT_REQUEST;//0;
		INVERT_RESPONSE=aIndividualStructure101.INVERT_RESPONSE;//0;
		C_IC_NA_1_PERIOD=aIndividualStructure101.C_IC_NA_1_PERIOD;//0;
		C_IC_TS_ENABLE=aIndividualStructure101.C_IC_TS_ENABLE;//1;
		C_IC_TIT_ENABLE=aIndividualStructure101.C_IC_TIT_ENABLE;//1;
		C_IC_TII_ENABLE=aIndividualStructure101.C_IC_TII_ENABLE;//0;
		NO_LINK_PERIOD=aIndividualStructure101.NO_LINK_PERIOD;//60;
		TU_RESPONSE_PERIOD=aIndividualStructure101.TU_RESPONSE_PERIOD;//30;
		REQ_RESPONSE_PERIOD=aIndividualStructure101.REQ_RESPONSE_PERIOD;//5;
		MEANDER_PERIOD=aIndividualStructure101.MEANDER_PERIOD;//1500;
		ADD_MEANDER_BEFORE_REQ=aIndividualStructure101.ADD_MEANDER_BEFORE_REQ;//0;
		SEND_CONFIRM=aIndividualStructure101.SEND_CONFIRM;//1;
		IC_ON_MEANDER=aIndividualStructure101.IC_ON_MEANDER;//1;
		m_IndividualStructureGranitArray.Copy(aIndividualStructure101.m_IndividualStructureGranitArray);
		m_TUGranitArray.Copy(aIndividualStructure101.m_TUGranitArray);
	}
};

struct IndividualStructureSTM: public CKPLVersion
{		
	int PROTOCOL_TYPE;/*=1 - ��� ��������� ��� ������� ������
					1- ������ (������� ���� �������� granit_mN_cX.ini � ���� �� tu_granit_pN_cX.ini)
					2 - ���� (������� ���� �������� aist_mN_cX.ini )*/
	int CHANNEL;/* � ����� ������ �� 0 �� 3*/
	int SPEED;/*
				1 - 600 ���
				2 - 300 ���
				3 - 200 ���
				6 - 100 ���*/
	CString strCOMMENT;//granit � ���� ����������� � �����

	�Granit m_Granit;

	IndividualStructureSTM()
	{			
		PROTOCOL_TYPE=1;
		CHANNEL=0;		
		SPEED=1;			
	}
	IndividualStructureSTM(const IndividualStructureSTM& aIndividualStructure101)
	{		
		PROTOCOL_TYPE=aIndividualStructure101.PROTOCOL_TYPE;
		CHANNEL=aIndividualStructure101.CHANNEL;		
		SPEED=aIndividualStructure101.SPEED;		
		m_Granit = aIndividualStructure101.m_Granit;
		strCOMMENT=aIndividualStructure101.strCOMMENT;	
	}
	void operator = (const IndividualStructureSTM& aIndividualStructure101)
	{
		PROTOCOL_TYPE=aIndividualStructure101.PROTOCOL_TYPE;
		CHANNEL=aIndividualStructure101.CHANNEL;		
		SPEED=aIndividualStructure101.SPEED;		
		m_Granit = aIndividualStructure101.m_Granit;
		strCOMMENT=aIndividualStructure101.strCOMMENT;	
	}
};
typedef CArray<IndividualStructureSTM,IndividualStructureSTM> CIndividualStructureSTMArray;

class CSTM;
typedef CArray<CSTM,CSTM> CSTMArray;
class  CSTM:
	public CKPLVersion
{
public:
	CSTM(void);
	~CSTM(void);

	int m_nProcNum;
	int PORT;
	int BAUDRATE;
	int STOPBITS;
	int PARITY;
	int BYTETIME;
	int WAITRESP;
	int NEXTMESSAGE;
	int AMOUNTBYTE;
	int CONTROLPOTOK;
	int NUMBER_NO_ANSWER;
	int TYPE;
	int SERVICE;

	CSTM(const CSTM& aIec101m)
	{
		m_nProcNum=aIec101m.m_nProcNum;
		PORT=aIec101m.PORT;
		BAUDRATE=aIec101m.BAUDRATE;
		STOPBITS=aIec101m.STOPBITS;
		PARITY=aIec101m.PARITY;
		BYTETIME=aIec101m.BYTETIME;
		WAITRESP=aIec101m.WAITRESP;
		NEXTMESSAGE=aIec101m.NEXTMESSAGE;
		AMOUNTBYTE=aIec101m.AMOUNTBYTE;
		CONTROLPOTOK=aIec101m.CONTROLPOTOK;
		NUMBER_NO_ANSWER=aIec101m.NUMBER_NO_ANSWER;
		
		TYPE=aIec101m.TYPE;
		SERVICE=aIec101m.SERVICE;
		
		m_IndividualStructureSTMArray.Copy(aIec101m.m_IndividualStructureSTMArray);		
		
	}
	void operator = (const CSTM& aIec101m)
	{
		m_nProcNum=aIec101m.m_nProcNum;
		PORT=aIec101m.PORT;
		BAUDRATE=aIec101m.BAUDRATE;
		STOPBITS=aIec101m.STOPBITS;
		PARITY=aIec101m.PARITY;
		BYTETIME=aIec101m.BYTETIME;
		WAITRESP=aIec101m.WAITRESP;
		NEXTMESSAGE=aIec101m.NEXTMESSAGE;
		AMOUNTBYTE=aIec101m.AMOUNTBYTE;
		CONTROLPOTOK=aIec101m.CONTROLPOTOK;
		NUMBER_NO_ANSWER=aIec101m.NUMBER_NO_ANSWER;
		
		TYPE=aIec101m.TYPE;
		SERVICE=aIec101m.SERVICE;
		
		m_IndividualStructureSTMArray.Copy(aIec101m.m_IndividualStructureSTMArray);
	}
	
	CIndividualStructureSTMArray m_IndividualStructureSTMArray;	

	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	
	//BOOL SaveToTuFile(CString strFile);
	//BOOL LoadFromTuFile(CString strFile);
};

