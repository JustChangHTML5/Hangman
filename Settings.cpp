#include <iostream>
#include "Settings.h"

extern char getArrow();

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