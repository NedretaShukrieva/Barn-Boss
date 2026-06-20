#include "Player.h"
#include <iostream>
#include "WheatSeed.h"
#include "CornSeed.h"
#include "Chicken.h"
#include "Cow.h"
#include <print>
#include <fstream>

Player::Player(const std::string& username, const std::string& password, Market& market, Taskboard& taskBoard):
    User(username, password), market(market), taskBoard(taskBoard)
{
}

unsigned int Player::checkBalance() const
{
    return balance;
}

unsigned int Player::checkScore() const
{
    return score;
}

unsigned int Player::getCurrentCycle() const
{
    return currentCycle;
}

void Player::setBalance(int newBalance)
{
    balance = newBalance;
}

void Player::setScore(int newScore)
{
    score = newScore;
}

Farm& Player::getFarm()
{
    return farm;
}

Barn& Player::getBarn()
{
    return barn;
}


void Player::checkBarn() const
{
    barn.display();
}

void Player::checkFarm() const
{
    farm.display();
}

bool Player::expandLand(unsigned int currentCap, std::function<void(unsigned int)> setCapacity)
{
    unsigned int totalPrice = PRICE * currentCap;

    if (score < CONDITION_EXPANSION * currentCap) {
        std::println("Not enough points!");
        return false;
    }
    if (balance < totalPrice) {
        std::println("Not enough balance!");
        return false;
    }

    balance -= totalPrice;
    setCapacity(currentCap + 1);
    std::println("Successful expansion!");
    return true;
}

bool Player::expandCropland()
{
    return expandLand(farm.getCroplandCapacity(),
        [this](unsigned int cap) { farm.setCroplandCapacity(cap); });
}

bool Player::expandFarmland()
{
    return expandLand(farm.getFarmlandCapacity(),
        [this](unsigned int cap) {farm.setFarmlandCapacity(cap); });

}

bool Player::sowPlant(unsigned int seedId) {

    ProductType seedType;
    std::unique_ptr<Plantable> plant;

    switch (seedId) {
    case 1:
        seedType = ProductType::WheatSeed;
        plant = std::make_unique<WheatSeed>();
        break;
    case 2:
        seedType = ProductType::CornSeed;
        plant = std::make_unique<CornSeed>();
        break;
    default:
        std::println("Invalid seed id!");
        return false;
    }

    if (!farm.hasCroplandSpace()) {
        std::println("No space in cropland!");
        return false;
    }

    if (barn.getQuantity(seedType) < 1) {
        std::println("Not enough seeds in barn!");
        return false;
    }

    barn.removeProduct(seedType, 1);
    farm.addPlant(std::move(plant));

    std::println("Plants planted successfully!");

    return true;
}

bool Player::addAnimal(unsigned int animalId) {
    ProductType animalType;
    std::unique_ptr<Animal> animal;

    switch (animalId) {
    case 3:
        animalType = ProductType::Chicken;
        animal = std::make_unique<Chicken>();
        break;
    case 4:
        animalType = ProductType::Cow;
        animal = std::make_unique<Cow>();
        break;
    default:
        std::println("Invalid animal id!");
        return false;
    }

    if (!farm.hasFarmlandSpace()) {
        std::println("No space in farmland!");
        return false;
    }

    if (barn.getQuantity(animalType) < 1) {
        std::println("Not enough animals in barn!");
        return false;
    }

    barn.removeProduct(animalType, 1);
    farm.addAnimal(std::move(animal));

    std::println("Animals added successfully!");

    return true;
}

void Player::harvest()
{
    farm.harvest(barn);
}

void Player::openMarketCatalog() const
{
    market.showCatalog();
}

bool Player::buyItem(unsigned int id, unsigned int quantity)
{
    return market.buyItem(id, quantity, balance, barn);
}

bool Player::sellItem(unsigned int id, unsigned int quantity)
{
    return market.sellItem(id, quantity, balance, barn);
}

void Player::showTaskBoard() const
{
    taskBoard.showTasks();
}

bool Player::completeTask(unsigned int id)
{
    Task* task=taskBoard.findTask(id);

    if (!task) {
        std::println ("Task does not exist!");
        return false;
    }

    if (barn.getQuantity(task->getProduct()) < task->getRequiredQuantity()) {
        std::println ("Not enough quantity to complete the task!");
        return false;
    }

    barn.removeProduct(task->getProduct(), task->getRequiredQuantity());
    balance += task->getRewardBalance();
    score += task->getRewardScore();
    taskBoard.removeTask(id);
    return true;
}

void Player::profileInfo() const
{
    std::println("ID: {}", this->getId());
    std::println("Username: {}", this->getUsername());
    std::println("Balance: {}", balance);
    std::println("Score: {}", score);
}

void Player::advanceCycle()
{
    currentCycle++;
    farm.growAll();
    
}


std::ostream& Player::serialize(std::ostream& os) const
{
    os << "Player ";
    serializeBase(os);
    os << balance << " " << score << " " << currentCycle << "\n";
    os << barn;
    os << farm;

    return os;
}

std::istream& Player::deserialize(std::istream& is)
{
    is >> balance >> score >> currentCycle;
    is >> barn;  
    is >> farm;  
    return is;
}


