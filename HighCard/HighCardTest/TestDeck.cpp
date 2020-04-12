#include "pch.h"
#include "CppUnitTest.h"
#include "Deck.h"
#include "FixedDeckSuit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCard
{
	TEST_CLASS(TestDeck)
	{
	public:

		TEST_METHOD(GetRandomCard)
		{
			UnlimitedDeckNoSuit deck;
			auto card = deck.SelectCardSafe(); // smart ptr
			size_t cardvalue = card->GetCardValue();
			Assert::IsTrue(cardvalue>=0 && cardvalue<=52);
		}

		TEST_METHOD(GetRandomSuitedCard)
		{
			DeckSuit deck;
			auto card = deck.SelectCardSafe();
			size_t cardvalue = card->GetCardValue();
			int cardsuit = (int)card->GetCardSuit();
			Assert::IsTrue(cardvalue >= 0 && cardvalue <= 52);
			Assert::IsTrue(cardsuit >= 0 && cardsuit < 4);
		}

		TEST_METHOD(GetFixedDeck_SuitedCard)
		{
			FixedDeckSuit deck{ 4 };
			auto card = deck.SelectCardSafe();
			size_t cardvalue = card->GetCardValue();
			int cardsuit = (int)card->GetCardSuit();
			Assert::IsTrue(cardvalue >= 0 && cardvalue <= 4);
			Assert::IsTrue(cardsuit >= 0 && cardsuit < 4);
		}

		TEST_METHOD(GetFixedDeck_SuitedCardSafe)
		{
			FixedDeckSuit deck{ 4 };
			auto card = deck.SelectCardSafe();
			size_t cardvalue = card->GetCardValue();
			int cardsuit = (int)card->GetCardSuit();
			Assert::IsTrue(cardvalue >= 0 && cardvalue <= 4);
			Assert::IsTrue(cardsuit >= 0 && cardsuit < 4);
		}

		TEST_METHOD(GetLimitedFixedDeck_SuitedCard)
		{
			LimitedDeckSuit deck{ 2 };

			Card* card = nullptr;
			card = deck.select();
			card = deck.select();
			Assert::IsNotNull(card);
			card = deck.select();
			Assert::IsNull(card);

			deck.reset(true);
		}

		TEST_METHOD(Wildcard_SuitedCard)
		{
			LimitedDeckSuit deck{ 2 };
			SuitedCard* pCard = (SuitedCard*)(deck.select());

			SuitedCard* pWildCard = new SuitedCard{ pCard->GetCardSuit(), pCard->GetCardValue() };
			deck.setWildCard(pWildCard);
			
			Assert::IsTrue(pCard->compare(*pWildCard) == 0);
			Assert::IsTrue(deck.isWildCard(pCard));
		}
	};
}