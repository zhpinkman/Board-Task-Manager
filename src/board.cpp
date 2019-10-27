#include "board.hpp"
#include <iostream>
#include <algorithm>

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
	containerList->deleteTask(findTask(taskName));
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
	Task* taskCopy = new Task(*task);
	destinationList->addTask(taskCopy);
	sourceList->deleteTask(task);
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

void Board::getUserTasks(const User* user)
{
	std::vector<Task *> userTasks;
	if (user == nullptr)
	{
		std::cout << "user does not exist" << std::endl;
		return;
	}
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserTasks(user);
		userTasks.insert(userTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	printTaskList(userTasks);
}

void Board::getUserUnfinishedTasks(std::string userName)
{
	std::vector<Task *> userUnfinishedTasks;
	User* user = findUser(userName);
	if (user == nullptr)
	{
		std::cout << "user does not exist" << std::endl;
		return;
	}
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserUnfinishedTasks(user);
		userUnfinishedTasks.insert(userUnfinishedTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	printTaskList(userUnfinishedTasks);
}

std::vector<Task *> Board::getUserUnfinishedTasks(const User *user)
{
	std::vector<Task *> userUnfinishedTasks;
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserUnfinishedTasks(user);
		userUnfinishedTasks.insert(userUnfinishedTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	return userUnfinishedTasks;
}

int Board::getTotalEstimatedTime()
{
	int maxEstimatedTime = -1;
	for (User* user: users)
	{
		maxEstimatedTime = std::max(maxEstimatedTime, calculateUserTotalWorkload(user));
	}
	return maxEstimatedTime;
}

int Board::getTotalRemainingTime()
{
	int maxRemainingTime = 0;
	for (User* user: users)
	{
		maxRemainingTime = std::max(maxRemainingTime, calculateUserRemainingWorkload(user));
	}
	return maxRemainingTime;
}

int Board::calculateEstimatedTime(std::vector<Task*> tasks)
{
	int totalEstimatedTime = 0;
	for (Task* task: tasks)
	{
		totalEstimatedTime += task->getEstimatedTime();
	}
	return totalEstimatedTime;
}

int Board::getUserWorkload(std::string userName)
{
	User *user = findUser(userName);
	if(user == nullptr) {
		return;
	}
	return calculateUserTotalWorkload(user);
}

int Board::calculateUserTotalWorkload(const User *user) 
{
	int userTasksEstimatedTime = 0;
	for (List* list : lists)
	{
		userTasksEstimatedTime += calculateEstimatedTime(list->getUserTasks(user));
	}
	return userTasksEstimatedTime;
}

int Board::calculateUserRemainingWorkload(const User *user) 
{
	int userTasksEstimatedTime = 0;
	for (List* list : lists)
	{
		userTasksEstimatedTime += calculateEstimatedTime(list->getUserUnfinishedTasks(user));
	}
	return userTasksEstimatedTime;
}

void Board::printUsersByWorkload()
{
	printUserList(getUsersSortedByWorkload());
}

void Board::printUsersByPerformance()
{
	printUserList(getUsersSortedByPerformance());
}

std::string Board::printBoard()
{
	std::string formattedOutput;
	for (List *list : lists)
	{
		formattedOutput += list->toString() + "\n";
	}
	return formattedOutput;
}

void Board::printUnassignedTasksByPriority()
{
	std::vector<Task*> tasksList;
	for (List* list: lists)
	{
		tasksList.insert(tasksList.end(), list->getUnassignedTasks().begin(), list->getUnassignedTasks().end());
	}
	tasksList = sortTaskListByPriority(tasksList);
	printTaskList(tasksList);
}

void Board::printAllUnfinishedTasksByPriority()
{
	std::vector<Task*> tasksList;
	for (User *user : users)
	{
		tasksList.insert(tasksList.end(), getUserUnfinishedTasks(user).begin(),getUserUnfinishedTasks(user).end());
	}
	tasksList = sortTaskListByPriority(tasksList);
	printTaskList(tasksList);
}

std::string Board::printUserList(std::vector<User *> userList)
{
	std::string formattedOutput;
	for (User *user : userList)
	{
		formattedOutput += user->toString() + "\n";
	}
	return formattedOutput;
}

bool Board::compareUsersByWorkload(const User *a, const User *b)
{
	return calculateUserTotalWorkload(a) < calculateUserTotalWorkload(b);
}

bool Board::compareUsersByPerformace(const User *a, const User *b)
{
	return calculateUserTotalWorkload(a) - calculateUserRemainingWorkload(a) < calculateUserTotalWorkload(b) - calculateUserRemainingWorkload(b);
}

bool Board::compareTasksByPriority(const Task *a, const Task *b)
{
	return a->hasHigherPriorityThan(*b);
}

std::vector<Task *> Board::sortTaskListByPriority(std::vector<Task *> taskList)
{
	std::sort(taskList.begin(), taskList.end(), compareTasksByPriority);
	return taskList;
}

std::vector<User *> Board::getUsersSortedByWorkload()
{
	std::vector<User *> usersCopy = users;
	std::sort(usersCopy.begin(), usersCopy.end(), compareUsersByWorkload);
	return usersCopy;
}

std::vector<User *> Board::getUsersSortedByPerformance()
{
	std::vector<User *> usersCopy = users;
	std::sort(usersCopy.begin(), usersCopy.end(), compareUsersByPerformace);
	return usersCopy;
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

Task *Board::findTaskInList(std::string listName, std::string taskName)
{
	List *listPointer = findList(listName);
	if (listPointer == nullptr)
	{
		return nullptr;
	}
	return listPointer->getTask(taskName);
}
