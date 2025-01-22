#include "Student1.h"
#include <fstream>

using namespace std;

Student::Student() : course(0), GPA(0.0) {
    cout << "Default Student constructor called" << endl;
}

Student::Student(const string& name, const string& group, const string& specialty, int course, double GPA) : name(name), group(group), specialty(specialty), course(course), GPA(GPA) {
    cout << "The Student constructor is called with parameters" << endl;
}

Student::Student(const Student& other) : name(other.name), group(other.group), specialty(other.specialty), course(other.course), GPA(other.GPA) {
    cout << "The Student copy constructor is called" << endl;
}

Student::~Student() {
    cout << "Student destructor called" << endl;
}

string Student::getName() const {
    return name;
}

string Student::getGroup() const {
    return group;
}

string Student::getSpecialty() const {
    return specialty;
}

int Student::getCourse() const {
    return course;
}

double Student::getGPA() const {
    return GPA;
}

void Student::setName(const string& name) {
    this->name = name;
}

void Student::setGroup(const string& group) {
    this->group = group;
}

void Student::setSpecialty(const string& specialty) {
    this->specialty = specialty;
}

void Student::setCourse(int course) {
    this->course = course;
}

void Student::setGPA(double GPA) {
    this->GPA = GPA;
}

void Student::print() const {
    cout << "Student: " << name << ", Group: " << group << ", Specialty: " << specialty << ", Course: " << course << ", GPA: " << GPA << endl;
}

void Student::saveToFile(ofstream& outFile) const {
    outFile << name << ";" << group << ";" << specialty << ";" << course << ";" << GPA << endl;
}

University* Student::loadFromFile(ifstream& inFile) {
    string name, group, specialty;
    int course;
    double GPA;

    getline(inFile, name, ';');
    getline(inFile, group, ';');
    getline(inFile, specialty, ';');
    inFile >> course;
    inFile.ignore();
    inFile >> GPA;
    inFile.ignore();

    cout << "Reinstated student: " << name << endl;
    return new Student(name, group, specialty, course, GPA);
}