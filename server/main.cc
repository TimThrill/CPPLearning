#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "EpollTask.h"
#include "SelectTask.h"

int main(int argc, char** argv)
{
	printf("Programme start\n");
	printf("Before create thread\n");
	pthread_t thread[5];
	pthread_attr_t attr;	/* Create thread attributes */
	/* Extra set beginning as not every implementation does this */
	/* Initialise and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	/* Extra set end */

#if 0
	int j[5];
	for(int i = 0; i < 5; i++)
	{
		j[i] = i;
		printf("j = %d\n", j[i]);
		if(pthread_create(&thread[i], NULL, thread_func, (void*)(j + i)))
		{
			printf("Create thread failed!\n");
		}
	}


	

	/* Extra set beginning as not every implementation does this */
	pthread_attr_destroy(&attr);
	/* Extra set end*/
	void* status;
	for(int i = 0; i < 5; i++)
	{
		int ret = pthread_join(thread[i], &status);
		if(ret)
		{
			printf("ERROR: return code from pthread_join() is %d\n", ret);
		}
		else
		{
			printf("Main thread: completed join with thread %dld having a status of %ld\n", i, (long)status);
		}
	}
	printf("Create thread successful!\n");
	pthread_exit(NULL);
#endif

	// EpollTask epollTask;
	SelectTask select;
	return 0;
}
