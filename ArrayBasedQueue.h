#pragma once
#include "MyVector.h"
#include <stdexcept>

template<typename T>
class ArrayBasedQueue {
private:
    MyVector<T> array;   // underlying storage
    size_t frontIndex = 0; // index of the front element

public:
    // Big-4 can be defaulted because MyVector manages memory safely
    ArrayBasedQueue() = default;

    ArrayBasedQueue(const ArrayBasedQueue&) = default;
    ArrayBasedQueue(ArrayBasedQueue&&) noexcept = default;
    ~ArrayBasedQueue() = default;

    // Enqueue (add to back)
    void enqueue(const T& value);
    void enqueue(T&& value);

    // Dequeue (remove from front)
    T dequeue();

    // Peek front element
    const T& front() const;

    // Check empty and size
    bool isEmpty() const;
    size_t getSize() const;

    // Optional: clear queue
    void clear();
};

#include "ArrayBasedQueue.inl"
