/*=========================

Author: Ivan Chang
Date: 7/6/23
M3 Capstone Project Design-Draft a Program: Hangman Game

=========================*/

#pragma once //Makes it so the compiler only includes the header file once
#include "Files.h" //Includes the other Files class

//defines an enum called Setting
//These represent all the different settings
enum Setting {
    eEntersInstantly, 
    eWords,
    ePhrases,
    eHints,
    eExit
};

//Define Settings class. This manages setting settings in the settings file.
class Settings : public Files {

public:

    //define useful variables
    vector<string> settingsFile;
    string filename;
    string yes;
    string no;

    //sets the settingsFile from the filepath and defines yes and no
    Settings(string filepath) {
        filename = filepath;
        openFile(filename, true);
        readFile(settingsFile);
        closeFile();
        yes = "Yes";
        no = "No";
	}

    //deconstructor method
	~Settings() {

	}

    //define array prototypes
    //isEnabled is an inline function that returns whether a setting is enabled or not
    inline bool isEnabled(int index) { return (settingsFile[index][0] == yes[0]); }
    void setSettings();

};