#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "task.hpp"

class List
{
public:
    List(std::string name);
    void addTask(Task *task);
    void deleteTask(Task *task);
    void clear();

    std::vector<Task *> getUnassignedTasks();
    std::vector<Task *> getUnfinishedTasks();
    std::vector<Task *> getUserUnfinishedTasks(const User* user);
    std::vector<Task *> getUserTasks(const User* user);
    Task *getTask(std::string taskName);

    bool compareName(std::string name);
    std::string toString();

private:
    std::vector<Task *> tasks;
    std::string listName;
};

#endif