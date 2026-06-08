#pragma once
#include "Utils.h"

static constexpr unsigned int COUNT = 9;

class Barn
{
private:

	unsigned int inventory[COUNT] = {};

public:

	void addProduct(ProductType type, unsigned int quantity);
	bool removeProduct(ProductType type, unsigned int quantity);

	unsigned int getQuantity(ProductType type) const;

	void display()const;

	friend std::ostream& operator<<(std::ostream& os, const Barn& barn);
	friend std::istream& operator>>(std::istream& is, Barn& barn);
};

