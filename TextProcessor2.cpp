#include "TextProcessor2.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

bool isNumber(const char* str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

char* TextProcessor::swapAdjacentWords(const char* line) {
    size_t lineLength = strlen(line) + 1;
    char* buffer = new char[lineLength];
    strcpy(buffer, line);  

    size_t maxWords = 16;
    char** words = new char* [maxWords];
    size_t wordCount = 0;

    char* token = strtok(buffer, " \t\n");
    while (token) {
        if (wordCount == maxWords) {
            size_t newMaxWords = maxWords * 2;
            char** temp = new char* [newMaxWords];
            memcpy(temp, words, maxWords * sizeof(char*));
            delete[] words;
            words = temp;
            maxWords = newMaxWords;
        }
        words[wordCount++] = token;
        token = strtok(nullptr, " \t\n");
    }

    for (size_t i = 0; i + 1 < wordCount; i += 2) {
        char* temp = words[i];
        words[i] = words[i + 1];
        words[i + 1] = temp;
    }


    size_t resultLength = 0;
    for (size_t i = 0; i < wordCount; ++i) {
        resultLength += strlen(words[i]) + 1; 
    }
    
    char* result = new char[resultLength];
    result[0] = '\0';  

    for (size_t i = 0; i < wordCount; ++i) {
        strcat(result, words[i]);  
        if (i + 1 < wordCount) {
            strcat(result, " ");  
        }
    }

    delete[] words;
    delete[] buffer;

    return result;
}

void TextProcessor::processorFile(const char* inputFile) {
    ifstream inFile(inputFile);

    if (!inFile) {
        cerr << "Error. Could not open file " << inputFile << "\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        char* processedLine = swapAdjacentWords(line.c_str());
        cout << processedLine << endl;
        delete[] processedLine;
    }

    inFile.close();
}

void TextProcessor::display(const char* inputFile) {
    ifstream inFile(inputFile);

    if (!inFile) {
        cerr << "Error. Could not open file " << inputFile << "\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}
