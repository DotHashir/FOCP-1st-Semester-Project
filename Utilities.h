#pragma once
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

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
    input = tolower(input);
    return true;
}

inline char getCharacterInput(string prompt)
{
    char input;
    while (true)
    {
        cout << prompt;

        if (isCorrectCharacterInput(input))
            return input;
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