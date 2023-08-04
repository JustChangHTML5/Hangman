/*=========================

Author: Ivan Chang
Date: 7/6/23
M3 Capstone Project Design-Draft a Program: Hangman Game

=========================*/

/*
* This represents which line in the code contains an example to a requirement.
3. Inputs and Output (I/O): line 226
4. Variables: line 195
5. Arrays: line 198
6. File I/O: line 72
7. Iteration (loops): line 119
8. Interaction: line 232
9. Control: line: 146
*/

#include <iostream> //Adds console input functions
#include <conio.h> //Has functions to get input without having to press enter
#include <fstream> //Adds functions to read from files
#include <string> //Adds a new datatype similar to and array of chars
#include <vector> //Adds a new datatype similar to array
#include <stdlib.h> //Contains resources to clear the console
#include <cstdlib> //Helps seed the rand() function
#include <time.h> //Gives data on the current time
#include <cctype> //Library that converts char cases
#include "Files.h" //Includes file class
#include "Settings.h" //Includes settings class

using namespace std; 

//Initalize functions
void menu();
void playAgain();
void game();

string ctos(char c) {
    string s(1, c);
    return s;
}

/*-----------------------------------
The toLower(s) function takes in a 
string as an argument and returns a 
lowercased version of the string.

It does this by passing in each 
character as a parameter to the 
tolower(c) function.
-----------------------------------*/
string toLower(string s) {
    for (char& c : s) {
        if (isalpha(c)) {
            c = tolower(c);
        }
    }
    return s;
}

/*-----------------------------------
The function getWords(wordArr) takes
in an array of words and it
doesn't return anything.

The function first opens a file and
adds each word it reads inside of the
file into the array of words.
-----------------------------------*/
void getWords(vector<string>& wordArr, string filePath) {
    Files file;
    file.openFile(filePath, true);
    file.readFile(wordArr);
    file.closeFile();
}

/*-----------------------------------
The drawHangman(wrongGuesses, maxWron
gGuesses) function takes in the 
amount of wrong guesses that have 
been made and the maximum amount of 
guesses that can be made before the 
user loses. It doesn't return 
anything.

The function firsts sets the maxWrong
Guesses variable to what it reads in 
the file and prints to the console 
the correct character image using 
information from the wrongGuesses 
variable. Finally, it closes the 
file.
-----------------------------------*/
void drawHangman(int wrongGuesses, int &maxWrongGuesses) {
    static vector<string> fileArr;
    if (!(fileArr.size() > 0)) {
        //6. File I/O
        getWords(fileArr, "character.txt");
    }

    int height = stoi(fileArr[0]);
    maxWrongGuesses = stoi(fileArr[1]);
    int offset = wrongGuesses * height + 2;
    for (int i = 0; i < height; i++) {
        int index = offset + i;
        cout << fileArr[index] << endl;
    }
}

char getArrow() {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        switch (_getch()) {
            case 72:
                return 'w';
                break;
            case 80:
                return 's';
                break;
            case 75:
                return 'a';
                break;
            case 77:
                return 'd';
                break;
            case 13:
                return 'z';
                break;
            case 27:
                return 'x';
                break;
        }
    } else {
        switch (ch) {
            case 27:
                return 'x';
                break;
            case 13:
                return 'z';
                break;
        }
    }
    return char(ch);
}

/*-----------------------------------
The generateUnkownWord(curWord, known
Letters, blank, unkownLetter) takes 
in a word string, a goal string, and 
two constant strings. It doesn't 
return anything.

The function converts every letter in 
the words string to an input constant 
and every space in the string to a 
different input constant. The final 
result is what the goal string, 
knownLetters, gets set equal to.
-----------------------------------*/
void generateUnkownWord(string curWord, string &knownLetters, const string unknownLetter) {
    //7. Iteration (loops)
    for (int i = 0; i < (int)curWord.length(); i++) {
        if (isalpha(curWord[i])) {
            knownLetters += unknownLetter[0];
        } else {
            knownLetters += curWord[i];
        }
    }
}

int countLetters(string curWord) {
    int sum = 0;
    for (char c : curWord) {
        if (isalpha(c)) {
            sum++;
        }
    }
    return sum;
}

void printWord(string word) {
    for (char c : word) {
        cout << " " << c;
    }
}

void instructions() {
    vector<string> dataFile;
    Files file;
    getWords(dataFile, "hasPlayed.txt");
    string zero = "0";
    vector<string> one = {"1"};
    string temp;
    int intTemp;

    system("cls");
    if (dataFile[0][0] == zero[0]) {
        vector<string> instructions;
        getWords(instructions, "instructions.txt");
        for (int i = 0; i < instructions.size(); i++) {
            cout << instructions[i] << endl;
        }
        intTemp = _getch();
        file.openFile("hasPlayed.txt", false);
        file.writeToFile(one);
        file.closeFile();
    }
}

