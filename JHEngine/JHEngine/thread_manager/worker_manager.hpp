/*

	Copyright (c) 2015 JaeHun Ahn

	Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

	object_manager.h

	스레드 관리자

*/

#ifndef _WORKER_MANAGER_HPP
#define _WORKER_MANAGER_HPP

#include "JHEngine\preprocess\jhengine_preprocess.hpp"
#include <list>

class CriticalSectionObj
{
private:
	CRITICAL_SECTION cs_;

public:
	CriticalSectionObj()
	{
		InitializeCriticalSection(&cs_);
	}

	~CriticalSectionObj(void)
	{
		DeleteCriticalSection(&cs_);
	}

	void Lock()
	{
		EnterCriticalSection(&cs_);
	}

	void UnLock()
	{
		DeleteCriticalSection(&cs_);
	}
};

class CriticalSectionLock
{
private:
	CriticalSectionLock(const CriticalSectionLock&);
	CriticalSectionLock &operator=(const CriticalSectionLock&);

private:
	CriticalSectionObj &cs_;

public:
	explicit CriticalSectionLock(CriticalSectionObj &cs)
		: cs_(cs)
	{
		cs_.Lock();
	}

	virtual ~CriticalSectionLock(void)
	{
		cs_.UnLock();
	}
};

class WorkerManager
{
private:
	WorkerManager(const WorkerManager&);
	WorkerManager &operator=(const WorkerManager&);

public:
	WorkerManager()
	{
	}

	virtual ~WorkerManager(void)
	{
	}
};

#endif