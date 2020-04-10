#pragma once

enum class HighCardRes { Win, Lose, Draw, Voided };

class Card
{
public:
	Card(size_t value)
		:CardValue{ value } {};
	virtual ~Card() {};

	virtual HighCardRes compare(const Card& other) const
	{
		HighCardRes res = HighCardRes::Voided;
		size_t OtherValue = other.GetCardValue();
		if (OtherValue == CardValue)
			res = HighCardRes::Draw;
		else if (OtherValue > CardValue)
			res = HighCardRes::Lose;
		else
			res = HighCardRes::Win;

		return res;
	}
	size_t GetCardValue() const { return CardValue; }
protected:
	const size_t CardValue;
};

enum class Suit { Spades, Clubs, Diamonds, Hearts };
class SuitedCard : public Card
{
public:
	SuitedCard(Suit suit, size_t value)
		:Card{ value }
	{};

	virtual ~SuitedCard();

	Suit GetCardSuit() { return CardSuit; }

	virtual HighCardRes compare(const Card& other) const
	{
		HighCardRes res = Card::compare(other);
		if (res == HighCardRes::Draw)
		{

		}
		return res;
	}
protected:
	Suit CardSuit;
};