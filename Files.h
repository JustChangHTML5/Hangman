#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Files {
public:
	ifstream instream;
	ofstream outstream;
	string curOpenFile;
	string curFilePath; 

	Files() {

	}
	
	void openFile(string filepath) {
		curFilePath = filepath;
		instream.open(curFilePath);
		//outstream.open(curFilePath);
	}

	void closeFile() {
		instream.close();
		//outstream.close();
	}

	void readFile(vector<string>& wordArr);
	vector<string> returnLines(int lineCount);
	
	~Files() {

	}
};