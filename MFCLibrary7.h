// MFCLibrary7.h: MFCLibrary7 DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include "MainDlg.h"

DWORD WINAPI ShowDialog(LPARAM lpData);
// CMFCLibrary7App
// 有关此类实现的信息，请参阅 MFCLibrary7.cpp
//

class CMFCLibrary7App : public CWinApp
{
public:
	CMFCLibrary7App();
	

private:

// 重写
public:
	virtual BOOL InitInstance();



	DECLARE_MESSAGE_MAP()
};
