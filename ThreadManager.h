#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <pthread.h>

class ThreadManager
{
	public:
		ThreadManager();
		pthread_t createJoinableThread(void* (*func)(void*), void* para);
	private:
		pthread_t threadHandle;
};

#endif
