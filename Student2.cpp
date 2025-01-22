#include "Student2.h"
#include "Exceptions2.h"

Student::Student() : surname("Unknown"), grades(nullptr), gradesCount(0) {
    cout << "Default constructor for Student called: " << this << "\n";
}

Student::Student(const string& surname, const float* grades, int gradesCount) : surname(surname), gradesCount(gradesCount) {
    if (gradesCount <= 0) {
        throw StudentException("Incorrect number of grades");
    }

    this->grades = new float[gradesCount];
    for (int i = 0; i < gradesCount; ++i) {
        this->grades[i] = grades[i];
    }
    cout << "The constructor with parameters for Student is called:" << this << "\n";
}

Student::Student(const Student& other) : surname(other.surname), gradesCount(other.gradesCount) {
    grades = new float[gradesCount];
    for (int i = 0; i < gradesCount; ++i) {
        grades[i] = other.grades[i];
    } 
    cout << "The copy constructor for Student is called: " << this << "\n";
}

Student::~Student() {
    cout << "The destructor for Student is called: " << this << "\n";
    delete[] grades;
}

string Student::getSurname() const {
    return surname;
}

void Student::setSurname(const string& surname) {
    this->surname = surname;
}

void Student::setGrades(const float* grades, int gradesCount) {
    if (gradesCount <= 0) {
        throw StudentException("The number of grades must be positive");
    }

    delete[] this->grades;
    this->gradesCount = gradesCount;
    this->grades = new float[gradesCount];
    for (int i = 0; i < gradesCount; ++i) {
        this->grades[i] = grades[i];
    }
}

void Student::getGrades() const {
    for (int i = 0; i < gradesCount; ++i) {
        cout << grades[i] << " ";
    }
    cout << endl;
}

double Student::getAverageGrade() const {
    if (gradesCount == 0) return 0.0;
    float sum = 0;
    for (int i = 0; i < gradesCount; ++i) {
        sum += grades[i];
    }
    return static_cast<double>(sum) / gradesCount;
}

ostream& operator<<(ostream& out, const Student& student) {
    out << "Surname and initials: " << student.surname << "\n";
    out << "Grades: ";
    for (int i = 0; i < student.gradesCount; ++i) {
        out << student.grades[i] << " ";
    }
    out << "\nAverage grade: " << student.getAverageGrade() << "\n";
    return out;
}

istream& operator>>(istream& in, Student& student) {
    cout << "Enter surname and initials: ";
    getline(in, student.surname);

    cout << "Enter number of grades: ";
    in >> student.gradesCount;

    if (in.fail() || student.gradesCount <= 0) {
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InputException("Error: incorrect number of grades");
    }

    delete[] student.grades;
    student.grades = new float[student.gradesCount];

    cout << "Enter grades separated by spaces: ";
    for (int i = 0; i < student.gradesCount; ++i) {
        in >> student.grades[i];
        if (in.fail()) {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InputException("Error entering grades");
        }
    }

    in.ignore(numeric_limits<streamsize>::max(), '\n');
    return in;
}
