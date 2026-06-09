#pragma once
#include "User.h"
#include "Market.h"

class MarketManager:public User
{
private:
	Market& market;

public:
	MarketManager(const std::string& username, const std::string& password, Market& market);

	void openMarketCatalog()const;
	void restock(unsigned int id, unsigned int quantity);
	void changePrice(unsigned int id, unsigned int newPrice);

	void profileInfo()const override;

	std::ostream& serialize(std::ostream& os) const override;
	std::istream& deserialize(std::istream& is) override;
};

