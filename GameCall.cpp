#include "pch.h"
#include "GameCall.h"
#include "GameBaseAddress.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <sstream>

/************************************************************************/
/* 函数说明：DNF组包卖物
/* 参数一：equPos  背包栏索引  从9开始是第一个栏位
/* Date：2019年8月16日14:23:31
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
/* 函数说明：DNF组包分解
/* 参数一：equPos  背包栏索引  从9开始是第一个栏位
/* Date：2019年8月16日14:23:31
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

//透明无敌   1开0关
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

//全屏移动物品
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
		//移动可以捡的物品
		if (objType == 289) {
			Pos pos = GetPos(person);
			//人物坐标正常
			if (pos.x != 0 && pos.y != 0) {
				//修改物品坐标
				utils::WriteValue(utils::ReadValue<DWORD>(objData + 196) + 16, pos.x - 2);
				utils::WriteValue(utils::ReadValue<DWORD>(objData + 196) + 20, pos.y - 2);
			}
		}
	}

	//下面这段不太明白作用
	char da1[2] = { 0x75,0x12 };
	char da2[2] = { 0x74,0x12 };

	Sleep(400);
	DWORD OldProtect = { 0 };
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)0x2CA8C96, &da1, 2);//范围写入
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, OldProtect, &OldProtect);
	Sleep(250);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)0x2CA8C96, &da2, 2);//范围写入
	VirtualProtectEx(HANDLE(-1), (PVOID)0x2CA8C96, 2, OldProtect, &OldProtect);
}

//还有没有物品需要捡起
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
		//物品类型，还有些物品不能移动
		if (objType == 289) {
			return true;
		}
	}
	return false;
}

//读坐标
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

//是否有营火
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

//出图
void GameCall::GooutMap() {
	BufferCall(42);
	SendPacketCall();
}

//判断是否有怪物
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
		// 类型里面有怪物直接返回true
		if (type == 529 || type == 545) {
			if (poin != base && team > 0 && live > 0) {
				return true;
			}
		}
	}
	return false;
}

//取技能指针
DWORD GameCall::GetSkillPointer(DWORD pos) {
	DWORD base = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD base2 = utils::ReadValue<DWORD>(base + 26984);
	DWORD base3 = utils::ReadValue<DWORD>(base2 + 136);
	return utils::ReadValue<DWORD>(base3 + pos);
}

//技能冷却判断
BOOL GameCall::SkillCooling(DWORD skPo) {
	if (skPo <= 0) {
		return FALSE;
	}
	
	//填空白
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
	stream << L"读取技能冷却结果：" << res;
	GameCall::Bulletin(stream.str());

	return  res< 0;
}

//自动发技能
DWORD GameCall::AutoSkill() {
	//按D键
	if (SkillCooling(GetSkillPointer(8))) {
		GameCall::Bulletin(L"D键");
		MemKeyBorad(301,2);
	}
	//按A键
	if (SkillCooling(GetSkillPointer(0))) {
		GameCall::Bulletin(L"A键");
		MemKeyBorad(299, 2);
	}
	return 0;
}

//组包进图
DWORD GameCall::IntoMap(DWORD id, DWORD diff, DWORD chasm, DWORD task) {
	if (task == 0) { // 没有任务
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

//组包选图
DWORD GameCall::SelectMap() {
	BufferCall(15);
	EncryptCall(0, 4);
	SendPacketCall();
	return 0;
}

//区域Call
DWORD GameCall::AreaCall(DWORD id) {

	__asm
	{
		PUSH id;
		PUSH - 1;
		MOV ECX, DWORD PTR SS : [BASE_AREA_PARAM_ADDR] ;
		MOV EAX, BASE_AREA_CALL_ADDR;
		CALL EAX;
	}
	//区域参数
	DWORD param = utils::ReadValue<DWORD>(BASE_AREA_PARAM_ADDR);
	DWORD bigArea = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR);
	DWORD smallArea = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR + 4);
	DWORD townX = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR + 8);
	DWORD townY = utils::ReadValue<DWORD>(param + OFFSET_AREA_ADDR + 12);
	TownRemove(bigArea, smallArea, townX, townY);
}

//组包移动
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

//缓冲CALL
DWORD GameCall::BufferCall(DWORD pa) {
	/*char buf[] = { 0xC3,0x90};
	DWORD OldProtect = { 0 };
	VirtualProtectEx(HANDLE(-1), (PVOID)0x,2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_ScopeWriteInAddr, &buf, 6);//范围写入
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
//加密CALL
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

//发包CALL
DWORD GameCall::SendPacketCall() {
	__asm
	{
		MOV EAX, BASE_SEND_PACKET_CALL_ADDR;
		CALL EAX;
	}
}

//是否在城镇
DWORD GameCall::IsInTown() {
	DWORD base = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	return utils::ReadValue<DWORD>(base + OFFSET_MAP);
}

//获取游戏状态  0选择角色，1城镇，2选图，3打怪
DWORD GameCall::GetGameState() {
	return utils::ReadValue<DWORD>(BASE_GAME_STATUS_ADDR);
}
/************************************
 * description:	在游戏公告显示信息
 * param:text 需要显示的信息
 * time: 2020.03.06.00.06
 ************************************/
