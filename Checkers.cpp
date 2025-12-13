#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Utilities.h"
#include "Checkers.h"
using namespace std;

static const int BOARD_SIZE = 8;
const char BLACK_PIECE = 'b';
const char WHITE_PIECE = 'w';

static char board[BOARD_SIZE][BOARD_SIZE];
bool isBlackTurn = true;
static bool gameOver = false;
int chainRow, chainCol;
bool chainJump = false;

void checkers()
{
    cout << "==============================" << endl
         << "     Welcome to Checkers!" << endl
         << "==============================" << endl;
    pauseScreen();
    clearScreen();

    int sr, sc, er, ec;

    initializeGame();
    initializeBoard();

    cout << "At any point you can input '" << YELLOW << "quit" << RESET << "' to exit the game" << endl;

    while (!gameOver)
    {
        printBoard();
        playerInput(sr, sc, er, ec);

        if (gameOver)
            break;

        if (isValidMove(sr, sc, er, ec, false))
        {
            clearScreen();
            makeMove(sr, sc, er, ec);
            piecePromotion(er, ec);
            if (!chainJump)
                isBlackTurn = !isBlackTurn;
            if (isWin())
                winScreen();
        }
    }
}

static void initializeGame()
{
    isBlackTurn = true;
    gameOver = false;
    chainJump = false;
}

static void initializeBoard()
{
    // Insert blank spaces on all board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = ' ';
    }

    // Initializes white's pieces
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if ((i + j) % 2 != 0)
                board[i][j] = 'w';
        }
    }

    // Initializes black's pieces
    for (int i = 5; i < 8; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if ((i + j) % 2 != 0)
                board[i][j] = 'b';
        }
    }
}

static void printBoard()
{
    // Writes headers A-H on top of board with buffer in the start
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++)
        cout << char('A' + i) << ' ';

    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Writes row numbers on the left side of the board
        cout << BOARD_SIZE - i << ' ';

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            string bg = ((i + j) % 2 == 0) ? BG_LIGHT : BG_DARK;

            if (tolower(board[i][j]) == 'w')
                cout << bg << BLUE << board[i][j] << RESET;
            else if (tolower(board[i][j]) == 'b')
                cout << bg << RED << board[i][j] << RESET;
            else
                cout << bg << board[i][j] << RESET;

            // Inserts seperation between columns
            if (j < 7)
                cout << "|";
        }

        // Writes row numbers on the right
        cout << ' ' << BOARD_SIZE - i << endl;

        // Inserts seperation between rows
        cout << "  ";
        cout << "---------------" << endl;
    }

    // Writes headers A-H on bottom of board with buffer in the start
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++)
        cout << char('A' + i) << ' ';
    cout << endl;
}

// Handles player input and verifies its correct format
static void playerInput(int &sr, int &sc, int &er, int &ec)
{
    // Keeps asking the user for input until correct answer is not given
    while (true)
    {
        string input;
        cout << (isBlackTurn ? RED : BLUE) << (isBlackTurn ? "Black's turn: " : "White's turn: ") << RESET;
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
        sr = static_cast<char>(BOARD_SIZE) - input[1];
        ec = tolower(input[3]) - 'a';
        er = static_cast<char>(BOARD_SIZE) - input[4];

        // Checks that the row and column input are within the range of the board
        if (sr < 0 || sr >= BOARD_SIZE || sc < 0 || sc >= BOARD_SIZE || er < 0 || er >= BOARD_SIZE || ec < 0 || ec >= BOARD_SIZE)
        {
            cout << "Error: Invalid coordinates. It must be between a1 and h8" << endl;
            continue;
        }

        break;
    }
}

static bool isValidMove(int sr, int sc, int er, int ec, bool quietMode)
{
    int direction = isBlackTurn ? -1 : 1;

    // When multi-jump is active
    if (chainJump)
    {
        // If the move mode is not using the piece for multi-jump
        if (sr != chainRow || sc != chainCol)
        {
            if (!quietMode)
                cout << "Error: Multi-jump active. You must move the piece at " << static_cast<char>(chainCol + 'a') << chainRow + BOARD_SIZE << endl;
            return false;
        }
        if (abs(er - sr) != 2 || abs(ec - sc) != 2)
        {
            if (!quietMode)
                cout << "Error: Multi-jump active. You must capture using the piece at " << static_cast<char>(chainCol + 'a') << chainRow + BOARD_SIZE << endl;
            return false;
        }
    }

    // Checks if the starting position is an empty space
    if (board[sr][sc] == ' ')
    {
        if (!quietMode)
            cout << "Error: The piece you are trying to move is an empty space" << endl;
        return false;
    }

    // Checks if the starting position has your piece or not
    else if (!isCurrentPlayerPiece(sr, sc))
    {
        if (!quietMode)
            cout << "Error: The piece you are trying to move is not yours" << endl;
        return false;
    }
    else if (sr == er && sc == ec)
    {
        if (!quietMode)
            cout << "Error: Ending and starting positions cannot be the same" << endl;
        return false;
    }
    // Checks if the ending position is empty
    else if (board[er][ec] != ' ')
    {
        if (!quietMode)
            cout << "Error: The place you are trying to move to is not empty" << endl;
        return false;
    }

    // Checks if the move is one jump diagonal
    else if (abs(ec - sc) == 1 && abs(er - sr) == 1)
    {
        if (isJumpAvailable())
        {
            if (!quietMode)
                cout << "Error: You must capture enemy's piece when you can" << endl;
            return false;
        }

        // Checks that the man pieces move only forward
        if (er == sr + direction)
            return true;
        else if (isupper(board[sr][sc]))
            return true;
    }
    // Validation for jump/capture
    else if (abs(ec - sc) == 2 && abs(er - sr) == 2 && isOpponentPiece((er + sr) / 2, (ec + sc) / 2))
    {
        if (er == sr + direction + direction)
            return true;
        else if (isupper(board[sr][sc]))
            return true;
    }

    if (!quietMode)
        cout << "Error: Wrong move" << endl;
    return false;
}

