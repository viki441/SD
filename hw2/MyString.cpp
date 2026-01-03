#include "MyString.h"
#include <cctype>

//-----------------Constructors----------------
MyString::MyString() {
    data.push_back('\0'); // always keep null terminator
}

MyString::MyString(const char* s) {
    if (!s) {
        data.push_back('\0');
        return;
    }
    size_t i = 0;
    while (s[i]) {
        data.push_back(s[i]);
        i++;
    }
    data.push_back('\0');
}

//-----------------Copy & Move----------------
MyString::MyString(const MyString& other) : data(other.data) {}
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

MyString::MyString(MyString&& other) noexcept : data(std::move(other.data)) {}
MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
    }
    return *this;
}

//-----------------Access---------------------
size_t MyString::getSize() const {
    return data.size() ? data.size() - 1 : 0; // exclude '\0'
}

const char* MyString::getString() const {
    if (data.empty()) return nullptr;       
    if (data.back() != '\0') return nullptr; 
    return data.getData();
}

char& MyString::operator[](size_t index) {
    if (index >= getSize()) throw std::out_of_range("Index out of range");
    return data[index];
}

const char& MyString::operator[](size_t index) const {
    if (index >= getSize()) throw std::out_of_range("Index out of range");
    return data[index];
}

//-----------------Comparison-----------------
bool MyString::operator==(const MyString& other) const {
    if (getSize() != other.getSize()) return false;
    for (size_t i = 0; i < getSize(); i++)
        if (data[i] != other.data[i]) return false;
    return true;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

//-----------------Modifiers------------------
void MyString::push_back(char c) {
    if (data.size() == 0) data.push_back(c);
    else {
        data[data.size() - 1] = c; // overwrite '\0'
        data.push_back('\0');       // keep null terminator
    }
}


char MyString::pop_back() {
    if (getSize() == 0) throw std::out_of_range("String is empty");
    char last = data[data.size() - 2]; // char before '\0'
    data.pop_back(); // remove '\0'
    data.pop_back(); // remove last char
    data.push_back('\0'); // restore terminator
    return last;
}

bool MyString::isEmpty() const {
    return getSize() == 0;
}

void MyString::clear() {
    data.clear();
    data.push_back('\0');
}

bool MyString::equalsIgnoreCase(const MyString& other) const {
    if (getSize() != other.getSize()) return false;
    for (size_t i = 0; i < getSize(); i++) {
        char a = std::tolower(data[i]);
        char b = std::tolower(other.data[i]);
        if (a != b) return false;
    }
    return true;
}

//-----------------Stream---------------------
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.getString();
    return os;
}
