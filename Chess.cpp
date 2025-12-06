#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdlib>
#include <limits>
#include "utilities.h"
#include "Chess.h"
using namespace std;

bool isWhiteTurn = true;
static bool gameOver = false;
bool whiteKingMoved = false;
bool blackKingMoved = false;
bool rightWhiteRookMoved = false;
bool leftWhiteRookMoved = false;
bool rightBlackRookMoved = false;
bool leftBlackRookMoved = false;
int enPassantCol = -1;

void chess()
{
    char board[8][8];
    initializeBoard(board);
    printBoard(board);
    int sr, sc, er, ec; // start row, start column, end row, end column
    while (!gameOver)
    {
        playerInput(sr, sc, er, ec);

        if (gameOver)
            break;

        if (isValidMove(sr, sc, er, ec, board, false))
        {
            clearScreen();

            makeMove(sr, sc, er, ec, board);
            printBoard(board);

            if (isCheckmate(board))
                cout << (isWhiteTurn ? "White" : "Black") << " won!" << endl;
            else if (isStalemate(board))
                cout << "The game resulted in a stalemate!" << endl;

            // Switches player's turn
            isWhiteTurn = !isWhiteTurn;

            // Checks and displays a warning if the next player's king is in check
            if (isInCheck(board))
                cout << "WARNING! " << (isWhiteTurn ? "White's" : "Black's") << " king is in check" << endl;
        }
    }
}

void initializeBoard(char board[8][8])
{
    // Insert blank spaces on all board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            board[i][j] = ' ';
    }

    // Setup row arrangement for black and white pieces
    char black_row[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    char white_row[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    for (int j = 0; j < 8; j++)
    {
        // Setup black pieces
        board[0][j] = black_row[j];
        board[1][j] = 'p';

        // Setup white pieces
        board[6][j] = 'P';
        board[7][j] = white_row[j];
    }
}

void printBoard(char board[8][8])
{
    // Writes headers A-H on top of board with buffer in the start
    cout << "  ";
    for (int i = 0; i < 8; i++)
        cout << char('A' + i) << ' ';

    cout << endl;

    for (int i = 0; i < 8; i++)
    {
        // Writes row numbers on the left side of the board
        cout << 8 - i << ' ';

        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j];

            // Inserts seperation between columns
            if (j < 7)
                cout << "|";
        }

        // Writes row numbers on the right
        cout << ' ' << 8 - i << endl;

        // Inserts seperation between rows
        cout << "  ";
        cout << "---------------" << endl;
    }

    // Writes headers A-H on bottom of board with buffer in the start
    cout << "  ";
    for (int i = 0; i < 8; i++)
        cout << char('A' + i) << ' ';
    cout << endl;
}

// Handles player input and verifies its correct format
void playerInput(int &sr, int &sc, int &er, int &ec)
{
    // Keeps asking the user for input until correct answer is not given
    while (true)
    {
        string input;
        cout << (isWhiteTurn ? "White's turn (P, R, N...): " : "Black's turn (p, r, n...): ");
        getline(cin, input);

        // Ends the game if user enters quit
        if (input == "quit")
        {
            gameOver = true;
            break;
        }
        // Verifies that the input format is correct
        else if (input.length() != 5 || input[2] != ' ')
        {
            cout << "Error: Invalid input format! (Use e1 e4)" << endl;
            continue;
        }

        // Breaks up the input into starting row, column and ending row, column
        sc = tolower(input[0]) - 'a';
        sr = '8' - input[1];
        ec = tolower(input[3]) - 'a';
        er = '8' - input[4];

        // Checks that the row and column input are within the range of the board
        if (sr < 0 || sr >= 8 || sc < 0 || sc >= 8 || er < 0 || er >= 8 || ec < 0 || ec >= 8)
        {
            cout << "Error: Invalid coordinates. It must be between a1 and h8" << endl;
            continue;
        }

        break;
    }
}

