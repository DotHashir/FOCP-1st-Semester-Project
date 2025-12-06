#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "utilities.h"
using namespace std;

void displayHangman(int attemptsLeft)
{
    switch (attemptsLeft)
    {
    case 6:
        cout << "\n  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n";
        break;
    case 5:
        cout << "\n  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n";
        break;
    case 4:
        cout << "\n  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n";
        break;
    case 3:
        cout << "\n  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n";
        break;
    case 2:
        cout << "\n  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n";
        break;
    case 1:
        cout << "\n  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n";
        break;
    case 0:
        cout << "\n  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n";
        break;
    }
}

int main()
{
    srand(time(0));

    string words[] = {"apple", "sunflower", "cherry", "orange", "grape", "fountain", "basket", "pineapple", "sticker", "strawberry", "guitar", "violin", "trumpet", "piano", "drum", "tornado", "harmony", "melody", "rhythm", "concert", "robot", "rocket", "galaxy", "comet", "meteor", "planet", "eclipse", "orbit", "asteroid", "cosmos", "shadow", "whisper", "thunder", "lightning", "breeze", "hurricane", "college", "blizzard", "avalanche", "rainbow", "castle", "dragon", "knight", "wizard", "princess", "kingdom", "treasure", "sword", "empire", "fortress", "dolphin", "tiger", "leopard", "parrot", "turtle", "kangaroo", "elephant", "penguin", "octopus", "gorilla", "puzzle", "mirror", "lantern", "thunderstorm", "journey", "mystery", "circus", "canyon", "desert", "jungle", "crystal", "diamond", "emerald", "sapphire", "gemstone", "pearl", "silver", "golden", "bronze", "quartz", "volcano", "island", "shoreline", "valley", "mountain", "waterfall", "forest", "river", "meadow", "compiler", "laptop", "battery", "keyboard", "monitor", "printer", "browser", "network", "server", "coding", "cricket"};

    int size = sizeof(words) / sizeof(words[0]);
    int index = rand() % size;
    string word = words[index];

    string blankWord(word.length(), '_');

    char wrongGuesses[6] = {};
    int wrongGuessesCount = 0;

    int attemptsLeft = 6;
    char guess;

    cout << "==============================" << endl;
    cout << "     Welcome to Hangman!" << endl;
    cout << "==============================" << endl;

    while (blankWord != word && attemptsLeft > 0)
    {
        clearScreen();

        displayHangman(attemptsLeft);

        cout << "\nWord: ";
        for (unsigned int i = 0; i < blankWord.length(); i++)
            cout << blankWord[i] << " ";

        cout << "\nWrong guesses: ";
        for (int i = 0; i < 6; i++)
        {
            if (wrongGuesses[i] != '\0')
                cout << wrongGuesses[i] << " ";
        }

        cout << "\nAttempts remaining: " << attemptsLeft << endl;

        guess = getCharacterInput("Enter your guess: ");

        if (blankWord.find(guess) != string::npos || find(wrongGuesses, wrongGuesses + 6, guess) != wrongGuesses + 6)
        {
            cout << "\n====================================" << endl;
            cout << "  You already guessed that letter!";
            cout << "\n====================================" << endl;
            pauseScreen();
            continue;
        }
        bool correct = false;
        for (unsigned int i = 0; i < word.length(); i++)
        {
            if (word[i] == guess)
            {
                blankWord[i] = guess;
                correct = true;
            }
        }
        if (correct)
        {
            cout << "\n========================" << endl;
            cout << "      Good Guess!";
            cout << "\n========================" << endl;
            pauseScreen();
        }

        if (!correct)
        {
            wrongGuesses[wrongGuessesCount] = guess;
            wrongGuessesCount++;
            attemptsLeft--;
            cout << "\n====================================" << endl;
            cout << "       Wrong Guess! Try Again!";
            cout << "\n====================================" << endl;
            pauseScreen();
        }
    }
    cout << "\n======================================================" << endl;
    if (blankWord == word)
        cout << "\n  Congratulations! You guessed the word right!: " << word << endl;
    else
        cout << "\n  You could not guess right! The word was: " << word << endl;

    cout << "\n======================================================" << endl;
    pauseScreen();
    return 0;
}