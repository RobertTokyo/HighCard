#pragma once
#include <set>

class Card;

class CardRepository
{
public:
	inline size_t Count() const { return repo.size(); }
	
	bool HasBeenUsed(Card* card);
	void Add(Card* card);
	void Reset(bool deleter = false);

protected:
	std::set<Card*>	repo;
};

