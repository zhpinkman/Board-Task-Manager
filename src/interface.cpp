#include "interface.hpp"
#include <iostream>

Interface::Interface()
{

}

void Interface::addUser(std::string username)
{
	std::cout << board.addUser(username) << std::endl;
}

void Interface::addTask(std::string list, std::string name, unsigned int estimatedTime, unsigned int priority, std::string description)
{
	std::cout << board.addTask(list, name, estimatedTime, priority, description) << std::endl;
}

void Interface::editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description)
{
	std::cout << board.editTask(task, estimatedTime, priority, description) << std::endl;
}

void Interface::deleteTask(std::string task)
{
	std::cout << board.deleteTask(task) << std::endl;
}

void Interface::assignTask(std::string task, std::string user)
{
	std::cout << board.setTaskOwner(task, user) << std::endl;
}

void Interface::moveTask(std::string task, std::string list)
{
	std::cout << board.moveTask(task, list) << std::endl;
}

void Interface::completeTask(std::string task)
{
	std::cout << board.completeTask(task) << std::endl;
}

void Interface::printTask(std::string task)
{
	std::cout << board.printTask(task) << std::endl;
}

void Interface::addList(std::string name)
{
	std::cout << board.addList(name) << std::endl;
}

void Interface::deleteList(std::string list)
{
	std::cout << board.deleteList(list) << std::endl;
}

void Interface::printList(std::string list)
{
	std::cout << board.printList(list) << std::endl;
}

void Interface::printUserTasks(std::string user)
{
	std::cout << board.printUserTasks(user) << std::endl;
}

void Interface::printUserUnfinishedTasks(std::string user)
{
	std::cout << board.printUserUnfinishedTasks(user) << std::endl;
}

void Interface::printTotalEstimatedTime()
{
	std::cout << board.getTotalEstimatedTime() << std::endl;
}

void Interface::printTotalRemainingTime()
{
	std::cout << board.getTotalRemainingTime() << std::endl;
}

void Interface::printUserWorkload(std::string user)
{
	std::cout << board.getUserWorkload(user) << std::endl;
}

void Interface::printUsersByWorkload()
{
	std::cout << board.printUsersByWorkload() << std::endl;
}

void Interface::printUsersByPerformance()
{
	std::cout << board.printUsersByPerformance() << std::endl;
}

void Interface::printAllLists()
{
    std::cout << board.printAllLists() << std::endl;
}

void Interface::printUnassignedTasksByPriority()
{
	std::cout << board.printUnassignedTasksByPriority() << std::endl;
}

void Interface::printAllUnfinishedTasksByPriority()
{
	std::cout << board.printAllUnfinishedTasksByPriority() << std::endl;
}

