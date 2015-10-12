#pragma once

#include "KPLVersion.h"
#include "Tu.h"

struct IndividualStructureSPA: public CKPLVersion
{
	int SLAVE_ADDRESS;//=5 - �������� LINK ������ ���������� 1-999
	int CHANNEL_NUM;//=1 - ����� ������ 1-999
	int TYPE_ID;//=30 - ��� �������. �������� ��������� IEC870-5-101 ��� ������ � ���� ���� � ���
	int	DATA_CAT;//=1 - ��������� ������
	/*1- I-input data
	2-O-output data
	3-S-setting value
	4-V-variable
	5-M-memory data
	6-C-condition of slave status
	7-F-slave identification
	8-T-time
	9-D-date and time
	10-Llast events
	11-B -backup events
	12-A-alarms valid*/
	int DATA_NUM;//=1- ����� ������ 1-65535
	int ADDRESS_PMZ;//=0 - ��������� ����� � ����� ������ �������� �������� ��� ������� �������������� ��������.
	int TYPE_STATUS;//=0;-��� ����������� �������, 0-���, 2-����.
	int MASKA_STATUS;//=0;- ����� ��� ����������� ������� (����������� ���������� � �������� � �������� � ������ � � ������ ���� �������� ����� ��������� �����������)
	int ADRES_STATUS;//=0; - ����� � ��� ��� ����� �������� �������.
	CString strCOMMENT;

	IndividualStructureSPA()
	{
		SLAVE_ADDRESS=1;
		CHANNEL_NUM=1;
		TYPE_ID=1;
		DATA_CAT=1;
		DATA_NUM=1;
		ADDRESS_PMZ=0;
		TYPE_STATUS=0;
		MASKA_STATUS=0;
		ADRES_STATUS=0;

		strCOMMENT=" ";
	}
	IndividualStructureSPA(const IndividualStructureSPA& aIndividualStructureSPA)
	{
		SLAVE_ADDRESS=aIndividualStructureSPA.SLAVE_ADDRESS;
		CHANNEL_NUM=aIndividualStructureSPA.CHANNEL_NUM;			
		TYPE_ID=aIndividualStructureSPA.TYPE_ID;		
		DATA_CAT=aIndividualStructureSPA.DATA_CAT;		
		DATA_NUM=aIndividualStructureSPA.DATA_NUM;		
		ADDRESS_PMZ=aIndividualStructureSPA.ADDRESS_PMZ;		
		TYPE_STATUS=aIndividualStructureSPA.TYPE_STATUS;
		MASKA_STATUS=aIndividualStructureSPA.MASKA_STATUS;		
		ADRES_STATUS=aIndividualStructureSPA.ADRES_STATUS;				
		strCOMMENT=aIndividualStructureSPA.strCOMMENT;
	}
	void operator = (const IndividualStructureSPA& aIndividualStructureSPA)
	{	
		SLAVE_ADDRESS=aIndividualStructureSPA.SLAVE_ADDRESS;
		CHANNEL_NUM=aIndividualStructureSPA.CHANNEL_NUM;			
		TYPE_ID=aIndividualStructureSPA.TYPE_ID;		
		DATA_CAT=aIndividualStructureSPA.DATA_CAT;		
		DATA_NUM=aIndividualStructureSPA.DATA_NUM;		
		ADDRESS_PMZ=aIndividualStructureSPA.ADDRESS_PMZ;		
		TYPE_STATUS=aIndividualStructureSPA.TYPE_STATUS;
		MASKA_STATUS=aIndividualStructureSPA.MASKA_STATUS;		
		ADRES_STATUS=aIndividualStructureSPA.ADRES_STATUS;	
		strCOMMENT=aIndividualStructureSPA.strCOMMENT;
	}
};

typedef CArray<IndividualStructureSPA,IndividualStructureSPA> CIndividualStructureSPAArray;

class CSPAm;
typedef CArray<CSPAm,CSPAm> CSPAmArray;

class CSPAm:public CKPLVersion
{
public:

	int m_nProcNum;

