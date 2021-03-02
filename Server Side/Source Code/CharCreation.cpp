#include <windows.h>
#include "hook.h"
#include "database.h"

extern DWORD dwCallSendPackets;

CDataBase g_DBobj2;
DWORD dwCheckCharname;
BYTE bCharName[16];
BOOL boolCheckCharname()
{
	CString str = "";
	CString s = "";
	CString bSql;
	int result;
	for (int i = 0; i<16; i++)
	{
		str.Format(L"%c", bCharName[i]);
		s += str;
	}
	bSql.Format(L"SELECT CharID FROM PS_GameData.dbo.Chars WHERE CharName = '%s'", s);
	result = _tcstoul(g_DBobj2.ExeSqlByCommand(bSql, "CharID"), 0, 10);

	if (result == 0)
		return 1;

	return 0;
}
void zCharName()
{
	for (int y = 0; y < 16; y++)
		bCharName[y] = 00;
}
BYTE sBytes[5];
DWORD dwExitCheckButton = 0x0047A574;
__declspec(naked) void naked_checkButton()
{
	_asm
	{
			pushad
			call zCharName
			mov eax,02
			mov ebx,00
		iniLoop:
			cmp ebx,13 // max
			jg retFalse
			mov cl, [edi + eax]
			mov [bCharName + ebx], cl
			inc eax
			inc ebx
			test cl, cl
			jne iniLoop
			call dwCheckCharname
			test al, al
			jne retTrue
		retFalse:
			mov dword ptr[sBytes],0x00000119
			jmp sendBytes
		retTrue:
			mov dword ptr[sBytes],0x00010119
		sendBytes:
			push 03
			lea ecx,[sBytes]
			push ecx
			mov ecx,esi
			call dwCallSendPackets
			popad
		jmp[dwExitCheckButton]
	}
}
void charCreation()
{
	dwCheckCharname = (DWORD)boolCheckCharname;
	if (g_DBobj2.LinkDataBase())
	{
		
		Hook((void*)0x0047A569, naked_checkButton, 6);
	}
}