/*

	Copyright (c) 2015 JaeHun Ahn

	Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

	process_manager.hpp

	프로세스 관리 헤더파일

*/

#ifndef _PROCESS_MANAGER_HPP
#define _PROCESS_MANAGER_HPP

#include "JHEngine\\preprocess\jhengine_preprocess.hpp"

class ProcessManager
{
private:
	ProcessManager(const ProcessManager&);
	ProcessManager &operator=(const ProcessManager&);

private:
	std::shared_ptr<void> process_handle_closer_;
	ProcessListStructure *pls_;

private:
	void Set(HANDLE process_handle)
	{
		process_handle_closer_.reset(process_handle, ::CloseHandle);
	}

	HANDLE Get() const
	{
		process_handle_closer_.get();
	}

public:
	ProcessManager()
		:pls_(nullptr)
	{
	}
	virtual ~ProcessManager(void)
	{
	}

	BOOL __stdcall Open(ProcessListStructure *pls)
	{
		process_handle_closer_.reset();
		pls_ = pls;
		HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pls->pid);
		if (!process_handle)
			return FALSE;

		Set(process_handle);
		return TRUE;
	}

	BOOL __stdcall IsOpened() const
	{
		return (process_handle_closer_ != nullptr);
	}

	ProcessListStructure *GetProcessListStructure() const
	{
		return pls_;
	}

	BOOL __stdcall Read8Bit(void *src, unsigned char *dst, unsigned long *req_size)
	{
		if (!IsOpened())
			return FALSE;

		BOOL result = ReadProcessMemory(Get(), src, (void*)&dst, 1, req_size);
		return result;
	}

	BOOL __stdcall Read16Bit(void *src, unsigned short *dst, unsigned long *req_size)
	{
		if (!IsOpened())
			return FALSE;

		BOOL result = ReadProcessMemory(Get(), src, (void*)&dst, 2, req_size);
		return result;
	}

	BOOL __stdcall Read32Bit(void *src, unsigned long *dst, unsigned long *req_size)
	{
		if (!IsOpened())
			return FALSE;

		BOOL result = ReadProcessMemory(Get(), src, (void*)&dst, 4, req_size);
		return result;
	}

	BOOL __stdcall Read64Bit(void *src, unsigned long long *dst, unsigned long *req_size)
	{
		if (!IsOpened())
			return FALSE;

		BOOL result = ReadProcessMemory(Get(), src, (void*)&dst, 8, req_size);
		return result;
	}

	BOOL __stdcall ReadArray(void *src, void *dst, unsigned long size, unsigned long *req_size)
	{
		if (!IsOpened())
			return FALSE;

		BOOL result = ReadProcessMemory(Get(), src, dst, size, req_size);
		return result;
	}

};



#endif