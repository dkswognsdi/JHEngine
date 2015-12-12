/*

	Copyright (c) 2015 JaeHun Ahn

	Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

	object_manager.h

	스레드 관리자

*/

#ifndef _THREAD_MANAGER_HPP
#define _THREAD_MANAGER_HPP

#include "JHEngine\preprocess\jhengine_preprocess.hpp"

template<typename function_type, typename... arg_list> class ThreadManager
{
private:
	ThreadManager(const ThreadManager&);
	ThreadManager &operator=(const ThreadManager&);
	//std::thread thread_;

public:
	explicit ThreadManager(function_type thread_proc, const arg_list&... thread_param)
	{
		std::thread t(thread_proc, thread_param...);
		t.join();
	}

	virtual ~ThreadManager(void)
	{
	}
};

#endif