void GameCall::Bulletin(std::wstring text) {
	if (text.empty()) {
		return;
	}

	std::wstring value = L"游戏外挂：";
	value += text;
	const wchar_t* txtAdr = value.c_str();

	__asm
	{
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH 0x24;//喇叭显示的位置
		PUSH 0xFF00;//喇叭颜色
		PUSH txtAdr;
		MOV ECX, BASE_STORE_ADDR;//商店基址
		MOV ECX, [ECX];
		MOV ECX, [ECX + 0x50];
		MOV EAX, NOTICE_CALL_ADDR;//公告Call
		CALL EAX;
	}
}

/************************************
 * description:	设置人物位置,数值一般都特别大
 * 如	y 1132888064
 *	    x 1147289600
 * param:z Z轴，一般为0，跳越是才有数值
 * param:y y轴，
 * param:x x轴，
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
 * description:	顺图，门开了直接过，前提是得开门的
	0左，1右，2上，3下
	call头部特征码
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

	//商店基址-8
	//8c大更新可能会改变
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
 * description:	获取人物在当前房间的位置
 * return:	结构体x,y
 * time: 2020.03.07.10.53
 ************************************/
Current_Room_Pos GameCall::CurrentRoomPos()
{

	Current_Room_Pos roleCurrentPos = { 0 };
	DWORD base = utils::ReadValue<DWORD>(BASE_STORE_ADDR - 0x8);
	if (0 == base) {
		GameCall::Bulletin(L"CurrentRoomPos 第一步失败");
		return Current_Room_Pos();
	}
	DWORD base2 = utils::ReadValue<DWORD>(base + BASE_TIME_ADDR);
	if (0 == base2) {
		GameCall::Bulletin(L"CurrentRoomPos 第二步失败");
		return Current_Room_Pos();
	}
	DWORD base3 = utils::ReadValue<DWORD>(base2 + OFFSET_DOOR_TYPE_ADDR);
	if (0 == base3) {
		GameCall::Bulletin(L"CurrentRoomPos 第三步失败");
		return Current_Room_Pos();
	}
	DWORD Role_Current_X = utils::ReadValue<DWORD>(base3 + OFFSET_CURRENT_ROOM_X); //获取角色当前X坐标

	DWORD Role_Current_Y = utils::ReadValue<DWORD>(base3 + OFFSET_CURRENT_ROOM_Y); //获取角色当前X坐标
	roleCurrentPos.x = Role_Current_X;
	roleCurrentPos.y = Role_Current_Y;
	return roleCurrentPos;
}

/************************************
 * description:	获取boss房间x，y
 * return:	结构体x,y
 * time: 2020.03.08.10.53
 ************************************/
