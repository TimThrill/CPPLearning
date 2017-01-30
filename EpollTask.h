#ifndef	EPOLL_TASK_H
#define EPOLL_TASK_H
#include "TaskManager.h"

/*
 * Epoll is available from Linux 2.6.
 * epoll_create() & epoll_create1() create a epoll instance, they take different arguments
 * epoll_ctl()	is used to add/remove descriptors to be watched on the epoll instance
 * epoll_wait() is used to wait for events on the watched set
 *
 * When descriptors are added to an epoll instance, they can be added in two modes: "level triggered" and "edge triggered"
 * "level triggered":	When you use level triggered mode, and data is available for reading, 
 * 						epoll_wait(2) will always return with ready events. If you don't read the data completely, 
 * 						and call epoll_wait(2) on the epoll instance watching the descriptor again, 
 * 						it will return again with a ready event because data is available.
 * "edge triggered":	In edge triggered mode, you will only get a readiness notfication once. 
 * 						If you don't read the data fully, and call epoll_wait(2) on the epoll instance watching the descriptor again, 
 * 						it will block because the readiness event was already delivered.
 */
class EpollTask : public TaskManager
{
	public:
	EpollTask();

	private:
	static void* initialEpoll(void*);
};
#endif
