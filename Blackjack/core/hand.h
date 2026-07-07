#pragma once

#include "card.h"
#include "settings.h"

#include <vector>

struct Hand
{
	void addCard(Card card);
	void clear();
	int score() const;
	bool isBust() const;

	std::vector<Card> cards;
};
