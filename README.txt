Below is an implementation for a game of HighCard, where two cards are drawn from a 52 card deck, and the highest card wins.

 

Refactor the code to:
1. Support ties when the face value of the cards are the same.
2. Allow for the ties to be resolved as a win by giving the different suits precedence.
3. Support for Multiple Decks.
4. Support the ability to never end in a tie, by dealing a further card to each player.
5. Make one of the cards in the deck a wild card ( beats all others ).
6. Now make the game work for a deck with 20 cards per suit

Apply all the best practices you would in what you consider to be production ready code. Include unit testing and show test coverage to the same level.

 

#include <stdlib.h>
#include <iostream>


class HighCard
{
public:
        HighCard() = default;
        ~HighCard() = default;

        bool Play();
};

inline bool HighCard::Play()
{
        int i = rand() % 52 + 1;
        int j = rand() % 52 + 1;
        return ( i < j );
}


int main (int argc, char **argv)
{
        HighCard card;

        if (card.Play())
        {
                std::cout << "win\n";
        }
        else
        {
                std::cout << "lose\n";
        }

        return 0;
}
