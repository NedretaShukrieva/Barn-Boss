#pragma once
#include "User.h"
#include "Taskboard.h"
#include <vector>

class TaskManager: public User
{
private:
	
	Taskboard& taskboard;

public:

    TaskManager(const std::string& username,
        const std::string& password, Taskboard& taskBoard);

    void showTasks() const;
    void addTask(const std::string& product, unsigned int quantity,
        unsigned int rewardBalance, unsigned int rewardScore);
    void removeTask(unsigned int taskId);

    void profileInfo()const override;

    std::ostream& serialize(std::ostream& os) const override;
    std::istream& deserialize(std::istream& is) override;
};

