#include "pch.h"
#include "GameCall.h"
#include "GameBaseAddress.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <sstream>

/************************************************************************/
/* ����˵����DNF�������
/* ����һ��equPos  ����������  ��9��ʼ�ǵ�һ����λ
/* Date��2019��8��16��14:23:31
/************************************************************************/
void GameCall::SellEquipment(DWORD equPos)
{
	BufferCall(22);
	EncryptCall(0, 1);
	EncryptCall(equPos, 2);
	EncryptCall(1, 2);
	EncryptCall(0, 4);
	EncryptCall(equPos + 1, 4);
	EncryptCall(0, 4);
	SendPacketCall();

}

/************************************************************************/
/* ����˵����DNF����ֽ�
/* ����һ��equPos  ����������  ��9��ʼ�ǵ�һ����λ
/* Date��2019��8��16��14:23:31
/************************************************************************/
void GameCall::BreakDownEquipment(DWORD equPos)
{
	BufferCall(26);
	EncryptCall(equPos, 2);
	EncryptCall(0, 1);
	EncryptCall(65535, 2);
	EncryptCall(319, 4);
	SendPacketCall();

}

//͸���޵�   1��0��
void GameCall::invincible(DWORD open) {
	DWORD person = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);

	__asm
	{
		MOV ECX, person;
		MOV ESI, ECX;
		PUSH - 1;
		PUSH 1;
		PUSH open;  
		PUSH 1;
		MOV EDX, BASE_INVINCIBLE_CALL_ADDR;
		CALL EDX;
	}
}

//ȫ���ƶ���Ʒ
void GameCall::RemoveProperty() {
	DWORD objBase = 0;
	DWORD objData = 0;
	DWORD objType = 0;
	DWORD person = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD objOffset = utils::ReadValue<DWORD>(person + 0xD4);
	if (objOffset == 0) {
		return;
	}
	DWORD start = utils::ReadValue<DWORD>(objOffset + OFFSET_START_ADDR);
	DWORD tail = utils::ReadValue<DWORD>(objOffset + OFFSET_TAIL_ADDR);
	DWORD num = (tail - start) / 4;
	for (int i = 0; i < num; i++) {
		objData = utils::ReadValue<DWORD>(start + 4 * i);
		objType = utils::ReadValue<DWORD>(objData + 0xB4);
		//�ƶ����Լ����Ʒ
		if (objType == 289) {
			Pos pos = GetPos(person);
			//������������
			if (pos.x != 0 && pos.y != 0) {
				//�޸���Ʒ����
				utils::WriteValue(utils::ReadValue<DWORD>(objData + 196) + 16, pos.x - 2);
				utils::WriteValue(utils::ReadValue<DWORD>(objData + 196) + 20, pos.y - 2);
			}
		}
	}

	//������β�̫��������
	char da1[2] = { 0x75,0x12 };
	char da2[2] = { 0x74,0x12 };

	Sleep(400);
	DWORD OldProtect = { 0 };
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)0x2CA8C96, &da1, 2);//��Χд��
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, OldProtect, &OldProtect);
	Sleep(250);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)0x2CA8C96, &da2, 2);//��Χд��
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, OldProtect, &OldProtect);
}

//����û����Ʒ��Ҫ����
BOOL GameCall::IsHaveGoodsNeedPickUp() {
	DWORD objBase = 0;
	DWORD objData = 0;
	DWORD objType = 0;
	DWORD person = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD objOffset = utils::ReadValue<DWORD>(person + 0xD4);
	if (objOffset == 0) {
		return false;
	}
	DWORD start = utils::ReadValue<DWORD>(objOffset + OFFSET_START_ADDR);
	DWORD tail = utils::ReadValue<DWORD>(objOffset + OFFSET_TAIL_ADDR) - 4;
	DWORD num = (tail - start) / 4;
	for (int i = 0; i < num; i++) {
		objData = utils::ReadValue<DWORD>(start + 4 * i);
		objType = utils::ReadValue<DWORD>(objData + 0xB4);
		//��Ʒ���ͣ�����Щ��Ʒ�����ƶ�
		if (objType == 289) {
			return true;
		}
	}
	return false;
}

