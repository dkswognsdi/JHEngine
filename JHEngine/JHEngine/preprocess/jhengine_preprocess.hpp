/*

Copyright (c) 2015 JaeHun Ahn

Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

jhengine_preprocess.hpp

전처리 시스템

*/

#ifndef _JHENGINE_PREPROCESS_HPP
#define _JHENGINE_PREPROCESS_HPP

#include <Windows.h>
#include <stdio.h>

//boost
#include "boost\scoped_array.hpp"
#include "boost\format.hpp"

#include <memory>
#include <thread>
#include <string>
#include <algorithm>
#include <vector>

#include "JHEngine\error\jhengine_errorcode.h"

typedef struct _ProcessListStructureA
{
	unsigned long pid;
	std::string process_name;
	HICON icon;
}ProcessListStructureA, *ProcessListStructureAPtr;

typedef struct _ProcessListStructureW
{
	unsigned long pid;
	std::wstring process_name;
	HICON icon;
}ProcessListStructureW, *ProcessListStructureWPtr;

typedef struct _MemoryScanStructure
{
	DWORD scan_start_address;
	DWORD scan_end_address;
	BOOL readonly_scan_check;
	BOOL readwrite_scan_check;
	BOOL writecopy_scan_check;
	BOOL readonly_x_scan_check;
	BOOL readwrite_x_scan_check;
	BOOL writecopy_x_scan_check;
}MemoryScanStructure, *MemoryScanStructurePtr;

typedef struct _ScanBuffer
{
	BYTE scan_code;
	BOOL scan_check;
}ScanBuffer, *ScanBufferPtr;

typedef boost::scoped_array<ScanBuffer> ScanBufferMgr;

typedef struct _WorkerData
{
	DWORD worker_id;
	PVOID worker_object;
}WorkerData, *WorkerDataPtr;

#ifdef _UNICODE
#define ProcessListStructure ProcessListStructureW
#else
#define ProcessListStructure ProcessListStructureA
#endif

#define NULL_CHECK_MACRO(var) \
if (var == nullptr || var == NULL)


#define AddPtr(x, y) (PVOID)((DWORD_PTR)(x) + (DWORD_PTR)(y))

#endif