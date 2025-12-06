#include <string>
#ifndef HANGMAN_H
#define HANGMAN_H

void Hangman();
void displayHangman(int attemptsLeft);
std::string getRandomWord();
bool isAlreadyGuessed(std::string blankWord, char guess, char wrongGuesses[]);
bool isCorrectGuess(std::string word, std::string &blankWord, char guess);

#endif