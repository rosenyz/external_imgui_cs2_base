#pragma once
#include "includes.h"


class Memory
{
public:

	uintptr_t process_id;
	HANDLE h_process;

	Memory(const char* process_name);

	uintptr_t GetModuleBaseAddress(const char* module_name);

	static BOOL CheckGameStatus(const char* process_name);

	template <typename T>
	T Read(uintptr_t addr);

	template<typename T>
	bool Write(uintptr_t& addr, T value);
};

template<typename T>
inline T Memory::Read(uintptr_t addr)
{
	T buff;

	ReadProcessMemory(this->h_process, (LPCVOID)addr, &buff, sizeof(T), NULL);
	
	return buff;
}

template<typename T>
inline bool Memory::Write(uintptr_t& addr, T value)
{
	if (WriteProcessMemory(this->h_process, (LPVOID)addr, &value, sizeof(T), NULL))
		return true;

	return false;
}