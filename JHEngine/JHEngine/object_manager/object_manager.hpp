/*

	Copyright (c) 2015 JaeHun Ahn

	Jaehun Ahn <dark_woah@naver.com ; dkswognsd@gmail.com>

	object_manager.h

	°´Ã¼ °ü¸®ÀÚ

*/

#ifndef _OBJECT_MANAGER_HPP
#define _OBJECT_MANAGER_HPP

#include "JHEngine\process\list\process_list.hpp"
#include "JHEngine\process\manager\process_manager.hpp"

class ObjectManager
{
private:
	ObjectManager(const ObjectManager&);
	ObjectManager &operator=(const ObjectManager&);

private:
	std::shared_ptr<CProcessList> process_list_;
	std::shared_ptr<ProcessManager> process_manager_;

public:
	ObjectManager()
	{
		process_list_ = std::make_shared<CProcessList>();
		process_manager_ = std::make_shared<ProcessManager>();
	}

	virtual ~ObjectManager(void)
	{
	}

	CProcessList *GetProcessListInstance() const { return process_list_.get(); }
	ProcessManager *GetProcessManagerInstance() const { return process_manager_.get(); }
};

#endif