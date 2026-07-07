#include "game_engine.h"
#include "settings.h"

void GameEngine::newRound()
{
	state_ = GameState{};
	state_.deck.shuffle();
	dealInitial();
	state_.phase = Phase::PlayerTurn;
}

void GameEngine::hit()
{
	if (state_.phase != Phase::PlayerTurn)
	{
		return;
	}

	state_.playerHand.addCard(state_.deck.dealCard());

	if (state_.playerHand.isBust())
	{
		finishRound(false);
	}
}

void GameEngine::stand()
{
	if (state_.phase != Phase::PlayerTurn)
	{
		return;
	}

	state_.phase = Phase::DealerTurn;
	playDealer();
}

void GameEngine::dealInitial()
{
	state_.dealerHand.addCard(state_.deck.dealCard());
	state_.playerHand.addCard(state_.deck.dealCard());
	state_.playerHand.addCard(state_.deck.dealCard());
}

void GameEngine::playDealer()
{
	while (state_.dealerHand.score() < Settings::dealerStop)
	{
		state_.dealerHand.addCard(state_.deck.dealCard());
	}

	if (state_.dealerHand.isBust())
	{
		finishRound(true);
		return;
	}

	finishRound(state_.playerHand.score() > state_.dealerHand.score());
}

void GameEngine::finishRound(bool playerWon)
{
	state_.phase = Phase::Finished;
	state_.playerWon = playerWon;
}
