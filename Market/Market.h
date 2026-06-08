#pragma once
#include "MarketItem.h"
#include <vector>
#include "Barn.h"
#include <fstream>

class Market
{
private:
	std::vector<MarketItem> catalog;

public:
	Market();
	
	void showCatalog()const;

	MarketItem* findItem(unsigned int id);

	bool buyItem(unsigned int id, unsigned int quantity, unsigned int& playerBalance, Barn& barn);
	bool sellItem(unsigned int id, unsigned int quantity, unsigned int& playerBalance, Barn& barn);
	void restock(unsigned int id, unsigned int quantity);
	void changePrice(unsigned int id, unsigned int newPrice);

	friend std::ostream& operator<<(std::ostream& os, const Market& market);
	friend std::istream& operator>>(std::istream& is, Market& market);

};

