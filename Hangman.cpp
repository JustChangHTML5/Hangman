/*=========================

Author: Ivan Chang
Date: 7/6/23
M3 Capstone Project Design-Draft a Program: Hangman Game

=========================*/
#include <iostream> //Adds console input functions
#include <fstream> //Adds functions to read from files
#include <string> //Adds a new datatype similar to and array of chars
#include <vector> //Adds a new datatype similar to array
#include <stdlib.h> //Contains resources to clear the console
#include <cstdlib> //Helps seed the rand() function
#include <time.h> //Gives data on the current time
#include <cctype> //Library that converts char cases
#include "Files.h" //Includes file class

using namespace std; 

//Initalize functions
void playAgain(); 
void game();

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
        c = tolower(c);
    }
    return s;
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
        Files file;
        file.openFile("character.txt");
        file.readFile(fileArr);
        file.closeFile();
    }

    int height = stoi(fileArr[0]);
    maxWrongGuesses = stoi(fileArr[1]);
    int offset = wrongGuesses * height + 2;
    for (int i = 0; i < height; i++) {
        int index = offset + i;
        cout << fileArr[index] << endl;
    }
}

/*-----------------------------------
The function getWords(wordArr) takes 
in an array of words and it 
doesn't return anything.

The function first opens a file and 
adds each word it reads inside of the 
file into the array of words.
-----------------------------------*/
void getWords(vector<string> &wordArr) {
    Files file;
    file.openFile("words.txt");
    file.readFile(wordArr);
    file.closeFile();
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
void generateUnkownWord(string curWord, string &knownLetters, const string blank, const string unknownLetter) {
    for (int i = 0; i < (int)curWord.length(); i++) {
        if (curWord[i] != blank[0]) {
            knownLetters += unknownLetter[0];
        } else {
            knownLetters += blank[0];
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
    string options = "yn";
    bool exit = true;
    while (exit) {
        getline(cin, choice);
        if (tolower(choice[0]) == tolower(options[0])) {
            game();
            exit = false;
            break;
        } else if (tolower(choice[0] == tolower(options[1]))) {
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

    //Defines a word array and generates words into the word array from the words file.
    vector<string> wordArr;
    getWords(wordArr);

    //Initializes the current word and defines the known letters variables and two constants to help display the known letters.
    string curWord = wordArr[rand() % wordArr.size()];
    string knownLetters = "";
    const string blank = " ";
    const string unknownLetter = "_";
    //Generates the known letters.
    generateUnkownWord(curWord, knownLetters, blank, unknownLetter);

    //Defines the current guess and a garbage variable.
    string curGuess;
    string temp;

    //Defines the amount of wrong guesses, the amount of guesses, if the current guess is right, if the user has won, and the maximum amount of wrong guesses.
    int wrongGuesses = 0;
    int guesses = 0;
    vector<char> rightLetters;
    vector<char> wrongLetters;
    bool curGuessRight = false;
    bool hasWon = false;
    int maxWrongGuesses = 6;

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
        cout << endl;
        drawHangman(wrongGuesses, maxWrongGuesses);
        cout << "Known Letters In The Word: " << knownLetters << "\n" << endl;
        cout << "Enter your guess:\n" << endl;
        getline(cin, curGuess);
        if (curGuess.length() == 1 || curGuess.length() == knownLetters.length()) {
            guesses++;
            curGuessRight = false;
            if (curGuess.length() == 1) {
                if (find(rightLetters.begin(), rightLetters.end(), tolower(curGuess[0])) == rightLetters.end() && find(wrongLetters.begin(), wrongLetters.end(), tolower(curGuess[0])) == wrongLetters.end()) {
                    for (int i = 0; i < (int)curWord.length(); i++) {
                        if (tolower(curWord[i]) == tolower(curGuess[0])) {
                            knownLetters[i] = curWord[i];
                            if (!curGuessRight) {
                                rightLetters.push_back(tolower(curGuess[0]));
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
            } else {
                if (toLower(curGuess) == toLower(curWord)) {
                    curGuessRight = true;
                }
            } if (!curGuessRight) {
                wrongLetters.push_back(tolower(curGuess[0]));
                wrongGuesses++;
            }
        } else {
            cout << "Invalid guess, try again (Press enter to continue)" << endl;
            getline(cin, temp);
        } if (knownLetters == curWord) {
            hasWon = true;
        }
    }

    //Clears the console and displays information based on whether the user won or lost.
    system("cls");

    //Tells player data and asks if they want to play again.
    if (hasWon) {
        drawHangman(wrongGuesses, maxWrongGuesses);
        cout << "Known Letters: " << knownLetters << endl;
        cout << "Final Word: " << curWord << "\n" << endl;
        cout << "Congratulations! You have completed the game!\n" << "You won with: " << wrongGuesses << " wrong guesses, " << guesses - wrongGuesses << " correct guesses, and " << guesses << " total guesses.\n" << endl;
        cout << "Play Again? [Y/N]" << endl;
    } else {
        drawHangman(wrongGuesses, maxWrongGuesses);
        cout << "Known Letters: " << knownLetters << endl;
        cout << "Final Word: " << curWord << "\n" << endl;
        cout << "You lost. Better luck next time!\n" << "You lost with: " << wrongGuesses << " wrong guesses, " << guesses - wrongGuesses << " correct guesses, and " << guesses << " total guesses.\n" << endl;
        cout << "Play Again? [Y/N]" << endl;
    }
    
    //check if user wants to play again
    playAgain();
}

int main() {
    game();
    return 0;
}