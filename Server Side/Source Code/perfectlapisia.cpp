#include "hook.h"
#include <Windows.h>



int typeids = 4;
int qnt = 4;



DWORD plapisia1jmp = 0x46CCB6;


__declspec(naked) void plapisia1()
{
	_asm
	{

		mov byte ptr[qnt], al
		cmp byte ptr[qnt], 0x32 //=50
		jl plapisia1jl
		sub[qnt], 0x32 //=50

		plapisia1jl:
		mov[esp + 0x13], al
			cmp al, 0x32 //=50

			jmp plapisia1jmp


	}
}


DWORD plapisia2jmp = 0x46CA08;

DWORD plapisia2jnejmp = 0x46CAB7;
__declspec(naked) void plapisia2()
{
	_asm
	{

		push eax
		mov eax, [edx + 0x41]
		mov[typeids], eax
		pop eax

		cmp byte ptr[edx + 0x40], 0x5F //95 type
		jne plapisia2jnes

		jmp plapisia2jmp

		plapisia2jnes :
		jmp plapisia2jnejmp




	}
}


DWORD plapisia3jmp = 0x46CD83;

DWORD plapisia3jaejmp = 0x46D11C;

__declspec(naked) void plapisia3()
{
	_asm
	{

		cmp byte ptr[typeids], 0x16
		je qnt1
		cmp byte ptr[typeids], 0x2A
		je qnt1
		cmp byte ptr[typeids], 0x17
		je qnt2
		cmp byte ptr[typeids], 0x2B
		je qnt2
		cmp byte ptr[typeids], 0x18
		je qnt3
		cmp byte ptr[typeids], 0x2C
		je qnt3
		cmp byte ptr[typeids], 0x19
		je qnt4
		cmp byte ptr[typeids], 0x2D
		je qnt4
		cmp byte ptr[typeids], 0x1A
		je qnt5
		cmp byte ptr[typeids], 0x2E
		je qnt5
		cmp byte ptr[typeids], 0x1B
		je qnt6
		cmp byte ptr[typeids], 0x2F
		je qnt6
		cmp byte ptr[typeids], 0x1C
		je qnt7
		cmp byte ptr[typeids], 0x30
		je qnt7
		cmp byte ptr[typeids], 0x1D
		je qnt8
		cmp byte ptr[typeids], 0x31
		je qnt8
		cmp byte ptr[typeids], 0x1E
		je qnt9
		cmp byte ptr[typeids], 0x32
		je qnt9
		cmp byte ptr[typeids], 0x1F
		je qnt10
		cmp byte ptr[typeids], 0x33
		je qnt10
		cmp byte ptr[typeids], 0x20
		je qnt11
		cmp byte ptr[typeids], 0x34
		je qnt11
		cmp byte ptr[typeids], 0x21
		je qnt12
		cmp byte ptr[typeids], 0x35
		je qnt12
		cmp byte ptr[typeids], 0x22
		je qnt13
		cmp byte ptr[typeids], 0x36
		je qnt13
		cmp byte ptr[typeids], 0x23
		je qnt14
		cmp byte ptr[typeids], 0x37
		je qnt14
		cmp byte ptr[typeids], 0x24
		je qnt15
		cmp byte ptr[typeids], 0x38
		je qnt15
		cmp byte ptr[typeids], 0x25
		je qnt16
		cmp byte ptr[typeids], 0x39
		je qnt16
		cmp byte ptr[typeids], 0x26
		je qnt17
		cmp byte ptr[typeids], 0x3A
		je qnt17
		cmp byte ptr[typeids], 0x27
		je qnt18
		cmp byte ptr[typeids], 0x3B
		je qnt18
		cmp byte ptr[typeids], 0x28
		je qnt19
		cmp byte ptr[typeids], 0x3C
		je qnt19
		cmp byte ptr[typeids], 0x29
		je qnt20
		cmp byte ptr[typeids], 0x3D
		je qnt20

		originalcode :
		cmp esi, eax
			jae plapisia3jaes
			jmp plapisia3exit

			qnt1 :
		cmp byte ptr[qnt], 0x0
			je plapisia3exit
			jmp originalcode

			qnt2 :
		cmp byte ptr[qnt], 0x1
			je plapisia3exit
			jmp originalcode

			qnt3 :
		cmp byte ptr[qnt], 0x2
			je plapisia3exit
			jmp originalcode

			qnt4 :
		cmp byte ptr[qnt], 0x3
			je plapisia3exit
			jmp originalcode

			qnt5 :
		cmp byte ptr[qnt], 0x4
			je plapisia3exit
			jmp originalcode

			qnt6 :
		cmp byte ptr[qnt], 0x5
			je plapisia3exit
			jmp originalcode

			qnt7 :
		cmp byte ptr[qnt], 0x6
			je plapisia3exit
			jmp originalcode

			qnt8 :
		cmp byte ptr[qnt], 0x7
			je plapisia3exit
			jmp originalcode

			qnt9 :
		cmp byte ptr[qnt], 0x8
			je plapisia3exit
			jmp originalcode

			qnt10 :
		cmp byte ptr[qnt], 0x9
			je plapisia3exit
			jmp originalcode

			qnt11 :
		cmp byte ptr[qnt], 0xA
			je plapisia3exit
			jmp originalcode

			qnt12 :
		cmp byte ptr[qnt], 0xB
			je plapisia3exit
			jmp originalcode

			qnt13 :
		cmp byte ptr[qnt], 0xC
			je plapisia3exit
			jmp originalcode

			qnt14 :
		cmp byte ptr[qnt], 0xD
			je plapisia3exit
			jmp originalcode

			qnt15 :
		cmp byte ptr[qnt], 0xE
			je plapisia3exit
			jmp originalcode

			qnt16 :
		cmp byte ptr[qnt], 0xF
			je plapisia3exit
			jmp originalcode

			qnt17 :
		cmp byte ptr[qnt], 0x10
			je plapisia3exit
			jmp originalcode

			qnt18 :
		cmp byte ptr[qnt], 0x11
			je plapisia3exit
			jmp originalcode

			qnt19 :
		cmp byte ptr[qnt], 0x12
			je plapisia3exit
			jmp originalcode

			qnt20 :
		cmp byte ptr[qnt], 0x13
			je plapisia3exit
			jmp originalcode


			plapisia3exit :
		jmp plapisia3jmp

			plapisia3jaes :
		jmp plapisia3jaejmp




	}
}



void perfectlapisia()
{

	// 
	Hook((void*)0x46CCB0, plapisia1, 6);
	// 
	Hook((void*)0x46C9FE, plapisia2, 10);
	// 
	Hook((void*)0x46CD7B, plapisia3, 8);

}