//������
Pos GameCall::GetPos(DWORD poiAddr) {
	DWORD pointer = 0;
	Pos pos = { 0 };
	if (utils::ReadValue<DWORD>(poiAddr + 0xB4) == 273) {
		pointer = utils::ReadValue<DWORD>(poiAddr + 484);
		pos.x = utils::ReadValue<float>(pointer + 0);
		pos.y = utils::ReadValue<float>(pointer + 4);
	}
	else {
		pointer = utils::ReadValue<DWORD>(poiAddr + 196);
		pos.x = utils::ReadValue<float>(pointer + 16);
		pos.y = utils::ReadValue<float>(pointer + 20);
	}
	return pos;
}

//�Ƿ���Ӫ��
BOOL GameCall::IsHaveFire() {
	DWORD ba = 0;
	DWORD type = 0;
	DWORD team = 0;
	DWORD code = 0;
	DWORD base = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD base2 = utils::ReadValue<DWORD>(base + OFFSET_MAP);
	if (base2 == 0) {
		return false;
	}
	DWORD start = utils::ReadValue<DWORD>(base2 + OFFSET_START_ADDR);
	DWORD tail = utils::ReadValue<DWORD>(base2 + OFFSET_TAIL_ADDR);
	DWORD num = (tail - start) / 4;
	for (int i = 0; i < num; i++) {
		ba = utils::ReadValue<DWORD>(start + 4 * i);
		type = utils::ReadValue<DWORD>(ba + 0xB4);
		team = utils::ReadValue<DWORD>(ba + 0x8C4);
		code = utils::ReadValue<DWORD>(ba + 0x450);
		if (type == 4 && team == 200) {
			if (code == 48026) {
				return true;
			}
		}
	}
	return false;
}

//��ͼ
void GameCall::GooutMap() {
	BufferCall(42);
	SendPacketCall();
}

//�ж��Ƿ��й���
BOOL GameCall::IsHaveMonster() {
	DWORD poin = 0;
	DWORD type = 0;
	DWORD team = 0;
	DWORD live = 0;
	DWORD base = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD base2 = utils::ReadValue<DWORD>(base + OFFSET_MAP);
	if (base2 == 0) {
		return false;
	}
	DWORD start = utils::ReadValue<DWORD>(base2 + OFFSET_START_ADDR);
	DWORD tail = utils::ReadValue<DWORD>(base2 + OFFSET_TAIL_ADDR);
	DWORD iterNum = (tail - start) / 4;
	for (DWORD i = 0; i < iterNum; i++) {
		poin = utils::ReadValue<DWORD>(start  + 4 * i);
		type = utils::ReadValue<DWORD>(poin + 0xB4);
		team = utils::ReadValue<DWORD>(poin + 0x8C4);
		live = utils::ReadValue<DWORD>(poin + 0x3E58);
		// ���������й���ֱ�ӷ���true
		if (type == 529 || type == 545) {
			if (poin != base && team > 0 && live > 0) {
				return true;
			}
		}
	}
	return false;
}

//ȡ����ָ��
DWORD GameCall::GetSkillPointer(DWORD pos) {
	DWORD base = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD base2 = utils::ReadValue<DWORD>(base + 26984);
	DWORD base3 = utils::ReadValue<DWORD>(base2 + 136);
	return utils::ReadValue<DWORD>(base3 + pos);
}

//������ȴ�ж�
BOOL GameCall::SkillCooling(DWORD skPo) {
	if (skPo <= 0) {
		return FALSE;
	}
	
	//��հ�
	utils::WriteValue(SKILL_COOLING_EMPTY_, 0);

	__asm 
	{
		PUSH 0;
		MOV EBX, skPo;
		MOV ECX, EBX;
		MOV EDX, BASEE_SKILL_COOLING_CALL_ADDR;
		CALL EDX;
		MOV ECX, SKILL_COOLING_EMPTY_;
		MOV ECX,DWORD PTR SS:[EAX];
	}
	DWORD res = utils::ReadValue<DWORD>(SKILL_COOLING_EMPTY_);

	std::wstringstream stream;
	stream << L"��ȡ������ȴ�����" << res;
	GameCall::Bulletin(stream.str());

	return  res< 0;
}

