#include "hook.h"

BYTE bBytes[251];
void zbBytes()
{
	for (int z = 0; z < 250; z++)
		bBytes[z] = 00;
}
__declspec(naked) void naked_funcAroundChar()
{
	_asm
	{
			pushad
			call zbBytes
			cmp word ptr [ebx + 0x1C0 + 0xE * 0x4], 00
			je checkCostume
			mov edx, [ebx + 0x1C0 + 0xE * 0x4]
			mov ecx, [edx + 0x40]
			mov byte ptr [bBytes + 0x3F], cl
			mov ecx, [edx + 0x41]
			mov byte ptr [bBytes + 0x40], cl
		checkCostume:
			cmp word ptr[ebx + 0x1C0 + 0xF * 0x4], 00
			je checkWing
			mov edx, [ebx + 0x1C0 + 0xF * 0x4]
			mov ecx, [edx + 0x40]
			mov byte ptr [bBytes + 0x42], cl
			mov ecx, [edx + 0x41]
			mov byte ptr [bBytes + 0x43], cl
		checkWing:
			cmp word ptr[ebx + 0x1C0 + 0x10 * 0x4], 00
			je cancel
			mov edx, [ebx + 0x1C0 + 0x10 * 0x4]
			mov ecx, [edx + 0x40]
			mov byte ptr [bBytes + 0x45], cl
			mov ecx, [edx + 0x41]
			mov byte ptr [bBytes + 0x46], cl
		cancel:
			popad
			push ebx
			mov ebx, [esp + 0x40]
			mov dword ptr [bBytes], ebx
			mov ebx, [esp + 0x44]
			mov dword ptr [bBytes + 0x04], ebx
			mov ebx, [esp + 0x48]
			mov dword ptr [bBytes + 0x08], ebx
			mov ebx, [esp + 0x4C]
			mov dword ptr [bBytes + 0x0C], ebx
			mov ebx, [esp + 0x50]
			mov dword ptr [bBytes + 0x10], ebx
			mov ebx, [esp + 0x54]
			mov dword ptr [bBytes + 0x14], ebx
			mov ebx, [esp + 0x58]
			mov dword ptr [bBytes + 0x18], ebx
			mov ebx, [esp + 0x5C]
			mov dword ptr [bBytes + 0x1C], ebx
			mov ebx, [esp + 0x60]
			mov dword ptr [bBytes + 0x20], ebx
			mov ebx, [esp + 0x64]
			mov dword ptr [bBytes + 0x24], ebx
			mov ebx, [esp + 0x68]
			mov dword ptr [bBytes + 0x28], ebx
			// +47 name
			mov ebx, [esp + 0x6C]
			mov dword ptr [bBytes + 0x47], ebx
			mov ebx, [esp + 0x70]
			mov dword ptr [bBytes + 0x4B], ebx
			mov ebx, [esp + 0x74]
			mov dword ptr [bBytes + 0x4F], ebx
			mov ebx, [esp + 0x78]
			mov dword ptr [bBytes + 0x53], ebx
			mov ebx, [esp + 0x7C]
			mov dword ptr [bBytes + 0x57], ebx
			// +5B guildname
			mov ebx, [esp + 0x80]
			mov dword ptr[bBytes + 0x5B], ebx
			mov ebx, [esp + 0x84]
			mov dword ptr[bBytes + 0x5F], ebx
			mov ebx, [esp + 0x88]
			mov dword ptr[bBytes + 0x63], ebx
			mov ebx, [esp + 0x8C]
			mov dword ptr[bBytes + 0x67], ebx
			mov ebx, [esp + 0x90]
			mov dword ptr[bBytes + 0x6B], ebx
			mov ebx, [esp + 0x94]
			mov dword ptr[bBytes + 0x6F], ebx
			mov ebx, [esp + 0x98]
			mov dword ptr[bBytes + 0x73], ebx
			pop ebx
			ret
	}
}
DWORD dwExitAroundChar1 = 0x00426C72;
__declspec(naked) void naked_aroundChar1()
{
	_asm
	{
		push eax
		call naked_funcAroundChar
		lea ecx, [bBytes]
		push ecx
		jmp [dwExitAroundChar1]
	}
}
DWORD dwExitAroundChar2 = 0x00426C9B;
__declspec(naked) void naked_aroundChar2()
{
	_asm
	{
		push eax
		call naked_funcAroundChar
		lea eax, [bBytes]
		push eax
		mov ecx, [esp + 0x18]
		jmp [dwExitAroundChar2]
	}
}
DWORD dwExitAppSlot = 0x00468A32;
DWORD dwFailAppSlot = 0x00468BE7;
DWORD dwCallAppearance = 0x00492C00;
__declspec(naked) void naked_appearanceSlot1()
{
	_asm
	{
			cmp ebx,0x0D
			ja appearance

			cmp ebx,0x08
			jnl fail
			jmp lbExit

		appearance:
			pushad
			push ebx
			mov ecx,esi
			call dwCallAppearance
			popad

		fail:
			jmp [dwFailAppSlot]

		lbExit:
			jmp [dwExitAppSlot]
	}
}
DWORD dwExitAppSlot2 = 0x00468B64;
__declspec(naked) void naked_appearanceSlot2()
{
	_asm
	{
		cmp ebx, 0x0D
			ja appearance

			cmp ebx, 0x08
			jnl fail
			jmp lbExit

		appearance:
			pushad
			push ebx
			mov ecx, esi
			call dwCallAppearance
			popad

		fail:
			jmp [dwFailAppSlot]

		lbExit:
			jmp [dwExitAppSlot2]
	}
}
DWORD dwExitAppSlot3 = 0x00468729;
DWORD dwFailAppSlot3 = 0x00468941;
__declspec(naked) void naked_appearanceSlot3()
{
	_asm
	{
		cmp ebx, 0x0D
			ja appearance

			cmp ebx, 0x08
			jnl fail
			jmp lbExit

		appearance:
			pushad
			push ebx
			mov ecx, esi
			call dwCallAppearance
			popad

		fail:
			jmp [dwFailAppSlot3]

		lbExit:
			jmp [dwExitAppSlot3]
	}
}
DWORD dwExitzSlot = 0x004555B7;
__declspec(naked) void naked_zSlot()
{
	_asm
	{
		lea eax, [edi + 0x1C0]
		mov dword ptr [edi + 0x200],00000000
		mov dword ptr [edi + 0x204],00000000
		mov dword ptr [edi + 0x208],00000000
		mov dword ptr [edi + 0x20C],00000000
		mov dword ptr [edi + 0x210],00000000
		jmp[dwExitzSlot]
	}
}
DWORD dwExitPreventsWrongItem = 0x0046838E;
DWORD dwFailPreventsWrongItem = 0x0046846B;
__declspec(naked) void naked_preventsWrongItem()
{
	_asm
	{
			cmp eax,0x0E
			je petSlot

			cmp eax,0x0F
			je costumeSlot

			cmp eax,0x10
			je wingSlot

		original:
			cmp eax,0x0D
			ja originalFail

			jmp [dwExitPreventsWrongItem]

		petSlot:
			cmp byte ptr [esi + 0x24],120
			jne fail
			jmp original

		costumeSlot:
			cmp byte ptr [esi + 0x24],150
			jne fail
			jmp original

		wingSlot:
			cmp byte ptr [esi + 0x24],121
			jne fail
			jmp original

		fail:
			xor al, al
			pop esi
			ret

		originalFail:
			jmp [dwFailPreventsWrongItem]
	}
}
void newSlots()
{
	
	Hook((void*)0x00468A29, naked_appearanceSlot1, 9);
	Hook((void*)0x00468B5B, naked_appearanceSlot2, 9);
	Hook((void*)0x00468720, naked_appearanceSlot3, 9);
	Hook((void*)0x004555B1, naked_zSlot, 6);
	Hook((void*)0x00468385, naked_preventsWrongItem, 9);
	Hook((void*)0x00426C6C, naked_aroundChar1, 6);
	Hook((void*)0x00426C91, naked_aroundChar2, 6);
	BYTE countBytes = 0x67;
	//BYTE countBytes2 = 0x61;
	writeBytes((void*)0x00426C6B, &countBytes, 1);
	writeBytes((void*)0x00426C90, &countBytes, 1);
	BYTE nBytes[] = { 0xB8, 0x62 };
	writeBytes((void*)0x0046754C, &nBytes, 2);
	writeBytes((void*)0x00467587, &nBytes, 2);
	writeBytes((void*)0x0046798C, &nBytes, 2);
	writeBytes((void*)0x004679C7, &nBytes, 2);
	writeBytes((void*)0x00468665, &nBytes, 2);
	writeBytes((void*)0x004686B6, &nBytes, 2);
	writeBytes((void*)0x004687CB, &nBytes, 2);
	writeBytes((void*)0x00468813, &nBytes, 2);
	writeBytes((void*)0x00468996, &nBytes, 2);
	writeBytes((void*)0x00468A6A, &nBytes, 2);
	writeBytes((void*)0x00468ABA, &nBytes, 2);
	writeBytes((void*)0x00469C64, &nBytes, 2);
	writeBytes((void*)0x00469CA4, &nBytes, 2);
	writeBytes((void*)0x0046C2DC, &nBytes, 2);
	writeBytes((void*)0x0046C317, &nBytes, 2);
	writeBytes((void*)0x0046C50C, &nBytes, 2);
	writeBytes((void*)0x0046C547, &nBytes, 2);
	writeBytes((void*)0x0046D3D8, &nBytes, 2);
	writeBytes((void*)0x0046D413, &nBytes, 2);
	writeBytes((void*)0x0046DB52, &nBytes, 2);
	writeBytes((void*)0x0046DB99, &nBytes, 2);
	writeBytes((void*)0x0046EDE7, &nBytes, 2);
	writeBytes((void*)0x0046EE22, &nBytes, 2);
	writeBytes((void*)0x00470A32, &nBytes, 2);
	writeBytes((void*)0x00470A78, &nBytes, 2);
	writeBytes((void*)0x004718B1, &nBytes, 2);
	writeBytes((void*)0x004718F1, &nBytes, 2);
	writeBytes((void*)0x00471DC5, &nBytes, 2);
	writeBytes((void*)0x00472092, &nBytes, 2);
	writeBytes((void*)0x00473912, &nBytes, 2);
	writeBytes((void*)0x0047AE7B, &nBytes, 2);
	BYTE bMaxSlot = 0x11; // 17 wing
	writeBytes((void*)0x00468955, &bMaxSlot, 1);
	writeBytes((void*)0x0046862D, &bMaxSlot, 1);
	writeBytes((void*)0x00461528, &bMaxSlot, 1);
	// temporary notice fix
	BYTE bTempFix = 0x00;
	writeBytes((void*)0x0049D949, &bTempFix, 1);
	writeBytes((void*)0x00428BD7, &bTempFix, 1);
}