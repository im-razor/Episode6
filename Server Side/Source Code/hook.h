#include <windows.h>


BOOL Hook(LPVOID lpAddress, LPVOID lpfn, SIZE_T dwSize);

BOOL writeBytes(void* pAddr, void* value, int size);