//�Զ�������
DWORD GameCall::AutoSkill() {
	//��D��
	if (SkillCooling(GetSkillPointer(8))) {
		GameCall::Bulletin(L"D��");
		MemKeyBorad(301,2);
	}
	//��A��
	if (SkillCooling(GetSkillPointer(0))) {
		GameCall::Bulletin(L"A��");
		MemKeyBorad(299, 2);
	}
	return 0;
}

//�����ͼ
DWORD GameCall::IntoMap(DWORD id, DWORD diff, DWORD chasm, DWORD task) {
	if (task == 0) { // û������
		BufferCall(16);
		EncryptCall(id, 4);
		EncryptCall(diff, 1);
		EncryptCall(4, 2);
		EncryptCall(chasm, 1);
		EncryptCall(0, 1);
		EncryptCall(65535, 2);
		EncryptCall(0, 4);
		EncryptCall(0, 1);
		EncryptCall(0, 4);
		EncryptCall(0, 1);
		EncryptCall(-1, 4);
		SendPacketCall();
	}
	else {
		BufferCall(16);
		EncryptCall(id, 4);
		EncryptCall(diff, 1);
		EncryptCall(4, 2);
		EncryptCall(0, 1);
		EncryptCall(0, 1);
		EncryptCall(65535, 2);
		EncryptCall(0, 4);
		EncryptCall(0, 1);
		EncryptCall(0, 4);
		EncryptCall(0, 1);
		EncryptCall(-1, 4);
		SendPacketCall();
	}
	return 0;
}

//���ѡͼ
DWORD GameCall::SelectMap() {
	BufferCall(15);
	EncryptCall(0, 4);
	SendPacketCall();
	return 0;
}

//����Call
DWORD GameCall::AreaCall(DWORD id) {

	__asm
	{
		PUSH id;
		PUSH - 1;
		MOV ECX, DWORD PTR SS : [BASE_AREA_PARAM_ADDR] ;
		MOV EAX, BASE_AREA_CALL_ADDR;
		CALL EAX;
	}
	//�������
	DWORD param = utils::ReadValue<DWORD>(BASE_AREA_PARAM_ADDR);
	DWORD bigArea = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR);
	DWORD smallArea = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR + 4);
	DWORD townX = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR + 8);
	DWORD townY = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR + 12);
	TownRemove(bigArea, smallArea, townX, townY);
}

//����ƶ�
DWORD GameCall::TownRemove(DWORD area, DWORD pos, DWORD x, DWORD y) {
	GameCall::BufferCall(36);
	GameCall::EncryptCall(area, 1);
	GameCall::EncryptCall(pos, 1);
	GameCall::EncryptCall(x, 2);
	GameCall::EncryptCall(y, 2);
	GameCall::EncryptCall(5, 1);
	GameCall::EncryptCall(38, 2);
	GameCall::EncryptCall(2, 2);
	GameCall::EncryptCall(0, 4);
	GameCall::EncryptCall(0, 1);
	GameCall::SendPacketCall();
	return 0;
}

//����CALL
DWORD GameCall::BufferCall(DWORD pa) {
	/*char buf[] = { 0xC3,0x90};
	DWORD OldProtect = { 0 };
	VirtualProtectEx(HANDLE(-1), (PVOID)0x,2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_ScopeWriteInAddr, &buf, 6);//��Χд��
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteInAddr, 6, OldProtect, &OldProtect);
	*/
	__asm
	{
		PUSH pa;
		MOV ECX, BASE_SEND_PACKET_ADDR;
		MOV ECX, DWORD PTR SS : [ECX] ;
		MOV EAX, BASE_BUFFER_CALL_ADDR;
		CALL EAX;
	}
}
//����CALL
DWORD GameCall::EncryptCall(DWORD pa, DWORD len) {
	DWORD tem = 0;
	if (len == 1) {
		tem = BASE_ENCRYPT_PACKET_CALL_ADDR;
	}
	else if (len == 2) {
		tem = BASE_ENCRYPT_PACKET_CALL_ADDR + 0x30;
	}
	else if (len == 4) {
		tem = BASE_ENCRYPT_PACKET_CALL_ADDR + 0x60;
	}
	else if (len == 8) {
		tem = BASE_ENCRYPT_PACKET_CALL_ADDR + 0x90;
	}
	__asm
	{
		PUSH pa
		MOV ECX, BASE_SEND_PACKET_ADDR;
		MOV ECX, DWORD PTR SS : [ECX] ;
		MOV EAX, tem;
		CALL EAX;
	}
}

