#pragma once
#include "Animal.h"

class Cow:public Animal
{
private:
	
	static constexpr unsigned int REQUIRED = 5;

public:
	Cow();
};

