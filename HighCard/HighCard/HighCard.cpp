// HighCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include "Deck.h"
#include "HighCard.h"

void HighCard::Reset()
{
	for (Deck* pDeck : mpDecks)
	{
		delete pDeck;
	}
	mpDecks.clear();
}

Deck* HighCard::getFirstDeck()
{
	Deck* pDeck{ nullptr };
	if (mpDecks.size() == 0) {
		Deck* pDeck = new UnlimitedDeckNoSuit;
		mpDecks.push_back(pDeck);
	}
	else
		pDeck = mpDecks[0];

	return pDeck;
}

// This was the original game
bool HighCard::Play()
{
	/* Select cards
	int i = rand() % 52 + 1;
	int j = rand() % 52 + 1; */
	Deck* pDeck = getFirstDeck();

	auto p1 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	auto p2 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	/* Compare cards
	return (i < j);
	*/
	int comp = p1->compare(*p2);
	return comp > 0;
}

// Task 1. Support ties when the face value of the cards are the same.
HighCardRes HighCard::PlayCanTie()
{
	Deck* pDeck = getFirstDeck();

	auto p1 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	auto p2 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	int comp = p1->compare(*p2);
	HighCardRes res{ HighCardRes::Lose };
	if (comp == 0)
		res = HighCardRes::Draw;
	else if (comp > 0)
		res = HighCardRes::Win;
	return res;
}

// Task 2. Allow for the ties to be resolved as a win by giving the different
// suits precedence.
HighCardRes HighCard::PlaySuitPrecedence()
{
	Deck* pDeck = getFirstDeck();
	auto p1 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	auto p2 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	int comp = p1->compare(*p2);

	HighCardRes res{ HighCardRes::Lose };
	if (comp == 0)
	{
		res = HighCardRes::Draw;
	}
	else if (comp > 0)
		res = HighCardRes::Win;
	return res;
}

HighCardRes HighCard::PlayMultiDecks()
{
	HighCardRes res{ HighCardRes::Lose };
	return res;
}

HighCardRes HighCard::PlayCanNeverTie()
{
	Deck* pDeck = getFirstDeck();
	auto p1 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	auto p2 = ((UnlimitedDeckNoSuit*)pDeck)->SelectCardSafe();
	int comp = p1->compare(*p2);

	HighCardRes res{ HighCardRes::Lose };
	return res;
}

HighCardRes HighCard::PlayWithWildcard()
{
	HighCardRes res{ HighCardRes::Lose };
	return res;
}

HighCardRes HighCard::PlayVarDecks()
{
	HighCardRes res{ HighCardRes::Lose };
	return res;
}

// End of file
