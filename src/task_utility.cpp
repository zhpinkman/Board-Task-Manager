#include "task_utility.hpp"
#include <sstream>
#include <iostream>

std::string formatTaskListToString(std::vector<Task *> taskList) 
{
	std::stringstream formatterStream;
	for (Task *task : taskList)
	{
		formatterStream << task->getSummary() << std::endl;
	}
	return formatterStream.str();
}