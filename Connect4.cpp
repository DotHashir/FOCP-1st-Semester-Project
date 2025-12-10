#include <iostream>
#include "Utilities.h"
#include "Connect4.h"
using namespace std;

static char board[6][7];
int col;
bool isRedTurn = true;
static bool gameOver = false;

void Connect4()
{
    initializeBoard();
    while (!gameOver)
    {
        printBoard();
        playerInput();
        makeMove();

        if (isWin())
        {
            clearScreen();
            printBoard();
            cout << "Congratulations! " << (isRedTurn ? "red" : "yellow") << " you won" << endl;
            pauseScreen();
            gameOver = true;
        }

        else if (isDraw())
        {
            clearScreen();
            printBoard();
            cout << "The game resulted in a draw" << endl;
            pauseScreen();
            gameOver = true;
        }

        isRedTurn = !isRedTurn;
        clearScreen();
    }
}

static void initializeBoard()
{
    // PLaces blank spaces in all the positions
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
            board[i][j] = ' ';
    }
}

static void printBoard()
{
    // Writes headers A-G on top of board with buffer in the start
    cout << "  ";
    for (int i = 0; i < 7; i++)
        cout << char('A' + i) << ' ';

    cout << endl;

    for (int i = 0; i < 6; i++)
    {
        // Writes row numbers on the left side of the board
        cout << 6 - i << ' ';

        for (int j = 0; j < 7; j++)
        {
            cout << board[i][j];

            // Inserts separation between columns
            if (j < 6)
                cout << "|";
        }

        // Inserts seperation between rows
        cout << endl
             << "  ";
        if (i < 5)
            cout << "-------------" << endl;
    }
}

static void playerInput()
{
    char input;
    while (true)
    {
        cout << (isRedTurn ? "Red's turn" : "Yellow's turn") << endl;
        input = tolower(getCharacterInput("Which column do you want to drop your piece in: "));

        if (input < 'a' || input > 'g')
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
    for (int i = 5; i >= 0; i--)
    {
        // Places piece into the first expty space it finds
        if (board[i][col] == ' ')
        {
            board[i][col] = isRedTurn ? 'R' : 'Y';
            break;
        }
    }
}

static bool isWin()
{
    char playerChar = isRedTurn ? 'R' : 'Y';

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == playerChar)
            {
                // Makes sure rows dont go out of bound
                if (i <= 3)
                {
                    // Veritcal check
                    int count = 0;
                    for (int m = 0; m < 4; m++)
                    {
                        if (board[i + m][j] == playerChar)
                            count++;
                        if (count == 4)
                            return true;
                    }
                }

                // Makes sure columns dont go out of bound
                if (j <= 3)
                {
                    // Horizontal Check
                    int count = 0;
                    for (int m = 0; m < 4; m++)
                    {
                        if (board[i][j + m] == playerChar)
                            count++;
                        if (count == 4)
                            return true;
                    }
                }

                // Makes sure both rows and columns dont go out of bound
                if (i <= 3 && j <= 3)
                {
                    // Diagonal check (down right)
                    int count = 0;
                    for (int m = 0; m < 4; m++)
                    {
                        if (board[i + m][j + m] == playerChar)
                            count++;
                        if (count == 4)
                            return true;
                    }
                }

                // Makes sure both rows and columns dont go out of bound
                if (i <= 3 && j >= 3)
                {
                    // Diagonal check (down left)
                    int count = 0;
                    for (int m = 0; m < 4; m++)
                    {
                        if (board[i + m][j - m] == playerChar)
                            count++;
                        if (count == 4)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

static bool isDraw()
{
    // Only looks through the top row, as when board will only be filled when there is no space in the top row
    for (int j = 0; j < 7; j++)
    {
        if (board[0][j] == ' ')
            return false;
    }
    return true;
}