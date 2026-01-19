#pragma once
#include "card.h"
#include "deck.h"
#include "settings.h"

struct Player
{
public:
	Player(int score = 0)
		:score_{ score }
	{
	}

	bool contest();
	
private:
	int score_{};
};
