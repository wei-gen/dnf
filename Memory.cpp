#include "pch.h"
#include "Memory.h"

/************************************
 * description:	读取2字节内存
 * param:hProcess	进程句柄
 * param:dwReadAddr	地址
 * param:bStatus	状态
 * time: 2020.03.06.00.15
 ************************************/
DWORD Memory::ReadMemory_DWORD(HANDLE hProcess, DWORD dwReadAddr, BOOL* bStatus)
{
	DWORD dwMemory = 0;
	BOOL fok;
	fok = ReadProcessMemory(hProcess,
		(LPCVOID)dwReadAddr,
		&dwMemory,
		4,
		NULL);
	if (bStatus != 0)
		*bStatus = fok;
	return dwMemory;
}

/************************************
 * description:	读取1字节内存
 * param:hProcess	进程句柄
 * param:dwReadAddr	地址
 * param:bStatus	状态
 * time: 2020.03.06.00.17
 ************************************/
BYTE Memory::ReadMemory_BYTE(HANDLE hProcess, DWORD dwReadAddr, BOOL* bStatus)
{
	BYTE dwMemory = 0;
	BOOL fok;
	fok = ReadProcessMemory(hProcess,
		(LPCVOID)dwReadAddr,
		&dwMemory,
		1,
		NULL);
	if (bStatus != 0)
		*bStatus = fok;
	return dwMemory;
}

/************************************
 * description:	读取4字节内存(单浮点)
 * param:hProcess	进程句柄
 * param:dwReadAddr	地址
 * param:bStatus	状态
 * time: 2020.03.06.00.17
 ************************************/
float Memory::ReadMemory_float(HANDLE hProcess, DWORD dwReadAddr, BOOL* bStatus)
{
	float fMemory = 0;
	BOOL fok;
	fok = ReadProcessMemory(hProcess,
		(LPCVOID)dwReadAddr,
		&fMemory,
		4,
		NULL);
	if (bStatus != 0)
		*bStatus = fok;
	return fMemory;
}

/************************************
 * description:	写入2字节数据
 * param:hProcess	进程句柄
 * param:dwReadAddr	地址
 * param:bStatus	状态
 * time: 2020.03.06.00.17
 ************************************/
BOOL Memory::WriteMemory_DWORD(HANDLE hProcess, DWORD dwReadAddr, DWORD dwNum)
{
	return WriteProcessMemory(hProcess,
		(LPVOID)dwReadAddr,
		&dwNum,
		4,
		NULL
	);
}

/************************************
 * description:	写入4字节数据(float)
 * param:hProcess	进程句柄
 * param:dwReadAddr	地址
 * param:bStatus	状态
 * time: 2020.03.06.00.17
 ************************************/
BOOL Memory::WriteMemory_float(HANDLE hProcess, DWORD dwReadAddr, float fNum)
{
	return WriteProcessMemory(hProcess,
		(LPVOID)dwReadAddr,
		&fNum,
		4,
		NULL
	);
}