// The final function that moves the piece after all the validation
void makeMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Displays a capture message if the place the piece was moved was occupied by an enemy piece
    if (board[er][ec] != ' ')
    {
        string playerPiece = getPieceName(board[sr][sc]);
        string enemyPiece = getPieceName(board[er][ec]);
        string playerColour = isWhiteTurn ? "White" : "Black";
        string enemyColour = isWhiteTurn ? "black" : "white";

        cout << playerColour << "'s " << playerPiece << " captured " << enemyColour << "'s " << enemyPiece << endl;
    }
    // Hanles En-Passant capturing
    else if (tolower(board[sr][sc]) == 'p' && board[er][ec] == ' ' && abs(ec - sc) == 1)
    {
        board[sr][ec] = ' ';
        cout << (isWhiteTurn ? "White" : "Black") << " performed En Passant capture" << endl;
    }

    // Logic for castling
    if (sr == 7 && sc == 4 && er == 7 && ec == 6 && board[sr][sc] == 'K')
    {
        board[er][ec] = 'K';
        board[7][5] = 'R';
        board[sr][sc] = ' ';
        board[7][7] = ' ';
    }
    else if (sr == 7 && sc == 4 && er == 7 && ec == 2 && board[sr][sc] == 'K')
    {
        board[er][ec] = 'K';
        board[7][3] = 'R';
        board[sr][sc] = ' ';
        board[7][0] = ' ';
    }
    else if (sr == 0 && sc == 4 && er == 0 && ec == 6 && board[sr][sc] == 'k')
    {
        board[er][ec] = 'k';
        board[0][5] = 'r';
        board[sr][sc] = ' ';
        board[0][7] = ' ';
    }
    else if (sr == 0 && sc == 4 && er == 0 && ec == 2 && board[sr][sc] == 'k')
    {
        board[er][ec] = 'k';
        board[0][3] = 'r';
        board[sr][sc] = ' ';
        board[0][0] = ' ';
    }
    // Makes the move
    else
    {
        board[er][ec] = board[sr][sc];
        board[sr][sc] = ' ';
    }

    // Updates different states needed for castling validation
    if (sr == 7 && sc == 4 && board[er][ec] == 'K')
        whiteKingMoved = true;
    else if (sr == 0 && sc == 4 && board[er][ec] == 'k')
        blackKingMoved = true;
    else if (sr == 7 && sc == 0 && board[er][ec] == 'R')
        leftWhiteRookMoved = true;
    else if (sr == 7 && sc == 7 && board[er][ec] == 'R')
        rightWhiteRookMoved = true;
    else if (sr == 0 && sc == 0 && board[er][ec] == 'r')
        leftBlackRookMoved = true;
    else if (sr == 0 && sc == 7 && board[er][ec] == 'r')
        rightBlackRookMoved = true;

    // Saves the column for En Passant
    if (tolower(board[er][ec]) == 'p' && abs(er - sr) == 2)
        enPassantCol = ec;
    else
        enPassantCol = -1;

    // Handles pawn promotion
    if ((board[er][ec] == 'P' && er == 0) || board[er][ec] == 'p' && er == 7)
        PawnPromotion(board, er, ec);
}

bool isValidMove(int sr, int sc, int er, int ec, char board[8][8], bool quietMode)
{
    // Checks if the starting position is an empty space
    if (board[sr][sc] == ' ')
    {
        if (!quietMode)
            cout << "Error: The piece you are trying to move is an empty space" << endl;
        return false;
    }

    // Checks if the starting position has your piece or not
    else if (!isCurrentPlayerPiece(board[sr][sc]))
    {
        if (!quietMode)
            cout << "Error: The piece you are trying to move is not yours" << endl;
        return false;
    }
    // Checks if the capturing position has your piece
    else if (isCurrentPlayerPiece(board[er][ec]))
    {
        if (!quietMode)
            cout << "Error: Cannot capture your own piece" << endl;
        return false;
    }
    else if (sr == er && sc == ec)
    {
        if (!quietMode)
            cout << "Error: Ending and starting positions cannot be the same" << endl;
        return false;
    }

    return isValidPieceMove(sr, sc, er, ec, board, quietMode);
}

bool isValidPieceMove(int sr, int sc, int er, int ec, char board[8][8], bool quietMode)
{
    // quietMode determines if error messages should be displayed for invalid moves

    char piece = tolower(board[sr][sc]);
    // Calls the correct function wrt to the type of piece moved
    switch (piece)
    {
    case 'p':
        if (!isValidPawnMove(sr, sc, er, ec, board))
        {
            if (!quietMode)
                cout << "Error: Invalid pawn move" << endl;
            return false;
        }
        break;
    case 'r':
        if (!isValidRookMove(sr, sc, er, ec, board))
        {
            if (!quietMode)
                cout << "Error: Invalid rook move" << endl;
            return false;
        }
        break;
    case 'b':
        if (!isValidBishopMove(sr, sc, er, ec, board))
        {
            if (!quietMode)
                cout << "Error: Invalid bishop move" << endl;
            return false;
        }
        break;
    case 'n':
        if (!isValidKnightMove(sr, sc, er, ec, board))
        {
            if (!quietMode)
                cout << "Error: Invalid knight move" << endl;
            return false;
        }
        break;
    case 'q':
        if (!isValidQueenMove(sr, sc, er, ec, board))
        {
            if (!quietMode)
                cout << "Error: Invalid queen move" << endl;
            return false;
        }
        break;
    case 'k':
        if (!isValidKingMove(sr, sc, er, ec, board))
        {
            if (!quietMode)
                cout << "Error: Invalid king move" << endl;
            return false;
        }
        break;
    }

    if (isMoveResultingInCheck(sr, sc, er, ec, board))
    {
        if (!quietMode)
            cout << "Error: Illegal move as it results in check" << endl;
        return false;
    }

    return true;
}

