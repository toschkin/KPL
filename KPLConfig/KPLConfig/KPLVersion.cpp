#include "StdAfx.h"
#include "KPLVersion.h"

int CKPLVersion::m_nVersion=KPL_CURRENTVERSION;

CKPLVersion::CKPLVersion(void)
{
	m_arrVersions.Add(10);
	m_arrVersions.Add(11);
	m_arrVersions.Add(12);
	m_arrVersions.Add(13);
	m_arrVersions.Add(14);
	m_arrVersions.Add(15);
	m_arrVersions.Add(16);
	m_arrVersions.Add(17);
	m_arrVersions.Add(18);
	m_arrVersions.Add(19);
	m_arrVersions.Add(20);
}

CKPLVersion::~CKPLVersion(void)
{
}
int CKPLVersion::Str2Array(CString szSrc, CStringArray * parrDest, TCHAR chrDelimiter)
{
	parrDest->RemoveAll();
	parrDest->FreeExtra();

	if (szSrc.Find(chrDelimiter) == -1)
	{
		parrDest->Add(szSrc);

		return 1;
	}

	CString	szTmp = "";
	int		nCount = 0;
	for (int i = 0; i < szSrc.GetLength(); i++)
	{
		if (szSrc[i] == chrDelimiter)
		{
			parrDest->Add(szTmp);
			szTmp = "";
			nCount++;
		}
		else
			szTmp += szSrc[i];
	}
	parrDest->Add(szTmp);
	nCount++;

	return nCount;
}
