#ifndef UNIVERSITY_H
#define UNIVERSITY_H
#include <fstream>

using namespace std;

class University {
public:
    virtual void print() const = 0;
    virtual void saveToFile(ofstream& outFile) const = 0;
    virtual ~University() {}
    static University* loadFromFile(ifstream& inFile);
};

#endif