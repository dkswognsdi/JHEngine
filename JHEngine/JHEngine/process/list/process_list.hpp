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
#include <strsafe.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

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

			std::shared_ptr<void> process_handle_closer(
				OpenProcess(PROCESS_ALL_ACCESS
				, FALSE
				, process_entry.th32ProcessID)
				, ::CloseHandle);

			if (process_handle_closer.get())
			{
				wchar_t path[MAX_PATH];
				if (GetModuleFileNameExW(process_handle_closer.get(), 0, path, sizeof(path)))
				{
					(process_list_structure_.get())[process_list_count].icon = ExtractIcon(AfxGetInstanceHandle(), path, 0);
				}
				else
					(process_list_structure_.get())[process_list_count].icon = NULL;
			}
			else
				(process_list_structure_.get())[process_list_count].icon = NULL;

			process_list_count++;
		}
		process_list_num_ = process_list_count;
		return ERROR_SUCCESS;
	}

	BOOL __stdcall ProcessListPrint(CImageList &imglist, CListCtrl &listbox_handle, CProcessList *process_list)
	{
		if (!SUCCEEDED(process_list->GetProcessList()))
			return FALSE;

		listbox_handle.DeleteAllItems();

		ProcessListStructure *process_list_structure = process_list->GetStructure();
		int process_num = process_list->GetSize();
		
		LV_COLUMN col;

		col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		col.fmt = LVCFMT_LEFT;

		col.pszText = L"";
		col.iSubItem = 0;
		col.cx = 1000;
		listbox_handle.InsertColumn(0, &col);
		listbox_handle.SetExtendedStyle(LVS_EX_SUBITEMIMAGES);

		for (int i = 0; i < process_num; i++)
		{
			wchar_t process_list_name[MAX_PATH];
			StringCbPrintfW(process_list_name
				, sizeof(process_list_name)
				, L"%08X-%ls"
				, process_list_structure[i].pid
				, process_list_structure[i].process_name.c_str());

			listbox_handle.InsertItem(i, process_list_name);

			HICON basic_icon = AfxGetApp()->LoadIcon(IDI_ICON1);

			if (process_list_structure[i].icon)
				imglist.Add(process_list_structure[i].icon);
			else
				imglist.Add(basic_icon);

			listbox_handle.SetItem(i, 0, LVIF_IMAGE, NULL, i, 0, 0, 0);
		}
		listbox_handle.SetImageList(&imglist, LVSIL_SMALL);

		return TRUE;
	}

	ProcessListStructure *GetStructure() const
	{
		return process_list_structure_.get();
	}

	int GetSize() const { return process_list_num_; }
};

#endif