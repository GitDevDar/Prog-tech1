#include "University1.h"
#include "Student1.h"
#include "Teacher1.h"
#include "AdminStaff1.h"
#include <stdexcept>

University* University::loadFromFile(ifstream& inFile) {
    char type;
    inFile.read(&type, sizeof(type));
    switch (type) {
        case 'S':
            return Student::loadFromFile(inFile);
        case 'T':
            return Teacher::loadFromFile(inFile);
        case 'A':
            return AdminStaff::loadFromFile(inFile);
        default:
            throw runtime_error("Unknown object type when loading from file.");
    }
}
