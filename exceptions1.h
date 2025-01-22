#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class KepperException : public std::exception {
protected:
    std::string message;

public:
    KepperException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class EmptyContainerException : public KepperException {
public:
    EmptyContainerException() : KepperException("Error. an attempt to remove an element from an empty container.") {}
};

class MemoryAllocationException : public KepperException {
public:
    MemoryAllocationException() : KepperException("Error. There is not enough memory to add a new element.") {}
};

class IndexOutOfRangeException : public KepperException {
public:
    IndexOutOfRangeException() : KepperException("Error. an attempt to access an element outside the container's boundaries.") {}
};

#endif