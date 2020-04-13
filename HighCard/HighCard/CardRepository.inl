#include "pch.h"
#include "CardRepository.h"

#include "Card.h"

template<class T>
bool CardRepository<T>::HasBeenUsed(Card* card)
{
	bool bFound{ false };
	for (auto c : repo)
	{
		Card* pCard = c.get();
		int comp = card->compare(*pCard);
		if(comp== 0)
		{
			bFound = true;
			break;
		}
	}
	return bFound;
}

template<class T>
void CardRepository<T>::Add(T card)
{
	repo.insert(card);
}

template<class T>
void CardRepository<T>::Reset(bool deleter)
{
	/*if (deleter == true)
	{
		for (auto c : repo)
			delete c;
	}*/
	repo.clear();
}