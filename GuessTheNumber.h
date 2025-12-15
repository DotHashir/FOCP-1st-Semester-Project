#include "Stats.h"
#ifndef GUESSTHENUMBER_H
#define GUESSTHENUMBER_H

void GuessTheNumber(playerStats &stats);
static void initializeGame();
int playRound(int &score);
std::string getRandomWord();

#endif