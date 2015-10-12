#pragma once

#include "KPLVersion.h"

struct MacrosBUTS: public CKPLVersion
{
	int TYPE;//32
	int ADDRESS_BUTS;//4
	int NUMBER_POSITION;//64
	int POSITION_DOUBLE;//0
	int ADDRESS_PMZ;//266
	int POS_BYTE;//0
	int POS_BIT;//0
	int COLOR_ON;//1
	int COLOR_OFF;//2
	int ON_VALUE;//1	
	CString strCOMMENT;

	MacrosBUTS()
	{
		TYPE=2;
		ADDRESS_BUTS=1;
		NUMBER_POSITION=1;
		POSITION_DOUBLE=0;
		ADDRESS_PMZ=0;
		POS_BYTE=0;
		POS_BIT=0;
		COLOR_ON=1;
		COLOR_OFF=2;
		ON_VALUE=1;
		strCOMMENT=" ";
	}
	MacrosBUTS(const MacrosBUTS& aMacrosBUTS)
	{
		TYPE=aMacrosBUTS.TYPE;
		ADDRESS_BUTS=aMacrosBUTS.ADDRESS_BUTS;
		NUMBER_POSITION=aMacrosBUTS.NUMBER_POSITION;
		POSITION_DOUBLE=aMacrosBUTS.POSITION_DOUBLE;
		ADDRESS_PMZ=aMacrosBUTS.ADDRESS_PMZ;
		POS_BYTE=aMacrosBUTS.POS_BYTE;
		POS_BIT=aMacrosBUTS.POS_BIT;
		COLOR_ON=aMacrosBUTS.COLOR_ON;
		COLOR_OFF=aMacrosBUTS.COLOR_OFF;
		ON_VALUE=aMacrosBUTS.ON_VALUE;		
		strCOMMENT=aMacrosBUTS.strCOMMENT;
	}
	void operator = (const MacrosBUTS& aMacrosBUTS)
	{
		TYPE=aMacrosBUTS.TYPE;
		ADDRESS_BUTS=aMacrosBUTS.ADDRESS_BUTS;
		NUMBER_POSITION=aMacrosBUTS.NUMBER_POSITION;
		POSITION_DOUBLE=aMacrosBUTS.POSITION_DOUBLE;
		ADDRESS_PMZ=aMacrosBUTS.ADDRESS_PMZ;
		POS_BYTE=aMacrosBUTS.POS_BYTE;
		POS_BIT=aMacrosBUTS.POS_BIT;
		COLOR_ON=aMacrosBUTS.COLOR_ON;
		COLOR_OFF=aMacrosBUTS.COLOR_OFF;
		ON_VALUE=aMacrosBUTS.ON_VALUE;		
		strCOMMENT=aMacrosBUTS.strCOMMENT;
	}
};

struct MacrosBUI: public CKPLVersion
{
	int TYPE;//=4Ч тип индикатора ѕ “»:	4 Ч  сегментный
	int ADDRESS_BUI;//=10- адрес блока ѕ “» 
	int NUMBER_POSITION;//1Ч номер индикатора в блоке ѕ “»
	int POSITION_DOUBLE;//0 - резерв
	int ADDRESS_PMZ;//501 - адрес в ѕћ« информационного объекта, с которого производитс€ выдача на индикатор  ѕ “»
	int ZNAK;/*/60 Ч код ASCII на матричном индикаторе в зависимости от параметров выдачи:
			60 Ч стрелка вверх при значении “» >0 и стрелка вниз при значении “» <0
			61 - стрелка вниз при значении “» >0 и стрелка вверх при значении “» <0
			62 - стрелка вправо при значении “» >0 и стрелка влево при значении “» <0
			63 - стрелка влево при значении “» >0 и стрелка вправо при значении “» <0
			92 Ч Ђ+ї при положительном значении Ђ-ї  при отрицательном значении
			58 Ч пробел
			65 - 90  - латинские буквы согласно стандарта ASCII
			128-159  -буквы кириллицы*/
	double CENA_SHKALI;//1.0 Ч множитель (об€зательно с точкой) 
	double SMESHENIE;//0.0 Ч смещение (об€зательно с точкой) 
	double MIN;//-1000.0 Ч минимальное значение которое может принимать физическа€ величина (об€зательно с точкой) 
	double MAX;//1000.0Ч максимальное значение которое может принимать физическа€ величина (об€зательно с точкой) 
	int DOP_FLAG;/*/1 Ч дополнительный флаг:
				бит 0 - если установлен, то значение информационного объекта представлено в дополнительном коде
				бит 1- если установлен, то значение  информационного объекта представлено в формате  ќћѕј——
				бит 3 Ч если установлен то на индикатор ѕ “» выводитьс€ значение с точкой
				ѕримечание:
				типы информационных объектов используемых в процессе вывода на щит:
				1,7,9,13*/
	CString strCOMMENT;

