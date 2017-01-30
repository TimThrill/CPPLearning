#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <string>
#include <pthread.h>

class ThreadManager
{
	public:
		pthread_t createJoinableThread(std::string funcName, void* (*func)(void*), void* para);
};

#endif
