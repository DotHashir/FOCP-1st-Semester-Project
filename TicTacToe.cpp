#include <iostream>
#include <cstdlib>
#include "utilities.h"
#include "TicTacToe.h"
#include "Stats.h"
using namespace std;

static const int BOARD_SIZE = 3;

static char board[BOARD_SIZE][BOARD_SIZE];
bool player1Turn = true;
char mark = 'X';
static bool gameOver = false;
static int missedWins = 0;
static bool canWin = false;

void TicTacToe(playerStats &stats)
{
    cout << "==============================" << endl
         << "  Welcome to Tic Tac Toe!" << endl
         << "==============================" << endl;
    pauseScreen();

    initializeGame();
    initializeBoard();

    while (!gameOver)
    {
        clearScreen();
        printBoard();
        determineMark();
        if (player1Turn)
            canWinNow();
        playerMove();

        if (isWin())
        {
            winScreen();
            if (player1Turn)
                update_ttt_stats(stats, 1, missedWins);
            else
                update_guess_stats(stats, -1, missedWins);
        }
        else if (isDraw())
        {
            drawScreen();
            update_ttt_stats(stats, 0, missedWins);
        }
        else
            player1Turn = !player1Turn;
    }
}

static void initializeGame()
{
    player1Turn = true;
    char mark = 'X';
    gameOver = false;
    missedWins = 0;
    canWin = false;
}

static void initializeBoard()
{
    // Places empty space in the entire board
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = ' ';
}

static void printBoard()
{
    // Display column numbers on top
    cout << "  1 2 3\n";

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Display row numbers on left
        cout << i + 1 << " ";

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 'X')
                cout << RED << "X" << RESET;
            else if (board[i][j] == 'O')
                cout << CYAN << "O" << RESET;
            else
                cout << " ";

            // Display the seperation between columns
            if (j < BOARD_SIZE - 1)
                cout << "|";
        }

        cout << endl;
        // Display the seperation between rows
        if (i < BOARD_SIZE - 1)
            cout << "  -----\n";
    }
}

void determineMark()
{
    mark = player1Turn ? 'X' : 'O';
}

void playerMove()
{
    int choice, row, col;

    while (true)
    {
        cout << "Player " << (player1Turn ? RED : CYAN) << (player1Turn ? "1(X)" : "2(O)") << RESET << ", enter your move (1-9) (0 to exit): ";
        choice = getIntegerInput("");

        // Ends the game if user enters 0
        if (choice == 0)
        {
            cout << "======================================================" << endl
                 << "You exited the game!" << endl
                 << "======================================================" << endl;
            gameOver = true;
            pauseScreen();
            break;
        }

        row = (choice - 1) / BOARD_SIZE;
        col = (choice - 1) % BOARD_SIZE;

        // Checks if the user choice is valid by seeing if its in the range and the position is empty
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ')
        {
            board[row][col] = mark;
            break;
        }
        else
        {
            cout << "Invalid move. Try again.\n";
        }
    }
}

static bool isWin()
{
    // Checks through each row and column
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
            return true;
        else if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
            return true;
    }

    // Checks both diagonals
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
        return true;
    else if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
        return true;

    return false;
}

static bool isDraw()
{
    // Checks if any place is not occupied by X or O
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

static void canWinNow()
{
    // If the canWin variable is already true meaning that the player had a winning opportunity last time and still game is continuing
    if (canWin)
    {
        missedWins++;
        canWin = false;
    }

    // Checks each row and column
    for (int i = 0; i < 3; i++)
    {
        if (canWinNowLine(board[i][0], board[i][1], board[i][2]))
        {
            canWin = true;
            return;
        }
        if (canWinNowLine(board[0][i], board[1][i], board[2][i]))
        {
            canWin = true;
            return;
        }
    }

    // Checks diagonals
    if (canWinNowLine(board[0][0], board[1][1], board[2][2]))
    {
        canWin = true;
        return;
    }
    if (canWinNowLine(board[0][2], board[1][1], board[2][0]))
    {
        canWin = true;
        return;
    }
}

// Function that helps canWin() function
bool canWinNowLine(char c1, char c2, char c3)
{
    int markCount = 0;
    int emptyCount = 0;

    // Notes whether each position is current player's mark or an empty place
    if (c1 == mark)
        markCount++;
    else if (c1 == ' ')
        emptyCount++;

    if (c2 == mark)
        markCount++;
    else if (c2 == ' ')
        emptyCount++;

    if (c3 == mark)
        markCount++;
    else if (c3 == ' ')
        emptyCount++;

    // If their are 2 marks and only 1 empty place meaning that the player can win on this turn
    if (markCount == 2 && emptyCount == 1)
        return true;

    return false;
}

static void winScreen()
{
    clearScreen();
    printBoard();
    cout << "**************************************************" << endl;
    cout << "CONGRATULATIONS! Player " << (player1Turn ? RED : CYAN) << (player1Turn ? "1(X)" : "2(O)") << RESET << " Won!" << endl;
    cout
        << "**************************************************" << endl;
    gameOver = true;
    pauseScreen();
}

static void drawScreen()
{
    clearScreen();
    printBoard();
    cout << "**************************************************" << endl;
    cout << "The game is a draw" << endl;
    cout << "**************************************************" << endl;
    gameOver = true;
    pauseScreen();
}