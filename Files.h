/*=========================

Author: Ivan Chang
Date: 7/6/23
M3 Capstone Project Design-Draft a Program: Hangman Game

=========================*/

#pragma once //Makes it so the compiler only includes the header file once
#include <fstream> //Adds functions to read from files
#include <string> //Adds a new datatype similar to and array of chars
#include <vector> //Adds a new datatype similar to array

using namespace std;

//Defines Files class. This manages reading and writing to and from files.
class Files {

public:

	//fstream variables
	ifstream instream;
	ofstream outstream;

	//current open file data
	string curOpenFile;
	string curFilePath; 

	//constructor method
	Files() {

	}
	
	//defines the prototype method openFile which opens a file
	//using a filepath to the instream variable defined earlier
	//the boolean readWrite determines if the funtion reads or 
	//writes from the file.
	void openFile(string filepath, bool readWrite) {
		curFilePath = filepath;
		if (readWrite) {
			instream.open(curFilePath);
		} else {
			outstream.open(curFilePath);
		}
	}

	//closes any files in the instream and outsream variables
	void closeFile() {
		if (instream.is_open()) {
			instream.close();
		}
		if (outstream.is_open()) {
			outstream.close();
		}
	}
	
	//deconstructor method
	~Files() {

	}

	//define array prototypes that will have stuff written into them in the 
	//cpp file.
	void readFile(vector<string>& wordArr);
	vector<string> returnLines(int lineCount);
	void writeToFile(vector<string> data);

};