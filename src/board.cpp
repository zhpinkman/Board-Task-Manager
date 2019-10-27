#include "board.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

Board::Board()
{
}

std::string Board::addUser(std::string userName)
{
	if (findUser(userName) != nullptr)
	{
		return "User already exists";
	}
	users.push_back(new User(userName));
	return "Success";
}

std::string Board::addTask(std::string listName, std::string name, int estimatedTime, int priority, std::string description)
{
	List *list = findList(listName);
	if (list == nullptr)
	{
		return "List not available";
	}
	if (findTask(name) != nullptr)
	{
		return "Task already exists";
	}
	list->addTask(new Task(name, estimatedTime, priority, description));
	return "Success";
}

std::string Board::editTask(std::string taskName, int estimatedTime, int priority, std::string description)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		return "Task does not exist";
	}
	task->editDetails(estimatedTime, priority, description);
	return "Success";
}

std::string Board::deleteTask(std::string taskName)
{
	List *containerList = findListContainingTask(taskName);
	if (containerList == nullptr)
	{
		return "Task does not exist";
	}
	containerList->deleteTask(findTask(taskName));
	return "Success";
}

std::string Board::setTaskOwner(std::string taskName, std::string userName)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		return "Task does not exist";
	}
	User *user = findUser(userName);
	if (user == nullptr)
	{
		return "User does not exist";
	}
	task->setOwner(user);
	return "Success";
}

std::string Board::moveTask(std::string taskName, std::string listName)
{
	List *destinationList = findList(listName);
	if (destinationList == nullptr)
	{
		return "List not available";
	}
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		return "Task does not exists";
	}
	List *sourceList = findListContainingTask(taskName);
	Task* taskCopy = new Task(*task);
	destinationList->addTask(taskCopy);
	sourceList->deleteTask(task);
	return "Success";
}

std::string Board::completeTask(std::string taskName)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		return "Task does not exists";
	}
	task->complete();
	return "Success";
}

std::string Board::printTask(std::string taskName)
{
	Task *task = findTask(taskName);
	if (task == nullptr)
	{
		return "Task does not exists";
	}
	return task->getFullDescription();
}

std::string Board::addList(std::string listName)
{
	if (findList(listName) != nullptr)
	{
		return "List already exists";
	}
	lists.push_back(new List(listName));
	return "Success";
}

std::string Board::deleteList(std::string listName)
{
	List *list = findList(listName);
	if (list == nullptr)
	{
		return "List does not exists";
	}
	lists.erase(std::find(lists.begin(), lists.end(), list));
	delete list;
	return "Success";
}

std::string Board::printList(std::string listName)
{
	List *list = findList(listName);
	if (list == nullptr)
	{
		return "List does not exists";
	}
	return list->toString();
}

std::string Board::printUserTasks(std::string userName) 
{
	User *user = findUser(userName);
	if (user == nullptr)
	{
		return "User does not exist";
	}
	return formatTaskListToString(getUserTasks(user));
}

std::vector<Task *> Board::getUserTasks(const User* user)
{
	std::vector<Task *> userTasks;
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserTasks(user);
		userTasks.insert(userTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	return userTasks;
}

std::string Board::printUserUnfinishedTasks(std::string userName)
{
	std::vector<Task *> userUnfinishedTasks;
	User* user = findUser(userName);
	if (user == nullptr)
	{
		return "User does not exist";
	}
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserUnfinishedTasks(user);
		userUnfinishedTasks.insert(userUnfinishedTasks.end(), userTasksInList.begin(), userTasksInList.end());
	}
	return formatTaskListToString(userUnfinishedTasks);
}

std::vector<Task *> Board::getUserUnfinishedTasks(const User *user)
{
	std::vector<Task *> userUnfinishedTasks;
	for (List *list : lists)
	{
		std::vector<Task *> userTasksInList = list->getUserUnfinishedTasks(user);\
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
		return 0;
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

int Board::calculateUserPerformance(const User *user) 
{
	return calculateUserTotalWorkload(user) - calculateUserRemainingWorkload(user);
}

std::string Board::printUsersByWorkload()
{
	return printUserList(getUsersSortedByWorkload());
}

std::string Board::printUsersByPerformance()
{
	return printUserList(getUsersSortedByPerformance());
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

std::string Board::printUnassignedTasksByPriority()
{
	std::vector<Task *> tasksList;
	for (List* list: lists)
	{
		std::vector<Task *> listUnassignedTasks = list->getUnassignedTasks();
		tasksList.insert(tasksList.end(), listUnassignedTasks.begin(), listUnassignedTasks.end());
	}
	tasksList = sortTaskListByPriority(tasksList);
	return formatTaskListToString(tasksList);
}

std::string Board::printAllUnfinishedTasksByPriority()
{
	std::vector<Task*> tasksList;
	for (User *user : users)
	{
		std::vector<Task *> userUnfinishedTasks = getUserUnfinishedTasks(user);
		tasksList.insert(tasksList.end(), userUnfinishedTasks.begin(),userUnfinishedTasks.end());
	}
	tasksList = sortTaskListByPriority(tasksList);
	return formatTaskListToString(tasksList);
}

std::string Board::printUserList(std::vector<User *> userList)
{
	std::stringstream formatterStream;
	for (int i = 0; i < userList.size(); i++)
	{
		formatterStream << i+1 << ". " << userList[i]->toString() << std::endl;
	}
	return formatterStream.str();
}

std::vector<Task *> Board::sortTaskListByPriority(std::vector<Task *> taskList)
{
	for (int i = 0; i < (int)taskList.size() - 1; i++) 
	{ 
		for (int j = 0; j < (int)taskList.size() - i - 1; j++) 
		{ 
			if (taskList[j]->hasHigherPriorityThan(*taskList[j+1])) 
			{ 
				Task* swapHelper = taskList[j];
				taskList[j] = taskList[j+1];
				taskList[j+1] = swapHelper;
			} 
		}
	} 
	return taskList;
}

std::vector<User *> Board::getUsersSortedByWorkload()
{
	std::vector<User *> usersCopy = users;
	for (int i = 0; i < (int)usersCopy.size() - 1; i++) 
	{ 
		for (int j = 0; j < (int)usersCopy.size() - i - 1; j++) 
		{ 
			if (calculateUserTotalWorkload(usersCopy[j]) > calculateUserTotalWorkload(usersCopy[j+1])) 
			{ 
				User* swapHelper = usersCopy[j];
				usersCopy[j] = usersCopy[j+1];
				usersCopy[j+1] = swapHelper;
			} 
		}
	} 
	return usersCopy;
}

std::vector<User *> Board::getUsersSortedByPerformance()
{
	std::vector<User *> usersCopy = users;
	for (int i = 0; i < (int)usersCopy.size() - 1; i++) 
	{ 
		for (int j = 0; j < (int)usersCopy.size() - i - 1; j++) 
		{ 
			if (calculateUserPerformance(usersCopy[j]) < calculateUserPerformance(usersCopy[j+1])) 
			{ 
				User* swapHelper = usersCopy[j];
				usersCopy[j] = usersCopy[j+1];
				usersCopy[j+1] = swapHelper;
			}
		}
	} 
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
