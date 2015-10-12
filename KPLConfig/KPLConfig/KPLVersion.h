#pragma once
#include <afxtempl.h> 

#define KPL_CURRENTVERSION 20

class CKPLVersion
{
public:
	CArray<int> m_arrVersions;
	static int m_nVersion;
	CKPLVersion(void);
	~CKPLVersion(void);
	
	int Str2Array(CString szSrc, CStringArray * parrDest, TCHAR chrDelimiter);
};