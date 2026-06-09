#pragma once
#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"

class UserFactory
{
public:
    static std::unique_ptr<User> createUser(
        const std::string& username,
        const std::string& password,
        const std::string& type,
        Market& market,
        Taskboard& taskboard);
};

