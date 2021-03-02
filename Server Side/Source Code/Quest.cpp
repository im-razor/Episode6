#include "hook.h"
#include <windows.h>
#include <string>

/*

DWORD CGameDataGetItemInfo = 0x4059B0;
DWORD CUserItemCreate = 0x46BD10;
DWORD CUserQuestFind = 0x48D3A0;
DWORD CUserQuestSuccessResult = 0x48DE10;

int GetQuestReward(LPVOID pUser, UINT16 wQuestId, UINT8 cIndex) {
	char cGold[32], cExp[32], cItemId[32];

	LPCSTR szIniPath = ".\\Data\\QuestReward.ini";
	std::string sQuestId = std::to_string(wQuestId);
	std::string sIndex = std::to_string(cIndex);

	UINT32 uGold, uExp, uItemId = 0;

	if (cIndex > 5) {
		return 0;
	}

	else if (cIndex == 3) {
		try {
			GetPrivateProfileStringA(sQuestId.c_str(), "Gold3", "", cGold, 32, szIniPath);
			uGold = std::stoi(cGold);

			GetPrivateProfileStringA(sQuestId.c_str(), "Exp3", "", cExp, 32, szIniPath);
			uExp = std::stoi(cExp);
		}
		catch (std::invalid_argument) {
			uGold, uExp = 0;
		}
		catch (std::out_of_range) {
			uGold, uExp = 0;
		}
	}

	else if (cIndex == 4) {
		try {
			GetPrivateProfileStringA(sQuestId.c_str(), "Gold4", "", cGold, 32, szIniPath);
			uGold = std::stoi(cGold);

			GetPrivateProfileStringA(sQuestId.c_str(), "Exp4", "", cExp, 32, szIniPath);
			uExp = std::stoi(cExp);
		}
		catch (std::invalid_argument) {
			uGold, uExp = 0;
		}
		catch (std::out_of_range) {
			uGold, uExp = 0;
		}
	}

	else if (cIndex == 5) {
		try {
			GetPrivateProfileStringA(sQuestId.c_str(), "Gold5", "", cGold, 32, szIniPath);
			uGold = std::stoi(cGold);

			GetPrivateProfileStringA(sQuestId.c_str(), "Exp5", "", cExp, 32, szIniPath);
			uExp = std::stoi(cExp);
		}
		catch (std::invalid_argument) {
			uGold, uExp = 0;
		}
		catch (std::out_of_range) {
			uGold, uExp = 0;
		}
	}

	try {
		GetPrivateProfileStringA(sQuestId.c_str(), sIndex.c_str(), "", cItemId, 32, szIniPath);
		uItemId = std::stoi(cItemId);
	}
	catch (std::invalid_argument) {
		uItemId = 0;
	}
	catch (std::out_of_range) {
		uItemId = 0;
	}

	int nType = uItemId / 1000;
	int nTypeId = uItemId % 1000;

	__asm {
		mov eax, pUser
		//save data in memory
		movzx ecx, cIndex
		mov[eax + 0x593C], ecx
		mov ecx, uGold
		mov[eax + 0x5940], ecx
		mov ecx, uExp
		mov[eax + 0x5944], ecx

		movzx ecx, nTypeId
		movzx eax, nType
		call CGameDataGetItemInfo
		test eax, eax
		je _fail

		mov ecx, pUser
		push 0x1 //count
		push eax //pInfo
		call CUserItemCreate

		_fail :
	}

	return 0;
}

DWORD dwPacketRetn = 0x47A0D7;
DWORD dwPacketJump = 0x47A0DE;
//hooks CUser::PacketQuest
void __declspec(naked) PacketHook() {
	__asm {
		//original code
		mov cl, byte ptr[esi + 0x4]
		mov ax, word ptr[esi + 0x2]

		cmp cl, 0x2 //reward 3
		ja reward
		jmp dwPacketRetn

		reward :
		pushad

			movzx edx, cl
			push edx //reward
			movzx edx, ax
			push edx //QuestId
			push edi //pUser
			call GetQuestReward
			add esp, 0xC

			popad

			pushad
			mov bl, cl

			movzx edx, ax
			push edx //QuestId
			call CUserQuestFind
			test eax, eax
			je _fail

			movzx edx, bl //reward
			push 0x0
			mov ebx, eax //eax = pQuest
			mov ecx, edi //edi = pUser
			call CUserQuestSuccessResult

			_fail :
		//clear memory
		xor ecx, ecx
			mov[edi + 0x593C], ecx
			mov[edi + 0x5940], ecx
			mov[edi + 0x5944], ecx

			popad
			jmp dwPacketJump
	}
}

DWORD dwExpRetn = 0x48DEC0;
DWORD dwExpJump = 0x48DEC4;
DWORD dwExpZero = 0x48DECF;
//hooks CUser::QuestSuccessResult
void __declspec(naked) ExpHook() {
	__asm {
		//orignal code
		mov byte ptr[esp + 0xC3], al
		//compare reward
		cmp byte ptr[edi + 0x593C], 0x2
		ja _reward
		jmp dwExpRetn

		_reward :
		mov esi, dword ptr[edi + 0x5944]
			cmp esi, 0x0
			jle _zero
			jmp dwExpJump

			_zero :
		xor esi, esi
			jmp dwExpZero
	}
}

DWORD dwGoldRetn1 = 0x48DE7B;
//hooks CUser::QuestSuccessResult
void __declspec(naked) GoldHook1() {
	__asm {
		//compare reward
		cmp byte ptr[edi + 0x593C], 0x2
		ja _reward

		_original :
		mov[esp + 0x1E], edx
			mov edx, 0x502 //opcode
			jmp dwGoldRetn1

			_reward :
		mov edx, dword ptr[edi + 0x5940]
			cmp edx, 0x0
			jle _zero
			jmp _original

			_zero :
		xor edx, edx
			jmp _original
	}
}

DWORD dwGoldRetn2 = 0x48DF00;
//hooks CUser::QuestSuccessResult
void __declspec(naked) GoldHook2() {
	__asm {
		//compare reward
		cmp byte ptr[edi + 0x593C], 0x2
		ja _reward

		_original :
		add ecx, eax
			mov[edi + 0x140], ecx
			jmp dwGoldRetn2

			_reward :
		mov eax, dword ptr[edi + 0x5940]
			cmp eax, 0x0
			jle _zero
			jmp _original

			_zero :
		xor eax, eax
			jmp _original
	}
}


void Quest() {
	Hook((LPVOID)0x47A0D0, PacketHook, 7);
	Hook((LPVOID)0x48DEB9, ExpHook, 7);
	Hook((LPVOID)0x48DE72, GoldHook1, 9);
	Hook((LPVOID)0x48DEF8, GoldHook2, 8);
}

*/