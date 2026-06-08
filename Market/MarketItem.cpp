#include "MarketItem.h"
#include <iostream>

MarketItem::MarketItem(ProductType type, unsigned int quantity, unsigned int price):product(type), quantity(quantity), price(price), id(static_cast<unsigned int>(type))
{
}

void MarketItem::display() const
{
	std::println("Product: {}, quantity: {}, price: {}", Utils::productTypeToString(product), quantity, price);
}

ProductType MarketItem::getProduct() const
{
	return product;
}

unsigned int MarketItem::getPrice() const
{
	return price;
}

unsigned int MarketItem::getQuantity() const
{
	return quantity;
}

unsigned int MarketItem::getId() const
{
	return id;
}


void MarketItem::setQuantity(unsigned int quantity)
{
	this->quantity = quantity;
}

void MarketItem::setPrice(unsigned int price)
{
	this->price = price;
}

void MarketItem::setProduct(const std::string& product)
{
	this->product = Utils::stringToProductType(product);
}

std::ostream& operator<<(std::ostream& os, const MarketItem& item)
{
	os << Utils::productTypeToString(item.product) << " "
		<< item.quantity << " "
		<< item.price;

	return os;
}

std::istream& operator>>(std::istream& is, MarketItem& item)
{
	std::string product;
	unsigned int quantity, price;

	if (!(is >> product >> quantity >> price))
		return is;

	item = MarketItem(Utils::stringToProductType(product), quantity, price);

	return is;
}
