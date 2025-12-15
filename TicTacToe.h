#include "Stats.h"
#ifndef TICTACTOE_H
#define TICTACTOE_H

void TicTacToe(playerStats &stats);
static void initializeGame();
static void initializeBoard();
static void printBoard();
void determineMark();
void playerMove();
static bool isWin();
static bool isDraw();
static void canWinNow();
bool canWinNowLine(char c1, char c2, char c3);
static void winScreen();
static void drawScreen();

#endif