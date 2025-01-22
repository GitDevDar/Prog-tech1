#include "AdminStaff1.h"
#include <fstream>

using namespace std;

AdminStaff::AdminStaff() {
    cout << "Default AdminStaff constructor called" << endl;
}

AdminStaff::AdminStaff(const string& name, const string& position, const string& phone, const string& responsibility) : name(name), position(position), phone(phone), responsibility(responsibility) {
    cout << "The AdminStaff constructor is called with parameters" << endl;
}

AdminStaff::AdminStaff(const AdminStaff& other) : name(other.name), position(other.position), phone(other.phone), responsibility(other.responsibility) {
    cout << "AdminStaff copy constructor called" << endl;
}

AdminStaff::~AdminStaff() {
    cout << "AdminStaff destructor called" << endl;
}

string AdminStaff::getName() const {
    return name;
}

string AdminStaff::getPosition() const {
    return position;
}

string AdminStaff::getPhone() const {
    return phone;
}

string AdminStaff::getResponsibility() const {
    return responsibility;
}

void AdminStaff::setName(const string& name) {
    this->name = name;
}

void AdminStaff::setPosition(const string& position) {
    this->position = position;
}

void AdminStaff::setPhone(const string& phone) {
    this->phone = phone;
}

void AdminStaff::setResponsibility(const string& resposibility) {
    this->responsibility = responsibility;
}

void AdminStaff::print() const {
    cout << "Administrative staff: " << name << ", Job title: " << position << ", Phone number: " << phone << ", Area of responsibility: " << responsibility << endl;
}

void AdminStaff::saveToFile(ofstream& outFile) const {
    outFile << name << ";" << position << ";" << phone << ";" << responsibility << endl;
}

University* AdminStaff::loadFromFile(ifstream& inFile) {
    string name, position, phone, responsibility;

    getline(inFile, name, ';');
    getline(inFile, position, ';');
    getline(inFile, phone, ';');
    getline(inFile, responsibility);

    cout << "Administrative staff reinstated: " << name << endl;

    return new AdminStaff(name, position, phone, responsibility);
}