static void makeMove(int sr, int sc, int er, int ec)
{
    int direction = isBlackTurn ? -1 : 1;

    // Making the move
    board[er][ec] = board[sr][sc];
    board[sr][sc] = ' ';

    if (abs(ec - sc) == 2)
    {
        board[(er + sr) / 2][(ec + sc) / 2] = ' ';
        cout << "Captured!" << endl;

        // Same piece can now capture other pieces
        if (!piecePromotion(er, ec) && canPieceJump(er, ec))
        {
            chainJump = true;
            chainRow = er;
            chainCol = ec;
            cout << "Multi-jump available! You must continue" << endl;
        }
        else
            chainJump = false;
    }
}

// Converts man pieces to king (lower to upper)
bool piecePromotion(int er, int ec)
{
    if (er == 0 && isBlackTurn)
    {
        board[er][ec] = toupper(board[er][ec]);
        cout << "Piece promoted to king at " << static_cast<char>(ec + 'a') << er + BOARD_SIZE << endl;
        return true;
    }

    else if (er == 7 && !isBlackTurn)
    {
        board[er][ec] = toupper(board[er][ec]);
        return true;
    }

    return false;
}

static bool isWin()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (isCurrentPlayerPiece(i, j))
            {
                // If the piece can jump meaning has a valid move available
                if (canPieceJump(i, j))
                    return false;

                // Makes sure that the arguments passed to isValidMove() dont go out of bound
                if (i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE && isValidMove(i, j, i + 1, j + 1, true))
                    return false;
                else if (i + 1 < BOARD_SIZE && j - 1 >= 0 && isValidMove(i, j, i + 1, j - 1, true))
                    return false;
                else if (i - 1 >= 0 && j + 1 < BOARD_SIZE && isValidMove(i, j, i - 1, j + 1, true))
                    return false;
                else if (i - 1 >= 0 && j - 1 >= 0 && isValidMove(i, j, i - 1, j - 1, true))
                    return false;
            }
        }
    }
    return true;
}

static void winScreen()
{
    clearScreen();
    printBoard();
    cout << "**************************************************" << endl;
    cout << "CONGRATULATIONS! " << (isBlackTurn ? "White" : "BLack") << " Won!" << endl;
    cout
        << "**************************************************" << endl;
    gameOver = true;
    pauseScreen();
}

// Returns if the piece passed to it can capture
bool canPieceJump(int row, int col)
{
    int direction = isBlackTurn ? -1 : 1;

    if (isCurrentPlayerPiece(row, col))
    {
        // All below ifs make sure that the row and column cordinates remain within the bound, has an opponent piece in one digonal jump and an empty space in two diagonal jump

        // Directions: Top-Left, Top-Right, Bot-Left, Bot-Right
        int dr[] = {-1, -1, 1, 1};
        int dc[] = {-1, 1, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            // The square being jumped over
            int rMid = row + dr[i];
            int cMid = col + dc[i];

            // The landing square
            int rEnd = row + 2 * dr[i];
            int cEnd = col + 2 * dc[i];

            // Bounds check
            if (rEnd < 0 || rEnd >= 8 || cEnd < 0 || cEnd >= 8)
                continue;

            // Move logic
            bool isForward = (isBlackTurn && dr[i] == -1) || (!isBlackTurn && dr[i] == 1);

            // If it's a King, or moving forward
            if (isupper(board[row][col]) || isForward)
            {
                if (isOpponentPiece(rMid, cMid) && board[rEnd][cEnd] == ' ')
                    return true;
            }
        }
    }
    return false;
}

// Checks through entire board if any of the current player's pieces can jump
bool isJumpAvailable()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (canPieceJump(i, j))
                return true;
        }
    }
    return false;
}

// Checks if the piece passed to it is current player's piece
static bool isCurrentPlayerPiece(int row, int col)
{
    if (tolower(board[row][col]) == (isBlackTurn ? 'b' : 'w'))
        return true;

    return false;
}

// Checks if the piece passed to it is current player's piece
bool isOpponentPiece(int row, int col)
{
    if (tolower(board[row][col]) == (isBlackTurn ? 'w' : 'b'))
        return true;

    return false;
}