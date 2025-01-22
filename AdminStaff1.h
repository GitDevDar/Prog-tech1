#ifndef ADMINSTAFF_H
#define ADMINSTAFF_H
#include "University1.h"
#include <iostream>
#include <string>

using namespace std;

class AdminStaff : public University {
private:
    string name;
    string position;
    string phone;
    string responsibility;

public:
    AdminStaff();
    AdminStaff(const string& name, const string& position, const string& phone, const string& responsibility);
    AdminStaff(const AdminStaff& other);

    ~AdminStaff();

    string getName() const;
    string getPosition() const;
    string getPhone() const;
    string getResponsibility() const;

    void setName(const string& name);
    void setPosition(const string& position);
    void setPhone(const string& phone);
    void setResponsibility(const string& responsibility);

    void print() const override;
    void saveToFile(ofstream& outFile) const override;
    static University* loadFromFile(ifstream& inFile);
};

#endif