#include <windows.h>
#include "hook.h"
#include "database.h"

CDataBase g_DBobj;
BYTE bTypeP;
BYTE bTypeIDP;
BYTE bTypeT;
BYTE bTypeIDT;
BYTE bTypeA;
BYTE bTypeIDA;
DWORD checkIds;
void voidCheckIds(DWORD dwCharID = 0)
{
	CString szSql;
	szSql.Format(L"SELECT [Type], [TypeID] FROM PS_GameData.dbo.CharItems WHERE Bag = 0 and Slot = 14 and CharID = %d", dwCharID);
	bTypeP = (BYTE)_tcstoul(g_DBobj.ExeSqlByCommand(szSql, "Type"), 0, 10);
	bTypeIDP = (BYTE)_tcstoul(g_DBobj.ExeSqlByCommand(szSql, "TypeID"), 0, 10);
	szSql.Format(L"SELECT [Type], [TypeID] FROM PS_GameData.dbo.CharItems WHERE Bag = 0 and Slot = 15 and CharID = %d", dwCharID);
	bTypeT = (BYTE)_tcstoul(g_DBobj.ExeSqlByCommand(szSql, "Type"), 0, 10);
	bTypeIDT = (BYTE)_tcstoul(g_DBobj.ExeSqlByCommand(szSql, "TypeID"), 0, 10);
	szSql.Format(L"SELECT [Type], [TypeID] FROM PS_GameData.dbo.CharItems WHERE Bag = 0 and Slot = 16 and CharID = %d", dwCharID);
	bTypeA = (BYTE)_tcstoul(g_DBobj.ExeSqlByCommand(szSql, "Type"), 0, 10);
	bTypeIDA = (BYTE)_tcstoul(g_DBobj.ExeSqlByCommand(szSql, "TypeID"), 0, 10);
}
BYTE pBytes[100];
DWORD dwCallSendPackets = 0x004ED0E0;
DWORD dwExitCharScreen = 0x0047B9B8;
__declspec(naked) void naked_selectScreen()
{
	_asm
	{
			mov word ptr [pBytes],0x00000101
			pushad
			// slot, charid and others...
			mov eax, [esp + 0xA6]
			mov dword ptr[pBytes + 0x02], eax
			mov eax, [esp + 0xA7]
			mov dword ptr[pBytes + 0x03], eax
			mov eax, [esp + 0xAB]
			mov dword ptr[pBytes + 0x07], eax
			mov eax, [esp + 0xAF]
			mov dword ptr[pBytes + 0x0B], eax
			mov eax, [esp + 0xB3]
			mov dword ptr[pBytes + 0x0F], eax
			mov eax, [esp + 0xB7]
			mov dword ptr[pBytes + 0x13], eax
			mov eax, [esp + 0xBB]
			mov dword ptr[pBytes + 0x17], eax
			mov eax, [esp + 0xBF]
			mov dword ptr[pBytes + 0x1B], eax
			mov eax, [esp + 0xC3]
			mov dword ptr[pBytes + 0x1F], eax
			mov eax, [esp + 0xC7]
			mov dword ptr[pBytes + 0x23], eax
			mov eax, [esp + 0xCB]
			mov dword ptr[pBytes + 0x27], eax
			mov eax, [esp + 0xCF]
			mov dword ptr[pBytes + 0x2B], eax
			mov eax, [esp + 0xD3]
			mov byte ptr [pBytes + 0x2F], al
			// items
			mov eax, [esp + 0xD4]
			mov dword ptr[pBytes + 0x39], eax
			mov eax, [esp + 0xD8]
			mov dword ptr[pBytes + 0x3D], eax
			mov eax, [esp + 0xEE]
			mov dword ptr[pBytes + 0x41], eax
			// name
			mov eax, [esp + 0xDC]
			mov dword ptr[pBytes + 0x4A], eax
			mov eax, [esp + 0xE0]
			mov dword ptr[pBytes + 0x4E], eax
			mov eax, [esp + 0xE4]
			mov dword ptr[pBytes + 0x52], eax
			mov eax, [esp + 0xE8]
			mov dword ptr[pBytes + 0x56], eax
			mov eax, [esp + 0xEC]
			mov dword ptr[pBytes + 0x5A], eax
			popad
			// name change stone and del char
			mov byte ptr [pBytes + 0x5D], al
			mov byte ptr [pBytes + 0x5E], dl
			pushad
			push [esp + 0xA7]
			call checkIds
			add esp, 0x4
			// pet, costume and wing
			movzx eax, byte ptr[bTypeP]
			mov byte ptr[pBytes + 0x36], al
			movzx eax, byte ptr[bTypeIDP]
			mov byte ptr[pBytes + 0x47], al
			movzx eax, byte ptr[bTypeT]
			mov byte ptr[pBytes + 0x37], al
			movzx eax, byte ptr[bTypeIDT]
			mov byte ptr[pBytes + 0x48], al
			movzx eax, byte ptr[bTypeA]
			mov byte ptr[pBytes + 0x38], al
			movzx eax, byte ptr[bTypeIDA]
			mov byte ptr[pBytes + 0x49], al
			push 99 // count of bytes sent
			lea ecx, [pBytes]
			push ecx
			mov ecx,ebp
			call dwCallSendPackets
			popad
			add esp,0x08
			jmp[dwExitCharScreen]
	}
}
void selectionScreen()
{
	checkIds = (DWORD)voidCheckIds;
	if (g_DBobj.LinkDataBase())
	{
		
		Hook((void*)0x0047B9AC, naked_selectScreen, 7);
	}
}