	MacrosBUI()
	{
		TYPE=4;
		ADDRESS_BUI=1;
		NUMBER_POSITION=1;
		POSITION_DOUBLE=0;
		ADDRESS_PMZ=0;
		ZNAK=58;
		CENA_SHKALI=1.0;
		SMESHENIE=0.0;
		MIN=0.0;
		MAX=0.0;
		DOP_FLAG=0;
		strCOMMENT=" ";
	}
	MacrosBUI(const MacrosBUI& aMacrosBUI)
	{
		TYPE=aMacrosBUI.TYPE;
		ADDRESS_BUI=aMacrosBUI.ADDRESS_BUI;
		NUMBER_POSITION=aMacrosBUI.NUMBER_POSITION;
		POSITION_DOUBLE=aMacrosBUI.POSITION_DOUBLE;
		ADDRESS_PMZ=aMacrosBUI.ADDRESS_PMZ;
		ZNAK=aMacrosBUI.ZNAK;
		CENA_SHKALI=aMacrosBUI.CENA_SHKALI;
		SMESHENIE=aMacrosBUI.SMESHENIE;
		MIN=aMacrosBUI.MIN;
		MAX=aMacrosBUI.MAX;
		DOP_FLAG=aMacrosBUI.DOP_FLAG;
		strCOMMENT=aMacrosBUI.strCOMMENT;
	}
	void operator = (const MacrosBUI& aMacrosBUI)
	{
		TYPE=aMacrosBUI.TYPE;
		ADDRESS_BUI=aMacrosBUI.ADDRESS_BUI;
		NUMBER_POSITION=aMacrosBUI.NUMBER_POSITION;
		POSITION_DOUBLE=aMacrosBUI.POSITION_DOUBLE;
		ADDRESS_PMZ=aMacrosBUI.ADDRESS_PMZ;
		ZNAK=aMacrosBUI.ZNAK;
		CENA_SHKALI=aMacrosBUI.CENA_SHKALI;
		SMESHENIE=aMacrosBUI.SMESHENIE;
		MIN=aMacrosBUI.MIN;
		MAX=aMacrosBUI.MAX;
		DOP_FLAG=aMacrosBUI.DOP_FLAG;
		strCOMMENT=aMacrosBUI.strCOMMENT;
	}
};
typedef CArray<MacrosBUI,MacrosBUI> CMacrosBUIArray;
typedef CArray<MacrosBUTS,MacrosBUTS> CMacrosBUTSArray;

class CMapboard;
typedef CArray<CMapboard,CMapboard> CMapboardArray;

class CMapboard:public CKPLVersion
{
public:
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

