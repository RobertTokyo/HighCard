// HighCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include "Deck.h"

class HighCard
{
public:
	HighCard()
		:mpDeck{ nullptr }// = default;
	{};

	~HighCard() = default;

	bool Play();

	void SetDeck(Deck* deck) { mpDeck = deck; }

protected:
	Deck* mpDeck;
};

// This was the original game
inline bool HighCard::Play()
{
	/* Select cards
	int i = rand() % 52 + 1;
	int j = rand() % 52 + 1; */
	if(mpDeck==nullptr)
		mpDeck = new UnlimitedDeckNoSuit;
	auto p1 = ((UnlimitedDeckNoSuit*)mpDeck)->SelectCardSafe();
	auto p2 = ((UnlimitedDeckNoSuit*)mpDeck)->SelectCardSafe();
	/* Compare cards
	return (i < j);
	*/
	int comp = p1->compare(*p2);
	return comp > 0;
}

int main(int argc, char **argv)
{
	HighCard card;

	if (card.Play())
	{
		std::cout << "win\n";
	}
	else
	{
		std::cout << "lose\n";
	}

	return 0;
}