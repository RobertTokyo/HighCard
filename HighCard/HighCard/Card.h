#pragma once

#include "CardUtils.h"

class Card
{
public:
	Card(size_t value)
		:CardValue{ value } {};
	Card(const Card& other)
		: CardValue{ other.GetCardValue()}
	{};

	Card operator=(const Card& other)
	{	
		CardValue = other.GetCardValue();
		return *this;
	};

	virtual ~Card() = default;

	virtual int compare(const Card& other) const
	{
		size_t OtherValue = other.GetCardValue();

		return (int)CardValue - (int)OtherValue;
	}
	size_t GetCardValue() const { return CardValue; }
protected:
	size_t CardValue;
};


class SuitedCard : public Card
{
public:
	SuitedCard(Suit suit, size_t value)
		: CardSuit{ suit },
		Card{ value }
	{};

	SuitedCard(const SuitedCard& other)
	:Card{ other.GetCardValue()},
		CardSuit{ other.GetCardSuit()}
	{};

	SuitedCard operator=(const SuitedCard& other)
	{
		CardValue = other.GetCardValue();
		CardSuit = other.GetCardSuit();
		return *this;
	};
	virtual ~SuitedCard() = default;

	Suit GetCardSuit() const { return CardSuit; }

	virtual int compare(const SuitedCard& other) const
	{
		int res = Card::compare(other);
		if (res == 0)
		{
			size_t MyRank = GetSuitRank(CardSuit);
			size_t OtherRank = GetSuitRank(other.GetCardSuit());
			res = (int)MyRank - (int)OtherRank;
		}
		return res;
	}
protected:
	Suit CardSuit;
};