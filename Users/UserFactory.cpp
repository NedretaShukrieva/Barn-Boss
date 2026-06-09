#include "UserFactory.h"

std::unique_ptr<User> UserFactory::createUser(const std::string& username, const std::string& password, const std::string& type, Market& market, Taskboard& taskboard)
{
    if (type == "Player")
        return std::make_unique<Player>(username, password, market, taskboard);
    if (type == "TaskManager")
        return std::make_unique<TaskManager>(username, password, taskboard);
    if (type == "MarketManager")
        return std::make_unique<MarketManager>(username, password, market);

    throw InvalidUserTypeException();
}
