#pragma once
#include "Plantable.h"

class CornSeed:public Plantable
{
private:
	
	static constexpr unsigned int REQUIRED = 4;

public:
	CornSeed();
};

