#include "ArrayBasedStack.h"


//////////////////////////////CTORS////////////////////////


template<typename T>
ArrayBasedStack<T>::ArrayBasedStack(size_t cap)
	: array(cap)
{}


///////////////////ADDITIONAL//////////////////////////////
template<typename T>
size_t ArrayBasedStack<T>::getSize() const
{
	return array.size();
}


template<typename T>
const T& ArrayBasedStack<T>::topElement() const 
{
	if (isEmpty()) throw std::underflow_error("Stack is empty");
	return array.back();
}


template <typename T>
void ArrayBasedStack<T>::push(const T& element)
{
	array.push_back(element);
}

template <typename T>
void ArrayBasedStack<T>::push(T&& element)
{
	array.push_back(std::move(element));
}


template<typename T>
T ArrayBasedStack<T>::pop()
{
	if (isEmpty()) throw std::underflow_error("Stack is empty\n");
	
	T value = std::move(array.back());
	array.pop_back();
	return value;
}


template<typename T>
bool ArrayBasedStack<T>::isEmpty() const
{
	return array.size() == 0;
}


template<typename T>
void ArrayBasedStack<T>::clearStack()
{
	array.clear();
}

