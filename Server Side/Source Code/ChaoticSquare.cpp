#include "hook.h"
#include <Windows.h>




DWORD chaoticpacketjmp = 0x00479FC1;

DWORD chaoticpacketjajmp = 0x0047A040;

DWORD chaoticpacketje1 = 0x00479FE1;
DWORD chaoticpacketje2 = 0x00479FEE;


DWORD chaoticpacketmainscall = 0x00479FC8;
__declspec(naked) void chaoticpacket()
{
	_asm
	{

		cmp eax, 0x2F // Kaotik Kare Ana paket
		je chaoticpacketmains
		cmp eax, 0x30 // Nesne paket
		je chaoticpacketjes1
		cmp eax, 0x31 // Baþarýlý - Baþarýsýz paket
		je chaoticpacketjes2

		// original code
		cmp eax, 0x09
		ja chaoticpacketjas

		jmp chaoticpacketjmp

		chaoticpacketmains:
		jmp chaoticpacketmainscall

		chaoticpacketjes1:
		jmp chaoticpacketje1

		chaoticpacketjes2:
		jmp chaoticpacketje2

		chaoticpacketjas:
		jmp chaoticpacketjajmp



	}


}


void ChaoticSquare()
{
	// 
	Hook((void*)0x00479FBC, chaoticpacket, 5);

}