#pragma once
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string BG_DARK = "\033[40m";  // Dark square background
const string BG_LIGHT = "\033[47m"; // Light square background
const string RESET = "\033[0m";

inline bool isCorrectIntegerInput(int &input)
{
    cin >> input;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    else if (cin.peek() != '\n')
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

inline int getIntegerInput(string prompt)
{
    int input;
    while (true)
    {
        cout << prompt;

        if (isCorrectIntegerInput(input))
            return input;
        else
            cout << "Error: Wrong input" << endl;
    }
}

inline bool isCorrectCharacterInput(char &input)
{
    cin >> input;

    if (cin.peek() != '\n')
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

inline char getCharacterInput(string prompt)
{
    char input;
    while (true)
    {
        cout << prompt;

        if (isCorrectCharacterInput(input))
            return towlower(input);
        else
            cout << "Error: Wrong input" << endl;
    }
}

inline void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void pauseScreen()
{
    cout << "Press enter key to cotinue...";
    cin.get();
}