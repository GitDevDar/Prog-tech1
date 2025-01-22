#include "Teacher1.h"
#include <fstream>

using namespace std;

Teacher::Teacher() {
    cout << "The default Teacher constructor is called" << endl;
}

Teacher::Teacher(const string& name, const string& groups, const string& subjects) : name(name), groups(groups), subjects(subjects) {
    cout << "The Teacher constructor is called with parameters" << endl;
}

Teacher::Teacher(const Teacher& other) : name(other.name), groups(other.groups), subjects(other.subjects) {
    cout << "The copy constructor Teacher is called" << endl;
}

Teacher::~Teacher() {
    cout << "Teacher destructor called" << endl;
}

string Teacher::getName() const {
    return name;
}

string Teacher::getGroups() const {
    return groups;
}

string Teacher::getSubjects() const {
    return subjects;
}

void Teacher::setName(const string& name) {
    this->name = name;
}

void Teacher::setGroups(const string& groups) {
    this->groups = groups;
}

void Teacher::setSubjects(const string& subjects) {
    this->subjects = subjects;
}

void Teacher::print() const {
    cout << "Teacher: " << name << ", Groups: " << groups << ", Subjects: " << subjects << endl;
}

void Teacher::saveToFile(ofstream& outFile) const {
    outFile << name << ";" << groups << ";" << subjects << endl;
}

University* Teacher::loadFromFile(ifstream& inFile) {
    string name, groups, subjects;
    
    getline(inFile, name, ';');
    getline(inFile, groups, ';');
    getline(inFile, subjects);

    cout << "Teacher reinstated: " << name << endl;
    return new Teacher(name, groups, subjects);
}