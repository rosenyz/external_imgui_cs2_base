#include "memory.h"

Memory::Memory(const char* process_name) {
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapShot == INVALID_HANDLE_VALUE)
		std::cout << "Failed to create snapshot!" << std::endl;

	PROCESSENTRY32 proc_entry;
	proc_entry.dwSize = sizeof(PROCESSENTRY32);

	while (Process32Next(snapShot, &proc_entry))
	{
		if (!strcmp(process_name, proc_entry.szExeFile))
		{
			this->process_id = proc_entry.th32ProcessID;
			this->h_process = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process_id);
			break;
		}
	}

	if (snapShot)
		CloseHandle(snapShot);
}

uintptr_t Memory::GetModuleBaseAddress(const char* module_name)
{
	MODULEENTRY32 mod_entry;
	mod_entry.dwSize = sizeof(MODULEENTRY32);

	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);

	uintptr_t result = 0;

	while (Module32Next(snapShot, &mod_entry))
	{
		if (!strcmp(module_name, mod_entry.szModule))
		{
			result = reinterpret_cast<uintptr_t>(mod_entry.modBaseAddr);
			break;
		}
	}

	if (snapShot)
		CloseHandle(snapShot);

	return result;
}

BOOL Memory::CheckGameStatus(const char* process_name)
{
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapShot == INVALID_HANDLE_VALUE)
		std::cout << "Failed to create snapshot!" << std::endl;

	PROCESSENTRY32 proc_entry;
	proc_entry.dwSize = sizeof(PROCESSENTRY32);

	while (Process32Next(snapShot, &proc_entry))
	{
		if (!strcmp(process_name, proc_entry.szExeFile))
		{
			return true;
			break;
		}
	}

	if (snapShot)
		CloseHandle(snapShot);
	return false;
}