void menu() {
    int curScreen = 0;
    vector<string> menuFile;
    bool exit = true;
    getWords(menuFile, "menu.txt");
    instructions();

    while (exit) {
        system("cls");
        int height = stoi(menuFile[0]);
        int offset = curScreen * height + 1;
        for (int i = 0; i < height; i++) {
            int index = offset + i;
            cout << menuFile[index] << endl;
        }
        switch (getArrow()) {
            case 'w':
                break;
            case 's':
                break;
            case 'a':
                curScreen--;
                if (curScreen < 0) {
                    curScreen = 2;
                }
                break;
            case 'd':
                curScreen++;
                if (curScreen > 2) {
                    curScreen = 0;
                }
                break;
            case 'z':
                if (curScreen == 0) {
                    game();
                }
                else if (curScreen == 1) {
                    Settings settings("settings.txt");
                    settings.setSettings();
                }
                else {
                    exit = false;
                }
                break;
            case 'x':
                exit = false;
                break;
        }
    }
}

/*-----------------------------------
The playAgain() function has no 
arguments and doesn't return anything 

The function asks the user whether or 
not they want to play again and 
executes the game() function 
accordingly. It uses a while loop to 
check if the user typed in an answer 
wrong. After any functions have 
been executed, it breaks out of the 
loop.
-----------------------------------*/
void playAgain() {
    string choice;
    string options = "YN";
    bool exit = true;
    //9. Control
    while (exit) {
        getline(cin, choice);
        if (tolower(choice[0]) == tolower(options[0])) {
            game();
            exit = false;
            break;
        } else if (tolower(choice[0]) == tolower(options[1])) {
            exit = false;
            break;
        }
        else {
            cout << "Please type your choice again! (Press enter to continue)" << endl;
            // Using choice as temporary storage as it will be overwritten later
            getline(cin, choice);
        }
        cout << "Play again? [Y/N]" << endl;
    }
}

