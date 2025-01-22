#ifndef STUDENT_H
#define STUDENT_H
#include "University1.h"
#include <iostream>
#include <string>

using namespace std;

class Student : public University {
private:
    string name;
    string group;
    string specialty;
    int course;
    double GPA;

public:
    Student();
    Student(const string& name, const string& group, const string& specialty, int course, double GPA);
    Student(const Student& other);

    ~Student();

    string getName() const;
    string getGroup() const;
    string getSpecialty() const;
    int getCourse() const;
    double getGPA() const;

    void setName(const string& name);
    void setGroup(const string& group);
    void setSpecialty(const string& specialty);
    void setCourse(int course);
    void setGPA(double GPA);

    void print() const override;
    void saveToFile(ofstream& outFile) const override;
    static University* loadFromFile(ifstream& inFile);
};

#endif