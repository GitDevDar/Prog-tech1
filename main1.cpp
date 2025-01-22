#include <iostream>
#include <locale>
#include <limits>
#include "exceptions1.h"
#include "Keeper1.h"
#include "Student1.h"
#include "Teacher1.h"
#include "AdminStaff1.h"

using namespace std;

void showMenu() {
    cout << "1. Add Student\n";
    cout << "2. Add Teacher\n";
    cout << "3. Add Administrator\n";
    cout << "4. Show everyone\n";
    cout << "5. Delete object\n";
    cout << "6. Save to file\n";
    cout << "7. Recover from file\n";
    cout << "0. Exit\n";
}

int main() {
    Keeper keeper;
    int choice;

    while (true) {
        showMenu();
        cout << "Select action: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong choice, try again.\n";
            continue;
        }
        cin.ignore();
        if (choice == 1) {
            string name, group, specialty;
            int course;
            double GPA;

            cout << "Enter full name: ";
            getline(cin, name);
            cout << "Enter group: ";
            getline(cin, group);
            cout << "Enter specialty: ";
            getline(cin, specialty);
            cout << "Enter course: ";
            cin >> course;
            cout << "Enter GPA (with a dot, for example 3.5): ";
            cin >> GPA;

            keeper.addObj(new Student(name, group, specialty, course, GPA));
            cout << "Student added successfully.\n";
        }
        else if (choice == 2) {
            string name, subjects, groups;

            cout << "Enter full name: ";
            getline(cin, name);
            cout << "Enter groups: ";
            getline(cin, groups);
            cout << "Enter Subjects: ";
            getline(cin, subjects);

            keeper.addObj(new Teacher(name,groups,subjects));
            cout << "Teacher added successfully.\n";
        }
        else if (choice == 3) {
            string name, position, phone, resposibility;
            
            cout << "Enter full name: ";
            getline(cin, name);
            cout << "Enter job title: ";
            getline(cin, position);
            cout << "Enter phone number: ";
            getline(cin, phone);
            cout << "Enter area of responsibility: ";
            getline(cin, resposibility);

            keeper.addObj(new AdminStaff(name, position, phone, resposibility));
            cout << "Administrator added successfully.\n";
        }
        else if (choice == 4) {
            keeper.printAll();
        }
        else if (choice == 5) {
            int index;
            cout << "Enter the index of the object you want to delete: ";
            cin >> index;
            try {
                keeper.removeObject(index);
                cout << "Object deleted successfully.\n";
            }
            catch (const IndexOutOfRangeException& ex) {
                cout << ex.what() << endl;
            }
        }
        else if (choice == 6) {
            keeper.saveToFile("data_s.txt");
            cout << "Objects successfully saved to file.\n";
        }
        else if (choice == 7) {
            keeper.loadFromFile("data_s.txt");
            cout << "Objects were successfully restored.\n";
        }
        else if (choice == 0) {
            break;
        }
    }

    return 0;
}