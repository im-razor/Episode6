#include <windows.h>
#include "hook.h"


BOOL Hook(LPVOID lpAddress, LPVOID lpfn, SIZE_T dwSize) {
	if (dwSize < 5) {
		return FALSE;
	}

	DWORD lpflOldProtect;
	if (!VirtualProtect(lpAddress, dwSize, PAGE_EXECUTE_READWRITE, &lpflOldProtect)) {
		return FALSE;
	};

	memset(lpAddress, 0x90, dwSize);
	DWORD dwAddress = ((DWORD)lpfn - (DWORD)lpAddress) - 5;
	*(PBYTE)lpAddress = 0xE9;
	*(PDWORD)((DWORD)lpAddress + 1) = dwAddress;

	DWORD flNewProtect = lpflOldProtect;
	VirtualProtect(lpAddress, dwSize, flNewProtect, &lpflOldProtect);
	return TRUE;
}


BOOL writeBytes(void* pAddr, void* value, int size)
{
	DWORD dwOldProtect;
	VirtualProtect(pAddr, size, PAGE_READWRITE, &dwOldProtect);
	WriteProcessMemory(GetCurrentProcess(), pAddr, value, size, NULL);
	VirtualProtect(pAddr, size, dwOldProtect, &dwOldProtect);
	return TRUE;
}