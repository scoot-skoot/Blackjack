#pragma once

#include "deck.h"
#include "hand.h"

#include <optional>

enum class Phase
{
	Deal,
	PlayerTurn,
	DealerTurn,
	Finished
};

struct GameState
{
	Deck deck{};
	Hand playerHand{};
	Hand dealerHand{};
	Phase phase{ Phase::Deal };
	std::optional<bool> playerWon{};
};

class GameEngine
{
public:
	void newRound();
	void hit();
	void stand();

	const GameState& state() const { return state_; }

private:
	GameState state_{};

	void dealInitial();
	void playDealer();
	void finishRound(bool playerWon);
};
