#pragma once

#include "KPLVersion.h"
#include "Tu.h"

struct IndividualStructureSPA: public CKPLVersion
{
	int SLAVE_ADDRESS;//=5 - значение LINK адреса устройства 1-999
	int CHANNEL_NUM;//=1 - номер канала 1-999
	int TYPE_ID;//=30 - тип функции. —огласно протокола IEC870-5-101 дл€ записи в этом типе в ѕћ«
	int	DATA_CAT;//=1 - категори€ данных
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
	int DATA_NUM;//=1- номер данных 1-65535
	int ADDRESS_PMZ;//=0 - стартовый адрес в карте пам€ти текущего процесса дл€ данного информационных объектов.
	int TYPE_STATUS;//=0;-тип внутреннего статуса, 0-нет, 2-есть.
	int MASKA_STATUS;//=0;- маска дл€ внутреннего статуса (выполн€етс€ логическое и значени€ в регистре с маской и в случаи нул€ значение будет считатьс€ достоверным)
	int ADRES_STATUS;//=0; - адрес в ѕћ« где лежит значение статуса.
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
	PORT=0 - указываетс€ номер —ќћ порта дл€ данного направлени€, 0-ttyS0, 1-ttyS1,...N-ttySN
BAUDRATE = 9600 - скорость бод. (9600 по умолчанию согласно протокола SPA)
STOPBITS=1 - указываетс€ количество стоп бит 1или 2 (1по умолчанию согласно протокола SPA)
PARITY=1 - чЄтность 0-нет, 1-чет, 2-нечет (1по умолчанию согласно протокола SPA)
BYTETIME=10 - врем€ отслеживани€ паузы между байтами посылки 1квант =10мс.
ƒиапазон значений от 1 до 3000 квантов
WAITRESP=100 - врем€ ожидани€ ответа в квантах, 1квант =10мс.
ƒиапазон значений от 1 до 3000 квантов
NEXTMESSAGE=10 - врем€ через которое посылаетс€ следующий запрос, после приЄма ответа в квантах, 1 квант=10мс ƒиапазон значений от1 до 3000 квантов
AMOUNTBYTE=7 - количество бит в байте -5,6 ,7, 8 ( 7 по умолчанию согласно протокола SPA)
FLOWCONTROLL=0 - контроль потока 0- нет, 1-аппаратный, 2- программный
NUMBER_NO_ANSWER=1 - количество не ответов устройства после которого устанавливаем флаг недостоверности в группе информационных объектов, принадлежащих данному устройству.
ƒиапазон установки - от 0 до 50
NUMBER_OF_DEVICES=1- количество устройств на линии
NUMBER_OF_INDIVIDUAL_STRUCTURES=2 количество структур описани€ данных
SERVICE=0 сервисное поле ( 0- значение по умолчанию, 1- отобразить процесс работы ѕќ в консоль)
RES_PORT=0 - значение резервного порта

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
