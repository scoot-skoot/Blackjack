#include "ConsoleView.h"

#include "../core/card.h"
#include "../core/game_engine.h"

#include <iostream>
#include <limits>

namespace
{
	void printHand(const Hand& hand, const char* label, bool hideFirstCard)
	{
		std::cout << label << ": ";
		for (std::size_t i = 0; i < hand.cards.size(); ++i)
		{
			if (i > 0)
			{
				std::cout << ' ';
			}

			if (hideFirstCard && i == 0)
			{
				std::cout << "??";
			}
			else
			{
				std::cout << hand.cards[i];
			}
		}

		if (hideFirstCard)
		{
			std::cout << " (showing " << hand.cards.front() << ')';
		}
		else
		{
			std::cout << " (score: " << hand.score() << ')';
		}

		std::cout << '\n';
	}

	char readChoice()
	{
		while (true)
		{
			std::cout << "(h) to hit, or (s) to stand: ";
			char choice{};
			std::cin >> choice;

			if (choice == 'h' || choice == 's')
			{
				return choice;
			}

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter 'h' or 's'.\n";
		}
	}
}

int ConsoleView::run(GameEngine& engine)
{
	engine.newRound();

	while (engine.state().phase == Phase::PlayerTurn)
	{
		const GameState& state = engine.state();
		printHand(state.dealerHand, "Dealer", true);
		printHand(state.playerHand, "You", false);

		if (readChoice() == 's')
		{
			engine.stand();
		}
		else
		{
			engine.hit();
			const Card& hit = engine.state().playerHand.cards.back();
			std::cout << "You were dealt " << hit << ". ";

			if (engine.state().phase == Phase::Finished)
			{
				std::cout << "You went bust!\n";
			}
			else
			{
				std::cout << "You now have: " << engine.state().playerHand.score() << ".\n";
			}
		}
	}

	const GameState& finalState = engine.state();

	if (finalState.phase == Phase::Finished)
	{
		printHand(finalState.dealerHand, "Dealer", false);
		printHand(finalState.playerHand, "You", false);

		if (finalState.dealerHand.isBust())
		{
			std::cout << "Dealer went bust!\n";
		}

		if (*finalState.playerWon)
		{
			std::cout << "You Win!\n";
			return 0;
		}

		std::cout << "You Lose!\n";
		return 1;
	}

	return 1;
}
