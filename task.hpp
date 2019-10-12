#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "user.hpp"
#include <string>

class Task
{
public:
	Task(std::string name, int estimatedTime, int priority, std::string description);
	Task(const Task &task);

	void addMember(User *user);

	bool isMember(User *user) const;

	std::string toString() const;

	void completeTask();
	bool isCompleted();
};

#endif