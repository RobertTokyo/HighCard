#include "pch.h"
#include "FixedDeckSuit.h"

FixedDeckSuit::~FixedDeckSuit()
{
	if (wildcard != nullptr)
		delete wildcard;
};

Card* FixedDeckSuit::select()
{
	if (NextCard > CardCount)
	{
		NextCard = 1;
		NextSuit++;
		if (NextSuit > 3)
			NextSuit = 0;
	}
	return new SuitedCard{ (Suit)NextSuit, NextCard++};
}

std::unique_ptr<SuitedCard> FixedDeckSuit::SelectCardSafe()
{
	SuitedCard* pCard = (SuitedCard*)select();
	std::unique_ptr<SuitedCard> p(pCard);

	return p;
}