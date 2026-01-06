#pragma once
#include "MyVector.h"
#include <stdexcept>
#include <ostream>
#include <iostream>

class MyString 
{
public:
    MyString();
    MyString(const char* s);

    MyString(const MyString& other);
    MyString& operator=(const MyString& other);

    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    ~MyString() = default;

    size_t getSize() const;
    const char* getString() const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;

    void push_back(char c);
    char pop_back();
    bool isEmpty() const;
    void clear();
    bool equalsIgnoreCase(const MyString& other) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
    MyVector<char> data;
    //void ensureNullTerminator();
};
