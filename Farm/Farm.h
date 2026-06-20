#pragma once
#include "Plantable.h"
#include "Animal.h"
#include "WheatSeed.h"
#include "CornSeed.h"
#include "Cow.h"
#include "Chicken.h"
#include "Barn.h"
#include <iostream>
#include <vector>
#include <memory>

class Farm
{
private:

	std::vector<std::unique_ptr<Plantable>> cropland;
	std::vector<std::unique_ptr<Animal>> farmland;

	unsigned int croplandCapacity = 3;
	unsigned int farmlandCapacity = 3;

public:
	bool addPlant(std::unique_ptr <Plantable> plant);
	bool addAnimal(std::unique_ptr<Animal> animal);

	void display()const;

	bool hasCroplandSpace()const;
	bool hasFarmlandSpace()const;

	unsigned int getCroplandCapacity()const;
	unsigned int getFarmlandCapacity()const;

	void setCroplandCapacity(unsigned int newCap);
	void setFarmlandCapacity(unsigned int newCap);

	void harvest(Barn& barn);
	void growAll();


	friend std::ostream& operator<<(std::ostream& os, const Farm& farm);
	friend std::istream& operator>>(std::istream& is, Farm& farm);
};

