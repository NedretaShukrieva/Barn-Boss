#include "System.h"
#include <print>
#include <iostream>
#include <fstream>
#include "GameSerializer.h"

void System::setCurrentUser(User* user)
{
    currentUser = user;
}

void System::registerUser(const std::string& username, const std::string& password, const std::string& type)
{
    try {
        if (!UserValidator::isValidUsername(users, username))
            throw InvalidUsernameException();
        if (!UserValidator::isValidPassword(password))
            throw InvalidPasswordException();
        if (type == "TaskManager" && hasTaskManager)
            throw GameException("Task Manager already exists!");
        if (type == "MarketManager" && hasMarketManager)
            throw GameException("Market Manager already exists!");

        users.push_back(std::move(UserFactory::createUser(username, password, type, market, taskboard)));

        if (type == "MarketManager") hasMarketManager = true;
        if (type == "TaskManager") hasTaskManager = true;

        std::println("Registration successful!");
    }
    catch (const GameException& e) {
        std::println("{}", e.what());
    }
}

void System::login(const std::string& username, const std::string& password)
{
    auto it = std::find_if(users.begin(), users.end(),
        [&username, &password](const std::unique_ptr<User>& user) {
            return user->getUsername() == username &&
                user->getPassword() == password;
        });

    if (it == users.end()) {
        std::println("Invalid username or password!");
        return;
    }

    currentUser = it->get();
    std::println ("Welcome {} ", username);
}

void System::handlePlayerCommand(const std::string& command, Player* player)
{
    if (command == "checkBalance") {
        std::println("Balance: {}", player->checkBalance());
    }
    else if (command == "checkScore") {
        std::println("Score: {}", player->checkScore());
    }
    else if (command == "checkBarn") {
        player->checkBarn();
    }
    else if (command == "checkFarm") {
        player->checkFarm();
    }
    else if (command == "expandCropland") {
        if (player->expandCropland())
            player->advanceCycle();
    }
    else if (command == "expandFarmland") {
        if (player->expandFarmland())
            player->advanceCycle();
    }
    else if (command == "sowPlant") {
        unsigned int seedId;
        std::cin >> seedId;
        
        if (player->sowPlant(seedId))
            player->advanceCycle();
    }
    else if (command == "addAnimal") {
        unsigned int animalId;
        std::cin >> animalId;

        if (player->addAnimal(animalId))
            player->advanceCycle();
    }
    else if (command == "harvest") {
        player->harvest();
    }
    else if (command == "openMarketCatalog") {
        player->openMarketCatalog();
    }
    else if (command == "buyItem") {
        
        unsigned int id, quantity;
        std::cin >> id >> quantity;

        if (player->buyItem(id, quantity))
            player->advanceCycle();
    }
    else if (command == "sellItem") {
        
        unsigned int id, quantity;
        std::cin >> id >> quantity;

        if (player->sellItem(id, quantity))
            player->advanceCycle();
    }
    else if (command == "showTaskBoard") {
        player->showTaskBoard();
    }
    else if (command == "completeTask") {
        unsigned int taskId;
        std::cin >> taskId;
        
        if (player->completeTask(taskId))
            player->advanceCycle();
    }
    else if (command == "showScoreboard") {
        Scoreboard::show(users);
    }
    else {
        std::println("Invalid command!");
    }
}

void System::handleTaskManagerCommand(const std::string& command, TaskManager* taskManager)
{
    if (command == "showTaskBoard") {
        taskManager->showTasks();
    }

    else if (command == "addTask") {

        std::string product;
        unsigned int quantity, rewardBalance, rewardScore;

        std::println("Enter product: ");
        std::cin >> product;
        std::println("Enter quantity: ");
        std::cin >> quantity;
        std::println("Enter reward balance: ");
        std::cin >> rewardBalance;
        std::println("Enter reward score: ");
        std::cin >> rewardScore;

        taskManager->addTask(product, quantity, rewardBalance, rewardScore);
    }

    else if (command == "remove task") {

        unsigned int id;
        std::println("Enter task id: ");
        std::cin >> id;

        taskManager->removeTask(id);
    }

    else if (command == "profileInfo") {
        taskManager->profileInfo();
    }

    else {
        std::println("Invalid command!");
    }
}

void System::handleMarketManagerCommand(const std::string& command, MarketManager* marketManager)
{
    if (command == "openMarketCatalog") {
        marketManager->openMarketCatalog();
    }

    else if (command == "restock") {
       
        unsigned int id, quantity;
        std::cin >> id >> quantity;

        marketManager->restock(id, quantity);
    }

    else if (command == "changePrice") {
     
        unsigned int id, newPrice;
        std::cin >> id >> newPrice;

        marketManager->changePrice(id, newPrice);
    }

    else if (command == "profileInfo") {
        marketManager->profileInfo();
    }

    else {
        std::println("Invalid command!");
    }
}

void System::handleLoggedInCommand(const std::string& command)
{
    Player* player = dynamic_cast<Player*>(currentUser);
    TaskManager* taskManager = dynamic_cast<TaskManager*>(currentUser);
    MarketManager* marketManager = dynamic_cast<MarketManager*>(currentUser);

    if (command == "logout") {
        currentUser->logout(*this);
    }
    else if (command == "profileInfo") {
        currentUser->profileInfo();
    }
    else if (command == "changePassword") {
        std::string oldPass, newPass;
        std::cin >> oldPass >> newPass;
        currentUser->changePassword(oldPass, newPass);
    }
    else if (command == "showScoreboard") {
        Scoreboard::show(users);
    }
    
    else if (player) {
        handlePlayerCommand(command, player);
    }
    
    else if (taskManager) {
        handleTaskManagerCommand(command, taskManager);
    }
    
    else if (marketManager) {
        handleMarketManagerCommand(command, marketManager);
    }
    else {
        std::println ("Invalid command!");
    }
}

void System::run()
{

    std::println("========================================");
    std::println("                Barn Boss               ");
    std::println("========================================");

    GameSerializer::load(*this, "save.txt");

    std::string command;
    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (currentUser == nullptr) {
            if (command == "register") {
                std::string username, password, type;
                std::cin >> username >> password >> type;
                registerUser(username, password, type);
            }
            else if (command == "login") {
                std::string username, password;
                std::cin >> username >> password;
                login(username, password);
            }
            else if (command == "exit") {
                GameSerializer::save(*this, "save.txt");
                std::println("State saved successfully");
                break;
            }
            else {
                std::cout << "Invalid command!\n";
            }
        }
        else {
            handleLoggedInCommand(command);
        }
    }
}

std::unique_ptr<User> System::loadUser(std::istream& is)
{
    std::string type;
    is >> type;

    unsigned int id; 
    std::string username, password;
    is >> id >> username >> password; 

    auto user = UserFactory::createUser(
        username,
        password,
        type,
        market,
        taskboard
    );

    user->setId(id); 
    return user;
}


