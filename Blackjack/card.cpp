#include "card.h"
#include <array>
#include <cassert>

enum Card::Rank
{
	rank_ace,
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,

	max_rank,
};

enum Card::Suit
{
	suit_clubs,
	suit_diamonds,
	suit_hearts,
	suit_spades,
	max_suit,
};

