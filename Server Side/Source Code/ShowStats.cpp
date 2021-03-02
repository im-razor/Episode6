#include <windows.h>
#include "hook.h"

extern DWORD dwCallSendPackets;

BYTE statsBytes[52];
void zStatsBytes()
{
	for (int y = 0; y <= 50; y++)
		statsBytes[y] = 00;
}
__declspec(naked) void sendFixedPackets()
{
	_asm
	{
			call zStatsBytes
			mov dword ptr [statsBytes],0x00000526
			//str
			movzx eax, word ptr[esi + 0x121C]
			movzx ebx, word ptr[esi + 0x16C]
			sub eax, ebx
			mov word ptr[statsBytes + 0x02], ax
			//dex
			movzx eax, word ptr[esi + 0x1220]
			movzx ebx, word ptr[esi + 0x16E]
			sub eax, ebx
			mov word ptr[statsBytes + 0x12], ax
			//int
			movzx eax, word ptr[esi + 0x1224]
			movzx ebx, word ptr[esi + 0x170]
			sub eax, ebx
			mov word ptr[statsBytes + 0x0A], ax
			//wis
			movzx eax, word ptr[esi + 0x1228]
			movzx ebx, word ptr[esi + 0x172]
			sub eax, ebx
			mov word ptr[statsBytes + 0x0E], ax
			//rec
			movzx eax, word ptr[esi + 0x122C]
			movzx ebx, word ptr[esi + 0x174]
			sub eax, ebx
			mov word ptr[statsBytes + 0x06], ax
			//luc
			movzx eax, word ptr[esi + 0x1230]
			movzx ebx, word ptr[esi + 0x176]
			sub eax, ebx
			mov word ptr[statsBytes + 0x16], ax
			//ph atk
			movzx eax, word ptr[esi + 0x13CC]
			mov word ptr[statsBytes + 0x1A], ax
			movzx ebx, word ptr[esi + 0x12E4]
			add eax, ebx
			mov word ptr[statsBytes + 0x1E], ax
			//mg atk
			movzx eax, word ptr[esi + 0x1424]
			mov word ptr[statsBytes + 0x22], ax
			movzx ebx, word ptr[esi + 0x12E4]
			add eax, ebx
			mov word ptr[statsBytes + 0x26], ax
			//ph def
			movzx eax, word ptr[esi + 0x13D4]
			mov word ptr[statsBytes + 0x2A], ax
			//mg def
			movzx eax, word ptr[esi + 0x142C]
			mov word ptr[statsBytes + 0x2E], ax
			push 50
			lea ecx, [statsBytes]
			push ecx
			mov ecx, esi
			call dwCallSendPackets
			ret
	}
}
DWORD dwExitFixStats = 0x00461005;
__declspec(naked) void naked_fixStats()
{
	_asm
	{
		mov dword ptr [esi + 0x1434],ecx
		pushad
		call sendFixedPackets
		popad
		jmp [dwExitFixStats]
	}
}
void showStats()
{
	Hook((void*)0x00460FFF, naked_fixStats, 6);
}
