#pragma once
#include <iostream>
//////////////////////////////CTORS////////////////////////
template<typename T>
arrayBasedStack<T>::arrayBasedStack()
	:capacity(1), top(0) // should i keep?
{}

template<typename T>
arrayBasedStack<T>::arrayBasedStack(size_t cap)
	: capacity(cap), top(0)
{
	//idk why not accept empty array
	if (cap == 0) throw std::invalid_argument("capacity must be more than 0\n");

	array = new T[capacity];
}



/////////////////////////////COPY//////////////////////////////
//{
	//template<typename T>
	//arrayBasedStack<T>::arrayBasedStack(const arrayBasedStack& other)
	//	:capacity(other.capacity), top(other.top)
	//{
	//	array = new T[capacity];
	//	for (size_t i = 0; i < top; i++)
	//		array[i] = other.array[i];
	//} look if there was no copyDynamic
//}
template<typename T>
arrayBasedStack<T>::arrayBasedStack(const arrayBasedStack& other)
{
	copyDynamic(other);
}

template<typename T>
arrayBasedStack<T>& arrayBasedStack<T>::operator=(const arrayBasedStack& other)
{
	if (this != &other)
	{
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}


////////////////////////////MOVE////////////////////////////
template<typename T>
arrayBasedStack<T>::arrayBasedStack(arrayBasedStack&& other) noexcept
	: array(other.array), capacity(other.capacity), top(other.top)
{ 
	other.capacity = 0;
	other.top = 0;
	other.array = nullptr;
}


template<typename T>
arrayBasedStack<T>& arrayBasedStack<T>::operator=(arrayBasedStack&& other) noexcept
{
	if (this != &other)
	{
		delete[] array;

		array = other.array;
		capacity = other.capacity;
		top = other.top;

		other.array = nullptr;
		other.capacity = 0;
		other.top = 0;
	}
	return *this;
}

///////////////////////////////DTOR///////////////////////////
template<typename T>
arrayBasedStack<T>::~arrayBasedStack()
{
	freeDynamic();
}

/////////////////DYNAMIC/////////////////////////////////////
template<typename T>
void arrayBasedStack<T>::freeDynamic()
{
	delete[] array;
	array = nullptr;
	
}

template<typename T>
void arrayBasedStack<T>::copyDynamic(const arrayBasedStack& other)
{
	capacity = other.capacity;
	top = other.top;

	array = new T[capacity];
	for (size_t i = 0; i < top; i++)
		array[i] = other.array[i];
}

////////////////////GETTERS////////////////////////////////
template<typename T>
const size_t arrayBasedStack<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
const size_t arrayBasedStack<T>::getSize() const
{
	return top;
}

///////////////////ADDITIONAL//////////////////////////////
template <typename T>
void arrayBasedStack<T>::push(const T& element)
{
	if (isFull()) throw std::overflow_error("Stack is full\n");
	array[top++] = element;
}

template <typename T>
void arrayBasedStack<T>::push(T&& element)
{
	if (isFull()) throw std::overflow_error("Stack is full\n");
	array[top++] = std::move(element);
}

template<typename T>
T arrayBasedStack<T>::pop()
{
	if (isEmpty()) throw std::underflow_error("Stack is empty\n");
	return array[--top];
}

template<typename T>
const T& arrayBasedStack<T>::topElement() const
{
	if (isEmpty()) throw std::underflow_error("Stack is empty\n");
	return array[top - 1];
}


template<typename T>
bool arrayBasedStack<T>::isEmpty() const
{
	return top == 0;
}

template<typename T>
bool arrayBasedStack<T>::isFull() const
{
	return top == capacity;
}

template<typename T>
void arrayBasedStack<T>::clearStack() 
{
	top = 0;
}