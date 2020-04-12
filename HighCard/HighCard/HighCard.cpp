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

LimitedDeckSuit* HighCard::getFirstDeck()
{
	LimitedDeckSuit* pDeck{ nullptr };
	if (mpDecks.size() == 0) {
		LimitedDeckSuit* pDeck = new LimitedDeckSuit{ 52 };
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
	LimitedDeckSuit* pDeck = ((LimitedDeckSuit*)getFirstDeck());

	auto p1 = pDeck->SelectCardSafe();
	auto p2 = pDeck->SelectCardSafe();
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
	LimitedDeckSuit* pDeck = ((LimitedDeckSuit*)getFirstDeck());
	auto p1 = pDeck->SelectCardSafe();
	auto p2 = pDeck->SelectCardSafe();
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
	HighCardRes res{ HighCardRes::Voided };

	size_t nDecks = mpDecks.size();
	if (nDecks > 0)
	{
		int DeckIndex = rand() % nDecks;
		auto card1 = mpDecks[DeckIndex]->SelectCardSafe();
		DeckIndex = rand() % nDecks;
		auto card2 = mpDecks[DeckIndex]->SelectCardSafe();

		int comp = card1->compare(*card2);

		HighCardRes res{ HighCardRes::Lose };
		if (comp == 0)
		{
			res = HighCardRes::Draw;
		}
		else if (comp > 0)
			res = HighCardRes::Win;
	}
	return res;
}

/* 4. Support the ability to never end in a tie, by dealing a further card to each player.
*/
HighCardRes HighCard::PlayCanNeverTie()
{
	LimitedDeckSuit* pDeck = ((LimitedDeckSuit*)getFirstDeck());
	int comp{ 0 };
	do {
		auto p1 = pDeck->SelectCardSafe();
		auto p2 = pDeck->SelectCardSafe();
		if(p1.get()!=nullptr && p2.get()!=nullptr)
			comp = p1->compare(*p2);
		else
		{
			pDeck->reset();
		}
	} while (comp == 0);

	HighCardRes res{ HighCardRes::Lose };
	if (comp > 0)
		res = HighCardRes::Win;
	return res;
}

/* 5. Make one of the cards in the deck a wild card ( beats all others ).
*/
HighCardRes HighCard::PlayWithWildcard()
{
	HighCardRes res{ HighCardRes::Lose };
	LimitedDeckSuit* pDeck = ((LimitedDeckSuit*)getFirstDeck());
	Card* pWildcard = pDeck->getWildCard();
	// If this deck has a wildcard, lose
	if(pWildcard==nullptr)
		// otherwise play normally
		res = PlaySuitPrecedence();
	return res;
}

// Created a deck with 20 cards on initialisation, so same as base game
HighCardRes HighCard::PlayVarDecks()
{
	HighCardRes res = PlaySuitPrecedence();
	return res;
}

// End of file
