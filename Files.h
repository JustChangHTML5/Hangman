#pragma once //Makes it so the compiler only includes the header file once
#include <fstream> //Adds functions to read from files
#include <string> //Adds a new datatype similar to and array of chars
#include <vector> //Adds a new datatype similar to array

using namespace std;

//Define Files class. This manages reading files. I have not yet added features to write to files.
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
	//using a filepath to the instream variable defined early
	void openFile(string filepath) {
		curFilePath = filepath;
		instream.open(curFilePath);
		//outstream.open(curFilePath);
	}

	//closes any files in the instream variable
	void closeFile() {
		instream.close();
		//outstream.close();
	}

	//define array prototypes that will have stuff written into them in the 
	//cpp file.
	void readFile(vector<string>& wordArr);
	vector<string> returnLines(int lineCount);
	
	//deconstructor method
	~Files() {

	}

};