/*

Copyright (c) 2015 JaeHun Ahn

Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

process_list.hpp

프로세스 리스트 관리 헤더파일

*/

#ifndef _PROCESS_LIST_HPP
#define _PROCESS_LIST_HPP

#include "JHEngine\\preprocess\jhengine_preprocess.hpp"
#include <TlHelp32.h>

template <typename _T>
struct ProcessListStructureDeleter
{
	void operator()(_T *ptr)
	{
		NULL_CHECK_MACRO(ptr)
			return;

		delete[]ptr;
	}
};

class CProcessList
{
private:
	std::shared_ptr<void> snapshot_handle_closer_;
	std::shared_ptr<ProcessListStructure> process_list_structure_;
	int process_list_num_;

public:
	CProcessList()
		: process_list_num_(NULL)
	{ 
		HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (snapshot_handle != INVALID_HANDLE_VALUE)
			snapshot_handle_closer_.reset(snapshot_handle, ::CloseHandle);
	}

	virtual ~CProcessList(void)
	{
	}

private:
	unsigned long GetProcessNum()
	{
		unsigned long result = 0;
		NULL_CHECK_MACRO(snapshot_handle_closer_)
		{
			return 0;
		}

		PROCESSENTRY32W process_entry;
		process_entry.dwSize = sizeof(process_entry);

		BOOL fok = Process32FirstW(snapshot_handle_closer_.get(), &process_entry);
		for (; fok; fok = Process32NextW(snapshot_handle_closer_.get(), &process_entry))
		{
			result++;
		}
		return result;
	}

public:
	LSTATUS __stdcall GetProcessList()
	{
		NULL_CHECK_MACRO(snapshot_handle_closer_)
		{
			return SNAPSHOT_CREATE_FAIL;
		}

		unsigned long process_num = GetProcessNum();
		if (!process_num)
			return GETPROCESSNUM_FAIL;

		process_list_structure_.reset(new ProcessListStructure[process_num], [](ProcessListStructureW *ptr)
		{
			NULL_CHECK_MACRO(ptr)
				return;

			delete[] ptr;
		}
		);

		PROCESSENTRY32W process_entry;
		process_entry.dwSize = sizeof(process_entry);

		BOOL fok = Process32FirstW(snapshot_handle_closer_.get(), &process_entry);
		int process_list_count = 0;
		for (; fok; fok = Process32NextW(snapshot_handle_closer_.get(), &process_entry))
		{
			if (process_list_count > process_num)
				break;

			(process_list_structure_.get())[process_list_count].pid = process_entry.th32ProcessID;
			(process_list_structure_.get())[process_list_count].process_name = process_entry.szExeFile;
			(process_list_structure_.get())[process_list_count].icon = ExtractIcon(AfxGetInstanceHandle(), process_entry.szExeFile, 0);
			process_list_count++;
		}
		process_list_num_ = process_list_count;
		return ERROR_SUCCESS;
	}

	ProcessListStructure *GetStructure() const
	{
		return process_list_structure_.get();
	}

	int GetSize() const { return process_list_num_; }
};

#endif