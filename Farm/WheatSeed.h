#pragma once
#include "Plantable.h"

class WheatSeed:public Plantable
{
private:

	static constexpr unsigned int REQUIRED = 3;

public:
	WheatSeed();
};