//����CALL
DWORD GameCall::SendPacketCall() {
	__asm
	{
		MOV EAX, BASE_SEND_PACKET_CALL_ADDR;
		CALL EAX;
	}
}

//�Ƿ��ڳ���
DWORD GameCall::IsInTown() {
	DWORD base = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	return utils::ReadValue<DWORD>(base + OFFSET_MAP);
}

//��ȡ��Ϸ״̬  0ѡ���ɫ��1����2ѡͼ��3���
DWORD GameCall::GetGameState() {
	return utils::ReadValue<DWORD>(BASE_GAME_STATUS_ADDR);
}
/************************************
 * description:	����Ϸ������ʾ��Ϣ
 * param:text ��Ҫ��ʾ����Ϣ
 * time: 2020.03.06.00.06
 ************************************/
void GameCall::Bulletin(std::wstring text) {
	if (text.empty()) {
		return;
	}

	std::wstring value = L"��Ϸ��ң�";
	value += text;
	const wchar_t* txtAdr = value.c_str();

	__asm
	{
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0x24;//������ʾ��λ��
		PUSH 0xFF00;//������ɫ
		PUSH txtAdr;
		MOV ECX, BASE_STORE_ADDR;//�̵��ַ
		MOV ECX, [ECX];
		MOV ECX, [ECX + 0x50];
		MOV EAX, NOTICE_CALL_ADDR;//����Call
		CALL EAX;
	}
}

/************************************
 * description:	��������λ��,��ֵһ�㶼�ر��
 * ��	y 1132888064
 *	    x 1147289600
 * param:z Z�ᣬһ��Ϊ0����Խ�ǲ�����ֵ
 * param:y y�ᣬ
 * param:x x�ᣬ
 * time: 2020.03.07.10.53
 ************************************/
void GameCall::PersonSiteCall(DWORD z, DWORD y, DWORD x) {
	DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	__asm
	{
		PUSH z;
		PUSH y;
		PUSH x;
		MOV ECX, dwPersonObject;
		MOV EAX, BASE_PERSON_SITE_ADDR;
		CALL EAX;
	}
}

/************************************
 * description:	˳ͼ���ſ���ֱ�ӹ���ǰ���ǵÿ��ŵ�
	0��1�ң�2�ϣ�3��
	callͷ��������
	01DECA50    55              push ebp
	01DECA51    8BEC            mov ebp,esp
	01DECA53    6A FF           push -0x1
	01DECA55    68 1EF2C504     push 0x4C5F21E
	01DECA5A    64:A1 00000000  mov eax,dword ptr fs:[0]
	01DECA60    50              push eax
	01DECA61    83EC 38         sub esp,0x38
	01DECA64    A1 0C792906     mov eax,dword ptr ds:[0x629790C]
	01DECA69    33C5            xor eax,ebp
 * time: 2020.03.08.17.02
 ************************************/
void GameCall::PassMap(DWORD direction) {

	//�̵��ַ-8
	//8c����¿��ܻ�ı�
	__asm
	{

		MOV ECX, DWORD PTR SS : [BASE_ROOM_NUMBER_ADDR] ;
		MOV ECX, DWORD PTR SS : [ECX + BASE_TIME_ADDR] ;
		MOV ECX, DWORD PTR SS : [ECX + 0x8C] ;
		PUSH(-1);
		PUSH(-1);
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH direction;
		MOV EAX, BASE_PASS_MAP_CALL_ADDR;
		CALL EAX;
	}
}

/************************************
 * description:	��ȡ�����ڵ�ǰ�����λ��
 * return:	�ṹ��x,y
 * time: 2020.03.07.10.53
 ************************************/
