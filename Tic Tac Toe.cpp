#include <iostream>
#include <cstdlib>
using namespace std;

char board[3][3];
int player = 1;
char mark = 'X';
int turn = 1;
bool gameOver = false;

void initializeBoard()
{
    // Places empty space in the entire board
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void displayBoard()
{
    // Display column numbers on top
    cout << "  0 1 2\n";

    for (int i = 0; i < 3; i++)
    {
        // Display row numbers on left
        cout << i << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            // Display the seperation between columns
            if (j < 2)
                cout << "|";
        }

        cout << endl;
        // Display the seperation between rows
        if (i < 2)
            cout << "  -----\n";
    }
}

void determinePlayer()
{
    if (turn % 2 != 0)
    {
        player = 1;
        mark = 'X';
    }
    else
    {
        player = 2;
        mark = 'O';
    }
}

void playerMove()
{
    int row, col;

    cout << "Player " << player << "(" << mark << "), enter your move (row and column): ";
    cin >> row >> col;

    // Checks if the user choice is valid by seeing if its in the range and the position is empty
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
    {
        board[row][col] = mark;
        turn++;
    }
    else
    {
        cout << "Invalid move. Try again.\n";
        playerMove();
    }
}

bool checkWin()
{
    // Checks through each row and column
    for (int i = 0; i < 3; i++)
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

bool checkDraw()
{
    // Checks if any place is not occupied by X or O
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

void winScreen()
{
    system("cls");
    displayBoard();
    cout << "**************************************************" << endl;
    cout << "CONGRATULATIONS! Player " << player << "(" << mark << ") WINS!" << endl;
    cout << "**************************************************" << endl;
    gameOver = true;
}

void drawScreen()
{
    system("cls");
    displayBoard();
    cout << "**************************************************" << endl;
    cout << "The game is a draw" << endl;
    cout << "**************************************************" << endl;
    gameOver = true;
}

int main()
{
    initializeBoard();

    while (!gameOver)
    {
        system("cls");
        displayBoard();
        determinePlayer();
        playerMove();
        if (checkWin())
            winScreen();
        else if (checkDraw())
            drawScreen();
    }
    return 0;
}