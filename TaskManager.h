#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <iostream>

/* All subtask should inheritent TaskManager */
class TaskManager
{
	public:
		/* Task name */
		std::string taskName;
		
		/* Constructor */
		TaskManager(std::string name) : taskName(name) 
		{
			std::cout<<"Start task < "<<taskName<<" >"<<std::endl;
		}
};

#endif
