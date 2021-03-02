#include "hook.h"
#include <windows.h>



DWORD SendPacket = 0x004ED0E0;

// For Duel Item packet
int DuelItemPacket[50];
int* DIP = DuelItemPacket;

// For Trade Item Fix
int TradeItemPacket[50];
int* TIP = TradeItemPacket;

// For UserStoredItem Fix
int Size[1];
int* S = Size;
/// 
int slot = 0;
int size[1];
int* sz = size;


// MarketViewFix
DWORD MarketViewFixretn = 0x48732A;
void __declspec(naked) MarketViewFix()

{
	__asm
	{
		mov ebx, [esi + 0xA0]
		mov[eax], ebx
		mov[eax + 0x0D], 0x00  //
		mov[eax - 0x01], cl
		movzx ebx, byte ptr[edx + 0x40]
		mov[eax + 0x04], bl
		movzx ebx, byte ptr[edx + 0x41]
		mov[eax + 0x05], bl
		movzx ebx, byte ptr[edx + 0x42]
		mov[eax + 0x06], bl
		movzx ebx, word ptr[edx + 0x44]
		mov[eax + 0x07], bx
		mov ebx, [edx + 0x46]
		mov[eax + 0x11], ebx //
		movzx ebx, word ptr[edx + 0x4A]
		mov[eax + 0x15], bx //
		mov ebx, [edx + 0x4C]
		mov[eax + 0x17], ebx //
		mov ebx, [edx + 0x50]
		add edx, 0x4C
		mov[eax + 0x1B], ebx //
		mov ebx, [edx + 0x08]
		mov[eax + 0x1F], ebx //
		mov ebx, [edx + 0x0C]
		mov[eax + 0x23], ebx //
		mov ebx, [edx + 0x10]
		mov[eax + 0x27], ebx //
		mov ebx, [esp + 0x10]
		mov dl, [edx + 0x14]
		inc ebx
		mov[eax + 0x2B], dl //
		mov[esp + 0x10], ebx
		add eax, 0x2D //
		jmp MarketViewFixretn
	}
}


// DuelItemFix
DWORD DuelItemFixretn = 0x0048C753;
void __declspec(naked) DuelItemFix()

{
	__asm
	{
		push 0x2B // Length packet
		lea ecx, [esp + 0x48]
		pushfd
		mov ebx, [ecx]
		mov[DuelItemPacket], ebx
		mov ebx, [ecx + 0x4]
		mov[DuelItemPacket + 0x4], ebx
		mov ebx, [ecx + 0x8]
		mov[DuelItemPacket + 0x10], ebx
		mov ebx, [ecx + 0x0C]
		mov[DuelItemPacket + 0x14], ebx
		mov ebx, [ecx + 0x10]
		mov[DuelItemPacket + 0x18], ebx
		mov ebx, [ecx + 0x14]
		mov[DuelItemPacket + 0x1C], ebx
		mov ebx, [ecx + 0x18]
		mov[DuelItemPacket + 0x20], ebx
		mov ebx, [ecx + 0x1C]
		mov[DuelItemPacket + 0x24], ebx
		mov ebx, [ecx + 0x20]
		mov[DuelItemPacket + 0x28], ebx
		popfd
		push DIP
		mov ecx, esi
		mov[DuelItemPacket + 0x2A], eax
		call SendPacket
		jmp DuelItemFixretn
	}
}


// TradeItemFix

DWORD TradeItemFixretn = 0x0047DF34;
void __declspec(naked) TradeItemFix()

{
	__asm
	{
		push 0x2B // Length packet
		lea eax, [esp + 0x20]
		pushfd
		// Make new packet
		mov ebx, [eax]
		mov[TradeItemPacket], ebx
		mov ebx, [eax + 0x4]
		mov[TradeItemPacket + 0x4], ebx
		mov ebx, [eax + 0x8]
		mov[TradeItemPacket + 0x10], ebx
		mov ebx, [eax + 0x0C]
		mov[TradeItemPacket + 0x14], ebx
		mov ebx, [eax + 0x10]
		mov[TradeItemPacket + 0x18], ebx
		mov ebx, [eax + 0x14]
		mov[TradeItemPacket + 0x1C], ebx
		mov ebx, [eax + 0x18]
		mov[TradeItemPacket + 0x20], ebx
		mov ebx, [eax + 0x1C]
		mov[TradeItemPacket + 0x24], ebx
		mov ebx, [eax + 0x20]
		mov[TradeItemPacket + 0x28], ebx
		popfd
		push TIP
		mov ecx, esi
		mov[TradeItemPacket + 0x2A], edx
		call SendPacket
		jmp TradeItemFixretn
	}
}


