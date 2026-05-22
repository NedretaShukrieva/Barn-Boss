#pragma once
#include "FarmObject.h"

class Plantable:public FarmObject
{
public:
	Plantable() = default;
	Plantable(ProductType inputType, ProductType outputType, unsigned int requiredCycle);
};

