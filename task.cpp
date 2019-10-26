#include "task.hpp"
#include <sstream>

Task(std::string name, int estimatedTime, int priority, std::string description) 
{
	editDetails(name, estimatedTime, priority, description);
	this->done = false;
	this->owner = nullptr;
}

Task(const Task &task) 
{
	this->name = task.name;
	this->estimatedTime = task.estimatedTime;
	this->priority = task.priority;
	this->description = task.description;
	this->owner = task.owner;
	this->done = task.done;
}

void editDetails(int estimatedTime, int priority, std::string description) 
{
	this->name = name;
	this->estimatedTime = estimatedTime;
	this->priority = priority;
	this->description = description;
}

void setOwner(User* user) 
{
	owner = user;
}

void complete() 
{
	done = true;
}

int getEstimatedTime() 
{
	return estimatedTime;
}

bool isCompleted() const 
{
	return done;
}

bool isOwner(const User* user) const 
{
	return user == owner;
}

bool hasOwner() const 
{
	return owner != nullptr;
}

bool compareName(std::string name) const 
{
	return name == this->name;
}

bool hasHigherPriorityThan(const Task &other) const 
{
	return this->priority > other.priority;
}

std::string getSummary() const 
{
	std::stringstream outputFormatter;
	outputFormatter << priority << SUMMARY_SEPARATOR << name << SUMMARY_SEPARATOR << 
		owner == nullptr ? NO_OWNER_IDENTICATOR : owner->toString() << 
		SUMMARY_SEPARATOR << estimatedTime << TIME_UNIT;
	return outputFormatter.to_str();
}

std::string getFullDescription() const 
{
	std::stringstream outputFormatter;
	outputFormatter << name << std::endl;
	outputFormatter << description << std::endl;
	outputFormatter << "Priority: " << priority << std::endl;
	outputFormatter << "Estimated Time: " << estimatedTime << std::endl;
	outputFormatter << "Assigned to " << 
		owner == nullptr ? NO_OWNER_IDENTICATOR : owner->toString() << std::endl; 
	return outputFormatter.to_str();
}
