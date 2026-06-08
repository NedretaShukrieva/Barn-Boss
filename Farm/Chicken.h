#pragma once
#include "Animal.h"

class Chicken:public Animal
{
private:

	static constexpr unsigned int REQUIRED = 3;

public:
	Chicken();
};

