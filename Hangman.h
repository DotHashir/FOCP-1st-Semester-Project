#include <string>
#include "Stats.h"
#ifndef HANGMAN_H
#define HANGMAN_H

void Hangman(playerStats &stats);
void displayHangman(int attemptsLeft);
std::string getRandomWord();
bool isAlreadyGuessed(std::string blankWord, char guess, char wrongGuesses[]);
bool isCorrectGuess(std::string word, std::string &blankWord, char guess);
int CalculateWordDifficulty(string word);

#endif