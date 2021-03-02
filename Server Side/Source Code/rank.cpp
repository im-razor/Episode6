#include "hook.h"




DWORD rankstatfixjmp = 0x49D018;

__declspec(naked) void rankstatfix()
{
	_asm
	{
		cmp ecx, 0x32
		jl rank1
		cmp ecx, 0x12C
		jl rank2
		cmp ecx, 0x3E8
		jl rank3
		cmp ecx, 0x1388
		jl rank4
		cmp ecx, 0x2710
		jl rank5
		cmp ecx, 0x4E20
		jl rank6
		cmp ecx, 0x7530
		jl rank7
		cmp ecx, 0x9C40
		jl rank8
		cmp ecx, 0xC350
		JL rank9
		cmp ecx, 0x11170
		JL rank10
		cmp ecx, 0x15F90
		JL rank11
		cmp ecx, 0x1ADB0
		JL rank12
		cmp ecx, 0x1FBD0
		JL rank13
		cmp ecx, 0x249F0
		JL rank14
		cmp ecx, 0x30D40
		JL rank15
		cmp ecx, 0x3D090
		JL rank16
		cmp ecx, 0x493E0
		JL rank17
		cmp ecx, 0x55730
		JL rank18
		cmp ecx, 0x6DDD0
		JL rank19
		cmp ecx, 0x7A120
		JL rank20
		cmp ecx, 0x86470
		JL rank21
		cmp ecx, 0x927C0
		JL rank22
		cmp ecx, 0x9EB10
		JL rank23
		cmp ecx, 0xAAE60
		JL rank24
		cmp ecx, 0xB71B0
		JL rank25
		cmp ecx, 0xC3500
		JL rank26
		cmp ecx, 0xCF850
		JL rank27
		cmp ecx, 0xDBBA0
		JL rank28
		cmp ecx, 0xE7EF0
		JL rank29
		cmp ecx, 0xDBBA0
		JL rank30
		cmp ecx, 0xF4240
		JGE rank31


		rank1 :
		mov ax, 1
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank2 :
		mov ax, 3
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank3 :
		mov ax, 5
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank4 :
		mov ax, 7
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank5 :
		mov ax, 0xC
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank6 :
		mov ax, 0x12
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank7 :
		mov ax, 0x14
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank8 :
		mov ax, 0x16
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank9 :
		mov ax, 0x18
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank10 :
		mov ax, 0x1A
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank11 :
		mov ax, 0x1A
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank12 :
		mov ax, 0x1A
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank13 :
		mov ax, 0x1B
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank14 :
		mov ax, 0x1B
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank15 :
		mov ax, 0x1B
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank16 :
		mov ax, 0x1C
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank17 :
		mov ax, 0x1C
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank18 :
		mov ax, 0x1C
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank19 :
		mov ax, 0x1C
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank20 :
		mov ax, 0x1C
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank21 :
		mov ax, 0x1C
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank22 :
		mov ax, 0x1D
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank23 :
		mov ax, 0x1D
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank24 :
		mov ax, 0x1D
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank25 :
		mov ax, 0x1D
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank26 :
		mov ax, 0x1D
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank27 :
		mov ax, 0x1E
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank28 :
		mov ax, 0x1E
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank29 :
		mov ax, 0x1E
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank30 :
		mov ax, 0x1E
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rank31 :
		mov ax, 0x1E
			mov[esp + 0x10], ax
			jmp rankstatfixexit

			rankstatfixexit :
		jmp dword ptr[rankstatfixjmp]



	}
}





void rankfix(){
	// 
	Hook((void*)0x0049D013, rankstatfix, 5);

}