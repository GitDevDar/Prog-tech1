#ifndef KEEPER_H
#define KEEPER_H
#include <iostream>
#include "University1.h"

using namespace std;

class Keeper {
private:
    University** objects;
    int capacity;
    int count;

    void resize();

public:
    Keeper();
    ~Keeper();

    void addObj(University* obj);
    void removeObject(int index);
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    void printAll() const;
};

#endif