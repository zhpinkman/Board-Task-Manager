#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <vector>
#include <iostream>
#include "task.hpp"

class List
{
public:
    List(std::string name);
    void addTask(Task *task);
    void deleteTask(std::string taskName);
    void printTasks();
    std::vector<Task *> getUnassignedTasks();
    std::vector<Task *> getUnfinishedTasks();
    std::vector<Task *> getUserUnfinishedTasks(std::string userName);
    std::vector<Task *> getUserTasks(std::string userName);
    Task *getTask(std::string taskName);

    bool compareName(std::string name);
    std::string toString();

private:
    std::vector<Task *> tasks;
    std::string listName;
};

#endif