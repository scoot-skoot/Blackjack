#include "hand.h"

void Hand::addCard(Card card)
{
	cards.push_back(card);
}

void Hand::clear()
{
	cards.clear();
}

int Hand::score() const
{
	int total{ 0 };
	int aces{ 0 };

	for (const Card& card : cards)
	{
		if (card.rank_ == Card::rank_ace)
		{
			++aces;
			total += 11;
		}
		else
		{
			total += Card::value[card.rank_];
		}
	}

	while (total > Settings::bustValue && aces > 0)
	{
		total -= 10;
		--aces;
	}

	return total;
}

bool Hand::isBust() const
{
	return score() > Settings::bustValue;
}
