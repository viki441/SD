#pragma once
#include <stdexcept>

template<typename T>
class arrayBasedStack
{
public:
	//ctors
	arrayBasedStack(); //def
	arrayBasedStack(size_t cap = 10);//param

	//copy
	arrayBasedStack(const arrayBasedStack& other);
	arrayBasedStack& operator=(const arrayBasedStack& other);

	//move
	arrayBasedStack(arrayBasedStack&& other) noexcept;
	arrayBasedStack& operator=(arrayBasedStack&& other) noexcept;

	//dtor
	~arrayBasedStack();

	//getters
	const size_t getSize() const;
	const size_t getCapacity() const;

	//dynamic
	void freeDynamic();
	void copyDynamic(const arrayBasedStack& other);

	//additional for the stack 
	void push(const T& element);
	void push(T&& element);

	T pop();

	const T& topElement() const;
	bool isEmpty() const;
	bool isFull() const;
	void clearStack();

private:
	T* array;
	size_t capacity;
	size_t top;
};


#include "arrayBasedStack.inl"