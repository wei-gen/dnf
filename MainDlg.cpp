// MainDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCLibrary7.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

// MainDlg 对话框

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MainDlg::~MainDlg()
{
}



BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &MainDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &MainDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON9, &MainDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON15, &MainDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON19, &MainDlg::OnBnClickedButton19)
END_MESSAGE_MAP()


// MainDlg 消息处理程序
// 全屏攻击
void MainDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	GameCall::FullScreenAttack();
	GameCall::Bulletin(L"开启全屏攻击！");
}

//秒杀
void MainDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	GameCall::DoubleAttack();
	GameCall::Bulletin(L"开启秒杀");
}

//测试自动放技能
void MainDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	GameCall::AutoSkill();
}

// 测试自动刷图（格蓝迪）
void MainDlg::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GameManager::AutoAttack, NULL, NULL, NULL);
	CloseHandle(hThread);
}

// 测试分解
void MainDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GameCall::BreakDownEquipment(9);
	GameCall::Bulletin(L"分解成功！");
}


/*
//第一个图,门没开，并且还有怪
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 3);
		}
		//吸取物品
		GameCall::PickUp();
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		Sleep(500);
		GameCall::Bulletin(L"通过第1个图");
		//第二个图
		GameCall::PassMap(1);
		GameCall::Bulletin(L"通过第2个图");
		Sleep(500);
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 3);
		}
		//吸取物品
		GameCall::PickUp();
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		//第三个图
		GameCall::PassMap(1);
		GameCall::Bulletin(L"通过第3个图");
		Sleep(500);
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 3);
		}
		//吸取物品
		GameCall::PickUp();
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		//第四个图
		GameCall::PassMap(3);
		GameCall::Bulletin(L"通过第4个图");
		Sleep(500);
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 3);
		}
		//吸取物品
		Sleep(500);
		GameCall::PickUp();
		Sleep(500);
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		Sleep(500);
		//第5个图
		GameCall::PassMap(3);
		GameCall::Bulletin(L"通过第5个图");
		Sleep(500);
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 3);
		}
		//吸取物品
		Sleep(500);
		GameCall::PickUp();
		Sleep(500);
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		Sleep(500);
		//第6个图
		GameCall::PassMap(1);
		GameCall::Bulletin(L"通过第6个图");
		Sleep(500);
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 3);
		}
		//吸取物品
		Sleep(500);
		GameCall::PickUp();
		Sleep(500);
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		Sleep(500);
		//第7个图
		GameCall::PassMap(2);
		GameCall::Bulletin(L"通过第7个图");
		Sleep(200);
		while (!GameCall::IsOpenDoor() && GameCall::IsHaveMonster()) {
			//一直按X
			GameCall::MemKeyBorad(314, 1);
		}
		//吸取物品
		Sleep(500);
		GameCall::PickUp();
		Sleep(500);
		//有物品就按X
		while (GameCall::IsHaveGoodsNeedPickUp()) {
			//一直按X
			GameCall::MemKeyBorad(314, 30);
		}
		Sleep(500);

		//判断营火出现
		if (GameCall::IsHaveFire()) {
			Sleep(1500);
			GameCall::GooutMap();//出图
			Sleep(8000);
		}
*/