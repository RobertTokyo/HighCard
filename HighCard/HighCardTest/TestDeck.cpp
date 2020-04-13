#include "pch.h"
#include "CppUnitTest.h"
#include "Deck.h"
#include "FixedDeckSuit.h"
#include "CardRepository.inl"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCard
{
	TEST_CLASS(TestDeck)
	{
	public:

		TEST_METHOD(GetRandomCard)
		{
			UnlimitedDeckNoSuit deck;
			auto card = deck.Select(); // smart ptr
			size_t cardvalue = card->GetCardValue();
			Assert::IsTrue(cardvalue>=0 && cardvalue<=52);
		}

		TEST_METHOD(GetRandomSuitedCard)
		{
			DeckSuit deck;
			std::shared_ptr<Card> card = deck.Select();
			size_t cardvalue = card->GetCardValue();
			SuitedCard* pSuitedCard = (SuitedCard*)(card.get());
			int cardsuit = (int)((SuitedCard*)card.get())->GetCardSuit();
			Assert::IsTrue(cardvalue >= 0 && cardvalue <= 52);
			Assert::IsTrue(cardsuit >= 0 && cardsuit < 4);
		}

		TEST_METHOD(GetFixedDeck_SuitedCard)
		{
			FixedDeckSuit deck{ 4 };
			auto card = deck.Select();
			size_t cardvalue = card->GetCardValue();
			SuitedCard* pSuitedCard = (SuitedCard*)(card.get());
			int cardsuit = (int)pSuitedCard->GetCardSuit();
			Assert::IsTrue(cardvalue >= 0 && cardvalue <= 4);
			Assert::IsTrue(cardsuit >= 0 && cardsuit < 4);
		}

		TEST_METHOD(GetFixedDeck_SuitedCardSafe)
		{
			FixedDeckSuit deck{ 4 };
			auto card = deck.Select();
			size_t cardvalue = card->GetCardValue();
			SuitedCard* pSuitedCard = (SuitedCard*)(card.get());
			int cardsuit = (int)pSuitedCard->GetCardSuit();
			Assert::IsTrue(cardvalue >= 0 && cardvalue <= 4);
			Assert::IsTrue(cardsuit >= 0 && cardsuit < 4);
		}

		TEST_METHOD(GetLimitedFixedDeck_SuitedCard)
		{
			LimitedDeckSuit deck{ 2 };

			std::shared_ptr<Card> card = deck.Select();
			Assert::IsNotNull(card.get());
			card = deck.Select();
			Assert::IsNotNull(card.get());

			card = deck.Select();
			Assert::IsNull(card.get());

			deck.reset(true);
		}

		TEST_METHOD(Wildcard_SuitedCard)
		{
			LimitedDeckSuit deck{ 2 };
			auto card = deck.Select();
			SuitedCard* pCard = (SuitedCard*)(card.get());

			SuitedCard* pWildCard = new SuitedCard{ pCard->GetCardSuit(), pCard->GetCardValue() };
			deck.setWildCard(pWildCard);
			
			Assert::IsTrue(pCard->compare(*pWildCard) == 0);
			Assert::IsTrue(deck.isWildCard(pCard));
		}
	};
}