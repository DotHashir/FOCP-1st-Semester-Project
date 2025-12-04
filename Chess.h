#include <string>
#ifndef CHESS_H
#define CHESS_H

void chess();
void initializeBoard(char board[8][8]);
void printBoard(char board[8][8]);
void playerInput(int &sr, int &sc, int &er, int &ec);
void makeMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isValidMove(int sr, int sc, int er, int ec, char board[8][8], bool quietMode);
bool isValidPieceMove(int sr, int sc, int er, int ec, char board[8][8], bool quietMode);
bool isValidPawnMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isValidRookMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isValidBishopMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isValidKnightMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isValidQueenMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isValidKingMove(int sr, int sc, int er, int ec, char board[8][8]);
bool isPathClear(int sr, int sc, int er, int ec, char board[8][8]);
bool isInCheck(char board[8][8]);
bool isMoveResultingInCheck(int sr, int sc, int er, int ec, char board[8][8]);
bool isCheckmate(char board[8][8]);
bool isStalemate(char board[8][8]);
void findKing(int &kr, int &kc, char board[8][8]);
bool isSquareAttacked(int row, int col, char board[8][8]);
bool hasAnyLegalMove(char board[8][8]);
void PawnPromotion(char board[8][8], int row, int col);
bool isCurrentPlayerPiece(char piece);
std::string getPieceName(char piece);

#endif