Current_Room_Pos GameCall::BossRoomPos()
{
	Current_Room_Pos roleCurrentPos = { 0 };
	DWORD base = utils::ReadValue<DWORD>(BASE_STORE_ADDR - 0x8);
	if (0 == base) {
		GameCall::Bulletin(L"BossRoomPos 第一步失败");
		return Current_Room_Pos();
	}
	DWORD base2 = utils::ReadValue<DWORD>(base + BASE_TIME_ADDR);
	if (0 == base2) {
		GameCall::Bulletin(L"BossRoomPos 第二步失败");
		return Current_Room_Pos();
	}
	DWORD base3 = utils::ReadValue<DWORD>(base2 + OFFSET_DOOR_TYPE_ADDR);
	if (0 == base3) {
		GameCall::Bulletin(L"BossRoomPos 第三步失败");
		return Current_Room_Pos();
	}
	DWORD Role_Current_X = GameCall::Dectypt(base3 + OFFSET_BOSS_ROOM_X_ADDR);
	DWORD Role_Current_Y = GameCall::Dectypt(base3 + OFFSET_BOSS_ROOM_Y_ADDR) - 1;//总是多了1
	roleCurrentPos.x = Role_Current_X;
	roleCurrentPos.y = Role_Current_Y;
	return roleCurrentPos;
}

/************************************
 * description:	内存按键
 * param:vkCode 按键码
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
 * description:	所有伤害全屏攻击，怪物及其他打出的伤害也是全屏攻击
 * time: 2020.03.06.14.48
 ************************************/
void GameCall::FullScreenAttack()
{

	//“0F 85 05 01 00 00” 
	char buf[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
	DWORD OldProtect = { 0 };
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteInAddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_ScopeWriteInAddr, &buf, 6);//范围写入
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteInAddr, 6, OldProtect, &OldProtect);

	VirtualProtectEx(HANDLE(-1), (PVOID)Base_AttackScopeddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_AttackScopeddr, &buf, 6);//攻击范围
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_AttackScopeddr, 6, OldProtect, &OldProtect);

	VirtualProtectEx(HANDLE(-1), (PVOID)Base_DamageScopeAddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_DamageScopeAddr, &buf, 6);//伤害范围
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_DamageScopeAddr, 6, OldProtect, &OldProtect);

	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteOutAddr, 6, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)Base_ScopeWriteOutAddr, &buf, 6);//范围写出
	VirtualProtectEx(HANDLE(-1), (PVOID)Base_ScopeWriteOutAddr, 6, OldProtect, &OldProtect);
}

/************************************
 * description:	3倍伤害
 *		倍功特侦码
		33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3
		00 00 00 00 8B 5D 14 8B 45 08 8B F9
		+ 4D  ----》地址处
		制造跳转
		02C260C9  E9 32 A6 7D FD 90
		制造倍功
		00400700
		C7 45 10 03 00 00 00 89 B5 68 FE FF FF E9 BC 59 82 02 90 90
		检测
		02C260E4  90 90 90 90 90
		02C26112  90 90 90 90 90
 *
 * time: 2020.03.08.10.35
 ************************************/
