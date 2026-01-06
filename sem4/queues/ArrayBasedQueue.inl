#include "ArrayBasedQueue.h"

template<typename T>
void ArrayBasedQueue<T>::enqueue(const T& value) 
{
    array.push_back(value);
}

template<typename T>
void ArrayBasedQueue<T>::enqueue(T&& value) 
{
    array.push_back(std::move(value));
}

template<typename T>
T ArrayBasedQueue<T>::dequeue() 
{
    if (isEmpty())
        throw std::underflow_error("Queue is empty");

    T val = std::move(array[frontIndex]);
    frontIndex++;

    if (frontIndex > 64 && frontIndex * 2 > array.size()) 
    {
        MyVector<T> newArray(array.size() - frontIndex);
        for (size_t i = frontIndex; i < array.size(); i++)
            newArray.push_back(std::move(array[i]));
        array = std::move(newArray);
        frontIndex = 0;
    }

    return val;
}

template<typename T>
const T& ArrayBasedQueue<T>::front() const 
{
    if (isEmpty())
        throw std::underflow_error("Queue is empty");
    return array[frontIndex];
}

template<typename T>
bool ArrayBasedQueue<T>::isEmpty() const 
{
    return frontIndex >= array.size();
}

template<typename T>
size_t ArrayBasedQueue<T>::getSize() const 
{
    return array.size() - frontIndex;
}

template<typename T>
void ArrayBasedQueue<T>::clear() 
{
    array.clear();
    frontIndex = 0;
}
