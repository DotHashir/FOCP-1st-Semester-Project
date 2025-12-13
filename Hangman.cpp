#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include "utilities.h"
#include "Hangman.h"
using namespace std;

const int MAX_LIVES = 6;

void Hangman()
{
    srand(time(0));

    string word = getRandomWord();

    // Sets a blanck word equal to the length of the word to be guessed
    string blankWord(word.length(), '_');

    char wrongGuesses[MAX_LIVES] = {};
    int wrongGuessesCount = 0;

    int attemptsLeft = MAX_LIVES;
    char guess;

    cout << "==============================" << endl
         << "     Welcome to Hangman!" << endl
         << "==============================" << endl;
    pauseScreen();

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
        for (int i = 0; i < MAX_LIVES; i++)
        {
            if (wrongGuesses[i] != '\0')
                cout << wrongGuesses[i] << " ";
        }

        cout << "\nAttempts remaining: " << attemptsLeft << endl;

        while (true)
        {
            guess = getCharacterInput("Enter your guess(0 to exit): ");

            // Ends the game if user enters 0
            if (guess == '0')
            {
                cout << "======================================================" << endl
                     << "You exited the game!" << endl
                     << "======================================================" << endl;
                pauseScreen();
                return;
            }

            if (!isalpha(guess))
                cout << "Please enter a valid letter (a-z)" << endl;
            else
                break;
        }

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
        cout << "\n  Congratulations! You guessed the word right!: " << GREEN << word << RESET << endl;
    else
        cout << "\n  You could not guess right! The word was: " << RED << word << RESET << endl;

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
    if (blankWord.find(guess) != string::npos || find(wrongGuesses, wrongGuesses + MAX_LIVES, guess) != wrongGuesses + MAX_LIVES)
    {
        cout << "\n====================================" << endl
             << YELLOW << "  You already guessed that letter!" << RESET << endl
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
             << GREEN << "      Good Guess!" << RESET << endl
             << "========================" << endl;
        pauseScreen();
        return true;
    }

    // Deals with wrong guess
    cout << "\n====================================" << endl
         << RED << "       Wrong Guess! Try Again!" << RESET << endl
         << "====================================" << endl;
    pauseScreen();
    return false;
}