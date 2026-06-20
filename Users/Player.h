#pragma once
#include "User.h"
#include "Barn.h"
#include "Farm.h"
#include <functional>
#include "Market.h"
#include "Taskboard.h"

class Player:public User
{
private:
	static constexpr unsigned int PRICE = 50;
	static constexpr unsigned int CONDITION_EXPANSION = 10;

	Barn barn;
	Farm farm;

	unsigned int balance = 100;
	unsigned int score = 0;

	unsigned int currentCycle = 0;

	Market& market;
	Taskboard& taskBoard;

public:
	Player(const std::string& username, const std::string& password, Market& market, Taskboard& taskBoard);
	
	unsigned int checkBalance()const;
	unsigned int checkScore()const;

	unsigned int getCurrentCycle()const;
	Farm& getFarm();
	Barn& getBarn();

	void setBalance(int newBalance);
	void setScore(int newScore);

	void checkBarn()const;
	void checkFarm()const;

	bool expandLand(unsigned int currentCap, std::function<void(unsigned int)> setCapacity);

	bool expandCropland();
	bool expandFarmland();


	bool sowPlant(unsigned int seedId);
	bool addAnimal(unsigned int animalId);

	void harvest();

	void openMarketCatalog()const;

	bool buyItem(unsigned int id, unsigned int quantity);
	bool sellItem(unsigned int id, unsigned int quantity);

	void showTaskBoard()const;
	bool completeTask(unsigned int id);

	void profileInfo()const override;   

	void advanceCycle();

	std::ostream& serialize(std::ostream& os) const;
	std::istream& deserialize(std::istream& is);
};

