#include "MyString.h"
#include <cstring>
#include <iostream>

using namespace std;

//CTORS-----------------------------------------------------------
MyString::MyString()
	:size(0), capacity(0), string(nullptr)
{}
MyString::MyString(const char* s)
{
	size_t n = 0;
	while (s[n]) n++;

	size = n;
	capacity = n + 1;
	string = new char[capacity];

	for (size_t i = 0; i < size; i++) string[i] = s[i];

	string[size] = '\0';

}

//DYNAMIC---------------------------------------------------------
void MyString::freeDynamic()
{
	delete[] string;
	string = nullptr;
}
void MyString::copyDynamic(const MyString& other)
{
	capacity = other.capacity;
	size = other.size;

	string = new char[capacity];
	for (size_t i = 0; i < size; i++) string[i] = other.string[i];
}

//COPY-------------------------------------------------------------
MyString::MyString(const MyString& other)
{
	copyDynamic(other);
}
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

//MOVE--------------------------------------------------------------
MyString::MyString(MyString&& other) noexcept
	:capacity(other.capacity), size(other.size), string(other.string)
{
	other.capacity = 0;
	other.size = 0;
	other.string = nullptr;
}
MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		freeDynamic();
		delete[] string;

		capacity = other.capacity;
		size = other.size;
		string = other.string;

		other.capacity = 0;
		other.size = 0;
		other.string = nullptr;
	}
	return *this;
}

//DTOR----------------------------------------------------------------
MyString::~MyString()
{
	freeDynamic();
}

//GETTERS--------------------------------------------------------------
const size_t MyString::getSize() const
{
	return size;
}
const char* MyString::getString() const
{
	return string;
}

//PREDEFINED-----------------------------------------------------------
char& MyString::operator[](size_t index)
{
	if (index >= size) throw out_of_range("No such index\n");
	return string[index];
}
const char& MyString::operator[](size_t index) const
{
	if (index >= size) throw out_of_range("No such index\n");
	return string[index];
}
bool MyString::operator==(const MyString& other) const
{
	if (size != other.size) return false;

	for (size_t i = 0; i < size; i++)
		if (string[i] != other.string[i]) return false;

	return true;

}
bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}


//ADDITIONAL------------------------------------------------------------
void MyString::push_back(const char c)
{
	if (size + 1 >= capacity)
	{
		size_t newCap = (capacity == 0) ? 8 : capacity * growthFactor;
		reserve(newCap);
	}

	string[size] = c;
	size++;
	string[size] = '\0';
}
void MyString::reserve(size_t newCapacity)
{
	if (newCapacity <= capacity) return;
	char* newString = new char[newCapacity];
	for (size_t i = 0; i < size; i++)
		newString[i] = string[i];

	newString[size] = '\0';
	delete[] string;
	string = newString;
	capacity = newCapacity;
}
char MyString::pop_back()
{
	if (isEmpty()) throw out_of_range("String is empty\n");

	char oldChar = string[size - 1];
	size--;
	string[size] = '\0';
	return oldChar;
}
const bool MyString::isEmpty() const
{
	return size == 0;
}
//void MyString::shrinkToSize()
//{
//	if (capacity > size * 2) //the logic here is questionable
//	{
//		size_t newCapacity = size + 1;
//		char* newString = new char[newCapacity];
//
//		for (size_t i = 0; i < size; i++)
//			newString[i] = string[i];
//
//		newString[size] = '\0';
//
//		delete[] string;
//		string = newString;
//		capacity = newCapacity;
//	}
//}
bool MyString::equalsIgnoreCase(const MyString& other) const
{
	if (this->size != other.size) return false;

	for (size_t i = 0; i < size; i++)
	{
		char a = string[i];
		char b = other.string[i];

		if (a >= 'A' && a <= 'Z') a = a - 'A' + 'a';
		if (b >= 'A' && b <= 'Z') b = b - 'A' + 'a';

		if (a != b) return false;
	}
	return true;
}
ostream& operator<<(ostream& os, const MyString& str) {
	os << str.getString();  
	return os;
}

//originally in Tokenizer, but moved here (use: in Tokenizer)
bool MyString::isLetter(const char ch)
{
	return (ch >= 'A' && ch <= 'Z') ||
		(ch >= 'a' && ch <= 'z');
}
bool MyString::isDigit(const char ch)
{
	return (ch >= '0' && ch <= '9');
}
bool MyString::isOperator(const char ch)
{
	return ch == '+' ||
		ch == '-' || ch == '*' || ch == '/' ||
		ch == '^';

}