Current_Room_Pos GameCall::CurrentRoomPos()
{

	Current_Room_Pos roleCurrentPos = { 0 };
	DWORD base = utils::ReadValue<DWORD>(BASE_STORE_ADDR - 0x8);
	if (0 == base) {
		GameCall::Bulletin(L"CurrentRoomPos ��һ��ʧ��");
		return Current_Room_Pos();
	}
	DWORD base2 = utils::ReadValue<DWORD>(base + BASE_TIME_ADDR);
	if (0 == base2) {
		GameCall::Bulletin(L"CurrentRoomPos �ڶ���ʧ��");
		return Current_Room_Pos();
	}
	DWORD base3 = utils::ReadValue<DWORD>(base2 + OFFSET_DOOR_TYPE_ADDR);
	if (0 == base3) {
		GameCall::Bulletin(L"CurrentRoomPos ������ʧ��");
		return Current_Room_Pos();
	}
	DWORD Role_Current_X = utils::ReadValue<DWORD>(base3 + OFFSET_CURRENT_ROOM_X); //��ȡ��ɫ��ǰX����

	DWORD Role_Current_Y = utils::ReadValue<DWORD>(base3 + OFFSET_CURRENT_ROOM_Y); //��ȡ��ɫ��ǰX����
	roleCurrentPos.x = Role_Current_X;
	roleCurrentPos.y = Role_Current_Y;
	return roleCurrentPos;
}

/************************************
 * description:	��ȡboss����x��y
 * return:	�ṹ��x,y
 * time: 2020.03.08.10.53
 ************************************/
Current_Room_Pos GameCall::BossRoomPos()
{
	Current_Room_Pos roleCurrentPos = { 0 };
	DWORD base = utils::ReadValue<DWORD>(BASE_STORE_ADDR - 0x8);
	if (0 == base) {
		GameCall::Bulletin(L"BossRoomPos ��һ��ʧ��");
		return Current_Room_Pos();
	}
	DWORD base2 = utils::ReadValue<DWORD>(base + BASE_TIME_ADDR);
	if (0 == base2) {
		GameCall::Bulletin(L"BossRoomPos �ڶ���ʧ��");
		return Current_Room_Pos();
	}
	DWORD base3 = utils::ReadValue<DWORD>(base2 + OFFSET_DOOR_TYPE_ADDR);
	if (0 == base3) {
		GameCall::Bulletin(L"BossRoomPos ������ʧ��");
		return Current_Room_Pos();
	}
	DWORD Role_Current_X = GameCall::Dectypt(base3 + OFFSET_BOSS_ROOM_X_ADDR);
	DWORD Role_Current_Y = GameCall::Dectypt(base3 + OFFSET_BOSS_ROOM_Y_ADDR) - 1;//���Ƕ���1
	roleCurrentPos.x = Role_Current_X;
	roleCurrentPos.y = Role_Current_Y;
	return roleCurrentPos;
}

/************************************
 * description:	�ڴ水��
 * param:vkCode ������
 * time: 2020.03.06.11.12
 ************************************/
void GameCall::MemKeyBorad(DWORD vkCode,DWORD time)
{
	DWORD keyBorad = utils::ReadValue<DWORD>(KEY_BOARD_ADDR);
	BYTE szKeyDown = { 1 };
	BYTE szKeyUP = { 0 };
	utils::WriteValue(keyBorad + vkCode, szKeyDown);
	Sleep(time * 30);
	utils::WriteValue(keyBorad + vkCode, szKeyUP);
	/*utils::WriteValue(keyBorad + vkCode, szKeyDown);
	Sleep(time*30);
	utils::WriteValue(keyBorad + vkCode, szKeyUP);*/
}

/************************************
 * description:	�����˺�ȫ�����������Ｐ����������˺�Ҳ��ȫ������
 * time: 2020.03.06.14.48
 ************************************/