// UserStoredItemFix

DWORD UserStoredItemFix_1retn = 0x004926B7;
void __declspec(naked) UserStoredItemFix_1()

{
	__asm
	{
		cmp eax, 00
		je edit
		add[sz], 0x8
		add eax, [sz]
		originalcode:
		mov[esp + eax + 0x1B], cl
			mov ecx, [edi]
			jmp UserStoredItemFix_1retn
			edit :
		mov[sz], 0
			jmp originalcode
	}
}

DWORD UserStoredItemFix_2retn = 0x0049272A;
void __declspec(naked) UserStoredItemFix_2()

{
	__asm
	{
			usıjng:
			lea edx, [esp + 0x18]
			add edx, 0x0F
			add edx, [slot]
			mov dword ptr[edx], 0x00000000
			mov dword ptr[edx + 0x4], 0x00000000
			add[slot], 0x29
			cmp[slot], 0x0668
			jl usıjng
			mov[slot], 0x00
			push 0x00000679
			jmp UserStoredItemFix_2retn
	}
}






void Slot()
{
	{
		Hook((void*)0x4872C1, MarketViewFix, 6);
		Hook((void*)0x48C741, DuelItemFix, 6);
		Hook((void*)0x47DF22, TradeItemFix, 6);
		Hook((void*)0x4926B1, UserStoredItemFix_1, 5);
		Hook((void*)0x492725, UserStoredItemFix_2, 5);

		DWORD prot = 0;
		DWORD ViewFixmemory = 0x477DE3; // ViewFix
		DWORD change_addr_6 = 0x48733F; // PetsAndCostumeFix
		DWORD Warehousememory1 = 0x49275B; // Warehouse Fix 1
		DWORD Warehousememory2 = 0x49271C; // Warehouse Fix 2
		DWORD Warehousememory3 = 0x49270D; // Warehouse Fix 3

		// ViewFix
		VirtualProtect((PBYTE)ViewFixmemory, 3, PAGE_EXECUTE_READWRITE, &prot);
		memcpy((void*)ViewFixmemory, (void*)(PBYTE)"\x83\xFB\x10", 3); // Max slot
		VirtualProtect((PBYTE)ViewFixmemory, 3, prot, &prot);
		// MarketViewFix
		VirtualProtect((PBYTE)change_addr_6, 3, PAGE_EXECUTE_READWRITE, &prot);
		memcpy((void*)change_addr_6, (void*)(PBYTE)"\x6B\xDB\x30", 3);
		VirtualProtect((PBYTE)change_addr_6, 3, prot, &prot);
		//Warehouse
		VirtualProtect((PBYTE)Warehousememory1, 4, PAGE_EXECUTE_READWRITE, &prot);
		memcpy((void*)Warehousememory1, (void*)(PBYTE)"\x8D\x4C\xD0\x1C", 4);
		VirtualProtect((PBYTE)Warehousememory1, 4, prot, &prot);

		VirtualProtect((PBYTE)Warehousememory2, 3, PAGE_EXECUTE_READWRITE, &prot);
		memcpy((void*)Warehousememory2, (void*)(PBYTE)"\x83\xFA\x28", 3);
		VirtualProtect((PBYTE)Warehousememory2, 3, prot, &prot);

		VirtualProtect((PBYTE)Warehousememory3, 4, PAGE_EXECUTE_READWRITE, &prot);
		memcpy((void*)Warehousememory3, (void*)(PBYTE)"\x8D\x74\x04\x2F", 4);
		VirtualProtect((PBYTE)Warehousememory3, 4, prot, &prot);


	}
}