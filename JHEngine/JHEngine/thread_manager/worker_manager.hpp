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
	CriticalSectionObj(const CriticalSectionObj&);
	CriticalSectionObj &operator=(const CriticalSectionObj&);

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


private:
	typedef std::shared_ptr<void> AutoHandle;
	typedef std::vector<AutoHandle> AutoHandleVec;
	typedef std::list<WorkerData> WokerDataList;

	AutoHandleVec thread_handle_mgr_;
	WokerDataList worker_list_;
	CriticalSectionObj woker_cs_;

private:
	BOOL init_chk_;
	DWORD process_num_;

private:
	static DWORD __stdcall WokerThreadProc(PVOID param)
	{
		WorkerManager *worker_mgr = reinterpret_cast<WorkerManager *>(param);
		for (;;)
		{
			Sleep(1000);
			if (worker_mgr->IsCommandEmpty())
				continue;

			WorkerData worker_data = worker_mgr->GetWorkerData();
		}
		return 0;
	}

private:
	BOOL Initialize()
	{
		SYSTEM_INFO system_info;
		GetSystemInfo(&system_info);
		if (!system_info.dwNumberOfProcessors)
			return FALSE;

		process_num_ = system_info.dwNumberOfProcessors;
		return TRUE;
	}

	BOOL IsCommandEmpty() const
	{
		return (worker_list_.empty());
	}

	WorkerData &GetWorkerData()
	{
		CriticalSectionLock cs_lock(woker_cs_);
		WorkerData &wd = worker_list_.front();
		worker_list_.pop_front();
		return wd;
	}

public:
	void __stdcall AddCommand(DWORD id, PVOID object)
	{
		WorkerData wd;
		wd.worker_id = id;
		wd.worker_object = object;

		CriticalSectionLock cs_lock(woker_cs_);
		worker_list_.push_back(wd);
	}

public:
	WorkerManager()
	{
		init_chk_ = Initialize();
		for (DWORD i = 0; i < (process_num_ * 2); i++)
		{
			HANDLE thread_handle = CreateThread(nullptr, NULL, &WorkerManager::WokerThreadProc, (LPVOID)this, 0, 0);
			if (thread_handle != INVALID_HANDLE_VALUE)
			{
				AutoHandle ah(thread_handle, [](PVOID param)
				{
					HANDLE h = (HANDLE)(param);
					if (WaitForSingleObject(h, 1000) != WAIT_OBJECT_0)
						TerminateThread(h, 0);

					CloseHandle(h);
				});
				thread_handle_mgr_.push_back(ah);
			}
		}
	}

	virtual ~WorkerManager(void)
	{
	}
};

#endif