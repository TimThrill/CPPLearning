#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread_func(void* para)
{
	int local_int = *((int*)para);
	printf("Execute thread: %d\n", local_int);
	if(local_int == 2)
	{
		sleep(4);
	}
	else
	{
		sleep(1);
	}
	
	pthread_exit(NULL);
}
