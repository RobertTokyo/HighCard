#pragma once
#include "Card.h"
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

	virtual Card* select() = 0;
	
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

	virtual Card* select()
	{
		size_t cardvalue = rand() % 52 + 1;
		return new Card{ cardvalue };
	}

	virtual std::unique_ptr<Card> SelectCardSafe()
	{
		Card* pCard = select();
		std::unique_ptr<Card> p(pCard);

		return p;
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

	// This can return a nullptr if we've used the cards
	virtual Card* select()
	{
		Card* card = nullptr;
		if (UsedCards.Count() < deck_size)
		{
			Card* card = UnlimitedDeckNoSuit::select();
			while (UsedCards.HasBeenUsed(card))
			{
				delete card;
				card = UnlimitedDeckNoSuit::select();
			}
			// Adds a raw ptr but doesn't own the card; the game owns the card
			UsedCards.Add(card);
		}
		return card;
	}

	virtual std::shared_ptr<Card> SelectCardShared()
	{
		Card* pCard = select();
		std::shared_ptr<Card> p(pCard);

		return p;
	}

	void reset(bool deleter = false)
	{
		UsedCards.Reset(deleter);
	}

protected:
	size_t			deck_size;
	CardRepository  UsedCards;
};


// Like a simple Deck but has suits but not memory
class DeckSuit : public Deck
{
public:
	DeckSuit() {};
	virtual ~DeckSuit() {};

	virtual Card* select()
	{
		size_t cardvalue = rand() % 13 + 1;
		size_t cardsuit = rand() % 4;
		Suit suit = (Suit)cardsuit;
		return new SuitedCard{ suit, cardvalue };
	}

	virtual std::unique_ptr<SuitedCard> SelectCardSafe()
	{
		SuitedCard* pCard = (SuitedCard*)select();
		std::unique_ptr<SuitedCard> p(pCard);

		return p;
	}
};

class LimitedDeckSuit : public DeckSuit
{
public:
	LimitedDeckSuit(size_t deck_size_limit)
		:deck_size{ deck_size_limit }
	{};
	virtual ~LimitedDeckSuit() {};

	void reset(bool deleter = false)
	{
		UsedCards.Reset(deleter);
	}

	virtual Card* select()
	{
		Card* card = nullptr;
		if (UsedCards.Count() < deck_size)
		{
			card = DeckSuit::select();
			while(UsedCards.HasBeenUsed(card))
			{
				delete card;
				card = DeckSuit::select();
			}
			UsedCards.Add(card);
		}
		return card;
	}

	virtual std::shared_ptr<SuitedCard> SelectCardShared()
	{
		SuitedCard* pCard = (SuitedCard*)select();
		std::shared_ptr<SuitedCard> p(pCard);

		return p;
	}

protected:
	CardRepository		UsedCards;
	size_t				deck_size;
};