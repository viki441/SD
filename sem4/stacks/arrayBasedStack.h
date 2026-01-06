#pragma once
#include <stdexcept>
#include <iostream>
#include "MyVector.h"
//////////////////////////////////USE MyVector from implementations!!
template<typename T>
class ArrayBasedStack
{
public:

	ArrayBasedStack() = default;
	explicit ArrayBasedStack(size_t cap);
	ArrayBasedStack(const ArrayBasedStack& other) = default;
	ArrayBasedStack& operator=(const ArrayBasedStack& other) = default;
	ArrayBasedStack(ArrayBasedStack&& other) noexcept = default;
	ArrayBasedStack& operator=(ArrayBasedStack&& other) noexcept = default;
	~ArrayBasedStack() = default;


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
