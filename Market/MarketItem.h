#pragma once
#include "Utils.h"
#include <print>

class MarketItem
{
private:

	unsigned int id;
	ProductType product;
	unsigned int quantity;
	unsigned int price;
	
public:
	MarketItem() = default;
	MarketItem(ProductType type, unsigned int quantity, unsigned int price);

	void display()const;

	ProductType getProduct()const;
	unsigned int getPrice()const;
	unsigned int getQuantity()const;
	unsigned int getId()const;

	void setQuantity(unsigned int quantity);
	void setPrice(unsigned int price);
	void setProduct(const std::string& product);

	friend std::ostream& operator<<(std::ostream& os, const MarketItem& item);
	friend std::istream& operator>>(std::istream& is, MarketItem& item);
};

