// HighCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include "Deck.h"
#include "HighCard.h"
#include "CardRepository.inl"
#include "LimitedCardDeck.h"

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

std::shared_ptr<Card> HighCard::getCardAlways(LimitedDeckSuit* pDeck)
{
	auto res = pDeck->Select();
	if (res.get() == nullptr)
	{
		pDeck->reset();
		res = pDeck->Select();
	}
	return res;
}

// This was the original game
bool HighCard::Play()
{
	/* Select cards
	int i = rand() % 52 + 1;
	int j = rand() % 52 + 1; */
	LimitedDeckSuit* pDeck = ((LimitedDeckSuit*)getFirstDeck());

	auto p1 = getCardAlways(pDeck);
	auto p2 = getCardAlways(pDeck);

	// This deck saves cards - just reset the deck
	pDeck->reset();
	/* Compare cards
	return (i < j);
	*/
	Card* pCard = p2.get();
	int comp = p1->compare(*pCard);
	return comp > 0;
}

// Task 1. Support ties when the face value of the cards are the same.
HighCardRes HighCard::PlayCanTie()
{
	LimitedDeckSuit* pDeck = getFirstDeck();

	auto p1 = getCardAlways(pDeck);
	auto p2 = getCardAlways(pDeck);
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
	LimitedDeckSuit* pDeck = getFirstDeck();
	auto p1 = getCardAlways(pDeck);
	auto p2 = getCardAlways(pDeck);
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
		auto card1 = mpDecks[DeckIndex]->Select();
		DeckIndex = rand() % nDecks;
		auto card2 = mpDecks[DeckIndex]->Select();

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
	LimitedDeckSuit* pDeck = (LimitedDeckSuit*)getFirstDeck();
	int comp{ 0 };
	do {
		auto p1 = getCardAlways(pDeck);
		auto p2 = getCardAlways(pDeck);
		comp = p1->compare(*p2);
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
	HighCardRes res{ HighCardRes::Lose };
	LimitedCardDeck* pDeck = ((LimitedCardDeck*)getFirstDeck());
	
	do {
		auto p1 = pDeck->Select();
		auto p2 = pDeck->Select();
		HighCardRes res{ HighCardRes::Voided };
		if (p1.get() && p2.get()) { // got 2 cards ?
			int comp = p1->compare(*p2); // Compare them
			if (comp < 0)
				res = HighCardRes::Lose;
			else if (comp == 0)
				res = HighCardRes::Draw;
			else if (comp > 0)
				res = HighCardRes::Win;
			p1.reset();
			p2.reset();
		}
		switch (res)
		{
		case HighCardRes::Draw:
			std::cout << "draw\n";
			break;
		case HighCardRes::Lose:
			std::cout << "lose\n";
			break;
		case HighCardRes::Win:
			std::cout << "win\n";
			break;
		case HighCardRes::Voided:
			std::cout << "Game over\n";
			break;
		}
		if (res != HighCardRes::Voided)
		{
			std::cout << "Play again ? (Y/N)";
			char resp;
			std::cin >> resp;
			if (resp == 'n' || resp == 'N')
				break;
		}
		else
			break;

	} while (1);
	return res;
}

// End of file
