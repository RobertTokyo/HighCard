#include "pch.h"
#include <map>
#include "CardUtils.h"

static std::map<Suit, size_t> sSuitRank;

size_t GetSuitRank(Suit suit)
{
	size_t rank{ 0 };
	if (sSuitRank.size() == 0)
		rank = DefaultSuitRank(suit);
	else
	{
		auto iter = sSuitRank.find(suit);
		if (iter == sSuitRank.end())
			rank = DefaultSuitRank(suit);
		else
			rank = iter->second;
	}
	return rank;
}

// https://en.wikipedia.org/wiki/High_card_by_suit says order alphabetically
size_t DefaultSuitRank(Suit suit)
{
	size_t rank{ 0 };
	switch (suit)
	{
	case Suit::Clubs:
		rank = 0;
		break;
	case Suit::Diamonds:
		rank = 1;
		break;
	case Suit::Hearts:
		rank = 2;
		break;
	case Suit::Spades:
		rank = 3;
		break;
	}
	return rank;
}

void RankSuit(Suit suit, size_t rank)
{
	sSuitRank[suit] = rank;
}
