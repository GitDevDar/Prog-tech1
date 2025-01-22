#include "Group2.h"
#include "Exceptions2.h"

using namespace std;

Group::Group() : groupNumber(0), students(nullptr), studentCount(0) {
    cout << "Called Default Constructor for group (address: " << this << ")\n";
}

Group::Group(int groupNumber) : groupNumber(groupNumber), students(nullptr), studentCount(0) {
    if (groupNumber <= 0) {
        throw GroupException("Error. Group number must be positive.");
    }
    cout << "Called Constructor with parameters for group No." << groupNumber << " (address: " << this << ")\n";
}

Group::Group(const Group& other) : groupNumber(other.groupNumber), studentCount(other.studentCount) {
    cout << "Called Copy Constructor for group No. " << other.groupNumber << " (address: " << this << ")\n";
    if (other.studentCount > 0) {
        students = new Student * [other.studentCount];
        for (int i = 0; i < other.studentCount; ++i) {
            students[i] = new Student(*other.students[i]);
        }
    }
    else {
        students = nullptr;
    }
}

Group::~Group() {
    for (int i = 0; i < studentCount; ++i) {
        delete students[i];
    }
    delete[] students;
    cout << "Called destructor for group No. " << groupNumber << " (address: " << this << ")\n";
}

int Group::getGroupNumber() const {
    return groupNumber;
}

void Group::setGroupNumber(int number) {
    if (number <= 0) {
        throw GroupException("Error. Group number must be positive.");
    }
    groupNumber = number;
}

void Group::addStudent(Student* student) {
    if (!student) {
        throw GroupException("Error. Pointer to student cannot be null.");
    }

    Student** newStudents = new Student * [studentCount + 1];
    for (int i = 0; i < studentCount; ++i) {
        newStudents[i] = students[i];
    }
    newStudents[studentCount] = student;
    delete[] students;
    students = newStudents;
    ++studentCount;

    cout << "The student was successfully added to the group No. " << groupNumber << ".\n";
}

void Group::addStudentAtPosition(Student* student, int position) {
    if (!student) {
        throw GroupException("Error. Pointer to student cannot be null.");
    }
    if (position < 0 || position > studentCount) {
        throw GroupException("Error. Incorrect position for adding a student.");
    }
    Student** newStudents = new Student * [studentCount + 1];
    for (int i = 0, j = 0; i < studentCount + 1; ++i) {
        if (i == position) {
            newStudents[i] = student;
        }
        else {
            newStudents[i] = students[j++];
        }
    }
    delete[] students;
    students = newStudents;
    ++studentCount;

    cout << "Student added on position " << position + 1 << " in group No. " << groupNumber << ".\n";
}

void Group::removeStudent(int index) {
    if (index < 0 || index >= studentCount) {
        throw GroupException("Error. Incorrect student index.");
    }
    delete students[index];
    for (int i = index; i < studentCount - 1; ++i) {
        students[i] = students[i + 1];
    }
    --studentCount;
    
    cout << "Student successfully removed from group No. " << groupNumber << ".\n";
}

void Group::showStudents() const {
    if (studentCount == 0) {
        cout << "Group No. " << groupNumber << " empty.\n";
        return;
    }
    
    cout << "Group No. " << groupNumber << ":\n";
    for (int i = 0; i < studentCount; ++i) {
        cout << " Student No. " << i + 1 << ": " << students[i]->getSurname() << ", Average grade: " << students[i]->getAverageGrade() << "\n";
    } 
}

double Group::getAverageGrade() const {
    if (studentCount == 0) {
        throw GroupException("Error. Unable to calculate Average grade for group without students.");
    }
    double total = 0.0;
    for (int i = 0; i < studentCount; ++i) {
        total += students[i]->getAverageGrade();
    }
    return total / studentCount;
}

Student* Group::getStudent(int index) const{
    if (index < 0 || index >= studentCount) {
        throw GroupException("Error. Incorrect student index.");
    }
    return students[index];
}

int Group::getStudentCount() const {
    return studentCount;
}
