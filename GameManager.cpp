#include "pch.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

//����Ʒ
void GameManager::PickUp() {
	while (GameCall::IsHaveGoodsNeedPickUp()) {
		Sleep(500);
		GameCall::RemoveProperty();
		Sleep(500);
		GameCall::MemKeyBorad(314, 1);
	}
}

// �Զ�ˢͼ
// ��Ҫ����ID  192������  104 ������
void GameManager::AutoAttack(DWORD mapId) {
	GameCall::Bulletin(L"�Զ�ˢͼ��ʼ");
	DWORD area = 0;	//��־�Ƿ������
	DWORD fen = 0;//��־�Ƿ�Ҫ�ֽ�װ��,1
	//��ƣ�ͻ����ڴ���Զ�ˢ
	while (GameCall::GetCurrentFatigue() > 0 || GameCall::GetGameState() == 3) {
		Sleep(1000);
		//��ƣ�ͣ��ڳ���
		if (GameCall::GetGameState() == 1) {
			if (fen == 1) {
				//�ֽ�4����Ʒ
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
			GameCall::SelectMap();//����ѡͼ
			Sleep(1500);
			GameCall::IntoMap(mapId, 4, 0, 0);//ѡ��ͼ��ج�μ�
			Sleep(5000);// Ҫ�ȴ�����
			GameCall::invincible(1);
			Sleep(1000);
			fen = 0;
		}
		if (GameCall::GetGameState() == 3) {
			//��û�������й�
			if (!GameCall::IsOpenDoor() || GameCall::IsHaveMonster()) {
				GameCall::MemKeyBorad(314, 1);//��X��
			}
			Sleep(1000);
			//�ſ��ˣ�û����
			if (GameCall::IsOpenDoor() && !GameCall::IsHaveMonster()) {
				//������Ʒû������
				PickUp();
				Sleep(1000);
				//��Ҫ������
				Current_Room_Pos pos = GameCall::CurrentRoomPos();
				if (pos.x == 0 && pos.y == 0) {//��һ������
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
				/*if (pos.x == 0 && pos.y == 0) {//��һ������
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
			//��boss���䲢��û�й���
			if (GameManager::IsInBossRoom() && !GameCall::IsHaveMonster()) {
				Sleep(2000);
				//������Ʒû������
				PickUp();
			}
			//�ж�Ӫ�����
			if (GameCall::IsHaveFire()) {
				fen = 1;
				Sleep(1000);
				DWORD pl = GameCall::GetCurrentFatigue();
				std::wstringstream stream;
				stream << L"ʣ��ƣ�ͣ�" << pl;
				GameCall::Bulletin(stream.str());
				Sleep(1000);
				GameCall::GooutMap();//��ͼ
				Sleep(3000);
			}
		
		}
		
	}
	GameCall::Bulletin(L"�Զ�ˢͼ����");
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

//�ж��Ƿ���boss����
BOOL GameManager::IsInBossRoom() {
	Current_Room_Pos crp = GameCall::CurrentRoomPos();
	Current_Room_Pos bossPos = GameCall::BossRoomPos();
	if (crp.x == bossPos.x && crp.y == bossPos.y) {
		return TRUE;
	}
	else
		return FALSE;
}

// ǿ�ƹ�ͼ
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

//�ƶ�
void remove(DWORD mapId) {
	if()
}