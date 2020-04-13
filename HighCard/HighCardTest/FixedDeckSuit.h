#pragma once
#include "Deck.h"

class FixedDeckSuit : public DeckSuit
{
public:
	FixedDeckSuit(size_t count, bool suits = true)
		: CardCount{ count },
		NextCard{ 1 },
		NextSuit{ 0 }
	{};

	virtual ~FixedDeckSuit();

	virtual Card* selectRaw();

protected:
	size_t CardCount;
	size_t NextCard;
	size_t NextSuit;
};