void GameCall::FullScreenAttack()
{

	//��0F 85 05 01 00 00�� 
	char buf[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
	DWORD OldProtect = { 0 };
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteInAddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_ScopeWriteInAddr, &buf, 6);//��Χд��
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteInAddr, 6, OldProtect, &OldProtect);

	VirtualProtectEx(HANDLE(-1), (PVOID)Base_AttackScopeddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_AttackScopeddr, &buf, 6);//������Χ
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_AttackScopeddr, 6, OldProtect, &OldProtect);

	VirtualProtectEx(HANDLE(-1), (PVOID)Base_DamageScopeAddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_DamageScopeAddr, &buf, 6);//�˺���Χ
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_DamageScopeAddr, 6, OldProtect, &OldProtect);

	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteOutAddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_ScopeWriteOutAddr, &buf, 6);//��Χд��
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteOutAddr, 6, OldProtect, &OldProtect);
}

/************************************
 * description:	3���˺�
 *		����������
		33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3
		00 00 00 00 8B 5D 14 8B 45 08 8B F9
		+ 4D  ----����ַ��
		������ת
		02C260C9  E9 32 A6 7D FD 90
		���챶��
		00400700
		C7 45 10 03 00 00 00 89 B5 68 FE FF FF E9 BC 59 82 02 90 90
		���
		02C260E4  90 90 90 90 90
		02C26112  90 90 90 90 90
 *
 * time: 2020.03.08.10.35
 ************************************/
void GameCall::DoubleAttack()
{
	int len = 6, len1 = 5, len2 = 20;
	//��Ҫ���ǵ�������
	char buf[] = { 0x90,0x90,0x90,0x90,0x90 };
	char buf1[] = { 0xE9,0x32,0xA6,0x7D,0xFD,0x90 };
	char buf2[] = { 0xC7,0x45,0x10,0x02 ,0x00,0x00,0x00,0x89,
					0xB5,0x68,0xFE,0xFF ,0xFF,0xE9,0xBC,0x59,
					0x82,0x02,0x90,0x90 };
	DWORD OldProtect = { 0 };
	//���ı�����ַ���ֽ��룬��ת�� BASE_DOUBLE_ATTACK_REALIZE ��ַ
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_ADDR, len, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_ADDR, &buf1, len);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x02C260C9, len, OldProtect, &OldProtect);
	//���б���ʵ�֣�Ȼ����ת��ȥ
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_REALIZE, len2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_REALIZE, &buf2, len2);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x00400700, len2, OldProtect, &OldProtect);
	//�رռ�⣬ȫ����Ϊ NOP
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_1, len1, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_1, &buf, len1);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x02C260E4, len1, OldProtect, &OldProtect);
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_2, len1, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_2, &buf, 5);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x02C26112, len1, OldProtect, &OldProtect);
}

/************************************
 * description:	��ȡʣ��ƣ��ֵ
 * time: 2020.03.06.14.48
 ************************************/
DWORD GameCall::GetCurrentFatigue() {
	//����ƣ��ֵ
	DWORD consumeFg = Dectypt(BASE_FATIGUE_ADDR);
	//���ƣ��ֵ
	DWORD maxFg = GetMaxFatigue();
	return maxFg - consumeFg;
}

/************************************
 * description:	��ȡ����λ��
 * time: 2020.03.06.14.48
 ************************************/
void GameCall::GetPersonSite() {
	// DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD dwX = utils::ReadValue<DWORD>(BASE_PERSON_X_ADDR);
	DWORD dwY = utils::ReadValue<DWORD>(BASE_PERSON_Y_ADDR);
	DWORD dwZ = utils::ReadValue<DWORD>(BASE_PERSON_Z_ADDR);
	std::wstringstream stream;
	stream << L"X����" << dwX << L"����" << L"Y����" << dwY << L"��" << L"Z����" << dwZ << L"��";
	GameCall::Bulletin(stream.str());
}

/************************************
 * description:	��ȡ���ƣ��
 * time: 2020.03.06.14.48
 ************************************/
DWORD GameCall::GetMaxFatigue() {
	return GameCall::Dectypt(BASE_MAX_FATIGUE_ADDR);
}

/************************************
 * description:	��ȡ��������������
 * time: 2020.03.06.14.48
 ************************************/
DWORD GameCall::GetPowerAndMentality() {
	DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD dwPower = GameCall::Dectypt(dwPersonObject + BASE_PERSON_POWER_OFFSET);
	DWORD dwMentality = GameCall::Dectypt(dwPersonObject + BASE_PERSON_MENTALITY_OFFSET);
	return dwPower + dwMentality;
}

