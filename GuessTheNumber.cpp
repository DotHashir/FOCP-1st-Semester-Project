#include <iostream>
#include <cstdlib>
#include <ctime>
#include "utilities.h"
#include "GuessTheNumber.h"
using namespace std;

void GuessTheNumber()
{
    int score = 0;
    int choice = 1;
    srand(time(0));

    cout << "----------NUMBER GUESSING GAME----------" << endl
         << "You have ten guesses max to guess the number" << endl;

    do
    {
        playRound(score);

        // Keeps asking the user until correct input
        while (true)
        {
            cout << "Press 1 if you want to play again and 0 if you want to quit: ";
            cin >> choice;

            if (choice == 0 || choice == 1)
                break;
            else
                cout << "Error: Wrong input" << endl;
        }
    } while (choice == 1);

    cout << "Game over! Your final score is: " << score << endl;
}

void playRound(int score)
{
    int guess;
    int attempts = 0;

    // Generates a random number between 1 and 50
    int number = rand() % 50 + 1;

    for (int i = 0; i < 10; i++)
    {
        guess = getIntegerInput("Guess a number between 1-50: ");
        attempts++;

        // If guessed number is out of range
        if (guess > 50 || guess < 1)
            cout << "Invalid input. The number does not lie between 1-50." << endl;

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
            cout << "Your guess is too low!" << endl;
        else if (guess < number)
            cout << "Your guess is low!" << endl;
        else if (guess - 5 > number)
            cout << "Your guess is too high!" << endl;
        else if (guess > number)
            cout << "Your guess is high!" << endl;

        // If guess is not correct and it is not the last attempt, show the attempts remaining
        if (guess != number && i != 9)
            cout << "Attempts left: " << 10 - attempts << endl
                 << endl;
    }
}