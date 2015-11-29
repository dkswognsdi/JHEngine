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
#include <memory>
#include <string>

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

#ifdef _UNICODE
#define ProcessListStructure ProcessListStructureW
#else
#define ProcessListStructure ProcessListStructureA
#endif

#define NULL_CHECK_MACRO(var) \
if (var == nullptr || var == NULL)

#endif