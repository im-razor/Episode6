#include "ItemMall.h"
#include "hook.h"


BOOL Mall::Init() {
	Mall obj;

	if (FAILED(CoInitialize(NULL))) {
		return FALSE;
	}

	HRESULT hr = m_pConnect.CreateInstance("ADODB.Connection");
	if (FAILED(hr)) {
		return FALSE;
	}

	Sleep(500);

	GetPrivateProfileStringA("DbInfo", "Account", "", obj.m_cUid, 32, ".\\Sh.ini");
	GetPrivateProfileStringA("DbInfo", "Pw", "", obj.m_cPwd, 32, ".\\Sh.ini");

	//LPCSTR szConnectionString = "Provider=SQLNCLI11;Server=127.0.0.1;Database=master;";
	LPCSTR szConnectionString = "Provider=SQLOLEDB;Server=127.0.0.1;Database=master;";
	m_pConnect->Open(szConnectionString, obj.m_cUid, obj.m_cPwd, adModeUnknown);

	CoUninitialize();
	return TRUE;
}

DWORD dwLoadRetn = 0x47D163;
//hooks CUser::PacketUserDBPoint
void __declspec(naked) LoadHook() {
	__asm {
		xor ebp, ebp
		add ebx, 0x5998
		mov eax, [esi + 0x6]
		mov[ecx + 0x5AC0], eax //point
		jmp dwLoadRetn
	}
}

DWORD CClientToMgrOnRecv = 0x406960;
DWORD WINAPI MallProc(LPVOID lpUid) {
	Mall obj;

	__asm {
		lea eax, [obj.m_pPacket + 0x12]
		mov[obj.m_pPacket + 0x4], eax

		mov[obj.m_pPacket + 0x12], 0x0
		mov[obj.m_pPacket + 0x13], 0x0
		mov[obj.m_pPacket + 0x14], 0x2
		mov[obj.m_pPacket + 0x15], 0x1B

		mov ecx, lpUid
		mov[obj.m_pPacket + 0x16], ecx

		lea eax, [obj.m_pPacket]
		push eax
		mov ecx, 0x0
		call CClientToMgrOnRecv
	}
	return 0;
}

void MallFunc(LPVOID& lpUid) {
	CreateThread(0, 0, MallProc, lpUid, 0, 0);
}

DWORD dwMallRetn = 0x488D5F;
//hooks CUser::PacketShop
void __declspec(naked) MallHook() {
	__asm {
		pushad
		lea eax, [edi + 0x582C]
		push eax //lpUid           
		call MallFunc
		add esp, 0x4
		popad
		jmp dwMallRetn
	}
}

void MainFunc() {

	Hook((LPVOID)0x47D151, LoadHook, 18);
	Hook((LPVOID)0x48876F, MallHook, 5);

}