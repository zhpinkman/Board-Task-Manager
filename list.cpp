#include "list.hpp"


List::List(std::string name)
{
    listName = name;
}

void List::addTask(Task *task)
{
    tasks.push_back(task);
}

void List::deleteTask(Task *task)
{
    tasks.erase(std::find(tasks.begin(), tasks.end(), task));
    delete task;
}

void clear()
{
    for (Task *task : tasks)
    {
        delete task;
    }
    tasks.clear();
}

std::vector<Task *> List::getUnassignedTasks()
{
    std::vector<Task *> unassignedTasks;
    for (Task *task : tasks) 
    {
        if (!task->hasOwner())
        {
            unassignedTasks.push_back(task);
        }
    }
    return unassignedTasks;
}

std::vector<Task *> List::getUnfinishedTasks()
{
    std::vector<Task *> unfinishedTasks;
    for (Task *task : tasks) 
    {
        if (!task->isCompleted())
        {
            unfinishedTasks.push_back(task);
        }
    }
    return unfinishedTasks;
}

std::vector<Task *> List::getUserUnfinishedTasks(const User *user)
{
    std::vector<Task *> userUnfinishedTasks;
    for (Task *task : tasks)
    {
        if (!task->isCompleted() && task->isOwner(user))
        {
            userUnfinishedTasks.push_back(task);
        }
    }
    return userUnfinishedTasks;
}

std::vector<Task *> List::getUserTasks(const User *user)
{
    std::vector<Task *> userTasks;
    for (Task *task : tasks)
    {
        if (task->isOwner(user))
        {
            userTasks.push_back(task);
        }
    }
    return userTasks;
}

Task *List::getTask(std::string taskName)
{
    for (Task *task : tasks)
    {
        if (task->compareName(taskName))
        {
            return task;
        }
    }
    return nullptr;
}

bool List::compareName(std::string name)
{
    return name == listName;
}

std::string List::toString() 
{
    std::string formattedOutput;
    for (Task *task : tasks)
    {
        formattedOutput += task->toString() + "\n";
    }
    return formattedOutput;
}