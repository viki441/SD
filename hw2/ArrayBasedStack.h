#pragma once
#include <stdexcept>
#include <iostream>
#include "MyVector.h"



template<typename T>
class ArrayBasedStack
{
public:
	//MyVector handles memory

	//ctors
	ArrayBasedStack() = default; //def

	//param?
	explicit ArrayBasedStack(size_t cap);

	//copy
	ArrayBasedStack(const ArrayBasedStack& other) = default;
	ArrayBasedStack& operator=(const ArrayBasedStack& other) = default;

	//move
	ArrayBasedStack(ArrayBasedStack&& other) noexcept = default;
	ArrayBasedStack& operator=(ArrayBasedStack&& other) noexcept = default;

	//dtor
	~ArrayBasedStack() = default;


	//additional for the stack 
	size_t getSize() const;
	const T& topElement() const;


	void push(const T& element);
	void push(T&& element);

	T pop();


	bool isEmpty() const;
	void clearStack();

private:
	MyVector<T> array;
};


#include "ArrayBasedStack.inl"