#pragma once
#include <Windows.h>

namespace Memory {

	DWORD ReadMemory_DWORD(HANDLE hProcess, DWORD dwReadAddr, BOOL* bStatus);
	BYTE ReadMemory_BYTE(HANDLE hProcess, DWORD dwReadAddr, BOOL* bStatus);
	float ReadMemory_float(HANDLE hProcess, DWORD dwReadAddr, BOOL* bStatus);
	BOOL WriteMemory_DWORD(HANDLE hProcess, DWORD dwReadAddr, DWORD dwNum);
	BOOL WriteMemory_float(HANDLE hProcess, DWORD dwReadAddr, float fNum);
}