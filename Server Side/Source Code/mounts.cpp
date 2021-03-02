#include "hook.h"




BYTE fix_mount[10];

DWORD newmountsjmp = 0x00491496;

__declspec(naked) void newmounts()
{
	_asm
	{
		cmp byte ptr[ecx + 0x0D * 0x4 + 0x1C0], 00
		je original

		push eax
		// get type
		mov eax, [ecx + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x40]
		// check type
		cmp al, 0x2A
		jne poporiginal
		// get typeid
		mov eax, [ecx + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x41]
		// check typeid
		cmp al, 0x62
		jbe poporiginal

		// opcode
		mov eax, [esp + 0x04]
		mov dword ptr[fix_mount], eax
		mov eax, [esp + 0x08]
		mov dword ptr[fix_mount + 0x04], eax

		// get mount id
		mov eax, [ecx + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x40]
		mov dword ptr[fix_mount + 0x07], eax
		mov eax, [ecx + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x41]
		mov dword ptr[fix_mount + 0x0B], eax
		pop eax

		// continue:
		push 0x0F
		lea edx, [fix_mount]

		newmountsexit:
		jmp[newmountsjmp]

			original :
			push 0x07
			lea edx, [esp + 0x04]
			jmp newmountsexit

			poporiginal :
		pop eax
			jmp original



	}
}


DWORD newmountsaroundjmp = 0x0042A572;

__declspec(naked) void newmountsaround()
{
	_asm
	{
		push eax

		mov eax, [esp + 0x18]
		mov dword ptr[fix_mount], eax
		mov eax, [esp + 0x1C]
		mov dword ptr[fix_mount + 0x04], eax

		cmp[esi + 0x0D * 0x4 + 0x1C0], 0x00
		je no_mount

		mov eax, [esi + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x40]
		mov dword ptr[fix_mount + 0x07], eax
		mov eax, [esi + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x41]
		mov dword ptr[fix_mount + 0x0B], eax

		contines :
		pop eax
			mov byte ptr[fix_mount + 0x06], al

			push 0x0F
			lea edx, [fix_mount]
			jmp dword ptr[newmountsaroundjmp]

			no_mount:
		mov dword ptr[fix_mount + 0x07], 0x00000000
			mov dword ptr[fix_mount + 0x0B], 0x00000000
			jmp contines

	}
}


DWORD newmountstownjmp = 0x004263B3;

__declspec(naked) void newmountstown()
{
	_asm
	{
		push eax

		cmp byte ptr[esp + 0x3C], 0x1D
		jne poporiginal

		mov eax, [esp + 0x3C]
		mov dword ptr[fix_mount], eax
		mov eax, [esp + 0x40]
		mov dword ptr[fix_mount + 0x04], eax

		cmp byte ptr[edi + 0x0D * 0x4 + 0x1C0], 0x00
		je no_mount

		mov eax, [edi + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x40]
		mov dword ptr[fix_mount + 0x07], eax
		mov eax, [edi + 0x0D * 0x4 + 0x1C0]
		movzx eax, byte ptr[eax + 0x41]
		mov dword ptr[fix_mount + 0x0B], eax

		continuef :
		pop eax
			mov byte ptr[fix_mount + 0x06], al


			lea ecx, [fix_mount]
			push 0x0F

			newmountstownexit:
		jmp[newmountstownjmp]

			original :
			lea ecx, [esp + 0x38]
			push 0x07
			jmp newmountstownexit

			poporiginal :
		pop eax
			jmp original

			no_mount :
		mov dword ptr[fix_mount + 0x07], 0x00000000
			mov dword ptr[fix_mount + 0x0B], 0x00000000
			jmp continuef

	}
}


DWORD gmmountsfixjmp = 0x0049DBE4;
__declspec(naked) void gmmountsfix()
{
	_asm
	{

		mov al, 0x01 //move value 01 into an 8-bit register
		mov[edi + 0x5814], al //make the offset value 01
		mov[edi + 0x147C], edx //and mount the character
		jmp[gmmountsfixjmp]
	}
}

DWORD gmoffonfixjmp = 0x004834EE;

__declspec(naked) void gmoffonfix()
{
	_asm
	{
		//prevent dismount ps_game crash with invisible gms
		//offsets: mount = 147C - charon/off = 5814
		mov byte ptr[ebp + 0x147C], 0x00 //move 0 into offset
		mov byte ptr[ebp + 0x5814], 0x01 //move 1 into offset
		jmp[gmoffonfixjmp]
	}
}




void newmountsfix()
{
	// new mounts
	Hook((void*)0x00491490, newmounts, 6);
	// new mounts around
	Hook((void*)0x0042A56C, newmountsaround, 6);
	// new mounts town
	Hook((void*)0x004263AD, newmountstown, 6);
	// GM Mounts insivble
	Hook((void*)0x0049DBDE, gmmountsfix, 6);
	// /char off --- /char on crash fix
	Hook((void*)0x004834E7, gmoffonfix, 7);
}