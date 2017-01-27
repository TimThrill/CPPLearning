#include <iostream>

#include "StdHead.h"
#include "ThreadManager.h"
#include "ThreadException.h"

ThreadManager::ThreadManager() : threadHandle(0) {}

pthread_t ThreadManager::createJoinableThread(void* (*func)(void* para), void* para)
{
	int ret = 0;
	pthread_t thread[5];
    pthread_attr_t attr;    /* Create thread attributes */
    /* Extra set beginning as not every implementation does this */
    /* Initialise and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    /* Extra set end */	

	ret = pthread_create(&threadHandle, NULL, func, para);
	if(ret != 0)
    {
    	std::string errStr = "Create thread failed! Error code: " + ret;
		throw ThreadException(errStr);
		return ERROR;
    }
	/* Extra set beginning as not every implementation does this */
    pthread_attr_destroy(&attr);
    /* Extra set end*/

	void* status;
	ret = pthread_join(threadHandle, &status);
	if(ret)
	{
		std::string errStr = "ERROR: return code from pthread_join() is " + ret;
		throw ThreadException(errStr);
		return ERROR;
	}
	else
	{
		std::cout<<"Main thread: completed join with thread,  having a status of "<<(long)status<<std::endl;
	}

	return threadHandle;
}
