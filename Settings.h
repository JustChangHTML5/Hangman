#pragma once
#include "Files.h"

enum Setting {
    eEntersInstantly, 
    eWords,
    ePhrases,
    eHints,
    eExit
};

class Settings : public Files {

public:

    vector<string> settingsFile;
    string filename;
    string yes;
    string no;

    Settings(string filepath) {
        filename = filepath;
        openFile(filename, true);
        readFile(settingsFile);
        closeFile();
        yes = "Yes";
        no = "No";
	}

	~Settings() {

	}

    inline bool isEnabled(int index) { return (settingsFile[index][0] == yes[0]); }
    void setSettings();

};