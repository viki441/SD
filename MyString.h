#pragma once
#include "MyVector.h"
#include <stdexcept>
#include <ostream>
#include <iostream>

class MyString {
public:
    // Constructors
    MyString();
    MyString(const char* s);

    // Copy
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);

    // Move
    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    // Destructor
    ~MyString() = default;

    // Accessors
    size_t getSize() const;
    const char* getString() const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;

    // Modifiers
    void push_back(char c);
    char pop_back();
    bool isEmpty() const;
    void clear();
    bool equalsIgnoreCase(const MyString& other) const;

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
    MyVector<char> data;
    //void ensureNullTerminator();
};
