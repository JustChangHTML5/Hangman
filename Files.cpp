#include "Files.h" //Include header file

/*-----------------------------------
The readFile(wordArr) takes in a 
vector of type string and returns 
nothing. wordArr is passed in by 
reference. The class this method is 
written for is called Files.

This method creates a string 
variable and reads lines of a 
predefined file to the string until 
it reaches the end of the file. It 
then records the data from the string 
variable into the wordArr vector.
-----------------------------------*/
void Files::readFile(vector<string> &wordArr) {
    string temp;
    while (!instream.eof()) {
        getline(instream, temp);
        wordArr.push_back(temp);
    }
}

/*-----------------------------------
The returnLines(lineCount) method 
takes in an integer, lineCount, and 
returns a vector of type string. The 
class this method is written for is 
called Files.

This method creates a vector of 
type string and another string 
variable. It uses the same method to 
read lines as the readFile method 
but enters the data into the vector 
defined at the start of the method 
instead of the wordArr variable. 
Instead of reading the entire file, 
it only reads up to lineCount lines. 
It ends by returning the vector.
-----------------------------------*/
vector<string> Files::returnLines(int lineCount) {
    vector<string> returnArr;
    string temp;
    for (int i = 0; i < lineCount; i++) {
        getline(instream, temp);
        returnArr.push_back(temp);
    }
    return returnArr;
}

void Files::writeToFile(vector<string> data) {
    for (int i = 0; i < data.size(); i++) {
        if (i != 0) {
            outstream << endl;
        }
        outstream << data[i];
    }
}