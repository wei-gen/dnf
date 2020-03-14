#include "pch.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

//捡物品
void GameManager::PickUp() {
	while (GameCall::IsHaveGoodsNeedPickUp()) {
		Sleep(500);
		GameCall::RemoveProperty();
		Sleep(500);
		GameCall::MemKeyBorad(314, 1);
	}
}

// 自动刷图
// 需要副本ID  192，钢铁  104 格蓝迪
void GameManager::AutoAttack(DWORD mapId) {
	GameCall::Bulletin(L"自动刷图开始");
	DWORD area = 0;	//标志是否在入口
	DWORD fen = 0;//标志是否要分解装备,1
	//有疲劳或者在打怪自动刷
	while (GameCall::GetCurrentFatigue() > 0 || GameCall::GetGameState() == 3) {
		Sleep(1000);
		//有疲劳，在城镇
		if (GameCall::GetGameState() == 1) {
			if (fen == 1) {
				//分解4个物品
				for (int i = 9; i < 13; i++) {
					GameCall::BreakDownEquipment(i);
					Sleep(3000);
				}
			}
			if (area == 0) {
				GameCall::AreaCall(mapId);
				area = 1;
			}
			Sleep(1500);
			GameCall::SelectMap();//进入选图
			Sleep(1500);
			GameCall::IntoMap(mapId, 4, 0, 0);//选择图，噩梦级
			Sleep(5000);// 要等待载入
			GameCall::invincible(1);
			Sleep(1000);
			fen = 0;
		}
		if (GameCall::GetGameState() == 3) {
			//门没开，还有怪
			if (!GameCall::IsOpenDoor() || GameCall::IsHaveMonster()) {
				GameCall::MemKeyBorad(314, 1);//按X键
			}
			Sleep(1000);
			//门开了，没怪了
			if (GameCall::IsOpenDoor() && !GameCall::IsHaveMonster()) {
				//还有物品没捡起来
				PickUp();
				Sleep(1000);
				//看要往哪走
				Current_Room_Pos pos = GameCall::CurrentRoomPos();
				if (pos.x == 0 && pos.y == 0) {//第一个房间
					GameCall::PassMap(1);
				}
				else if (pos.x == 1 && pos.y == 0) {
					GameCall::PassMap(1);
				}
				else if (pos.x == 2 && pos.y == 0) {
					GameCall::PassMap(3);
				}
				else if (pos.x == 2 && pos.y == 1) {
					GameCall::PassMap(0);
				}
				else if (pos.x == 1 && pos.y == 1) {
					GameCall::PassMap(3);
				}
				else if (pos.x == 1 && pos.y == 2) {
					GameCall::PassMap(1);
				}
				else if (pos.x == 2 && pos.y == 2) {
					GameCall::PassMap(1);
				}
				/*if (pos.x == 0 && pos.y == 0) {//第一个房间
					GameCall::PassMap(1);
				}
				else if (pos.x == 1 && pos.y == 0) {
					GameCall::PassMap(1);
				}
				else if (pos.x == 2 && pos.y == 0) {
					GameCall::PassMap(3);
				}
				else if (pos.x == 2 && pos.y == 1) {
					GameCall::PassMap(3);
				}
				else if (pos.x == 2 && pos.y == 2) {
					GameCall::PassMap(1);
				}
				else if (pos.x == 3 && pos.y == 2) {
					GameCall::PassMap(2);
				}*/
			
			}
			//在boss房间并且没有怪物
			if (GameManager::IsInBossRoom() && !GameCall::IsHaveMonster()) {
				Sleep(2000);
				//还有物品没捡起来
				PickUp();
			}
			//判断营火出现
			if (GameCall::IsHaveFire()) {
				fen = 1;
				Sleep(1000);
				DWORD pl = GameCall::GetCurrentFatigue();
				std::wstringstream stream;
				stream << L"剩余疲劳：" << pl;
				GameCall::Bulletin(stream.str());
				Sleep(1000);
				GameCall::GooutMap();//出图
				Sleep(3000);
			}
		
		}
		
	}
	GameCall::Bulletin(L"自动刷图结束");
}

void GameManager::DownXKey() {

	while (true) {
		GameCall::MemKeyBorad(314,1);
	}
}

void GameManager::QuanPingGongJi() {

	while (true) {
		GameCall::FullScreenAttack();
	}
}

//判断是否在boss房间
BOOL GameManager::IsInBossRoom() {
	Current_Room_Pos crp = GameCall::CurrentRoomPos();
	Current_Room_Pos bossPos = GameCall::BossRoomPos();
	if (crp.x == bossPos.x && crp.y == bossPos.y) {
		return TRUE;
	}
	else
		return FALSE;
}

// 强制过图
void GameManager::PassMapUp() {
	GameCall::PassMap(2);
}
void GameManager::PassMapDown() {
	GameCall::PassMap(3);
}
void GameManager::PassMapLeft() {
	GameCall::PassMap(0);
}
void GameManager::PassMapRight() {
	GameCall::PassMap(1);
}

//移动
void remove(DWORD mapId) {
	if()
}