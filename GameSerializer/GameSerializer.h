#pragma once
#include <string>

class System;

class GameSerializer
{
public:
	static void save(const System& system, const std::string& filename);
	static void load(System& system, const std::string& filename);
};

