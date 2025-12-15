#include <iostream>
#include "Stats.h"
#include "utilities.h"
#include "TicTacToe.h"
#include "Chess.h"
#include "GuessTheNumber.h"
#include "Hangman.h"
#include "Connect4.h"
#include "Checkers.h"
using namespace std;

void showMenu(); // funtcion prototype

int main()
{
    playerStats sessionStats;
    int choice;
    do
    { // a loop that keeps asking the user which game they want to play until they exit it.,
        clearScreen();
        showMenu();
        choice = getIntegerInput("");
        switch (choice)
        {
        case 1:
            clearScreen();
            chess(sessionStats);
            break;
        case 2:
            clearScreen();
            Hangman(sessionStats);
            break;
        case 3:
            clearScreen();
            GuessTheNumber(sessionStats);
            break;
        case 4:
            clearScreen();
            checkers(sessionStats);
            break;
        case 5:
            clearScreen();
            TicTacToe(sessionStats);
            break;
        case 6:
            clearScreen();
            Connect4(sessionStats);
            break;
        case 7:
            clearScreen();
            print_final_report(sessionStats);
            break;
        case 0:
            cout << "Thank you for playing at Game Hub!" << endl; // exits loop
            pauseScreen();
            break;
        default:
            cout << "Invalid input. Please choose a number between 0-6." << endl; // shows that the input wasnt one that is defined in the code
            pauseScreen();
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
    cout << "4. Checkers\n";
    cout << "5. Tic Tac Toe\n";
    cout << "6. Connect 4\n";
    cout << "7. Report\n";
    cout << "0. Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
}