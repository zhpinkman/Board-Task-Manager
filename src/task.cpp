#include "task.hpp"
#include <string>
#include <sstream>

Task::Task(std::string name, int estimatedTime, int priority, std::string description)
{
	this->name = name;
	editDetails(estimatedTime, priority, description);
	this->done = false;
	this->owner = nullptr;
}

Task::Task(const Task &task)
{
	this->name = task.name;
	this->estimatedTime = task.estimatedTime;
	this->priority = task.priority;
	this->description = task.description;
	this->owner = task.owner;
	this->done = task.done;
}

void Task::editDetails(int estimatedTime, int priority, std::string description)
{
	this->name = name;
	this->estimatedTime = estimatedTime;
	this->priority = priority;
	this->description = description;
}

void Task::setOwner(User* user)
{
	owner = user;
}

void Task::complete()
{
	done = true;
}

int Task::getEstimatedTime()
{
	return estimatedTime;
}

bool Task::isCompleted() const
{
	return done;
}

bool Task::isOwner(const User* user) const
{
	return user == owner;
}

bool Task::hasOwner() const
{
	return owner != nullptr;
}

bool Task::compareName(std::string name) const
{
	return name == this->name;
}

bool Task::hasHigherPriorityThan(const Task &other) const
{
	return this->priority > other.priority;
}

std::string Task::getSummary() const
{
	std::stringstream outputFormatter;
	outputFormatter << priority << SUMMARY_SEPARATOR << name << SUMMARY_SEPARATOR <<
		(owner == nullptr ? NO_OWNER_IDENTICATOR : owner->toString()) <<
		SUMMARY_SEPARATOR << estimatedTime << TIME_UNIT;
	return outputFormatter.str();
}

std::string Task::getFullDescription() const
{
	std::stringstream outputFormatter;
	outputFormatter << name << std::endl;
	outputFormatter << description << std::endl;
	outputFormatter << "Priority: " << priority << std::endl;
	outputFormatter << "Estimated Time: " << estimatedTime << std::endl;
	outputFormatter << (owner == nullptr ? NO_OWNER_IDENTICATOR : "Assigned to " + owner->toString());
	outputFormatter << std::endl;
	return outputFormatter.str();
}
