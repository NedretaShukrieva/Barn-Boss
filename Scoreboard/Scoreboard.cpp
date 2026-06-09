#include "Scoreboard.h"
#include <algorithm>

void Scoreboard::show(const std::vector<std::unique_ptr<User>>& users)
{
	std::vector<Player*> players;

	for (const auto& user:users)
	{
		Player* player= dynamic_cast<Player*>(user.get());

		if (player) {
			players.push_back(player);
		}
	}

	std::sort(players.begin(), players.end(), [](Player* a, Player* b) {

		if (a->checkScore() != b->checkScore()) {
			return a->checkScore() > b->checkScore();
		}

		if (a->checkBalance() != b->checkBalance()) {
			return a->checkBalance() > b->checkBalance();
		}
			
		return a->getId() < b->getId();
		
		});

	std::println("=== SCOREBOARD ===");

	for (int i = 0; i < players.size(); i++) {
		std::println("{}. {} | Score: {} | Balance: {}",
			i + 1,
			players[i]->getUsername(),
			players[i]->checkScore(),
			players[i]->checkBalance());
	}

}