void GameCall::DoubleAttack()
{
	int len = 6, len1 = 5, len2 = 20;
	//需要覆盖的特侦码
	char buf[] = { 0x90,0x90,0x90,0x90,0x90 };
	char buf1[] = { 0xE9,0x32,0xA6,0x7D,0xFD,0x90 };
	char buf2[] = { 0xC7,0x45,0x10,0x02 ,0x00,0x00,0x00,0x89,
					0xB5,0x68,0xFE,0xFF ,0xFF,0xE9,0xBC,0x59,
					0x82,0x02,0x90,0x90 };
	DWORD OldProtect = { 0 };
	//更改倍功地址的字节码，跳转到 BASE_DOUBLE_ATTACK_REALIZE 地址
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_ADDR, len, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_ADDR, &buf1, len);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x02C260C9, len, OldProtect, &OldProtect);
	//进行倍功实现，然后跳转回去
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_REALIZE, len2, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_REALIZE, &buf2, len2);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x00400700, len2, OldProtect, &OldProtect);
	//关闭检测，全部置为 NOP
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_1, len1, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_1, &buf, len1);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x02C260E4, len1, OldProtect, &OldProtect);
	VirtualProtectEx(HANDLE(-1), (PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_2, len1, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy((PVOID)BASE_DOUBLE_ATTACK_DET_ADDR_2, &buf, 5);
	VirtualProtectEx(HANDLE(-1), (PVOID)0x02C26112, len1, OldProtect, &OldProtect);
}

/************************************
 * description:	获取剩余疲劳值
 * time: 2020.03.06.14.48
 ************************************/
DWORD GameCall::GetCurrentFatigue() {
	//消耗疲劳值
	DWORD consumeFg = Dectypt(BASE_FATIGUE_ADDR);
	//最大疲劳值
	DWORD maxFg = GetMaxFatigue();
	return maxFg - consumeFg;
}

/************************************
 * description:	获取人物位置
 * time: 2020.03.06.14.48
 ************************************/
void GameCall::GetPersonSite() {
	// DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD dwX = utils::ReadValue<DWORD>(BASE_PERSON_X_ADDR);
	DWORD dwY = utils::ReadValue<DWORD>(BASE_PERSON_Y_ADDR);
	DWORD dwZ = utils::ReadValue<DWORD>(BASE_PERSON_Z_ADDR);
	std::wstringstream stream;
	stream << L"X：【" << dwX << L"】，" << L"Y：【" << dwY << L"】" << L"Z：【" << dwZ << L"】";
	GameCall::Bulletin(stream.str());
}

/************************************
 * description:	获取最大疲劳
 * time: 2020.03.06.14.48
 ************************************/
DWORD GameCall::GetMaxFatigue() {
	return GameCall::Dectypt(BASE_MAX_FATIGUE_ADDR);
}

/************************************
 * description:	获取力量和智力两倍
 * time: 2020.03.06.14.48
 ************************************/
DWORD GameCall::GetPowerAndMentality() {
	DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD dwPower = GameCall::Dectypt(dwPersonObject + BASE_PERSON_POWER_OFFSET);
	DWORD dwMentality = GameCall::Dectypt(dwPersonObject + BASE_PERSON_MENTALITY_OFFSET);
	return dwPower + dwMentality;
}

/************************************
 * description:	查看地图是否开门
 *	1没有打开，0打开，特别大的数字说明未在图中
 * time: 2020.03.06.14.48
 ************************************/
BOOL GameCall::IsOpenDoor() {
	//人物对象+地图偏移+是否开门偏移
	DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	DWORD temp = utils::ReadValue<DWORD>(dwPersonObject + OFFSET_MAP);
	if (GameCall::Dectypt(temp + OFFSET_ISOPEN) == 0) {
		return true;
	}
	return false;
}

/************************************
 * description:	查看是否通关
 *	1没有打开，0打开，特别大的数字说明未在图中
 * time: 2020.03.06.14.48
 ************************************/
 /*DWORD GameCall::IsPasser() {
	 //获取人物对象
	 DWORD dwPersonObject = utils::ReadValue<DWORD>(BASE_PERSON_ADDR);
	 DWORD temp = utils::ReadValue<DWORD>(dwPersonObject + OFFSET_MAP);
	 return GameCall::Dectypt(temp + OFFSET_ISOPEN);
 }*/

 /************************************************************************/
 /* 函数说明：DNF解密
 /* param：_address 需要解密的地址
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
/* 函数说明：DNF加密
/* 参数1：_address 需要加密的地址
/* 参数2：value 需要加密的值
/* 参数3：type 加密类型，一般填0
/* Date：2019年7月18日10:26:52
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