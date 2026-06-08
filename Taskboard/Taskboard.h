#pragma once
#include "Task.h"
#include <vector>

class Taskboard
{
    std::vector<Task> tasks;

public:
    Taskboard(); 

    void showTasks() const;
    void addTask(const std::string& product, unsigned int quantity,
        unsigned int rewardBalance, unsigned int rewardScore);
    void removeTask(unsigned int taskId);

    Task* findTask(unsigned int taskId); 

    friend std::ostream& operator<<(std::ostream& os, const Taskboard& taskboard);
    friend std::istream& operator>>(std::istream& is, Taskboard& taskboard);
    
};