bool isValidPawnMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Determines whether to move up or down through the array
    int direction = isWhiteTurn ? -1 : 1;

    // For forward movement
    if (sc == ec)
    {
        // For 1 step movement
        if (er == (sr + direction) && board[er][ec] == ' ')
            return true;
        // For 2 step movement in the initial position
        else if (isWhiteTurn && sr == 6 && er == 4 && board[5][ec] == ' ' && board[er][ec] == ' ')
            return true;
        else if (!isWhiteTurn && sr == 1 && er == 3 && board[2][ec] == ' ' && board[er][ec] == ' ')
            return true;
    }

    // For diagonal capturing
    if (abs(ec - sc) == 1 && er == (sr + direction) && board[er][ec] != ' ')
        return true;

    // Logic for En Passant rule
    if (abs(ec - sc) == 1 && er == (sr + direction) && board[er][ec] == ' ')
    {
        if (isWhiteTurn && sr == 3 && ec == enPassantCol)
            return true;
        else if (!isWhiteTurn && sr == 4 && ec == enPassantCol)
            return true;
    }
    return false;
}

bool isValidRookMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Checks if the movement is along horizontal or vertical
    if (sr != er && sc != ec)
        return false;

    return isPathClear(sr, sc, er, ec, board);
}

bool isValidBishopMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Checks if the movement is in a digonal
    if (abs(sr - er) != abs(sc - ec))
        return false;

    return isPathClear(sr, sc, er, ec, board);
}

bool isValidKnightMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Confirms that the distance between its destination row and column is either 1 and 2 or 2 and 1
    if ((abs(er - sr) == 2 && abs(ec - sc) == 1) || (abs(er - sr) == 1 && abs(ec - sc) == 2))
        return true;

    return false;
}

bool isValidQueenMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Checks if the movement is in a digonal or vertical or horizontal
    if ((abs(sr - er) != abs(sc - ec)) && (sr != er && sc != ec))
        return false;

    return isPathClear(sr, sc, er, ec, board);
}

bool isValidKingMove(int sr, int sc, int er, int ec, char board[8][8])
{
    // Logic for castling
    if (abs(ec - sc == 2))
    {
        // Makes sure that all the conditions for castiling are satisfied
        if (board[sr][sc] == 'K' && er == 7 && ec == 6 && !whiteKingMoved && !rightWhiteRookMoved && isPathClear(sr, sc, er, ec, board) && !isInCheck(board) && !isSquareAttacked(7, 5, board) && !isSquareAttacked(7, 6, board))
            return true;
        if (board[sr][sc] == 'K' && er == 7 && ec == 2 && !whiteKingMoved && !leftWhiteRookMoved && isPathClear(sr, sc, er, ec, board) && !isInCheck(board) && !isSquareAttacked(7, 3, board) && !isSquareAttacked(7, 2, board))
            return true;
        if (board[sr][sc] == 'k' && er == 0 && ec == 6 && !blackKingMoved && !rightBlackRookMoved && isPathClear(sr, sc, er, ec, board) && !isInCheck(board) && !isSquareAttacked(0, 5, board) && !isSquareAttacked(0, 6, board))
            return true;
        if (board[sr][sc] == 'k' && er == 0 && ec == 2 && !blackKingMoved && !leftBlackRookMoved && isPathClear(sr, sc, er, ec, board) && !isInCheck(board) && !isSquareAttacked(0, 3, board) && !isSquareAttacked(0, 2, board))
            return true;
    }

    // Check if the movement is only around the king
    else if (abs(er - sr) > 1 || abs(ec - sc) > 1)
        return false;

    return true;
}

// Checks that there are no other pieces in between for the sliding pieces (Rook, Bishop, Queen)
bool isPathClear(int sr, int sc, int er, int ec, char board[8][8])
{
    // For horizontal movement
    if (sr == er)
    {
        // Determines whether to move left or right
        int direction = (ec > sc) ? 1 : -1;
        for (int col = sc + direction; col != ec; col += direction)
        {
            if (board[er][col] != ' ')
                return false;
        }
    }
    // For vertical movement
    else if (sc == ec)
    {
        // Determines whether to move up or down
        int direction = (er > sr) ? 1 : -1;
        for (int row = sr + direction; row != er; row += direction)
        {
            if (board[row][ec] != ' ')
                return false;
        }
    }
    // For diagonal movement
    else
    {
        int colDirection = (ec > sc) ? 1 : -1;
        int rowDirection = (er > sr) ? 1 : -1;
        int row = sr + rowDirection;
        int col = sc + colDirection;

        while (row != er)
        {
            if (board[row][col] != ' ')
                return false;

            row += rowDirection;
            col += colDirection;
        }
    }

    return true;
}

