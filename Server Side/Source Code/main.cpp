#include <windows.h>
#include "ItemMall.h"


void selectionScreen();
void charCreation();
void newSlots();
void showStats();
void confirmButtonTrade();
void Slot();
void MainFunc();
void ChaoticSquare();
void perfectlapisia();
void newmountsfix();
void rankfix();


DWORD WINAPI Main(LPVOID) {
	Mall obj;
	obj.Init();

	MainFunc();
	rankfix();
	newmountsfix();
	perfectlapisia();
	ChaoticSquare();
	selectionScreen();
	charCreation();
	newSlots();
	showStats();
	confirmButtonTrade();
	Slot();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, Main, 0, 0, 0);
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

