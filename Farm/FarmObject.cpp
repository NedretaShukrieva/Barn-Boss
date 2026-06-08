#include "FarmObject.h"
#include <print>

FarmObject::FarmObject(ProductType inputType, ProductType outputType, unsigned int requiredCycle)
	:inputType(inputType), outputType(outputType), requiredCycle(requiredCycle)
{
}

ProductType FarmObject::getInputType() const
{
	return inputType;
}

ProductType FarmObject::getOutputType() const
{
	return outputType;
}

void FarmObject::display() const
{
	std::println("{} - Cycle: {}/{}",
		Utils::productTypeToString(inputType),
		currentCycle,
		requiredCycle);
}

void FarmObject::grow()
{
	currentCycle++;
}

bool FarmObject::isReady() const
{
	return currentCycle>=requiredCycle;
}

unsigned int FarmObject::getCurrentCycle() const
{
	return currentCycle;
}

unsigned int FarmObject::getRequiredCycle() const
{
	return requiredCycle;
}

void FarmObject::setCurrentCycle(unsigned int cycle)
{
	currentCycle = cycle;
}
