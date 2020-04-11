#pragma once

enum class Suit { Clubs=0, Diamonds=1, Hearts=2, Spades=3};

size_t GetSuitRank(Suit suit);
size_t DefaultSuitRank(Suit suit);
void RankSuit(Suit suit, size_t rank);
