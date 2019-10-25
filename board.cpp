#include "board.hpp"
#include <iostream>

Board::Board()
{
}

void Board::addUser(std::string username)
{
	if (findUser(username) != nullptr)
	{
		std::cout << "User already exists" << std::endl;
		return;
	}
	users.push_back(new User(username));
}

void Board::addTask(std::string listName, std::string name, int estimatedTime, int priority, std::string description)
{
	List *list = findList(listName);
	if (list == nullptr)
	{
		std::cout << "List not available" << std::endl;
		return;
	}
	if (findTask(name) != nullptr)
	{
		std::cout << "Task already exists" << std::endl;
		return;
	}
	list->addTask(new Task(name, estimatedTime, priority, description));
}

void Board::editTask(std::string taskName, int estimatedTime, int priority, std::string description)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		std::cout << "Task does not exist" << std::endl;
		return;
	}
	task->editDetails(estimatedTime, priority, description);
}

void Board::deleteTask(std::string taskName)
{
	List *containerList = findListContainingTask(taskName);
	if (containerList == nullptr)
	{
		std::cout << "Task does not exist" << std::endl;
		return;
	}
	containerList->deleteTask(taskName);
}

void Board::setTaskOwner(std::string taskName, std::string username)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		std::cout << "Task does not exist" << std::endl;
		return;
	}
	User *user = findUser(username);
	if (user == nullptr)
	{
		std::cout << "User does not exist" << std::endl;
		return;
	}
	task->setOwner(user);
}

void Board::moveTask(std::string taskName, std::string listName)
{
	List *destinationList = findList(listName);
	if (destinationList == nullptr)
	{
		std::cout << "List not available" << std::endl;
		return;
	}
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		std::cout << "Task does not exists" << std::endl;
		return;
	}
	List *sourceList = findListContainingTask(taskName);
	task = new Task(*task);
	destinationList->addTask(task);
	sourceList->deleteTask(taskName);
}

void Board::completeTask(std::string taskName)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		std::cout << "Task does not exists" << std::endl;
		return;
	}
	task->complete();
}

void Board::printTask(std::string taskName)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		std::cout << "Task does not exists" << std::endl;
		return;
	}
	std::cout << task->toString() << std::endl;
}

void Board::addList(std::string listName)
{
	if (findList(listName) != nullptr)
	{
		std::cout << "List already exists" << std::endl;
		return;
	}
	lists.push_back(new List(listName));
}

void Board::deleteList(std::string listName)
{
	List *list = findList(listName);
	if (list == nullptr)
	{
		std::cout << "List does not exists" << std::endl;
		return;
	}
	lists.erase(std::find(lists.begin(), lists.end(), list));
	delete list;
}

void Board::printList(std::string listName)
{
	List *list = findList(listName);
	if (list == nullptr)
	{
		std::cout << "List does not exists" << std::endl;
		return;
	}
	std::cout << list->toString() << std::endl;
}

void Board::getUserTasks(std::string userName)
{
	std::vector<Task *> userTasks;
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserTasks(userName);
		userTasks.insert(userTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	TaskUtility::printTaskList(userTasks);
}

void Board::getUserUnfinishedTasks(std::string userName)
{
	std::vector<Task *> userUnfinishedTasks;
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserUnfinishedTasks(userName);
		userUnfinishedTasks.insert(userUnfinishedTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	TaskUtility::printTaskList(userUnfinishedTasks);
}

void Board::getTotalEstimatedTime()
{
}

void Board::getTotalRemainingTime()
{
}

void Board::getUserWorkload(std::string user)
{
}

void Board::printUsersByWorkload()
{
}

void Board::printUsersByPerformance()
{
}

void Board::printBoard()
{
}

void Board::printUnassignedTasksByPriority()
{
}

void Board::printAllUnfinishedTasksByPriority()
{
}

User *Board::findUser(std::string name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->compareName(name))
		{
			return users[i];
		}
	}
	return nullptr;
}

List *Board::findList(std::string name)
{
	for (int i = 0; i < lists.size(); i++)
	{
		if (lists[i]->compareName(name))
		{
			return lists[i];
		}
	}
	return nullptr;
}

Task *Board::findTask(std::string name)
{
	for (int i = 0; i < lists.size(); i++)
	{
		Task *task = lists[i]->getTask(name);
		if (task != nullptr)
		{
			return task;
		}
	}
	return nullptr;
}

List *Board::findListContainingTask(std::string taskName)
{
	for (int i = 0; i < lists.size(); i++)
	{
		Task *task = lists[i]->getTask(taskName);
		if (task != nullptr)
		{
			return lists[i];
		}
	}
	return nullptr;
}

Task *Board::getTaskFromList(std::string listName, std::string taskName)
{
	List *listPointer = findList(listName);
	if (listPointer == nullptr)
	{
		std::cout << "List not available" << std::endl;
		return;
	}
	return listPointer->getTask(taskName);
}
