#pragma once
#include <string>
#include "Utils.h"

class FarmObject
{
private:
	ProductType inputType;   
	ProductType outputType;
	unsigned int currentCycle = 0;
	unsigned int requiredCycle;

public:
	FarmObject(ProductType inputType, ProductType outputType, unsigned int requiredCycle);

	ProductType getInputType() const;
	ProductType getOutputType() const;

	virtual ~FarmObject() = default;

	void display()const;
	void grow();
	bool isReady()const;

	unsigned int getCurrentCycle()const;
	unsigned int getRequiredCycle()const;
	void setCurrentCycle(unsigned int cycle);
};

