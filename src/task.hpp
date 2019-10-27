#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "user.hpp"
#include <string>

const std::string SUMMARY_SEPARATOR = " | ";
const std::string TIME_UNIT = "h";
const std::string NO_OWNER_IDENTICATOR = "Unassigned";

class Task
{
public:
	Task(std::string name, int estimatedTime, int priority, std::string description);
	Task(const Task &task);

	void editDetails(int estimatedTime, int priority, std::string description);

	void setOwner(User* user);
	void complete();
	int getEstimatedTime();

	bool isCompleted() const;
	bool isOwner(const User* user) const;
	bool hasOwner() const;
	bool compareName(std::string name) const;
	bool hasHigherPriorityThan(const Task &other) const;

	std::string toString() const;

private:
	std::string name, description;
	int priority, estimatedTime;
	bool done;
	User *owner;
};

#endif