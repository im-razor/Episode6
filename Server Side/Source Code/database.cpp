#define WIN32_LEAN_AND_MEAN
#include  "atlstr.h"
#include <windows.h>
#include "database.h"
#include "hook.h"


CDataBase::CDataBase(void)
{
	m_vecDATABASE.clear();
	m_dwIndex = 0;
}

BOOL CDataBase::LinkDataBase()
{
	CoInitialize(NULL);
	try
	{
		HRESULT hr1 = m_pConnect.CreateInstance(L"ADODB.Connection");
		if (FAILED(hr1))
		{
			return FALSE;
		}
	}
	catch (_com_error)
	{
		OutputDebugString(L"");
	}
	Sleep(500);
	wchar_t szUser[255];
	wchar_t szPass[255];
	GetPrivateProfileString(L"DbInfo", L"Account", L"", szUser, 255, L".\\Sh.ini");
	GetPrivateProfileString(L"DbInfo", L"Pw", L"", szPass, 255, L".\\Sh.ini");
	CString szLink;
	CString szUid = szUser;
	CString szPwd = szPass;
	szLink.Format(L"Provider=SQLOLEDB;Server=127.0.0.1;Database=PS_GameDefs;"); //define the login string
	m_pConnect->Open(_bstr_t(szLink), _bstr_t(szUid), _bstr_t(szPwd), adModeUnknown); //execute the query
	return TRUE;
}

BOOL CDataBase::ExeSqlByCon(CString szSql)
{
	try {
		m_pConnect->Execute(_bstr_t(szSql), NULL, 1);
	}
	catch (_com_error)
	{
		return FALSE;
	}
	return TRUE;
}
