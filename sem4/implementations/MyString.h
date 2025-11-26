#pragma once
#include <stdexcept>
#include <fstream>
#include <ostream>

using namespace std;

class MyString
{

public:

	MyString();
	MyString(const char* s);
	
	//copy
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	//move
	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	//dtor
	~MyString();

	//getters and setters
	const size_t getSize() const;
	const char* getString() const;

	//predefined operators	
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;


	//additional
	void push_back(const char c);
	void reserve(size_t newCapacity);
	char pop_back();
	const bool isEmpty() const;
	bool equalsIgnoreCase(const MyString& other) const;
	friend ostream& operator<<(ostream& os, const MyString& str);
	
	static bool isLetter(const char ch);
	static bool isDigit(const char ch);
	static bool isOperator(const char ch);
	
	//void print() const;


private:

	char* string;
	size_t size;
	size_t capacity;
	int gowthFactor = 2;

	void freeDynamic();
	void copyDynamic(const MyString& other);

	void resize(const int growthFactor);
	//void shrinkToSize();
};


