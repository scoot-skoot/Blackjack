#pragma once
#include "card.h"
#include "Random.h"
#include <algorithm>

class Deck
{
public:
	Deck()
	{
		std::size_t count{ 0 };
		for (const auto& suit : Card::allSuit)
		{
			for (const auto& rank : Card::allRank)
			{
				cards_[count++] = Card{ rank, suit };
			}
		}
	}

	Card dealCard()
	{
		assert(nextCardIndex != 51);
		return cards_[nextCardIndex++];
	}

	void shuffle()
	{
		std::shuffle(cards_.begin(), cards_.end(), Random::mt);
	}
private:
	std::array<Card, 52> cards_{};
	std::size_t nextCardIndex{};
};