/*-----------------------------------
The game() function has no arguments 
and doesn't return anything.

The function runs everything except 
for the menu. This mainly includes 
the base hangman game.
-----------------------------------*/
void game() {
    //Seed the random function based on the time so it generates differently every time you run the program.
    srand((int)time(0));
    int intTemp;
    for (int i = 0; i < 273; i++) {
        intTemp = rand();//run random function a few times to make it more even
    }

    //Initialize getch() in case the program needs it.
    int getch();

    //Reads from the settings file so other parts of the program can do actions based on the settings.
    Settings settings("settings.txt");

    //Yes and No
    string yes = "Yes";
    string no = "No";

    //Defines a word array and generates words into the word array from the words file.
    vector<string> wordArr;
    if (settings.isEnabled(eWords)) {
        getWords(wordArr, "words.txt");
    }
    if (settings.isEnabled(ePhrases)) {
        getWords(wordArr, "phrases.txt");
    }

    //Initializes the current word and defines the known letters variables and a constant to help display the known letters.
    string curWord = wordArr[rand() % wordArr.size()];
    string knownLetters = "";
    const string unknownLetter = "_";
    //Generates the known letters.
    generateUnkownWord(curWord, knownLetters, unknownLetter);

    //Defines the current guess and a garbage variable.
    string curGuess;
    string temp;

    //Defines the amount of wrong guesses, the amount of guesses, if the current guess is right, if the user has won, and the maximum amount of wrong guesses.
    //4. Variables
    int wrongGuesses = 0;
    int guesses = 0;
    vector<string> rightLetters; // 5. Arrays
    vector<string> wrongLetters;
    bool curGuessRight = false;
    bool hasWon = false;
    int maxWrongGuesses = 9;
    int hintsUsed = 0;

    bool exitedByWill = false; //If true, it beans that they used the equals button to finish the game instead of completing it

    /*The main loop lets the user make multiple guesses until they have made too many wrong ones
    or have guessed the word and finished the game.
    The main loop also displays the known letters and the hangman's current state.
    The main while loop stops if the user has made too many wrong guesses or has won.
    The user cannot make the same guess twice*/
    while (wrongGuesses < maxWrongGuesses && hasWon == false) {
        system("cls");
        cout << "Wrong Guesses: ";
        for (int i = 0; i < wrongLetters.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << wrongLetters[i];
        }
        cout << endl;
        cout << "Correct Guesses: ";
        for (int i = 0; i < rightLetters.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << rightLetters[i];
        }
        //3. Inputs and Output (I/O)
        cout << endl;
        cout << endl;
        drawHangman(wrongGuesses, maxWrongGuesses);
        cout << endl;
        cout << "How many letters in Word/Phrase: " << countLetters(curWord) << endl;
        cout << "Amount of letters remaining in Word/Phrase: " << countLetters(curWord) - countLetters(knownLetters) << endl;
        cout << endl;
        cout << "Known Letters In The Word/Phrase:";
        printWord(knownLetters);
        cout << endl << endl;
        cout << "Enter your guess:\n" << endl;
        if (settings.isEnabled(eEntersInstantly)) {
            curGuess = getch();
            if (curGuess != "?" && curGuess != "=") {
                if (!('a' <= curGuess[0] && curGuess[0] <= 'z' || 'A' <= curGuess[0] && curGuess[0] <= 'Z')) {
                    curGuess = "~"; //The user did something they shouldn't have
                }
            }
        } else {
            getline(cin, curGuess);
        }
        //8. Interaction
        if (curGuess == "=") {
            exitedByWill = true;
            break;
        }
        if (curGuess == "?" && settings.isEnabled(eHints)) {
            for (int i = 0; i < knownLetters.length(); i++) {
                if (knownLetters[i] == unknownLetter[0]) {
                    hintsUsed++;
                    rightLetters.push_back(toLower(ctos(curWord[i])));
                    for (int j = 0; j < (int)curWord.length(); j++) {
                        if (tolower(curWord[j]) == tolower(curWord[i])) {
                            knownLetters[j] = curWord[j];
                        }
                    }
                    break;
                }
            }
        } else if (curGuess.length() == 1 && isalpha(curGuess[0]) || curGuess.length() == knownLetters.length()) {
            if (curGuess.length() == 1 || curGuess.length() == knownLetters.length()) {
                guesses++;
                curGuessRight = false;
                if (curGuess.length() == 1) {
                    if (find(rightLetters.begin(), rightLetters.end(), toLower(curGuess)) == rightLetters.end() && find(wrongLetters.begin(), wrongLetters.end(), toLower(curGuess)) == wrongLetters.end()) {
                        for (int i = 0; i < (int)curWord.length(); i++) {
                            if (tolower(curWord[i]) == tolower(curGuess[0])) {
                                knownLetters[i] = curWord[i];
                                if (!curGuessRight) {
                                    rightLetters.push_back(toLower(curGuess));
                                }
                                curGuessRight = true;
                            }
                        }
                    }
                    else {
                        cout << "You cannot guess the same letter twice (Press enter to continue)" << endl;
                        getline(cin, temp);
                        continue;
                    }
                }
                else {
                    if (toLower(curGuess) == toLower(curWord)) {
                        knownLetters = curGuess;
                        curGuessRight = true;
                        rightLetters.push_back(toLower(curGuess)); // useless because the game ends anyways so nobody will get to see this
                    }
                }
                if (!curGuessRight) {
                    wrongLetters.push_back(toLower(curGuess));
                    wrongGuesses++;
                }
            }
        } else {
            cout << "Invalid guess, try again (Press enter to continue)" << endl;
            getline(cin, temp);
        } 
        if (knownLetters == curWord) {
            hasWon = true;
        }
    }

    //Clears the console and displays information based on whether the user won or lost.
    system("cls");

    //Tells player data and asks if they want to play again.
    if (hasWon) {
        drawHangman(wrongGuesses, maxWrongGuesses);
        cout << "Known Letters: " << knownLetters << endl;
        cout << "Final Word: " << curWord << endl;
        if (settings.isEnabled(eHints)) {
            cout << "Hints Used: " << hintsUsed << "\n" << endl;
        }
        cout << "Congratulations! You have completed the game!\n" << "You won with: " << wrongGuesses << " wrong guesses, " << guesses - wrongGuesses << " correct guesses, and " << guesses << " total guesses.\n" << endl;
        cout << "Play Again? [Y/N]" << endl;
    } else {
        drawHangman(wrongGuesses, maxWrongGuesses);
        cout << "Known Letters: " << knownLetters << endl;
        cout << "Final Word: " << curWord << endl;
        if (settings.isEnabled(eHints)) {
            cout << "Hints Used: " << hintsUsed << "\n" << endl;
        }
        cout << "You lost. Better luck next time!\n" << "You lost with: " << wrongGuesses << " wrong guesses, " << guesses - wrongGuesses << " correct guesses, and " << guesses << " total guesses.\n" << endl;
        cout << "Play Again? [Y/N]" << endl;
    }
    
    //check if user wants to play again
    if (exitedByWill == false) {
        playAgain();
    }
}

int main() {
    menu();
    //game();
    return 0;
}