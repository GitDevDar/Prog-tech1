#include <iostream>
#include <limits>
#include <algorithm>
#include "Group2.h"
#include "Exceptions2.h"
#include "TextProcessor2.h"

using namespace std;

void createGroup(Group**& groups, int& groupCount, int& groupCapacity);
void deleteGroup(Group**& groups, int& groupCount);
void addStudentToGroup(Group** groups, int groupCount);
void removeStudentFromGroup(Group** groups, int groupCount);
void editGroup(Group** groups, int groupCount);
void editStudentInGroup(Group** groups, int groupCount);
void addGroupAtPosition(Group**& groups, int& groupCount, int& groupCapacity);
void addStudentAtPosition(Group** groups, int groupCount);
void showGroups(Group** groups, int groupCount);
void showHighAchievers(Group** groups, int groupCount);

int main() {
    int groupCapacity = 2;
    int groupCount = 0;
    
    Group** groups = new Group * [groupCapacity];

    TextProcessor processor;
    
    const char* inputFile = "Input.txt";

    while (true) {
        cout << "Main menu:\n";
        cout << "1. Task 1: Working with groups and students\n";
        cout << "2. Task 2: Processing text from file\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        
        cin.ignore();

        if (choice == 0) {
            cout << "Exit the program.\n";
            break;
        }
        else if (choice == 1) {
            while (true) {
                cout << "Task 1 menu:\n";
                cout << "1. Create group\n";
                cout << "2. Delete group\n";
                cout << "3. Add student to group\n";
                cout << "4. Remove student from group\n";
                cout << "5. Edit group\n";
                cout << "6. Edit student in group\n";
                cout << "7. Add a student to a specific position in group\n";
                cout << "8. Show all groups\n";
                cout << "9. Show students with grade > 4.0\n";
                cout << "0. To main menu\n";
                cout << "Choice: ";

                int subChoice;
                cin >> subChoice;

                cin.ignore();

                if (subChoice == 0) {
                    break;
                }

                try {
                    switch (subChoice) {
                        case 1:
                            createGroup(groups, groupCount, groupCapacity);
                            break;
                        case 2:
                            deleteGroup(groups, groupCount);
                            break;
                        case 3:
                            addStudentToGroup(groups, groupCount);
                            break;
                        case 4:
                            removeStudentFromGroup(groups, groupCount);
                            break;
                        case 5:
                            editGroup(groups, groupCount);
                            break;
                        case 6:
                            editStudentInGroup(groups, groupCount);
                            break;
                        case 7:
                            addStudentAtPosition(groups, groupCount);
                            break;
                        case 8:
                            showGroups(groups, groupCount);
                            break;
                        case 9:
                            showHighAchievers(groups, groupCount);
                            break;
                        default:
                            cout << "Error: incorrect choice.\n";
                    }
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }
        }
        else if (choice == 2) {
            while (true) {
                cout << "Task 2 menu:\n";
                cout << "1. Output text from file\n";
                cout << "2. Output text with word order changed\n";
                cout << "0. To main menu\n";
                cout << "Choice: ";

                int subChoice;
                cin >> subChoice;
                if (subChoice == 0) {
                    break;
                }

                switch (subChoice) {
                    case 1:
                        processor.display(inputFile);
                        break;
                    case 2:
                        processor.processorFile(inputFile);
                        break;
                    default:
                        cout << "Error. Incorrect input. Try again.\n";
                }
            }
        }
    }
    for (int i = 0; i < groupCount; ++i) {
        delete groups[i];
    }

    delete[] groups;
    return 0;
}

void createGroup(Group**& groups, int& groupCount, int& groupCapacity) {
    if (groupCount == groupCapacity) {
        groupCapacity *= 2;
        Group** newGroups = new Group * [groupCapacity];
        for (int i = 0; i < groupCount; ++i) {
            newGroups[i] = groups[i];
        }
        
        delete[] groups;
        groups = newGroups;
    }

    int groupNumber;
    cout << "Enter group number: ";
    cin >> groupNumber;

    groups[groupCount++] = new Group(groupNumber);
    cout << "Group created successfully.\n";

    sort(groups, groups + groupCount, [](Group * a, Group * b){ return a->getGroupNumber() < b->getGroupNumber(); });
    cout << "Groups are ordered by ascending number.\n";
}

void deleteGroup(Group**& groups, int& groupCount) {
    if (groupCount == 0) {
        throw GroupException("Group list is empty.");
    }

    cout << "Enter the group number to delete: ";
    int groupNumber;
    cin >> groupNumber;

    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            delete groups[i];

            for (int j = i; j < groupCount - 1; ++j) {
                groups[j] = groups[j + 1];
            }
            --groupCount;
            cout << "Group successfully deleted.\n";
            return;
        }
    }
    
    throw GroupException("Group with specified number was not found.");
}

void addStudentToGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty.\n";
        return;
    }

    cout << "Enter the group number where you want to add a student: ";
    int groupNumber;
    cin >> groupNumber;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Error: incorrect group number.\n";
        return;
    }

    cin.ignore();

    Group* targetGroup = nullptr;
    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            targetGroup = groups[i];
            break;
        }
    }

    if (!targetGroup) {
        cout << "Group with specified number was not found.\n";
        return;
    }


    Student* newStudent = new Student();
    try {
        cout << "Enter student details:\n";
        cin >> *newStudent;
        targetGroup->addStudent(newStudent);
    }

    catch (const exception& e) {
        delete newStudent;
        cout << "Error: " << e.what() << "\n";
    }
}

void removeStudentFromGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        throw GroupException("Group list is empty.");
    }

    cout << "Enter group number: ";
    int groupNumber;
    cin >> groupNumber;

    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
        cout << "Enter student number to delete: ";
        int studentindex;
        cin >> studentindex;

        groups[i]->removeStudent(studentindex - 1);
        cout << "Student successfully removed from group No. " << groupNumber << ".\n";
        return;
        }
    }

    throw GroupException("Group with specified number was not found.");
}

void editGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        throw GroupException("Group list is empty.");
    }

    cout << "Enter group number to edit: ";
    int groupNumber;
    cin >> groupNumber;

    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            cout << "Enter a new number for group No." << groupNumber << ": ";
            int newNumber;
            cin >> newNumber;
            groups[i]->setGroupNumber(newNumber);

            sort(groups, groups + groupCount, [](Group* a, Group* b){ return a->getGroupNumber() < b->getGroupNumber();});
            cout << "Group number has been successfully changed and the groups are sorted.\n";
            return;
        }
    }

    throw GroupException("Group with specified number was not found.");
}

void editStudentInGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty.\n";
        return;
    }

    cout << "Enter group number: ";
    int groupNumber;
    cin >> groupNumber;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Error: incorrect entry of group number.\n";
        return;
    }

    Group* targetGroup = nullptr;
    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber){
            targetGroup = groups[i];
            break;
        }
    }

    if (!targetGroup) {
        cout << "Group with specified number was not found.\n";
        return; 
    }

    cout << "Enter student number to edit: ";
    int studentindex;
    cin >> studentindex;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Error: incorrect entry of student number.\n";
        return;
    }

    if (studentindex <= 0 || studentindex > targetGroup->getStudentCount()) {
        cout << "Error: incorrect number of student.\n";
        return;
    }

    Student* studentToEdit = targetGroup->getStudent(studentindex - 1);
    if (!studentToEdit) {
        cout << "Error: student not found.\n";
        return;
    }

    cout << "Editing a student:\n";
    cin.ignore();

    try {
        cin >> *studentToEdit;
        cout << "Student successfully edited.\n"; 
    }

    catch (const exception& e){
        cout << "Error editing student: " << e.what() << "\n";
    }
}

void addGroupAtPosition(Group**& groups, int& groupCount, int& groupCapacity) {
    if (groupCount == groupCapacity) {
        groupCapacity *= 2;
        Group** newGroups = new Group * [groupCapacity];
        
        for (int i = 0; i < groupCount; ++i) {
            newGroups[i] = groups[i];
        }

        delete[] groups;
        groups = newGroups;
    }

    int position, groupNumber;
    cout << "Enter position for new group (1-" << groupCount + 1 << "): ";
    cin >> position;

    if (position < 1 || position > groupCount + 1) {
        throw InputException("Incorrect position.");
    }

    cout << "Enter new group number: ";
    cin >> groupNumber;

    for (int i = groupCount; i >= position; --i) {
        groups[i] = groups [i - 1];
    } 
    groups[position - 1] = new Group(groupNumber);
    ++groupCount;

    sort(groups, groups + groupCount, [](Group* a, Group* b){ return a->getGroupNumber() < b->getGroupNumber();});
    cout << "Group was successfully added and groups are sorted by ascending number.\n";
}

void addStudentAtPosition(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty.";
        return;
    }

    try {
        cout << "Enter group number: ";
        int groupNumber;
        cin >> groupNumber;

        if (cin.fail()) {
            throw InputException("Error: incorrect group number");
        }
        Group* targetGroup = nullptr;
        for (int i = 0; i < groupCount; ++i) {
            if (groups[i]->getGroupNumber() == groupNumber) {
                targetGroup = groups[i];
                break;
            }
        }
        
        if (!targetGroup) {
            throw GroupException("Group with specified number was not found.");
        }

        cout << "Enter a position for a new student (1-"<< targetGroup->getStudentCount() + 1 << "):";

        int position;
        cin >> position;

        if (cin.fail() || position < 1 || position > targetGroup->getStudentCount() + 1) {
            throw InputException("Error: incorrect position for adding a student.");
        }
        
        Student* newStudent = new Student();
        cout << "Enter student details:\n";
        cin.ignore();
        cin >> *newStudent;

        try {
            targetGroup->addStudentAtPosition(newStudent, position - 1);
            cout << "Student was successfully added on position " << position << " in group No. " << groupNumber << ".\n";
        }

        catch (const exception& e) {
            delete newStudent;
            throw;
        }
    }

    catch (const InputException& e) {
        cout << "Entry error: " << e.what() << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    catch (const GroupException& e) {
        cout << "Error with group: " << e.what() << "\n";
    }

    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void showGroups(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty.\n";
        return;
    }

    for (int i = 0; i < groupCount; ++i) {
        groups[i]->showStudents();
        cout << "--------------------------------------\n";
    }
}

void showHighAchievers(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty.\n";
        return;
    }

    for (int i = 0; i < groupCount; ++i) {
        Group* group = groups[i];
        cout << "Group No. " << group->getGroupNumber() << ":\n";

        bool found = false;
        for (int j = 0; j < group->getStudentCount(); ++j) {
            Student* student = group->getStudent(j);
            if (student->getAverageGrade() > 4.0) {
                cout << "Student No. " << (j + 1) << ": " << student->getSurname() << ", Average grade: " << student->getAverageGrade() << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No students with a average grade higher than 4.0.\n";
        }

        cout << "--------------------------------------\n"; 
    }
}