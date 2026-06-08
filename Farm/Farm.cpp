#include "Farm.h"
#include <print>
#include "GameException.h"

bool Farm::addPlant(std::unique_ptr<Plantable> plant)
{
	if (cropland.size() >= croplandCapacity) {
		std::println("No space in cropland!");
		return false;
	}

	cropland.push_back(std::move(plant));
	return true;
}

bool Farm::addAnimal(std::unique_ptr<Animal> animal)
{
	if (farmland.size() >= farmlandCapacity) {
		std::println("No space in farmland!");
		return false;
	}

	farmland.push_back(std::move(animal));
	return true;
}

void Farm::display() const
{
	std::println("=== FARM ===");
	std::println("Cropland: {}/{} slots used", cropland.size(), croplandCapacity);
	std::println("Farmland: {}/{} slots used", farmland.size(), farmlandCapacity);

	if (!cropland.empty()) {
		std::println("-- Plants --");
		for (const auto& plant : cropland) {
			std::println("  {} - Cycle: {}/{}",
				Utils::productTypeToString(plant->getInputType()),
				plant->getCurrentCycle(),
				plant->getRequiredCycle());
		}
	}

	if (!farmland.empty()) {
		std::println("-- Animals --");
		for (const auto& animal : farmland) {
			std::println("  {} - Cycle: {}/{}",
				Utils::productTypeToString(animal->getInputType()),
				animal->getCurrentCycle(),
				animal->getRequiredCycle());
		}
	}
}

bool Farm::hasCroplandSpace() const
{
	return cropland.size() < croplandCapacity;
}

bool Farm::hasFarmlandSpace() const
{
	return farmland.size() < farmlandCapacity;
}

unsigned int Farm::getCroplandCapacity() const
{
	return croplandCapacity;
}

unsigned int Farm::getFarmlandCapacity() const
{
	return farmlandCapacity;
}

void Farm::setCroplandCapacity(unsigned int newCap)
{
	croplandCapacity = newCap;
}


void Farm::harvest(Barn& barn)
{
	std::erase_if(cropland, [&barn](const std::unique_ptr<Plantable>& p) {
		if (p->isReady()) {
			barn.addProduct(p->getOutputType(), 1);
			return true;
		}
		return false;
		});

	std::erase_if(farmland, [&barn](const std::unique_ptr<Animal>& a) {
		if (a->isReady()) {
			barn.addProduct(a->getOutputType(), 1);
			return true;
		}
		return false;
		});

	std::println("Harvest completed!");
}

void Farm::growAll()
{
	for (size_t i = 0; i < cropland.size(); i++)
	{
		cropland[i]->grow();
	}

	for (size_t i = 0; i < farmland.size(); i++)
	{
		farmland[i]->grow();
	}
}


std::ostream& operator<<(std::ostream& os, const Farm& farm)
{
	os << "FARM\n";
	os << farm.croplandCapacity << " " << farm.farmlandCapacity << "\n";

	os << "CROPLAND " << farm.cropland.size() << "\n";
	for (const auto& plant : farm.cropland) {
		os << Utils::productTypeToString(plant->getInputType())
			<< " " << plant->getCurrentCycle() << "\n";
	}

	os << "FARMLAND " << farm.farmland.size() << "\n";
	for (const auto& animal : farm.farmland) {
		os << Utils::productTypeToString(animal->getInputType())
			<< " " << animal->getCurrentCycle() << "\n";
	}

	os << "END\n";

	return os;
}

std::istream& operator>>(std::istream& is, Farm& farm)
{
	farm.cropland.clear();
	farm.farmland.clear();

	std::string section;
	is >> section;

	if (section != "FARM") {
		throw InvalidFileFormatException();
	}
		
	is >> farm.croplandCapacity >> farm.farmlandCapacity;

	is >> section;

	if (section != "CROPLAND") {
		throw InvalidFileFormatException();
	}
		
	unsigned int cropCount;
	is >> cropCount;

	for (unsigned int i = 0; i < cropCount; i++) {
		std::string productName;
		unsigned int cycle;
		is >> productName >> cycle;

		ProductType type = Utils::stringToProductType(productName);

		std::unique_ptr<Plantable> plant;

		switch (type) {
		case ProductType::WheatSeed: plant = std::make_unique<WheatSeed>(); break;
		case ProductType::CornSeed:  plant = std::make_unique<CornSeed>();  break;
		}

		if (plant) {
			plant->setCurrentCycle(cycle);
			farm.cropland.push_back(std::move(plant));
		}
	}

	
	is >> section;

	if (section != "FARMLAND") {
		throw InvalidFileFormatException();
	}
		
	unsigned int animalCount;
	is >> animalCount;

	for (unsigned int i = 0; i < animalCount; i++) {

		std::string productName;
		unsigned int cycle;
		is >> productName >> cycle;

		ProductType type = Utils::stringToProductType(productName);

		std::unique_ptr<Animal> animal;

		switch (type) {
		case ProductType::Chicken: animal = std::make_unique<Chicken>(); break;
		case ProductType::Cow:     animal = std::make_unique<Cow>();     break;
		}

		if (animal) {
			animal->setCurrentCycle(cycle);
			farm.farmland.push_back(std::move(animal));
		}
	}

	std::string endToken;
	is >> endToken;

	if (endToken != "END") {
		throw InvalidFileFormatException();
	}
		
	return is;
}