/************************************
 * description:	�鿴��ͼ�Ƿ���
 *	1û�д򿪣�0�򿪣��ر�������˵��δ��ͼ��
 * time: 2020.03.06.14.48
 ************************************/
BOOL GameCall::IsOpenDoor() {
	//�������+��ͼƫ��+�Ƿ���ƫ��
	DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD temp = utils::ReadValue<DWORD>(dwPersonObject + OFFSET_MAP);
	if (GameCall::Dectypt(temp + OFFSET_ISOPEN) == 0) {
		return true;
	}
	return false;
}

/************************************
 * description:	�鿴�Ƿ�ͨ��
 *	1û�д򿪣�0�򿪣��ر�������˵��δ��ͼ��
 * time: 2020.03.06.14.48
 ************************************/
 /*DWORD GameCall::IsPasser() {
	 //��ȡ�������
	 DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	 DWORD temp = utils::ReadValue<DWORD>(dwPersonObject + OFFSET_MAP);
	 return GameCall::Dectypt(temp + OFFSET_ISOPEN);
 }*/

 /************************************************************************/
 /* ����˵����DNF����
 /* param��_address ��Ҫ���ܵĵ�ַ
  * time: 2020.03.06.14.48
 /************************************************************************/
DWORD GameCall::Dectypt(DWORD _address)
{
	DWORD eax, esi, edx;
	eax = utils::ReadValue<DWORD>(_address);
	esi = utils::ReadValue<DWORD>(BASE_ENCRYPT_ADDR);
	edx = eax;
	edx >>= 16;
	edx = utils::ReadValue<DWORD>(esi + edx * 4 + 36);
	eax = eax & 0xffff;
	eax = utils::ReadValue<DWORD>(edx + eax * 4 + 8468);
	edx = WORD(eax);
	esi = edx;
	esi <<= 16;
	esi = esi ^ edx;
	edx = utils::ReadValue<DWORD>(_address + 4);
	eax = esi ^ edx;
	return eax;
}

/************************************************************************/
/* ����˵����DNF����
/* ����1��_address ��Ҫ���ܵĵ�ַ
/* ����2��value ��Ҫ���ܵ�ֵ
/* ����3��type �������ͣ�һ����0
/* Date��2019��7��18��10:26:52
/************************************************************************/
void GameCall::Encrypt(DWORD _address, DWORD value, DWORD type)
{
	int encryptID;
	int deviationParam;
	int deviationAddr;
	int data;
	int lastAddr;
	short ax;
	short si;
	encryptID = utils::ReadValue<DWORD>(_address);
	deviationParam = utils::ReadValue<DWORD>(BASE_DECTYPT_ADDR);
	deviationParam = utils::ReadValue<DWORD>(deviationParam + (encryptID >> 16) * 4 + 36);
	deviationAddr = deviationParam + (encryptID & 0xFFFF) * 4 + 8468;
	deviationParam = utils::ReadValue<DWORD>(deviationAddr);
	data = deviationParam & 0xFFFF;
	data = data + (data << 16);
	ax = (short)(deviationParam & 0xFFFF);
	si = 0;
	if (type == 0)
	{
		lastAddr = _address & 15;
		switch (lastAddr)
		{
		case 0:
			si = (short)(value >> 16);
			si = (short)(si - ax);
			si = (short)(si + value);
			break;
		case 4:
			si = (short)((value & 0xFFFF) - (value >> 16));;
			break;
		case 8:
			si = (short)(value >> 16);
			si = (short)(si * value);
			break;
		case 12:
			si = (short)(value >> 16);
			si = (short)(si + value);
			si = (short)(si + ax);
			break;
		default:
			break;
		}
	}
	else if (type == 1)
		si = value & 16;
	else if (type == 2)
		si = value;
	else if (type == 3)
	{
		si = value >> 16;
		si += value;
	}
	ax = (short)(si ^ ax);
	data = data ^ value;
	utils::WriteValue((_address + (type != 4 ? 4 : 8)), data);
	utils::WriteValue((deviationAddr + 2), ax);


}