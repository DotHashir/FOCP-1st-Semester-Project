#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "utilities.h"
#include "Hangman.h"
using namespace std;

void Hangman()
{
    srand(time(0));

    string word = getRandomWord();

    // Sets a blanck word equal to the length of the word to be guessed
    string blankWord(word.length(), '_');

    char wrongGuesses[6] = {};
    int wrongGuessesCount = 0;

    int attemptsLeft = 6;
    char guess;

    cout << "==============================" << endl
         << "     Welcome to Hangman!" << endl
         << "==============================" << endl;

    // Continue as long as word has not been guessed or o attempts are left
    while (blankWord != word && attemptsLeft > 0)
    {
        clearScreen();

        displayHangman(attemptsLeft);

        // Displays blank spaces and guessed charcters with spaces
        cout << "\nWord: ";
        for (unsigned int i = 0; i < blankWord.length(); i++)
            cout << blankWord[i] << " ";

        // Displays all the charcters that have been wrongly guessed
        cout << "\nWrong guesses: ";
        for (int i = 0; i < 6; i++)
        {
            if (wrongGuesses[i] != '\0')
                cout << wrongGuesses[i] << " ";
        }

        cout << "\nAttempts remaining: " << attemptsLeft << endl;

        guess = getCharacterInput("Enter your guess: ");

        if (isAlreadyGuessed(blankWord, guess, wrongGuesses))
            continue;

        if (!isCorrectGuess(word, blankWord, guess))
        {
            // Adds the current guess to wrongGuesses array
            wrongGuesses[wrongGuessesCount] = guess;
            wrongGuessesCount++;

            attemptsLeft--;
        }
    }

    if (attemptsLeft == 0)
    {
        clearScreen();
        displayHangman(attemptsLeft);
    }

    // Message for end of the game
    cout << "\n======================================================" << endl;
    if (blankWord == word)
        cout << "\n  Congratulations! You guessed the word right!: " << word << endl;
    else
        cout << "\n  You could not guess right! The word was: " << word << endl;

    cout << "\n======================================================" << endl;
    pauseScreen();
}

// Displays the hangman figure depending on how much attempts we have failed
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

string getRandomWord()
{
    // Collection of all the words that have the chance of being asked in th hangman game
    string words[] = {"apple", "sunflower", "cherry", "orange", "grape", "fountain", "basket", "pineapple", "sticker", "strawberry", "guitar", "violin", "trumpet", "piano", "drum", "tornado", "harmony", "melody", "rhythm", "concert", "robot", "rocket", "galaxy", "comet", "meteor", "planet", "eclipse", "orbit", "asteroid", "cosmos", "shadow", "whisper", "thunder", "lightning", "breeze", "hurricane", "college", "blizzard", "avalanche", "rainbow", "castle", "dragon", "knight", "wizard", "princess", "kingdom", "treasure", "sword", "empire", "fortress", "dolphin", "tiger", "leopard", "parrot", "turtle", "kangaroo", "elephant", "penguin", "octopus", "gorilla", "puzzle", "mirror", "lantern", "thunderstorm", "journey", "mystery", "circus", "canyon", "desert", "jungle", "crystal", "diamond", "emerald", "sapphire", "gemstone", "pearl", "silver", "golden", "bronze", "quartz", "volcano", "island", "shoreline", "valley", "mountain", "waterfall", "forest", "river", "meadow", "compiler", "laptop", "battery", "keyboard", "monitor", "printer", "browser", "network", "server", "coding", "cricket"};

    // Finds the size of the array of collection of words annd then choses a random word from it
    int size = sizeof(words) / sizeof(words[0]);
    int index = rand() % size;
    return words[index];
}

bool isAlreadyGuessed(string blankWord, char guess, char wrongGuesses[])
{
    // Looks though the blankWord for guess and returns true if found or looks though the entire wrongGuesses array and returns true if it doesnt reach the end of array
    if (blankWord.find(guess) != string::npos || find(wrongGuesses, wrongGuesses + 6, guess) != wrongGuesses + 6)
    {
        cout << "\n====================================" << endl
             << "  You already guessed that letter!" << endl
             << "====================================" << endl;
        pauseScreen();
        return true;
    }

    return false;
}

bool isCorrectGuess(string word, string &blankWord, char guess)
{
    bool correct = false;
    for (unsigned int i = 0; i < word.length(); i++)
    {
        // Looks through the word if the guessed character matches any charcter in the word
        if (word[i] == guess)
        {
            blankWord[i] = guess;
            correct = true;
        }
    }
    // Displays a good guess message if the guess is correct
    if (correct)
    {
        cout << "\n========================" << endl
             << "      Good Guess!" << endl
             << "========================" << endl;
        pauseScreen();
        return true;
    }

    // Deals with wrong guess
    cout << "\n====================================" << endl
         << "       Wrong Guess! Try Again!" << endl
         << "====================================" << endl;
    pauseScreen();
    return false;
}