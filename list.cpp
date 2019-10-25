#include "list.hpp"
List::List(std::string name)
{
    listName = name;
}
void List::addTask(Task *task)
{
    // todo do we have to check duplicate or not ??
    tasks.push_back(task);
}
void List::deleteTask(std::string taskName)
{
    int taskIndex = 0;
    for (Task *task : tasks)
    {
        if (task->compareName(taskName))
        {
            tasks.erase(tasks.begin() + taskIndex);
            return;
        }
        taskIndex++;
    }
    std::cout << "task not found in the list" << std::endl;
}
void List::printTasks()
{
    for (Task *task : tasks)
        task->toString();
}
std::vector<Task *> List::getUnassignedTasks()
{
    std::vector<Task *> unassignedTasks;
    for (Task *task : tasks)
        if (task->getOwner() == nullptr)
            unassignedTasks.push_back(task);
    return unassignedTasks;
}
std::vector<Task *> List::getUnfinishedTasks()
{
    std::vector<Task *> unfinishedTasks;
    for (Task *task : tasks)
        if (!task->isCompleted())
            unfinishedTasks.push_back(task);
    return unfinishedTasks;
}
std::vector<Task *> List::getUserUnfinishedTasks(std::string userName)
{
    std::vector<Task *> userUnfinishedTasks;
    for (Task *task : tasks)
        if (!task->isCompleted() && task->isOwner(userName))
            userUnfinishedTasks.push_back(task);
    return userUnfinishedTasks;
}
std::vector<Task *> List::getUserTasks(std::string userName)
{
    std::vector<Task *> userTasks;
    for (Task *task : tasks)
        if (task->isOwner(userName))
            userTasks.push_back(task);
    return userTasks;
}
Task *List::getTask(std::string taskName)
{
    for (Task *task : tasks)
        if (task->compareName(taskName))
            return task;
    std::cout << "task not found" << std::endl;
    return nullptr;
}

bool List::compareName(std::string name)
{
    return name == listName;
}
// std::string List::toString() {}