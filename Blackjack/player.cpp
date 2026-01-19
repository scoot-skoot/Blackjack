#include "player.h"

bool Player::contest()
{

	Deck deck;
	deck.shuffle();


	//Dealer gets one card
	Player dealer{ Card::value[deck.dealCard().rank_] };

	//Player gets two cards
	score_ += Card::value[deck.dealCard().rank_];
	score_ += Card::value[deck.dealCard().rank_];

	std::cout << "The dealer is showing: " << dealer.score_ << '\n';
	std::cout << "You have score: " << score_ << '\n';
	bool stand{ false };
	do {
		std::cout << "(h) to hit, or (s) to stand: ";
		char choice{};
		std::cin >> choice;
		if (choice == 's')
		{
			stand = true;
			continue;
		}

		Card hit = deck.dealCard();
		score_ += Card::value[hit.rank_];
		std::cout << "You were dealt " << hit << ". ";
		std::cout << "You now have: " << score_ << ".\n";

		if (score_ > Settings::bustValue)
		{
			std::cout << "You went bust!\n";
			return false;
		}

	} while (!stand);

	while (dealer.score_ < Settings::dealerStop)
	{
		Card hit = deck.dealCard();
		dealer.score_ += Card::value[hit.rank_];
		std::cout << "The dealer flips a " << hit << ". ";
		std::cout << "They now have: " << dealer.score_ << ".\n";
		if (dealer.score_ > Settings::bustValue) return true;
	}
	return (score_ > dealer.score_);
}