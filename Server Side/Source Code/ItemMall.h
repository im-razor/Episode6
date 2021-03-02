#pragma once
#import "msado15.dll" no_namespace rename("EOF", "adoEOF")
#include <windows.h>
#include "hook.h"


class Mall {
public:
	Mall(void) : m_cUid{ 0 }, m_cPwd{ 0 }, m_pPacket{ 0 } {}
	~Mall(void) {}
	BOOL Init();
public:
	_ConnectionPtr m_pConnect;
	char m_cUid[32];
	char m_cPwd[32];
	PBYTE m_pPacket[96];
};