// Checks if in the current state of the board your king is in check or not
bool isInCheck(char board[8][8])
{
    int kr, kc;
    findKing(kr, kc, board);

    return isSquareAttacked(kr, kc, board);
}

bool isMoveResultingInCheck(int sr, int sc, int er, int ec, char board[8][8])
{
    // Creates a copy of the current board
    char tempBoard[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            tempBoard[i][j] = board[i][j];
    }

    // Handles the exceptional case of En-Passant capturing
    if (tolower(tempBoard[sr][sc]) == 'p' && tempBoard[er][ec] == ' ' && abs(ec - sc) == 1)
        tempBoard[sr][ec] = ' ';

    // Makes the move in the fake board to see if there results a check
    tempBoard[er][ec] = tempBoard[sr][sc];
    tempBoard[sr][sc] = ' ';

    return isInCheck(tempBoard);
}

bool isCheckmate(char board[8][8])
{
    if (!isInCheck(board) || hasAnyLegalMove(board))
        return false;

    gameOver = true;
    return true;
}

bool isStalemate(char board[8][8])
{
    if (isInCheck(board) || hasAnyLegalMove(board))
        return false;

    gameOver = true;
    return true;
}

// This function find the position of king in the array(board)
void findKing(int &kr, int &kc, char board[8][8])
{
    char kingPiece = isWhiteTurn ? 'K' : 'k';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == kingPiece)
            {
                kr = i;
                kc = j;
                return;
            }
        }
    }
}

// This function checks if the array element(board position) passed to it is attacked by any other enemy's piece
bool isSquareAttacked(int row, int col, char board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = board[i][j];

            // Skips player's own pieces and empty spaces
            if (isCurrentPlayerPiece(piece))
                continue;
            else if (piece == ' ')
                continue;

            // Checks if the piece can attack by calling their respective functions
            switch (tolower(piece))
            {
            case 'p':
            {
                int direction = isWhiteTurn ? 1 : -1;
                if (abs(col - j) == 1 && row == (i + direction))
                    return true;
                break;
            }
            case 'r':
                if (isValidRookMove(i, j, row, col, board))
                    return true;
                break;
            case 'b':
                if (isValidBishopMove(i, j, row, col, board))
                    return true;
                break;
            case 'n':
                if (isValidKnightMove(i, j, row, col, board))
                    return true;
                break;
            case 'q':
                if (isValidQueenMove(i, j, row, col, board))
                    return true;
                break;
            case 'k':
                if (isValidKingMove(i, j, row, col, board))
                    return true;
                break;
            }
        }
    }
    return false;
}

bool hasAnyLegalMove(char board[8][8])
{
    // Itterates through every position on the board for starting position
    for (int sr = 0; sr < 8; sr++)
    {
        for (int sc = 0; sc < 8; sc++)
        {
            // Only continues if the position is occupied by player's own piece
            if (isCurrentPlayerPiece(board[sr][sc]))
            {
                // Itterates through every position on the board for destination position
                for (int er = 0; er < 8; er++)
                {
                    for (int ec = 0; ec < 8; ec++)
                    {
                        // Sees if there is any single legal move
                        if (isValidMove(sr, sc, er, ec, board, true))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

// Handles logic for pawn promotion
void PawnPromotion(char board[8][8], int row, int col)
{
    char choice;

    // Infinite loop until user makes a valid input
    while (true)
    {
        choice = getCharacterInput("Which piece do you want to promote your pawn to(Q, N, R, B): ");

        if (choice == 'q' || choice == 'n' || choice == 'r' || choice == 'b')
        {
            if (row == 0)
                board[row][col] = toupper(choice);
            else if (row == 7)
                board[row][col] = choice;

            break;
        }
        else
            cout << "Error: Wrong input" << endl;
    }
}

// Checks if the piece passed to it belongs to the current player
bool isCurrentPlayerPiece(char piece)
{
    if (isWhiteTurn && (piece >= 'A' && piece <= 'Z'))
        return true;
    else if (!isWhiteTurn && (piece >= 'a' && piece <= 'z'))
        return true;
    else
        return false;
}

// Converts piece character to its full name
string getPieceName(char piece)
{

    switch (tolower(piece))
    {
    case 'p':
        return "pawn";
    case 'r':
        return "rook";
    case 'b':
        return "bishop";
    case 'n':
        return "knight";
    case 'q':
        return "queen";
    case 'k':
        return "king";
    default:
        return "error in fetching piece name";
    }
}