#pragma once
#include "User.h"
#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"
#include "UserFactory.h"
#include "Scoreboard.h"
#include <vector>
#include <memory>

class GameSerializer;

class System
{

	friend class GameSerializer;
private:

	std::vector<std::unique_ptr<User>> users;
	User* currentUser = nullptr;

	bool hasTaskManager = false;
	bool hasMarketManager = false;

	Market market;
	Taskboard taskboard;


public:
	void setCurrentUser(User* user);
	void registerUser(const std::string& username, const std::string& password, const std::string& type);

	void login(const std::string& username, const std::string& password);

	void handlePlayerCommand(const std::string& command, Player* player);
	void handleTaskManagerCommand(const std::string& command, TaskManager* taskManager);
	void handleMarketManagerCommand(const std::string& command, MarketManager* marketManager);

	void handleLoggedInCommand(const std::string& command);

	void run();

	std::unique_ptr<User> loadUser(std::istream& is);
	

};

