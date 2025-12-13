#ifndef TICTACTOE_H
#define TICTACTOE_H

void TicTacToe();
static void initializeGame();
static void initializeBoard();
static void printBoard();
void determineMark();
void playerMove();
static bool isWin();
static bool isDraw();
static void winScreen();
static void drawScreen();

#endif