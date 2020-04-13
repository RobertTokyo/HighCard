#pragma once
#include "Card.h"
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <mutex>
#include "CardRepository.h"

// Abstract Deck that might have a "wildcard"
class Deck
{
public:
	Deck()
		: wildcard{ nullptr }
	{};
	virtual ~Deck() {
		if (wildcard != nullptr)
			delete wildcard;
	};

	virtual Card* selectRaw() = 0;

	virtual std::shared_ptr<Card> Select()
	{
		Card* pCard = selectRaw();
		std::shared_ptr<Card> p(pCard);

		return p;
	}
	
	virtual bool isWildCard(Card* card)
	{
		bool wild{ false };
		if (wildcard!=nullptr)
		{
			wild = card->compare(*wildcard) == 0;
		}
		return wild;
	};

	virtual void setWildCard(Card* wild)
	{
		wildcard = wild;
	};

	virtual Card* getWildCard()
	{
		return wildcard;
	};

protected:
	Card* wildcard;
};

// Simple Deck without suits or memory
class UnlimitedDeckNoSuit : public Deck
{
public:
	UnlimitedDeckNoSuit() {};
	virtual ~UnlimitedDeckNoSuit() {};

	virtual Card* selectRaw()
	{
		size_t cardvalue = rand() % 52 + 1;
		return new Card{ cardvalue };
	}
};

// Simple Deck without suits but with memory
class LimitedDeckNoSuit : public UnlimitedDeckNoSuit
{
public:
	LimitedDeckNoSuit(size_t limit)
	: deck_size{limit}
	{};
	virtual ~LimitedDeckNoSuit() {};

	virtual std::shared_ptr<Card> Select()
	{
		Card* pCard = selectRaw();
		std::shared_ptr<Card> p(pCard);
		if (UsedCards.Count() < deck_size)
		{
			Card* card = UnlimitedDeckNoSuit::selectRaw();
			while (UsedCards.HasBeenUsed(card))
			{
				delete card;
				Card* card = UnlimitedDeckNoSuit::selectRaw();
			}
			// Adds a raw ptr but doesn't own the card; the game owns the card
			UsedCards.Add(p);
		}
		return p;
	}

	void reset(bool deleter = false)
	{
		UsedCards.Reset(deleter);
	}

protected:
	size_t						deck_size;
	CardRepository<std::shared_ptr<Card>>  UsedCards;
};


// Like a simple Deck but has suits but not memory
class DeckSuit : public Deck
{
public:
	DeckSuit() {};
	virtual ~DeckSuit() {};

	virtual Card* selectRaw()
	{
		size_t cardvalue = rand() % 13 + 1;
		size_t cardsuit = rand() % 4;
		Suit suit = (Suit)cardsuit;
		return new SuitedCard{ suit, cardvalue };
	}
};

class LimitedDeckSuit : public DeckSuit
{
public:
	LimitedDeckSuit(size_t deck_size_limit)
		:deck_size{ deck_size_limit }
	{};
	virtual ~LimitedDeckSuit() {};

	virtual std::shared_ptr<Card> Select()
	{
		Card* pCard = selectRaw();
		std::shared_ptr<Card> p;
		if (UsedCards.Count() < deck_size)
		{
			while (UsedCards.HasBeenUsed(pCard))
			{
				delete pCard;
				pCard = selectRaw();
			}
			/*std::cout << "Raw card " << pCard->GetCardValue() << ", suit=" <<
				(int)((SuitedCard*)pCard)->GetCardSuit() << std::endl;*/
			p = std::shared_ptr<Card>(pCard);
			UsedCards.Add(p);
		}
		return p;
	}

	void reset(bool deleter = false)
	{
		UsedCards.Reset(deleter);
	}

protected:
	CardRepository<std::shared_ptr<Card>>		UsedCards;
	size_t				deck_size;
};