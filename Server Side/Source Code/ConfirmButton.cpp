#include "hook.h"
#include <windows.h>

extern DWORD dwCallSendPackets;

BYTE tradeBytes[5];
DWORD dwExitConfirmBtnTrade = 0x0047E0DA;
__declspec(naked) void naked_confirmBtnTrade()
{
	_asm
	{
			pushad
			mov dword ptr [tradeBytes],0x00010A0A
			mov eax, [edi + 0x2]
			mov byte ptr [tradeBytes + 0x03], al
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets
			mov byte ptr [tradeBytes + 0x02], 0x02
			mov eax,[edi + 0x02]
			mov byte ptr [tradeBytes + 0x03], al
			cmp dword ptr [ebx + 0x15C4], 00
			je fail
			cmp dword ptr [ebx + 0x68],-1
			je fail
			mov ebx,[ebx + 0x15C4]
			cmp dword ptr [ebx + 0x68],-1
			je fail
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets
			cmp byte ptr [edi + 0x02],00
			je cancel_trade
			jmp fail

		cancel_trade:
			mov dword ptr [tradeBytes],0x01030A05
			mov byte ptr [ebx + 0x15E4],00
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets

			mov dword ptr [tradeBytes],0x00010A0A
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets

			mov dword ptr [tradeBytes],0x01030A05
			mov ebx, [ebx + 0x15C4]
			mov byte ptr[ebx + 0x15E4],00
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets

			mov dword ptr [tradeBytes],0x00020A0A
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets

		fail:
			popad

			jmp [dwExitConfirmBtnTrade]
	}
}
DWORD dwExitPreventsExploit = 0x0047E00D;
_declspec(naked) void naked_preventsExploit()
{
	_asm
	{
			call dwCallSendPackets

			push 04
			mov dword ptr [tradeBytes],0x00010A0A
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets

			mov byte ptr [tradeBytes + 0x02], 0x02
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, ebx
			call dwCallSendPackets

			push 04
			mov dword ptr[tradeBytes], 0x00010A0A
			lea eax, [tradeBytes]
			push eax
			mov ecx, esi
			call dwCallSendPackets

			mov byte ptr [tradeBytes + 0x02], 0x02
			push 04
			lea eax, [tradeBytes]
			push eax
			mov ecx, esi
			call dwCallSendPackets
			pop edi

			jmp[dwExitPreventsExploit]
	}
}
void confirmButtonTrade()
{
	
	Hook((void*)0x0047E0CF, naked_confirmBtnTrade, 6);
	Hook((void*)0x0047E007, naked_preventsExploit, 6);
}