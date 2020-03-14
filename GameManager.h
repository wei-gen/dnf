#pragma once
#include "GameCall.h"

namespace GameManager {

	void DownXKey();

	void QuanPingGongJi();

	BOOL IsInBossRoom();
	
	void PassMapUp();
	void PassMapDown();
	void PassMapLeft();
	void PassMapRight();
	void PickUp();
	void AutoAttack(DWORD mapId);
}