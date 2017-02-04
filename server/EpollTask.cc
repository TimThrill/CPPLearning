#include <iostream>

#include "EpollTask.h"
#include "../common/ThreadException.h"
#include "../common/ThreadManager.h"

EpollTask::EpollTask() : TaskManager("Epoll Task") 
{
	try
	{
		ThreadManager epollTask;
		pthread_t threadHandle = epollTask.createJoinableThread("NULL", initialEpoll, NULL);
	}
	catch (ThreadException& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}

void* EpollTask::initialEpoll(void* para)
{
}
