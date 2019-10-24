#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "user.hpp"
#include <string>

class Task
{
public:
	Task(std::string name, int estimatedTime, int priority, std::string description);
	Task(const Task &task);

	void editDetails(int estimatedTime, int priority, std::string newDescription);

	void setOwner(User* user);
	void complete();

	bool isCompleted() const;
	bool isOwner(User* user) const;
	bool compareName(std::string name) const;
	bool hasHigherPriorityThan(const Task &other) const;

	std::string toString() const;

	static int calculateEstimatedTime(const std::vector<Task> &tasks);

private:
	std::string name, description;
	int priority, estimatedTime;
};

#endif