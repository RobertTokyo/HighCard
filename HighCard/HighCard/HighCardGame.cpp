#include "pch.h"
#include <iostream>
#include "HighCard.h"
#include "Deck.h"
#include "Card.h"

void HighCardClassic();
void PlaySuitPrecedence();
void PlayMultiDecks();
void PlayCanNeverTie();
void PlayWithWildcard();
void PlayVarDecks();


enum class action { QUIT, CLASSIC, CAN_TIE, SUIT_ORDER, MULTI_DECK, NO_TIES, WITH_WILDCARD, DECK_VARYSIZE, NO_CMD };
HighCard card;

static void menu()
{
	std::cout << "Game type" << std::endl;
	std::cout << "\t1) Classic" << std::endl;
	std::cout << "\t2) Game can tie" << std::endl;
	std::cout << "\t3) Suits precedence" << std::endl;
	std::cout << "\t4) Multiple Decks" << std::endl;
	std::cout << "\t5) No ties" << std::endl;
	std::cout << "\t6) Wildcard always wins" << std::endl;
	std::cout << "\t7) Variable decksize" << std::endl;

	std::cout << std::endl;
	std::cout << "Q to exit program" << std::endl;
}

static action readAction()
{
	action CMD{ action::NO_CMD };
	char ch;
	std::cin >> ch;
	switch (ch)
	{
	case '1':
		CMD = action::CLASSIC;
		break;
	case '2':
		CMD = action::CAN_TIE;
		break;
	case '3':
		CMD = action::SUIT_ORDER;
		break;
	case '4':
		CMD = action::MULTI_DECK;
		break;
	case '5':
		CMD = action::NO_TIES;
		break;
	case '6':
		CMD = action::WITH_WILDCARD;
		break;
	case '7':
		CMD = action::DECK_VARYSIZE;
		break;
	case 'Q':
	case 'q':
		CMD = action::QUIT;
		break;
	default:
		CMD = action::NO_CMD;
		break;
	}
	return CMD;
}
static action getAction()
{
	menu();
	return readAction();
}


/*
1. Support ties when the face value of the cards are the same.
2. Allow for the ties to be resolved as a win by giving the different suits
precedence.
3. Support for Multiple Decks.
4. Support the ability to never end in a tie, by dealing a further card to each
player.
5. Make one of the cards in the deck a wild card ( beats all others ).
6. Now make the game work for a deck with 20 cards per suit
*/

int main(int /*argc*/, char /**argv*/)
{
	action CMD = getAction();
	while (CMD != action::QUIT)
	{
		switch (CMD)
		{
		case action::CLASSIC:
			HighCardClassic();
			break;
		case action::CAN_TIE:
			void PlaySuitPrecedence();
			break;
		case action::DECK_VARYSIZE:
			void PlayVarDecks();
			break;
		case action::MULTI_DECK:
			void PlayMultiDecks();
			break;
		case action::NO_TIES:
			void PlayCanNeverTie();
			break;
		case action::SUIT_ORDER:
			void PlaySuitPrecedence();
			break;
		case action::WITH_WILDCARD:
			void PlayWithWildcard();
			break;
		default:
			std::cout << "UNKNOWN CMD" << std::endl;
			break;
		}
	}

	return 0;
}

void HighCardClassic()
{
	if (card.Play())
	{
		std::cout << "win\n";
	}
	else
	{
		std::cout << "lose\n";
	}
}

void PlaySuitPrecedence()
{
	HighCardRes res = card.PlaySuitPrecedence();
	switch (res)
	{
	case HighCardRes::Draw:
		std::cout << "draw\n";
		break;
	case HighCardRes::Lose:
		std::cout << "lose\n";
		break;
	case HighCardRes::Win:
		std::cout << "win\n";
		break;
	case HighCardRes::Voided:
		std::cout << "voided game\n";
		break;
	}
}

void PlayMultiDecks()
{
	card.Reset();
	Deck* deck1 = new LimitedDeckSuit{ 52 };
	card.AddDeck(deck1);
	Deck* deck2 = new LimitedDeckSuit{ 52 };
	card.AddDeck(deck2);

	HighCardRes res = card.PlayMultiDecks();
	switch (res)
	{
	case HighCardRes::Draw:
		std::cout << "draw\n";
		break;
	case HighCardRes::Lose:
		std::cout << "lose\n";
		break;
	case HighCardRes::Win:
		std::cout << "win\n";
		break;
	case HighCardRes::Voided:
		std::cout << "voided game\n";
		break;
	}
}

void PlayCanNeverTie()
{
	Deck* deck1 = new LimitedDeckSuit{ 52 };
	card.SetDeck(deck1);
	HighCardRes res = card.PlayCanNeverTie();
	switch (res)
	{
	case HighCardRes::Draw:
		std::cout << "draw\n";
		break;
	case HighCardRes::Lose:
		std::cout << "lose\n";
		break;
	case HighCardRes::Win:
		std::cout << "win\n";
		break;
	case HighCardRes::Voided:
		std::cout << "voided game\n";
		break;
	}
}

void PlayWithWildcard()
{
	Deck* deck = new LimitedDeckSuit{ 52 };
	card.SetDeck(deck);
	Card* pWildcard = new SuitedCard{ Suit::Diamonds, 7 };

	deck->setWildCard(pWildcard);
	
	HighCardRes res = card.PlayWithWildcard();
	switch (res)
	{
	case HighCardRes::Draw:
		std::cout << "draw\n";
		break;
	case HighCardRes::Lose:
		std::cout << "lose\n";
		break;
	case HighCardRes::Win:
		std::cout << "win\n";
		break;
	case HighCardRes::Voided:
		std::cout << "voided game\n";
		break;
	}
}

void PlayVarDecks()
{
	Deck* deck = new LimitedDeckSuit{ 20 };
	card.SetDeck(deck);

	HighCardRes res = card.PlayVarDecks();
	switch (res)
	{
	case HighCardRes::Draw:
		std::cout << "draw\n";
		break;
	case HighCardRes::Lose:
		std::cout << "lose\n";
		break;
	case HighCardRes::Win:
		std::cout << "win\n";
		break;
	case HighCardRes::Voided:
		std::cout << "voided game\n";
		break;
	}
}

// End of file