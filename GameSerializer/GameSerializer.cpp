#include "GameSerializer.h"
#include "System.h"
#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"
#include "UserFactory.h"
#include <fstream>
#include <print>

// GameSerializer.cpp
void GameSerializer::save(const System& system, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::println("Failed to save!");
        return;
    }

    file << "USERS " << system.users.size() << "\n";
    for (const auto& user : system.users) {
        file << *user;
    }

    file << system.market;
    file << system.taskboard;
}

void GameSerializer::load(System& system, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::println("No save file found. Starting new world!");
        return;
    }

    try {
        std::string section;
        unsigned int count;
        file >> section >> count;

        for (unsigned int i = 0; i < count; i++) {
            auto user = system.loadUser(file);
            if (!file) break;

            user->deserialize(file);

            if (dynamic_cast<TaskManager*>(user.get()))   system.hasTaskManager = true;
            if (dynamic_cast<MarketManager*>(user.get())) system.hasMarketManager = true;

            system.users.push_back(std::move(user));
        }

        unsigned int maxId = 0;
        for (const auto& user : system.users) {
            if (user->getId() > maxId)
                maxId = user->getId();
        }
        User::setCountOfUsers(maxId);

        file >> system.market;
        file >> system.taskboard;

        std::println("Game loaded successfully!");
    }
    catch (const std::exception& e) {
        std::println("Error loading save file: {}", e.what());
        std::println("Starting new world!");
        system.users.clear();
        system.hasTaskManager = false;
        system.hasMarketManager = false;
    }
}