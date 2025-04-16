#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Invalid number of arguments." << endl;
        return 1;
    }

    string fileName = argv[1];
    string wordToSearch = argv[2];
    string fileExtension = ".txt";

    fileName += fileExtension;

    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Error opening the file. Please check if the file exists and try again." << endl;
        return 1;
    }

    int lineNumber = 1; 
    string line;
    bool found = false; 

    while (getline(inputFile, line)) {
        size_t pos = 0;
        while ((pos = line.find(wordToSearch, pos)) != string::npos) {
            cout << "The word '" << wordToSearch << "' appeared in line number: " << lineNumber << endl;
            pos += wordToSearch.length(); 
            found = true;
        }
        lineNumber++;
    }

    inputFile.close();

    if (!found) {
        cout << "The word '" << wordToSearch << "' was not found in the file '" << fileName << "'." << endl;
    }

    return 0;
}