#pragma once
#include "Deck.h"
#include <vector>
#include <array>

class Card;

class LimitedCardDeck : public LimitedDeckSuit
{
public:
	LimitedCardDeck(size_t deck_size_limit);
	virtual ~LimitedCardDeck() =default;

	virtual Card* selectRaw();
	virtual std::shared_ptr<Card> Select();

protected:
	std::array<std::vector<Card*>, 4> AvailableCards;
};

