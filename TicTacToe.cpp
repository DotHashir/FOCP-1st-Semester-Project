#include <iostream>
#include <cstdlib>
#include "utilities.h"
#include "TicTacToe.h"
using namespace std;

static const int BOARD_SIZE = 3;

static char board[BOARD_SIZE][BOARD_SIZE];
bool player1Turn = true;
char mark = 'X';
static bool gameOver = false;

void TicTacToe()
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
        playerMove();
        if (isWin())
            winScreen();
        else if (isDraw())
            drawScreen();
        else
            player1Turn = !player1Turn;
    }
}

static void initializeGame()
{
    player1Turn = true;
    char mark = 'X';
    gameOver = false;
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