#include <iostream>
#include "Utilities.h"
#include "Connect4.h"
using namespace std;

const int ROWS = 6;
const int COLS = 7;

static char board[ROWS][COLS];
static int col, row;
bool isRedTurn = true;
static bool gameOver = false;

void Connect4()
{
    cout << "==============================" << endl
         << "     Welcome to Connect 4!" << endl
         << "==============================" << endl;
    pauseScreen();
    clearScreen();

    initializeGame();
    initializeBoard();
    while (!gameOver)
    {
        printBoard();
        playerInput();
        makeMove();

        if (isWin())
        {
            winScreen();
        }

        else if (isDraw())
        {
            drawScreen();
        }

        isRedTurn = !isRedTurn;
        clearScreen();
    }
}

static void initializeGame()
{
    isRedTurn = true;
    gameOver = false;
}

static void initializeBoard()
{
    // PLaces blank spaces in all the positions
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            board[i][j] = ' ';
    }
}

static void printBoard()
{
    // Writes headers A-G on top of board with buffer in the start
    cout << "  ";
    for (int i = 0; i < COLS; i++)
        cout << char('A' + i) << ' ';

    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        // Writes row numbers on the left side of the board
        cout << ROWS - i << ' ';

        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 'R')
                cout << RED << "R" << RESET;
            else if (board[i][j] == 'Y')
                cout << YELLOW << "Y" << RESET;
            else
                cout << " ";

            // Inserts separation between columns
            if (j < COLS - 1)
                cout << BLUE << "|" << RESET;
        }

        // Inserts seperation between rows
        cout << endl
             << "  ";
        if (i < ROWS - 1)
            cout << BLUE << "-------------" << RESET << endl;
    }
}

static void playerInput()
{
    char input;
    while (true)
    {
        cout << (isRedTurn ? RED : YELLOW) << (isRedTurn ? "Red's turn" : "Yellow's turn") << RESET << endl;
        input = tolower(getCharacterInput("Which column do you want to drop your piece in (0 to exit): "));

        // Ends the game if user enters 0
        if (input == '0')
        {
            cout << "======================================================" << endl
                 << "You exited the game!" << endl
                 << "======================================================" << endl;
            gameOver = true;
            pauseScreen();
            break;
        }

        if (input < 'a' || input > 'a' + COLS)
            cout << "Error: Input a character between A and G" << endl;
        else if (board[0][input - 'a'] != ' ')
            cout << "Error: Column " << toupper(input) << " is full. Please choose another column." << endl;
        else
            break;
    }

    // Converts player character input into board array index
    col = input - 'a';
}

static void makeMove()
{
    for (int i = ROWS - 1; i >= 0; i--)
    {
        // Places piece into the first empty space it finds
        if (board[i][col] == ' ')
        {
            board[i][col] = isRedTurn ? 'R' : 'Y';
            row = i;
            break;
        }
    }
}

static bool isWin()
{
    char playerChar = isRedTurn ? 'R' : 'Y';
    int count;

    // Verical Check
    count = 1;
    // Only check below as the piece was just dropped
    for (int i = row + 1; i < ROWS && board[i][col] == playerChar; i++)
        count++;

    if (count >= 4)
        return true;

    // Horizontal check
    count = 1;
    // Check on left side of the dropped piece
    for (int i = col - 1; i >= 0 && board[row][i] == playerChar; i--)
        count++;
    // Check on the right side of the dropped piece
    for (int i = col + 1; i < COLS && board[row][i] == playerChar; i++)
        count++;

    if (count >= 4)
        return true;

    // Diagonal check (top left to down right)
    count = 1;
    // Check down right
    for (int i = row + 1, j = col + 1; i < ROWS && j < COLS && board[i][j] == playerChar; i++, j++)
        count++;
    // Check top left
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0 && board[i][j] == playerChar; i--, j--)
        count++;

    if (count >= 4)
        return true;

    // Diagonal check (top right to down left)
    count = 1;
    // Check down left
    for (int i = row + 1, j = col - 1; i < ROWS && j >= 0 && board[i][j] == playerChar; i++, j--)
        count++;
    // Check top right
    for (int i = row - 1, j = col + 1; i >= 0 && j < COLS && board[i][j] == playerChar; i--, j++)
        count++;

    if (count >= 4)
        return true;

    return false;
}

static void winScreen()
{
    clearScreen();
    printBoard();
    cout << "**************************************************" << endl;
    cout << "Congratulations! " << (isRedTurn ? RED : YELLOW) << (isRedTurn ? "red" : "yellow") << RESET << " you won" << endl;
    cout
        << "**************************************************" << endl;
    gameOver = true;
    pauseScreen();
}

static bool isDraw()
{
    // Only looks through the top row, as when board will only be filled when there is no space in the top row
    for (int j = 0; j < COLS; j++)
    {
        if (board[0][j] == ' ')
            return false;
    }
    return true;
}

static void drawScreen()
{
    clearScreen();
    printBoard();
    cout << "**************************************************" << endl;
    cout << "The game resulted in a draw" << endl;
    cout << "**************************************************" << endl;
    gameOver = true;
    pauseScreen();
}