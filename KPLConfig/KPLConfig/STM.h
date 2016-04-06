#pragma once
#include "kplversion.h"

#define PROTOCOL_TYPE_GRANIT	1
#define PROTOCOL_TYPE_AIST		2

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
	int N_KP;//=1- номер КП, 0 - 256
	int PACKET_TYPE;/*=4 тип ожидаемого пакета с данными 4- для ТС ТИ ТИИ 
	Какие кроме цифры 4 еще могут быть заданы здесь? *
	Для все х типов данных тут 4е других  в документации нет*/
	int AFB;//=2 — адрес функционального блока, 0 -16
	int INFO_TYPE;//=2 — тип информации 2- ТС 3, 6, 7-ТИТ 4 -ТИИ
	int GROUP_NUMBER;//=0- номер группы , 0-16
	int NUMBER;//=64 количество данных взятых из посылки 64-ТС , 16- ТИТ или ТИИ
	int ADDRESS_PMZ;//=0 адрес в ПМЗ с которого размещаются обьекты
	int DATA_FORMAT;//0- значение от 0 до 255 1- значение со знаком где ноль это 125
	CString strCOMMENT;//granit — поле комментарий к блоку

	IndividualStructureGranit()
	{	
		N_KP=1;
		PACKET_TYPE=4;
		AFB=0;		
		INFO_TYPE=2;	
		GROUP_NUMBER=0;
		NUMBER=64;
		ADDRESS_PMZ=0;
		DATA_FORMAT = 0;
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
		DATA_FORMAT = aIndividualStructure101.DATA_FORMAT;
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
		DATA_FORMAT = aIndividualStructure101.DATA_FORMAT;
		strCOMMENT=aIndividualStructure101.strCOMMENT;	
	}
};
typedef CArray<IndividualStructureGranit,IndividualStructureGranit> CIndividualStructureGranitArray;

struct СGranit: public CKPLVersion
{		
	int NUMBER_NO_ANSWER;/*=3 — количество не ответов для структур фильтров. Слова «неответов» в русском языке нет и вообще какое-то странное название поля. Может переименуешь?  
	Количество запросов, без ответа от КП, после которого генерируется неисправность блока данных.*/
	int TYPE;/*=1 тип протокола 1- запрос по таймеру 2 - без запроса режим подслушивания*/
	int LOG_ENABLE;/*=1 — вести лог обмена 0 - нет 1- да*/
	int ALARM_ENABLE;/*=1 — вести лог аварий 0 - нет 1-да*/
	int SERVICE;/*=1 - сервисное поле 0 — нет 1 — выводить лог обмена в консоль*/
	int MEANDER_VALUE;/*=21765 — значение меандра для опроса 0х55 05 hex (12 бит 010101010101) где 05 - старший байт 55 - младший байт при формировании запроса в канал (может быть заданно другое значение)*/
	int INVERT_REQUEST;/*=0 инвертирование посылки запроса 0- нет , 1- да*/
	int INVERT_RESPONSE;/*=0 инвертирование принятой посылки 0- нет , 1- да*/
	int C_IC_NA_1_PERIOD;/*=0 период после которого включается цикл команд запросов всех данных, сек*/
	int C_IC_TS_ENABLE;/*=1 вести запрос ТС 0- нет , 1- да*/
	int C_IC_TIT_ENABLE;/*=1 вести запрос ТИ 0- нет , 1- да*/
	int C_IC_TII_ENABLE;/*=0 (резерв) вести запрос ТИИ 0- нет , 1- да*/
	int NO_LINK_PERIOD;/*=60 - период «молчания» КП после которого генерируется флаг всем данны «недостоверно», сек*/
	int TU_RESPONSE_PERIOD;/*=30 - период ожидания подтверждения команды ТУ после которого будет установлен флаг ТУ не успешно , сек*/
	int REQ_RESPONSE_PERIOD;/*=5 - период ожидания ответа после запроса, сек*/
	int MEANDER_PERIOD;/*=1500 - период посылки меандров , мили сек*/
	int ADD_MEANDER_BEFORE_REQ;/*=0 - добавление меандра перед посылкой запроса 0- нет 1 -да*/
	int SEND_CONFIRM;/*=1 - посылать подтверждение приема пакета ТС, ТИ, ТИИ 0- нет 1- да*/
	int IC_ON_MEANDER;/*=1 - посылать следующий запрос данных после получения меандра от КП 0- нет 1 -да*/

	CIndividualStructureGranitArray m_IndividualStructureGranitArray;
	CTUGranitArray	m_TUGranitArray;

	СGranit()
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
	~СGranit()
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
	СGranit(const СGranit& aIndividualStructure101)
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
	void operator = (const СGranit& aIndividualStructure101)
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

struct IndividualStructureAIST : public CKPLVersion
{
	int PACKET_TYPE;/*2 –тип пакета данных
		........... 1 - ТС 8 бит ТС располагаются один за другим в ПМЗ с адреса указаного в поле ADRESS_PMZ 2 –ТИ одно байтные
		........... 3 –ТИ двухбайтные следущий парметр по счету будет принят как старший байт
		...........двухбайтного ТИ*/
	int ADDRESS_PARAM;//адрес данных	
	int ADDRESS_PMZ;//=0 адрес в ПМЗ с которого размещаются обьекты
	CString strCOMMENT;//granit — поле комментарий к блоку

