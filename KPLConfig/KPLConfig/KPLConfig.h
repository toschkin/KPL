
// KPLConfig.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������

#include "KPLProject.h"
// CKPLConfigApp:
// � ���������� ������� ������ ��. KPLConfig.cpp
//

class CKPLConfigApp : public CWinApp
{
public:
	CKPLConfigApp();

// ���������������
	public:
	virtual BOOL InitInstance();

// ����������
	CKPLProject m_KPLProject;

	DECLARE_MESSAGE_MAP()
};

extern CKPLConfigApp theApp;