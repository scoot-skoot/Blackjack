#include <iostream>
#include <algorithm>
#include "Random.h"
#include "card.h"
#include "deck.h"
#include "player.h"
#include "settings.h"

int main()
{
	Player player{};

	(player.contest()) ? (std::cout << "You Win!") : (std::cout << "You Lose!");

	return 0;
}