/*

	Copyright (c) 2015 JaeHun Ahn

	Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

	memory_scanner.hpp

	메모리 스캐너

*/

#ifndef _MEMORY_SCANNER_HPP
#define _MEMORY_SCANNER_HPP

#include "JHEngine\preprocess\jhengine_preprocess.hpp"
#include "JHEngine\process\manager\process_manager.hpp"

class MemoryScanner
{
public:
	typedef std::vector<DWORD> ScanResultVec;

private:
	MemoryScanner(const MemoryScanner&);
	MemoryScanner &operator=(const MemoryScanner&);

	ScanResultVec scan_result_;

private:
	BOOL IsScanMemory(DWORD protect)
	{
		return (
			(protect & PAGE_NOACCESS) ||
			(protect & PAGE_NOCACHE) ||
			(protect & PAGE_EXECUTE) ||
			(protect & PAGE_GUARD)
			);
	}

	BOOL IsMappedMemory(DWORD state)
	{
		return (state & MEM_MAPPED);
	}

	VOID GetProtect(MemoryScanStructure &memory_scan_structure, DWORD &protect)
	{
		if (memory_scan_structure.readonly_scan_check)
			protect |= PAGE_READONLY;

		if (memory_scan_structure.readonly_x_scan_check)
			protect |= PAGE_EXECUTE_READ;

		if (memory_scan_structure.readwrite_scan_check)
			protect |= PAGE_READWRITE;

		if (memory_scan_structure.readwrite_x_scan_check)
			protect |= PAGE_EXECUTE_READWRITE;

		if (memory_scan_structure.writecopy_scan_check)
			protect |= PAGE_WRITECOPY;

		if (memory_scan_structure.readonly_scan_check)
			protect |= PAGE_EXECUTE_WRITECOPY;
	}

	/*VOID ScanResultClear(CListCtrl &list_ctrl)
	{
		scan_result_.clear();
		list_ctrl.SetItemCountEx(0, LVSICF_NOSCROLL | LVSICF_NOINVALIDATEALL);
	}*/

	BOOL IsScanResultEmpty() const
	{
		return scan_result_.empty();
	}

	int GetScanResultSize() const
	{
		return scan_result_.size();
	}

public:
	MemoryScanner()
	{
	}

	virtual ~MemoryScanner(void)
	{
	}

	ScanResultVec &GetScanResult()
	{
		return scan_result_;
	}

	VOID ScanResultClear(CListCtrl &list_ctrl)
	{
		scan_result_.clear();
		list_ctrl.SetItemCountEx(0, LVSICF_NOSCROLL | LVSICF_NOINVALIDATEALL);
	}

public:
	BOOL __stdcall FirstScan(ProcessManager *process_manager, MemoryScanStructure &memory_scan_structure, ScanBufferPtr scan_buffer, unsigned long scan_size, CListCtrl &list_ctrl, CStatic &count_label)
	{
		ScanResultClear(list_ctrl);
		if (memory_scan_structure.scan_end_address < memory_scan_structure.scan_start_address)
			return FALSE;

		if (!process_manager || !scan_buffer || !scan_size)
			return FALSE;

		static const DWORD type = MEM_PRIVATE | MEM_IMAGE | MEM_MAPPED;
		static const PVOID SCAN_MAXIMUM_PTR = (PVOID)(0x7FFE0000);
		PVOID start = reinterpret_cast<PVOID>(memory_scan_structure.scan_start_address);
		PVOID end = reinterpret_cast<PVOID>(memory_scan_structure.scan_end_address);
		DWORD protect = 0, scan_count = 0;

		GetProtect(memory_scan_structure, protect);

		if (end > SCAN_MAXIMUM_PTR)
			end = SCAN_MAXIMUM_PTR;

		MEMORY_BASIC_INFORMATION mbi;
		while (start < end)
		{
			if (VirtualQueryEx(process_manager->Get(), start, &mbi, sizeof(mbi)) != sizeof(mbi))
				return FALSE;

			if (IsScanMemory(mbi.Protect))
			{
				start = AddPtr(start, mbi.RegionSize);
				continue;
			}

			if ((mbi.State & MEM_COMMIT) && (mbi.Type & type) && (mbi.Protect & protect))
			{
				DWORD req_size = 0;
				DWORD blk_size = mbi.RegionSize;
				boost::scoped_array<BYTE> buffer(new BYTE[mbi.RegionSize]);
				process_manager->ReadArray(mbi.BaseAddress, buffer.get(), blk_size, &req_size);
				PBYTE cmpbuffer = buffer.get();

				for (DWORD i = 0; i < blk_size; i++)
				{
					for (DWORD j = 0; j < scan_size; j++)
					{
						if (cmpbuffer[i + j] != scan_buffer[j].scan_code && scan_buffer[j].scan_check)
							break;

						if (j == scan_size - 1)
						{
							scan_result_.push_back((DWORD)(mbi.BaseAddress) + i);
						}
					}
				}
			}
			start = AddPtr(start, mbi.RegionSize);
		}
		if (!IsScanResultEmpty())
			list_ctrl.SetItemCountEx(GetScanResultSize(), LVSICF_NOSCROLL | LVSICF_NOINVALIDATEALL);

		boost::wformat found_str_format(L"Found: %d");
		found_str_format % GetScanResultSize();

		count_label.SetWindowTextW(found_str_format.str().c_str());
		return TRUE;
	}

};

#endif