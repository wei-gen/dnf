#pragma once
#include <iostream>

//����λ��
typedef struct _Current_Room_Pos
{
	int x;
	int y;
}Current_Room_Pos, * PCurrent_Room_Pos;

//��ͼ�����λ��
typedef struct _Pos
{
	float x;
	float y;
}Pos, * PPos;

typedef struct Map_Data
{
	char name[100] ;
	DWORD id;
	DWORD aisle[100];
	LPARAM startPos;
	LPARAM tailPos;
	DWORD wide;
	DWORD len;
	LPARAM go[100];
	DWORD fg;

};

namespace GameCall{
	void BreakDownEquipment(DWORD equPos);
	void SellEquipment(DWORD equPos);
	void invincible(DWORD v);
	void Bulletin(std::wstring text);
	void MemKeyBorad(DWORD vkCode, DWORD time);
	void FullScreenAttack();
	DWORD GetCurrentFatigue();
	DWORD GetMaxFatigue();
	DWORD GetPowerAndMentality();
	DWORD Dectypt(DWORD _address);
	void Encrypt(DWORD _address, DWORD value, DWORD type);
	BOOL IsOpenDoor();
	DWORD IsPasser();
	void PersonSiteCall(DWORD z, DWORD y, DWORD x);
	void GetPersonSite();
	void DoubleAttack();
	Current_Room_Pos CurrentRoomPos();
	Current_Room_Pos BossRoomPos();
	void PassMap(DWORD direction);
	DWORD GetGameState();
	DWORD IsInTown();
	DWORD BufferCall(DWORD pa);
	DWORD EncryptCall(DWORD pa, DWORD len);
	DWORD SendPacketCall();
	DWORD AreaCall(DWORD id);
	BOOL IsHaveGoodsNeedPickUp();
	DWORD AutoSkill();
	BOOL SkillCooling(DWORD skPo);
	DWORD GetSkillPointer(DWORD pos);
	BOOL IsHaveMonster();
	DWORD TownRemove(DWORD area, DWORD pos, DWORD x, DWORD y);//����ƶ�
	DWORD SelectMap();
	DWORD IntoMap(DWORD id,DWORD diff,DWORD chasm,DWORD task);//�����ͼ
	void GooutMap();//��ͼ
	BOOL IsHaveFire();
	Pos GetPos(DWORD pointer);
	void RemoveProperty();
};

