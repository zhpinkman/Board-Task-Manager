#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "user.hpp"
#include "list.hpp"
#include "task_utility.hpp"
#include <vector>
#include <string>

class Board
{
public:
    Board();
    std::string addUser(std::string username);
    std::string addTask(std::string list, std::string name, int estimatedTime, int priority, std::string description);
    std::string editTask(std::string task, int estimatedTime, int priority, std::string description);
    std::string deleteTask(std::string task);
    std::string setTaskOwner(std::string task, std::string member);
    std::string moveTask(std::string task, std::string list);
    std::string completeTask(std::string task);
    std::string printTask(std::string task);


    std::string addList(std::string name);
    std::string deleteList(std::string list);
    std::string printList(std::string list);

    std::string printUserTasks(std::string userName);
    std::vector<Task*> getUserTasks(const User* user);
    std::vector<Task*> getUserUnfinishedTasks(const User* user);
    std::string printUserUnfinishedTasks(std::string userName);

    int getTotalEstimatedTime();
    int getTotalRemainingTime();
    int calculateEstimatedTime(std::vector<Task*> tasks);
    int calculateUserTotalWorkload(const User* user);
    int calculateUserRemainingWorkload(const User* user);
    int calculateUserPerformance(const User *user);
    std::vector<User*> getUsersSortedByPerformance();
    std::vector<Task*> sortTaskListByPriority(std::vector<Task*> taskList);

    int getUserWorkload(std::string user);
    bool compareUsersByWorkload(const User* a, const User* b);
    std::vector<User *> getUsersSortedByWorkload();
    bool compareUsersByPerformace(const User *a, const User *b);

    std::string printUsersByWorkload();
    std::string printUsersByPerformance();
    std::string printUserList(std::vector<User *> userList);
    bool compareTasksByPriority(const Task* a, const Task* b);

    std::string printBoard();
    std::string printUnassignedTasksByPriority();
    std::string printAllUnfinishedTasksByPriority();

private:
    std::vector<User *> users;
    std::vector<List *> lists;

    User *findUser(std::string name);
    List *findList(std::string name);
    Task *findTask(std::string name);

    List *findListContainingTask(std::string taskName);

    Task *findTaskInList(std::string listName, std::string taskName);
};

#endif