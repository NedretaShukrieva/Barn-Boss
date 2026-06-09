#include "MarketManager.h"

MarketManager::MarketManager(const std::string& username, const std::string& password, Market& market):User(username, password), market(market)
{
}

void MarketManager::openMarketCatalog() const
{
	market.showCatalog();
}

void MarketManager::restock(unsigned int id, unsigned int quantity)
{
	market.restock(id, quantity);
}

void MarketManager::changePrice(unsigned int id, unsigned int newPrice)
{
	market.changePrice(id, newPrice);
}

void MarketManager::profileInfo() const
{
	std::println("ID: {}", this->getId());
	std::println("Username: {}", this->getUsername());
	std::println("Role: MarketManager");
}

std::ostream& MarketManager::serialize(std::ostream& os) const
{
	os << "MarketManager ";
	serializeBase(os);
	os << "\n";
	return os;
}

std::istream& MarketManager::deserialize(std::istream& is)
{
	return is;
}
