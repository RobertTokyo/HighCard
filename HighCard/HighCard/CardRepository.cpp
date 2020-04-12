#include "pch.h"
#include "CardRepository.h"
#include "Card.h"

bool CardRepository::HasBeenUsed(Card* card)
{
	bool bFound{ false };
	auto iter = repo.find(card);
	if (iter != repo.end())
		bFound = true;

	return bFound;
}

void CardRepository::Add(Card* card)
{
	repo.insert(card);
}

void CardRepository::Reset(bool deleter)
{
	if (deleter == true)
	{
		for (Card* c : repo)
			delete c;
	}
	repo.clear();
}