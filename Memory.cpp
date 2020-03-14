#include "pch.h"
#include "Memory.h"

/************************************
 * description:	��ȡ2�ֽ��ڴ�
 * param:hProcess	���̾��
 * param:dwReadAddr	��ַ
 * param:bStatus	״̬
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
 * description:	��ȡ1�ֽ��ڴ�
 * param:hProcess	���̾��
 * param:dwReadAddr	��ַ
 * param:bStatus	״̬
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
 * description:	��ȡ4�ֽ��ڴ�(������)
 * param:hProcess	���̾��
 * param:dwReadAddr	��ַ
 * param:bStatus	״̬
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
 * description:	д��2�ֽ�����
 * param:hProcess	���̾��
 * param:dwReadAddr	��ַ
 * param:bStatus	״̬
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
 * description:	д��4�ֽ�����(float)
 * param:hProcess	���̾��
 * param:dwReadAddr	��ַ
 * param:bStatus	״̬
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