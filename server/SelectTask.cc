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
#include "../common/ThreadManager.h"

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

	
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(listenSocket == -1)
	{
			std::cout<<"Error: create socket failed"<<std::endl;
	}
	std::cout<<"Server listen at socket: "<<listenSocket<<std::endl;

	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0x00, sizeof(struct sockaddr_in));
	serverAddress.sin_family = AF_INET;	/* Set protocol */
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(8888);	/* Set server port number */

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

	/* Initialise the set of active sockets. */
	FD_ZERO(&active_fd_set);
	/* Add listen socket to active_fd_set */
	FD_SET(listenSocket, &active_fd_set);

	int FD_SET_SIZE = listenSocket + 1;

	/* Loop for select */
	while(1)
	{
		/* Block until readable data arrives on one or more sockets. */
		read_fd_set = active_fd_set;
		
		std::cout<<"Select start"<<std::endl;
		if(select(FD_SET_SIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			printf("Error: select error\n");
			pthread_exit(NULL);
		}
		std::cout<<"select end, FD_SET_SIZE: "<<FD_SET_SIZE<<std::endl;

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
					std::cout<<"Server connect! Create read socket: "<<readSocket<<std::endl;
					FD_SET(readSocket, &active_fd_set);	/* update fd set */
					FD_SET_SIZE = readSocket + 1;
				}
				else
				{
					/* Data arriving on a connected socket */
					std::cout<<"Data arriving on a connected socket, socket number: "<<i<<std::endl;
					char str[10] = {0};
					int ret = read(i, str, 512);
					std::cout<<"Read "<<ret<<" bytes. Content: "<<str<<std::endl;
				}
			}
			else
			{
				std::cout<<"FD: "<<i<<" No readable data"<<std::endl;
			}
		}
	}
	return NULL;
}
