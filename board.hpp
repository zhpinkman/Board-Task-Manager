#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "user.hpp"
#include "list.hpp"
#include <vector>
#include <string>

class Board
{
public:
    Board();
    void addUser(std::string username);
    void addTask(std::string list, std::string name, int estimatedTime, int priority, std::string description);
    void editTask(std::string task, int estimatedTime, int priority, std::string description);
    void deleteTask(std::string task);
    void addMember(std::string task, std::string member);
    void moveTask(std::string task, std::string list);
    void completeTask(std::string task);
    void printTask(std::string task);

    void addList(std::string name);
    void deleteList(std::string list);
    void printList(std::string list);

    void getUserTasks(std::string user);
    void getUserUnfinishedTasks(std::string user);

    void getTotalEstimatedTime();
    void getTotalRemainingTime();

    void getUserWorkload(std::string user);

    void printUsersByWorkload();
    void printUsersByPerformance();

    void printBoard();
    void printUnassignedTasksByPriority();
    void printAllUnfinishedTasksByPriority();

private:
    std::vector<User> users;
    std::vector<List> lists;
};

#endif