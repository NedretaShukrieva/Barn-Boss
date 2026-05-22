#pragma once
#include "FarmObject.h"

class Animal:public FarmObject
{
public:
	Animal() = default;
	Animal(ProductType inputType, ProductType outputType, unsigned int requiredCycle);
};

