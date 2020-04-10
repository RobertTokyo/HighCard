#pragma once
class Deck
{
public:
	Deck() {};
	virtual ~Deck() {};

	virtual Card select() = 0;
};