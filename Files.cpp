#include "Files.h"

void Files::readFile(vector<string>& wordArr) {
    string temp;
    while (!instream.eof()) {
        getline(instream, temp);
        wordArr.push_back(temp);
    }
}

vector<string> Files::returnLines(int lineCount) {
    vector<string> returnArr;
    string temp;
    for (int i = 0; i < lineCount; i++) {
        getline(instream, temp);
        returnArr.push_back(temp);
    }
    return returnArr;
}