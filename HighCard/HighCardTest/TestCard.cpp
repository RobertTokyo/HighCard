#include "pch.h"
#include "CppUnitTest.h"
#include "Card.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCard
{
	TEST_CLASS(TestCard)
	{
	public:

		TEST_METHOD(Card_SameCard)
		{
			Card first{ 0 };
			Card second{ 0 };
			int res = first.compare(second);
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(Card_SecondHigherCard)
		{
			Card first{ 0 };
			Card second{ 1 };
			int res = first.compare(second);
			Assert::IsTrue(res < 0);
		}

		TEST_METHOD(Card_SecondLowerCard)
		{
			Card first{ 1 };
			Card second{ 0 };
			int res = first.compare(second);
			Assert::IsTrue(res > 0);
		}

		TEST_METHOD(SameCardSuited_SameSuit)
		{
			SuitedCard first{ Suit::Clubs, 0};
			SuitedCard second{ Suit::Clubs, 0 };
			int res = first.compare(second);
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(SecondHigherCardSuited_SameSuit)
		{
			SuitedCard first{ Suit::Clubs, 0 };
			SuitedCard second{ Suit::Clubs, 1 };
			int res = first.compare(second);
			Assert::IsTrue(res < 0);
		}

		TEST_METHOD(SecondLowerCardSuited_SameSuit)
		{
			SuitedCard first{ Suit::Clubs, 1 };
			SuitedCard second{ Suit::Clubs, 0 };
			int res = first.compare(second);
			Assert::IsTrue(res > 0);
		}

		TEST_METHOD(SameCardSuited_LowerSuit)
		{
			SuitedCard first{ Suit::Clubs, 0 };
			SuitedCard second{ Suit::Clubs, 0 };
			int res = first.compare(second);
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(SecondHigherCardSuited_LowerSuit)
		{
			SuitedCard first{ Suit::Clubs, 0 };
			SuitedCard second{ Suit::Clubs, 1 };
			int res = first.compare(second);
			Assert::IsTrue(res < 0);
		}

		TEST_METHOD(SecondLowerCardSuited_LowerSuit)
		{
			SuitedCard first{ Suit::Clubs, 1 };
			SuitedCard second{ Suit::Clubs, 0 };
			int res = first.compare(second);
			Assert::IsTrue(res > 0);
		}

		TEST_METHOD(SameCardSuited_HigherSuit)
		{
			SuitedCard first{ Suit::Clubs, 0 };
			SuitedCard second{ Suit::Clubs, 0 };
			int res = first.compare(second);
			Assert::AreEqual(res, 0);
		}

		TEST_METHOD(SecondHigherCardSuited_HigherSuit)
		{
			SuitedCard first{ Suit::Clubs, 0 };
			SuitedCard second{ Suit::Clubs, 1 };
			int res = first.compare(second);
			Assert::IsTrue(res < 0);
		}

		TEST_METHOD(SecondLowerCardSuited_HigherSuit)
		{
			SuitedCard first{ Suit::Clubs, 1 };
			SuitedCard second{ Suit::Clubs, 0 };
			int res = first.compare(second);
			Assert::IsTrue(res > 0);
		}

	};
}