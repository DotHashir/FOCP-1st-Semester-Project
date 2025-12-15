#include "Stats.h"
#ifndef CONNECT4_H
#define CONNECT4_H

void Connect4(playerStats &stats);
static void initializeGame();
static void initializeBoard();
static void printBoard();
static void playerInput();
static void makeMove();
static bool isWin();
static void winScreen();
static bool isDraw();
static void drawScreen();
static void canWinNow();

#endif