	int NUMBER_BUTS;//=5 - количество панелей ѕ “—
	int NUMBER_BUI;//=5 - количество панелей ѕ “»
	int START_ADDRESS_BUTS;//=1- стартовый адрес панели ѕ “— (адрес 0- запрещЄнный)
	int START_ADDRESS_BUI;//=10 Ч стартовый адрес панели ѕ “» (адрес 0- запрещЄнный)
	int OPROS_STATUS;//=1 Ч врем€ опроса статусов прибора, если 0- опрос не производитс€, 1 квант Ч 1 секунда
	//NUMBER_MACROS_TS=12 Ч количество макросов дл€ дл€ вывода информации на ѕ “—
	//NUMBER_MACROS_TI=12 Ч количество макросов дл€ выдачи на ѕ “»
	//NUMBER_SUM_TI=0 Ч количество макросов описывающие суммарные “»
	int TIMER_AUTO_KVIT_TS;//=10 Ч врем€ автоквитировани€ дл€ панелей ѕ “—,1 квант Ч 1 секунда
	int TIMER_AUTO_KVIT_TI;//=10Ч врем€ автоквитировани€ дл€ панелей ѕ “»,1 квант Ч 1 секунда

	CMacrosBUIArray		m_MacrosBUIArray;
	CMacrosBUTSArray	m_MacrosBUTSArray;

	CMapboard(const CMapboard& aMapboard)
	{
		m_nProcNum=aMapboard.m_nProcNum;
		PORT=aMapboard.PORT;
		BAUDRATE=aMapboard.BAUDRATE;
		STOPBITS=aMapboard.STOPBITS;
		PARITY=aMapboard.PARITY;
		BYTETIME=aMapboard.BYTETIME;
		WAITRESP=aMapboard.WAITRESP;
		NEXTMESSAGE=aMapboard.NEXTMESSAGE;
		AMOUNTBYTE=aMapboard.AMOUNTBYTE;
		CONTROLPOTOK=aMapboard.CONTROLPOTOK;
		NUMBER_NO_ANSWER=aMapboard.NUMBER_NO_ANSWER;
		NUMBER_BUTS=aMapboard.NUMBER_BUTS;
		NUMBER_BUI=aMapboard.NUMBER_BUI;
		START_ADDRESS_BUTS=aMapboard.START_ADDRESS_BUTS;
		START_ADDRESS_BUI=aMapboard.START_ADDRESS_BUI;
		OPROS_STATUS=aMapboard.OPROS_STATUS;			
		m_MacrosBUIArray.Copy(aMapboard.m_MacrosBUIArray);
		m_MacrosBUTSArray.Copy(aMapboard.m_MacrosBUTSArray);
		TIMER_AUTO_KVIT_TS=aMapboard.TIMER_AUTO_KVIT_TS;
		TIMER_AUTO_KVIT_TI=aMapboard.TIMER_AUTO_KVIT_TI;
	}
	void operator = (const CMapboard& aMapboard)
	{
		m_nProcNum=aMapboard.m_nProcNum;
		PORT=aMapboard.PORT;
		BAUDRATE=aMapboard.BAUDRATE;
		STOPBITS=aMapboard.STOPBITS;
		PARITY=aMapboard.PARITY;
		BYTETIME=aMapboard.BYTETIME;
		WAITRESP=aMapboard.WAITRESP;
		NEXTMESSAGE=aMapboard.NEXTMESSAGE;
		AMOUNTBYTE=aMapboard.AMOUNTBYTE;
		CONTROLPOTOK=aMapboard.CONTROLPOTOK;
		NUMBER_NO_ANSWER=aMapboard.NUMBER_NO_ANSWER;
		NUMBER_BUTS=aMapboard.NUMBER_BUTS;
		NUMBER_BUI=aMapboard.NUMBER_BUI;
		START_ADDRESS_BUTS=aMapboard.START_ADDRESS_BUTS;
		START_ADDRESS_BUI=aMapboard.START_ADDRESS_BUI;
		OPROS_STATUS=aMapboard.OPROS_STATUS;	
		m_MacrosBUIArray.Copy(aMapboard.m_MacrosBUIArray);
		m_MacrosBUTSArray.Copy(aMapboard.m_MacrosBUTSArray);
		TIMER_AUTO_KVIT_TS=aMapboard.TIMER_AUTO_KVIT_TS;
		TIMER_AUTO_KVIT_TI=aMapboard.TIMER_AUTO_KVIT_TI;
	}	

	CMapboard(void);
	~CMapboard(void);	

	BOOL LoadFromFile(CString strFile);
	BOOL SaveToFile(CString strFile);
};
