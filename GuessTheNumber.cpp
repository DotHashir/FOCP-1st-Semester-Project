#include <iostream>
#include <cstdlib>
#include <ctime>
#include "utilities.h"
#include "GuessTheNumber.h"
using namespace std;

const int MAX_RANGE = 50;
const int MAX_GUESSES = 10;
bool gameOver = false;

void GuessTheNumber()
{
    int score = 0;
    int choice = 1;
    srand(time(0));

    initializeGame();

    cout << "----------NUMBER GUESSING GAME----------" << endl
         << "You have ten guesses max to guess the number" << endl;

    while (!gameOver)
    {
        playRound(score);

        if (gameOver)
            break;

        // Keeps asking the user until correct input
        while (true)
        {
            getIntegerInput("Press 1 to play again, 0 to quit: ");

            if (choice == 0)
                break;
            else if (choice == 1)
            {
                gameOver = true;
                break;
            }
            else
                cout << "Error: Wrong input" << endl;
        }
    }

    cout << "Game over! Your final score is: " << score << endl;
}

static void initializeGame()
{
    gameOver = false;
}

void playRound(int &score)
{
    int guess;
    int attempts = 0;

    // Generates a random number between 1 and MAX_RANGE
    int number = rand() % MAX_RANGE + 1;

    for (int i = 0; i < MAX_GUESSES; i++)
    {
        cout << "Guess a number between 1-" << MAX_RANGE << " (-1 to exit): ";
        guess = getIntegerInput("");
        attempts++;

        // Ends the game if user enters quit
        if (guess == -1)
        {
            cout << "======================================================" << endl
                 << "You exited the game!" << endl
                 << "======================================================" << endl;
            gameOver = true;
            pauseScreen();
            return;
        }

        // If guessed number is out of range
        if (guess > MAX_RANGE || guess < 1)
            cout << "Invalid input. The number does not lie between 1-" << MAX_RANGE << endl;

        // Correct guess
        else if (number == guess)
        {
            score++;
            cout << "Your guess is correct!" << endl
                 << "Your current score is: " << score << endl;
            break;
        }
        // After final attempt
        else if (i == 9)
        {
            cout << "You lost!" << endl
                 << "The number was: " << number << endl;
        }

        // Wrong guess logic
        else if (guess + 5 < number)
            cout << "Your guess is low!" << endl;
        else if (guess < number)
            cout << "Your guess is low, but very close!" << endl;
        else if (guess - 5 > number)
            cout << "Your guess is high!" << endl;
        else if (guess > number)
            cout << "Your guess is high, but very close!" << endl;

        // If guess is not correct and it is not the last attempt, show the attempts remaining
        if (guess != number && i != 9)
            cout << "Attempts left: " << MAX_GUESSES - attempts << endl
                 << endl;
    }
}