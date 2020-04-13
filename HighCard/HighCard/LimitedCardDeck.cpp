#include "pch.h"
#include "LimitedCardDeck.h"
#include "Card.h"

LimitedCardDeck::LimitedCardDeck(size_t deck_size_limit)
:LimitedDeckSuit{ deck_size_limit }
{
	for (size_t suit = 0; suit < 4; suit++)
	{
		for (size_t card = 1; card <= deck_size; card++)
		{
			AvailableCards[suit].push_back(new SuitedCard{ (Suit)suit, card });
		}
	}
}

std::shared_ptr<Card> LimitedCardDeck::Select()
{
	Card* pCard = selectRaw();
	std::shared_ptr<Card> p(pCard);

	return p;
}

Card* LimitedCardDeck::selectRaw()
{
	Card* pCard = nullptr;
	std::array<size_t, 4> suit_sizes{ AvailableCards[0].size(), AvailableCards[1].size(),
		AvailableCards[2].size(), AvailableCards[3].size() };
	size_t totalCards = suit_sizes[0] + suit_sizes[1] + suit_sizes[2] + suit_sizes[3];

	if (totalCards > 0)
	{
		size_t index = rand() % totalCards;

		size_t Suit = 0;
		while (Suit < 4)
		{
			size_t CurrentSuitSize{ suit_sizes[Suit] };
			if (CurrentSuitSize >0 && index < CurrentSuitSize)
			{
				pCard = AvailableCards[Suit][index];
				auto iter = AvailableCards[Suit].begin();
				for (size_t i = 0; i < index; i++)
					iter++;
				AvailableCards[Suit].erase(iter);
				break;
			}
			else
			{
				Suit++;
				index -= CurrentSuitSize;
			}
		}
	}

	return pCard;
}


