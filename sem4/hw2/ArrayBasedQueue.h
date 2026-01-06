#pragma once
#include "MyVector.h"
#include <stdexcept>

template<typename T>
class ArrayBasedQueue 
{
private:
    MyVector<T> array;
    size_t frontIndex = 0;

public:
    ArrayBasedQueue() = default;
    ArrayBasedQueue(const ArrayBasedQueue&) = default;
    ArrayBasedQueue(ArrayBasedQueue&&) noexcept = default;
    ~ArrayBasedQueue() = default;


    void enqueue(const T& value);
    void enqueue(T&& value);
    T dequeue();

    const T& front() const;
    bool isEmpty() const;
    size_t getSize() const;
    void clear();
};

#include "ArrayBasedQueue.inl"