	IndividualStructureAIST()
	{		
		PACKET_TYPE = 4;
		ADDRESS_PARAM = 0;		
		ADDRESS_PMZ = 0;
	}
	IndividualStructureAIST(const IndividualStructureAIST& aIndividualStructure101)
	{		
		PACKET_TYPE = aIndividualStructure101.PACKET_TYPE;
		ADDRESS_PARAM = aIndividualStructure101.ADDRESS_PARAM;		
		ADDRESS_PMZ = aIndividualStructure101.ADDRESS_PMZ;
		strCOMMENT = aIndividualStructure101.strCOMMENT;
	}
	void operator = (const IndividualStructureAIST& aIndividualStructure101)
	{
		PACKET_TYPE = aIndividualStructure101.PACKET_TYPE;
		ADDRESS_PARAM = aIndividualStructure101.ADDRESS_PARAM;
		ADDRESS_PMZ = aIndividualStructure101.ADDRESS_PMZ;
		strCOMMENT = aIndividualStructure101.strCOMMENT;
	}
};
typedef CArray<IndividualStructureAIST, IndividualStructureAIST> CIndividualStructureAISTArray;

struct СAIST : public CKPLVersion
{
	int LOG_ENABLE;// = 1— вести лог обмена 0 - нет 1 - да
	int ALARM_ENABLE;// = 1 — вести лог аварий 0 - нет 1 - да
	int SERVICE;// = 0 - сервисное поле 0 — нет 1 — выводить лог обмена в консоль
	int NO_LINK_PERIOD;// = 0 - резервное поле всегда 0

	CIndividualStructureAISTArray m_IndividualStructureAISTArray;
	
	СAIST()
	{		
		LOG_ENABLE = 0;
		ALARM_ENABLE = 0;
		SERVICE = 0;		
		NO_LINK_PERIOD = 0;		
	}
	~СAIST()
	{
		LOG_ENABLE = 0;
		ALARM_ENABLE = 0;
		SERVICE = 0;
		NO_LINK_PERIOD = 0;
		m_IndividualStructureAISTArray.RemoveAll();		
	}
	СAIST(const СAIST& aIndividualStructure101)
	{		
		LOG_ENABLE = aIndividualStructure101.LOG_ENABLE;//1;
		ALARM_ENABLE = aIndividualStructure101.ALARM_ENABLE;//1;
		SERVICE = aIndividualStructure101.SERVICE;//1;		
		NO_LINK_PERIOD = aIndividualStructure101.NO_LINK_PERIOD;//60;		
		m_IndividualStructureAISTArray.Copy(aIndividualStructure101.m_IndividualStructureAISTArray);		
	}
	void operator = (const СAIST& aIndividualStructure101)
	{
		LOG_ENABLE = aIndividualStructure101.LOG_ENABLE;//1;
		ALARM_ENABLE = aIndividualStructure101.ALARM_ENABLE;//1;
		SERVICE = aIndividualStructure101.SERVICE;//1;		
		NO_LINK_PERIOD = aIndividualStructure101.NO_LINK_PERIOD;//60;		
		m_IndividualStructureAISTArray.Copy(aIndividualStructure101.m_IndividualStructureAISTArray);
	}
};

struct IndividualStructureSTM: public CKPLVersion
{		
	int PROTOCOL_TYPE;/*=1 - тип протокола для данного канала
					1- Гранит (создать файл настроек granit_mN_cX.ini и файл ТУ tu_granit_pN_cX.ini)
					2 - АИСТ (создать файл настроек aist_mN_cX.ini )*/
	int CHANNEL;/* — номер канала от 0 до 3*/
	int SPEED;/*
				1 - 600 бод
				2 - 300 бод
				3 - 200 бод
				6 - 100 бод*/
	int CHANNEL2;//номер приемного канала от 4 до 7 для протокола Гранит (для остальных протоколов неактивное поле)
	CString strCOMMENT;//granit — поле комментарий к блоку

	СGranit m_Granit;
	СAIST	m_AIST;

	IndividualStructureSTM()
	{			
		PROTOCOL_TYPE=1;
		CHANNEL=0;		
		SPEED=1;
		CHANNEL2 = 0;
	}
	IndividualStructureSTM(const IndividualStructureSTM& aIndividualStructure101)
	{		
		PROTOCOL_TYPE=aIndividualStructure101.PROTOCOL_TYPE;
		CHANNEL=aIndividualStructure101.CHANNEL;		
		SPEED=aIndividualStructure101.SPEED;	
		CHANNEL2 = aIndividualStructure101.CHANNEL2;
		m_Granit = aIndividualStructure101.m_Granit;
		m_AIST = aIndividualStructure101.m_AIST;
		strCOMMENT=aIndividualStructure101.strCOMMENT;	
	}
	void operator = (const IndividualStructureSTM& aIndividualStructure101)
	{
		PROTOCOL_TYPE=aIndividualStructure101.PROTOCOL_TYPE;
		CHANNEL=aIndividualStructure101.CHANNEL;		
		SPEED=aIndividualStructure101.SPEED;	
		CHANNEL2 = aIndividualStructure101.CHANNEL2;
		m_Granit = aIndividualStructure101.m_Granit;
		m_AIST = aIndividualStructure101.m_AIST;
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

