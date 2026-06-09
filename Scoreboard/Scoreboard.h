#pragma once
#include "Player.h"
#include <vector>
#include <memory>

class Scoreboard
{
private:

public:
	Scoreboard() = delete;
	static void show(const std::vector<std::unique_ptr<User>>& users);
};

