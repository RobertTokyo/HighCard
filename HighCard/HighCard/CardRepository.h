#pragma once
#include <set>

class Card;

template <class T>
class CardRepository
{
public:
	inline size_t Count() const { return repo.size(); }
	
	bool HasBeenUsed(Card* card);
	void Add(T card);
	void Reset(bool deleter = false);

protected:
	std::set<T>	repo;
};

