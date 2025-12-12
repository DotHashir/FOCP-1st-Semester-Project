#ifndef CHECKERS_H
#define CHECKERS_H

void checkers();
static void initializeBoard();
static void printBoard();
static void playerInput(int &sr, int &sc, int &er, int &ec);
static bool isValidMove(int sr, int sc, int er, int ec, bool quietMode);
static void makeMove(int sr, int sc, int er, int ec);
bool piecePromotion(int er, int ec);
static bool isWin();
static void winScreen();
bool canPieceJump(int row, int col);
bool isJumpAvailable();
static bool isCurrentPlayerPiece(int row, int col);
bool isOpponentPiece(int row, int col);

#endif