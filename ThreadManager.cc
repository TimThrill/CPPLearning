#include <iostream>

#include "StdHead.h"
#include "ThreadManager.h"
#include "ThreadException.h"

/*
 * Description: Create a joinable thread
 * Arguments:
 * 	std::string funcName		The name of the function will be called in the new thread
 * 	void* (*func)(void* para)	The address of the function will be called in the new thread
 * 	void* para					The address of the parameter will be passed to the function
 * Return value:
 * 	pthread_t	The created pthread_t structure
 * 	
 * */
pthread_t ThreadManager::createJoinableThread(std::string funcName, void* (*func)(void* para), void* para)
{
	int ret = 0;
	pthread_t threadHandle;
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
