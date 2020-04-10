// HighCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	return (i < j);
}


int main(int argc, char **argv)
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