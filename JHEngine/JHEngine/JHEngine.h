
// JHEngine.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "JHEngine\object_manager\object_manager.hpp"

// CJHEngineApp:
// �� Ŭ������ ������ ���ؼ��� JHEngine.cpp�� �����Ͻʽÿ�.
//

class CJHEngineApp : public CWinApp
{
public:
	CJHEngineApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CJHEngineApp theApp;