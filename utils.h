#include <Windows.h>


namespace utils
{
	/************************************
	 * description:	读取内存
	 * param:address	地址
	 * time: 2020.03.06.00.25
	 ************************************/
	template<typename T> T ReadValue(DWORD address)
	{
		T  value = { 0 };
		__try {
			value = *(T*)(address);
		}
		__except (1) {
			return T();
		}
		return value;
	}

	/************************************
	 * description:	写入内存
	 * param:address	地址
	 * param:Value		写入值
	 * time: 2020.03.06.00.25
	 ************************************/
	template <typename T>
	bool WriteValue(DWORD address, T Value)
	{
		__try {
			DWORD len = sizeof(T);
			DWORD OldProtect = { 0 };
			VirtualProtectEx(HANDLE(-1), (PVOID)address, len, PAGE_EXECUTE_READWRITE, &OldProtect);
			memcpy((PVOID)address, &Value, len);
			VirtualProtectEx(HANDLE(-1), (PVOID)address, len, OldProtect, &OldProtect);

		}
		__except (1) {
			return false;
		}

		return true;
	}

	/************************************
	 * description:	写入内存，自己控制写入长度
	 * param:address	地址
	 * param:Value		写入值
	 * param:len		写入长度
	 * time: 2020.03.06.00.25
	 ************************************/
	template <typename T>
	bool WriteValueBySize(DWORD address, T value, DWORD len)
	{
		__try {
			DWORD OldProtect = { 0 };
			VirtualProtectEx(HANDLE(-1), (PVOID)address, len, PAGE_EXECUTE_READWRITE, &OldProtect);
			memcpy((PVOID)address, &value, len);
			VirtualProtectEx(HANDLE(-1), (PVOID)address, len, OldProtect, &OldProtect);

		}
		__except (1) {
			return false;
		}

		return true;
	}
}