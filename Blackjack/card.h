#include <iostream>
#include <array>
#include <cassert>

struct Card
{
	enum Rank
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

	enum Suit
	{
		suit_clubs,
		suit_diamonds,
		suit_hearts,
		suit_spades,
		max_suit,
	};

	static constexpr std::array <Rank, max_rank> allRank{ rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
	static constexpr std::array <Suit, max_suit> allSuit{ suit_clubs, suit_diamonds, suit_hearts, suit_spades };
	static constexpr std::array <char, max_rank> rankValue{ 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
	static constexpr std::array <char, max_suit> suitValue{ 'C', 'D', 'H', 'S' };

	static constexpr std::array<int, max_rank> value{ 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

	static_assert(std::size(allRank) == max_rank);

	static_assert(std::size(rankValue) == max_rank);
	static_assert(std::size(suitValue) == max_suit);
	static_assert(std::size(value) == max_rank);


	Rank rank_{};
	Suit suit_{};

	friend std::ostream& operator<<(std::ostream& out, Card card)
	{
		out << card.rankValue[card.rank_];
		out << card.suitValue[card.suit_];
		return out;
	}
};

