#ifndef TEACHER_H
#define TEACHER_H
#include "University1.h"
#include <iostream>
#include <string>

using namespace std;

class Teacher : public University {
private:
    string name;
    string groups;
    string subjects;

public:
    Teacher();
    Teacher(const string& name, const string& groups, const string& subjects);
    Teacher(const Teacher& other);

    ~Teacher();

    string getName() const;
    string getGroups() const;
    string getSubjects() const;

    void setName(const string& name);
    void setGroups(const string& groups);
    void setSubjects(const string& subjects);

    void print() const override;
    void saveToFile(ofstream& outFile) const override;
    static University* loadFromFile(ifstream& inFile);
};

#endif