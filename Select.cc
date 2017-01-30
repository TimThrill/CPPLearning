#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Select.h"
#include "ThreadManager.h"

Select::Select()
{
	ThreadManager pthread;
	pthread_t threadHandle = pthread.createJoinableThread("initialSelect", initialSelect, NULL);
}

void* Select::initialSelect(void* para)
{
	int socket;
	fd_set active_fd_set, read_fd_set;
	socklen_t size;
	struct sockaddr* clientName;

	/* Initialise the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(socket, &active_fd_set);

	const int FD_SET_SIZE = socket + 1;

	/* Loop for select */
	while(1)
	{
		/* Block until readable data arrives on one or more sockets. */
		read_fd_set = active_fd_set;
		if(select(FD_SET_SIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			printf("Error: select error\n");
			pthread_exit(NULL);
		}

		/* Process all sockets with input data */
		for(int i = 0; i < FD_SET_SIZE; i++)
		{
			if(FD_ISSET(i, &read_fd_set))	/* Exist data */
			{
				if(i == socket)	/* Connection request on original socket. */
				{
					size = sizeof(struct sockaddr);
					int readSocket = accept(socket, (struct sockaddr*)&clientName, &size);
					if(readSocket < 0)
					{
						printf("Error: accept error\n");
						pthread_exit(NULL);
					}
					printf("Server connect!\n");
					FD_SET(readSocket, &active_fd_set);
				}
				else
				{
					/* Data arriving on a connected socket */
					printf("Data arriving on a connected socket\n");
				}
			}
		}
	}
	return NULL;
}
