// MFCLibrary7.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "MFCLibrary7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCLibrary7App

BEGIN_MESSAGE_MAP(CMFCLibrary7App, CWinApp)
END_MESSAGE_MAP()


// CMFCLibrary7App 构造

CMFCLibrary7App::CMFCLibrary7App()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCLibrary7App 对象

CMFCLibrary7App theApp;


// CMFCLibrary7App 初始化

BOOL CMFCLibrary7App::InitInstance()
{
	CWinApp::InitInstance();
	HANDLE hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ShowDialog, NULL, NULL, NULL);//创建线程
	return TRUE;
}
MainDlg* mdlg;
DWORD WINAPI ShowDialog(LPARAM lpData)
{
	mdlg = new MainDlg;//给指针分配空间 
	mdlg->DoModal();//阻塞的方式 模态窗口
	delete mdlg;//释放空间
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);//释放DLL退出线程
	return TRUE;
}



