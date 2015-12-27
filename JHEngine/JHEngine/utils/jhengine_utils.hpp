/*

	Copyright (c) 2015 JaeHun Ahn

	Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

	jhengine_utils.hpp

	JHEngine Utils

*/

#ifndef _JHENGINE_UTILS_HPP
#define _JHENGINE_UTILS_HPP

#include "JHEngine\preprocess\jhengine_preprocess.hpp" 

namespace JHEngineUtils
{
	static void ErrorMsg(wchar_t *fmt, ...)
	{
		wchar_t msg[MAX_PATH];
		va_list ap;

		va_start(ap, fmt);
		vswprintf_s(msg, fmt, ap);
		MessageBoxW(0, msg, L"Err", 64);
		va_end(ap);
	}

	template<typename T>
	static void StrToNum(std::string &str, T& val)
	{
		std::stringstream sstream(str);
		sstream >> std::hex >> val;
		MessageBoxW(0, std::to_wstring(val).c_str(), L"", 64);
	}

	template<typename T>
	static void WStrToNum(std::wstring &wstr, T& val)
	{
		std::wstringstream wsstream(wstr);
		wsstream >> std::hex >> val;
	}
}


#endif