	/*
	PORT=0 - ����������� ����� ��� ����� ��� ������� �����������, 0-ttyS0, 1-ttyS1,...N-ttySN
BAUDRATE = 9600 - �������� ���. (9600 �� ��������� �������� ��������� SPA)
STOPBITS=1 - ����������� ���������� ���� ��� 1��� 2 (1�� ��������� �������� ��������� SPA)
PARITY=1 - �������� 0-���, 1-���, 2-����� (1�� ��������� �������� ��������� SPA)
BYTETIME=10 - ����� ������������ ����� ����� ������� ������� 1����� =10��.
�������� �������� �� 1 �� 3000 �������
WAITRESP=100 - ����� �������� ������ � �������, 1����� =10��.
�������� �������� �� 1 �� 3000 �������
NEXTMESSAGE=10 - ����� ����� ������� ���������� ��������� ������, ����� ����� ������ � �������, 1 �����=10�� �������� �������� ��1 �� 3000 �������
AMOUNTBYTE=7 - ���������� ��� � ����� -5,6 ,7, 8 ( 7 �� ��������� �������� ��������� SPA)
FLOWCONTROLL=0 - �������� ������ 0- ���, 1-����������, 2- �����������
NUMBER_NO_ANSWER=1 - ���������� �� ������� ���������� ����� �������� ������������� ���� ��������������� � ������ �������������� ��������, ������������� ������� ����������.
�������� ��������� - �� 0 �� 50
NUMBER_OF_DEVICES=1- ���������� ��������� �� �����
NUMBER_OF_INDIVIDUAL_STRUCTURES=2 ���������� �������� �������� ������
SERVICE=0 ��������� ���� ( 0- �������� �� ���������, 1- ���������� ������� ������ �� � �������)
RES_PORT=0 - �������� ���������� �����

	*/
	int PORT;
	int BAUDRATE;
	int STOPBITS;
	int PARITY;
	int BYTETIME;
	int WAITRESP;
	int NEXTMESSAGE;
	int AMOUNTBYTE;
	int FLOWCONTROLL;
	int NUMBER_NO_ANSWER;
	int NUMBER_OF_DEVICES;
	//NUMBER_OF_INDIVIDUAL_STRUCTURES
	int SERVICE;	
	int RES_PORT;
	
	CSPAm(const CSPAm& aSPAm)
	{
		m_nProcNum=aSPAm.m_nProcNum;
		PORT=aSPAm.PORT;
		BAUDRATE=aSPAm.BAUDRATE;
		STOPBITS=aSPAm.STOPBITS;
		PARITY=aSPAm.PARITY;
		BYTETIME=aSPAm.BYTETIME;
		WAITRESP=aSPAm.WAITRESP;
		NEXTMESSAGE=aSPAm.NEXTMESSAGE;
		AMOUNTBYTE=aSPAm.AMOUNTBYTE;
		FLOWCONTROLL=aSPAm.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aSPAm.NUMBER_NO_ANSWER;		
		NUMBER_OF_DEVICES=aSPAm.NUMBER_OF_DEVICES;		
		SERVICE=aSPAm.SERVICE;
		RES_PORT=aSPAm.RES_PORT;
		
		m_IndividualStructureSPAArray.RemoveAll();
		for(int i = 0; i < aSPAm.m_IndividualStructureSPAArray.GetSize(); i++)
			m_IndividualStructureSPAArray.Add(aSPAm.m_IndividualStructureSPAArray[i]);
		m_TuArray.Copy(aSPAm.m_TuArray);
	}
	void operator = (const CSPAm& aSPAm)
	{
		m_nProcNum=aSPAm.m_nProcNum;
		PORT=aSPAm.PORT;
		BAUDRATE=aSPAm.BAUDRATE;
		STOPBITS=aSPAm.STOPBITS;
		PARITY=aSPAm.PARITY;
		BYTETIME=aSPAm.BYTETIME;
		WAITRESP=aSPAm.WAITRESP;
		NEXTMESSAGE=aSPAm.NEXTMESSAGE;
		AMOUNTBYTE=aSPAm.AMOUNTBYTE;
		FLOWCONTROLL=aSPAm.FLOWCONTROLL;
		NUMBER_NO_ANSWER=aSPAm.NUMBER_NO_ANSWER;		
		NUMBER_OF_DEVICES=aSPAm.NUMBER_OF_DEVICES;		
		SERVICE=aSPAm.SERVICE;
		RES_PORT=aSPAm.RES_PORT;
		
		m_IndividualStructureSPAArray.RemoveAll();
		for(int i = 0; i < aSPAm.m_IndividualStructureSPAArray.GetSize(); i++)
			m_IndividualStructureSPAArray.Add(aSPAm.m_IndividualStructureSPAArray[i]);
		m_TuArray.Copy(aSPAm.m_TuArray);
	}

	CIndividualStructureSPAArray m_IndividualStructureSPAArray;
	CTuArray	m_TuArray;

	CSPAm(void);
	~CSPAm(void);
	BOOL SaveToFile(CString strFile);
	BOOL LoadFromFile(CString strFile);
	BOOL SaveToTuFile(CString strFile);
	BOOL LoadFromTuFile(CString strFile);
};
