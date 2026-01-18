#include <iostream>
#include <algorithm>
#include "Random.h"
#include "card.h"
#include "deck.h"

int main()
{
	Deck deck{};
	std::cout << deck.dealCard() << " " << deck.dealCard() << '\n';

	deck.shuffle();
	std::cout << deck.dealCard() << " " << deck.dealCard() << '\n';

	return 0;
}