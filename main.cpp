#include <iostream>
#include "utilities.h"
#include "TicTacToe.h"
#include "Chess.h"
#include "GuessTheNumber.h"
#include "Hangman.h"
#include "Connect4.h"
using namespace std;

void showMenu(); // funtcion prototype

int main()
{
    int choice;
    do
    { // a loop that keeps asking the user which game they want to play until they exit it.,
        clearScreen();
        showMenu();
        choice = getIntegerInput("");
        switch (choice)
        {
        case 1:
            chess();
            break;
        case 2:
            Hangman();
            break;
        case 3:
            GuessTheNumber();
            break;
        case 4:
            break;
        case 5:
            TicTacToe();
            break;
        case 6:
            Connect4();
            break;
        case 0:
            cout << "Thank you for playing at Game Hub!"; // exits loop
            break;
        default:
            cout << "Invalid input. Please choose a number between 0-6."; // shows that the input wasnt one that is defined in the code
        }
        cout << endl;
    } while (choice != 0);
}

void showMenu()
{ // function that shows which game can be played in the app
    cout << "=============================\n";
    cout << "        GAME HUB MENU      \n";
    cout << "=============================\n";
    cout << "1. Chess\n";
    cout << "2. Hangman\n";
    cout << "3. Guess the Number\n";
    cout << "4. Head or Tails\n";
    cout << "5. Tic Tac Toe\n";
    cout << "6. Connect 4\n";
    cout << "0. Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
}