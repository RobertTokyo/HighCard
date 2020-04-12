#pragma once
#include <vector>

class Deck;

enum class HighCardRes { Win, Lose, Draw, Voided };

class HighCard
{
public:
	HighCard() = default;
	~HighCard() = default;

	void Reset();
	bool Play();

	/*
	1. Support ties when the face value of the cards are the same.
	2. Allow for the ties to be resolved as a win by giving the different suits precedence.
	3. Support for Multiple Decks.
	4. Support the ability to never end in a tie, by dealing a further card to each player.
	5. Make one of the cards in the deck a wild card(beats all others).
	6. Now make the game work for a deck with 20 cards per suit */
	HighCardRes PlayCanTie();
	HighCardRes PlaySuitPrecedence();
	HighCardRes PlayMultiDecks();
	HighCardRes PlayCanNeverTie();
	HighCardRes PlayWithWildcard();
	HighCardRes PlayVarDecks();

	void SetDeck(Deck* deck) { mpDecks.clear();  mpDecks.push_back(deck); }
	void AddDeck(Deck* deck) { mpDecks.push_back(deck); }

protected:
	Deck*	getFirstDeck();
	std::vector<Deck*> mpDecks;
};

// End of file
