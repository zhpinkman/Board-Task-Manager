#include "utrello_interface.hpp"
#include <iostream>

UTrelloInterface::UTrelloInterface()
{

}

std::string UTrelloInterface::addUser(std::string username)
{
	return board.addUser(username);
}

std::string UTrelloInterface::addTask(std::string list, std::string name, unsigned int estimatedTime, unsigned int priority, std::string description)
{
	return board.addTask(list, name, estimatedTime, priority, description);
}

std::string UTrelloInterface::editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description)
{
	return board.editTask(task, estimatedTime, priority, description);
}

std::string UTrelloInterface::deleteTask(std::string task)
{
	return board.deleteTask(task);
}

std::string UTrelloInterface::assignTask(std::string task, std::string user)
{
	return board.setTaskOwner(task, user);
}

std::string UTrelloInterface::moveTask(std::string task, std::string list)
{
	return board.moveTask(task, list);
}

std::string UTrelloInterface::completeTask(std::string task)
{
	return board.completeTask(task);
}

std::string UTrelloInterface::printTask(std::string task)
{
	return board.printTask(task);
}

std::string UTrelloInterface::addList(std::string name)
{
	return board.addList(name);
}

std::string UTrelloInterface::deleteList(std::string list)
{
	return board.deleteList(list);
}

std::string UTrelloInterface::printList(std::string list)
{
	return board.printList(list);
}

std::string UTrelloInterface::printUserTasks(std::string user)
{
	return board.printUserTasks(user);
}

std::string UTrelloInterface::printUserUnfinishedTasks(std::string user)
{
	return board.printUserUnfinishedTasks(user);
}

int UTrelloInterface::printTotalEstimatedTime()
{
	return board.getTotalEstimatedTime();
}

int UTrelloInterface::printTotalRemainingTime()
{
	return board.getTotalRemainingTime();
}

int UTrelloInterface::printUserWorkload(std::string user)
{
	return board.getUserWorkload(user);
}

std::string UTrelloInterface::printUsersByWorkload()
{
	return board.printUsersByWorkload();
}

std::string UTrelloInterface::printUsersByPerformance()
{
	return board.printUsersByPerformance();
}

std::string UTrelloInterface::printAllLists()
{
    return board.printAllLists();
}

std::string UTrelloInterface::printUnassignedTasksByPriority()
{
	return board.printUnassignedTasksByPriority();
}

std::string UTrelloInterface::printAllUnfinishedTasksByPriority()
{
	return board.printAllUnfinishedTasksByPriority();
}

