#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

#include "SelectTask.h"
#include "ThreadManager.h"

SelectTask::SelectTask()
{
	ThreadManager pthread;
	pthread_t threadHandle = pthread.createJoinableThread("initialSelect", initialSelect, NULL);
}

void* SelectTask::initialSelect(void* para)
{
	int listenSocket;
	int svrPort;	/* Server side port number */
	fd_set active_fd_set, read_fd_set;
	socklen_t size;
	struct sockaddr* clientName;

	/* Initialise the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(listenSocket, &active_fd_set);

	listenSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if(listenSocket == -1)
	{
			std::cout<<"Error: create socket failed"<<std::endl;
	}

	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0x00, sizeof(struct sockaddr_in));
	serverAddress.sin_family = AF_UNIX;	/* Set protocol */
	serverAddress.sin_port = htons(8888);	/* Set server port number */
	memset(serverAddress.sin_zero, 0x00, sizeof(serverAddress.sin_zero));

	/* Bind server socket */
	if(bind(listenSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr)) == -1)
	{
		std::cout<<"Error: Server bind error!"<<std::endl;
	}

	/* Listen server socket */
	if(listen(listenSocket, 5) == -1)
	{
		std::cout<<"Error: Listen error!"<<std::endl;
	}

	const int FD_SET_SIZE = listenSocket + 1;

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
				if(i == listenSocket)	/* Connection request on original socket. */
				{
					size = sizeof(struct sockaddr);
					int readSocket = accept(listenSocket, (struct sockaddr*)&clientName, &size);
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
