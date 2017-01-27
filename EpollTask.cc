#include <iostream>

#include "EpollTask.h"
#include "ThreadException.h"
#include "ThreadManager.h"

EpollTask::EpollTask() : TaskManager("Epoll Task") 
{
	try
	{
		ThreadManager epollTask;
		pthread_t threadHandle = epollTask.createJoinableThread(NULL, NULL);
	}
	catch (ThreadException& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}
