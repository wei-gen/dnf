#include <Windows.h>


namespace utils
{
	/************************************
	 * description:	��ȡ�ڴ�
	 * param:address	��ַ
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
	 * description:	д���ڴ�
	 * param:address	��ַ
	 * param:Value		д��ֵ
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
	 * description:	д���ڴ棬�Լ�����д�볤��
	 * param:address	��ַ
	 * param:Value		д��ֵ
	 * param:len		д�볤��
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