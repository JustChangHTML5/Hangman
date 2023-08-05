/*=========================

Author: Ivan Chang
Date: 7/6/23
M3 Capstone Project Design-Draft a Program: Hangman Game

=========================*/

#include <iostream> //include iostream
#include "Settings.h" //include settings header file

extern char getArrow(); //gets the getArrow() function from the main Hangman.cpp

/*-----------------------------------
The setSettings() function takes in 
nothing and returns nothing. The class 
this method is written for is called 
Settings.

This method reads from the settings 
file and creates a hardcoded UI that 
helps the user change things in the 
settings file. The user can control a 
pointer to select which settings they 
want to change.
-----------------------------------*/
void Settings::setSettings() {
    int pointer = eEntersInstantly;
    bool exit = true;
    while (exit) {
        system("cls");
        cout << "Guess Enters Instantly: " << settingsFile[eEntersInstantly];

        if (pointer == eEntersInstantly) {
            cout << " <--";
        }
        cout << endl;
        cout << "Words: " << settingsFile[eWords];
        if (pointer == eWords) {
            cout << " <--";
        }
        cout << endl;
        cout << "Phrases: " << settingsFile[ePhrases];
        if (pointer == ePhrases) {
            cout << " <--";
        }
        cout << endl;
        cout << "Hints (? to activate): " << settingsFile[eHints];
        if (pointer == eHints) {
            cout << " <--";
        }
        cout << endl;
        cout << "Exit?";
        if (pointer == eExit) {
            cout << " <--";
        }
        cout << endl;
        switch (getArrow()) {
            case 'w':
                pointer--;
                if (pointer < eEntersInstantly) {
                    pointer = eExit;
                }
                break;
            case 's':
                pointer++;
                if (pointer > eExit) {
                    pointer = eEntersInstantly;
                }
                break;
            case 'z':
                if (pointer == eWords) {
                    if (isEnabled(pointer)) {
                        settingsFile[ePhrases] = yes;
                    }
                } 
                if (pointer == ePhrases) {
                    if (isEnabled(pointer)) {
                        settingsFile[eWords] = yes;
                    }
                }
                if (pointer < eExit) {
                    if (isEnabled(pointer)) {
                        settingsFile[pointer] = no;
                    }
                    else {
                        settingsFile[pointer] = yes;
                    }
                }
                else {
                    exit = false;
                    openFile(filename, false);
                    writeToFile(settingsFile);
                    closeFile();
                }
                break;
            case 'x':
                exit = false;
                break;
        }
    }
}