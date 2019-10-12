#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <vector>
#include "task.hpp"

class List
{
public:
    List(std::string name);
    void addTask(std::string taskName);
    void deleteTask(std::string taskName);
    void printTasks();
    std::vector<Task> getUnassignedTasks();
    std::vector<Task> getUnfinishedTasks();
    std::vector<Task> getUserTasks(std::string username);
    Task getTask(std::string taskName);

    std::string toString();

private:
    std::vector<Task> tasks;
};

#endif