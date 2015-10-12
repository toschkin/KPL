
// KPLConfig.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы

#include "KPLProject.h"
// CKPLConfigApp:
// О реализации данного класса см. KPLConfig.cpp
//

class CKPLConfigApp : public CWinApp
{
public:
	CKPLConfigApp();

// Переопределение
	public:
	virtual BOOL InitInstance();

// Реализация
	CKPLProject m_KPLProject;

	DECLARE_MESSAGE_MAP()
};

extern CKPLConfigApp theApp;