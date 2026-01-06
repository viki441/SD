#pragma once
#include <stdexcept>
#include <utility>

template<typename T>
class MyVector
{
public:
    MyVector();
    MyVector(size_t initialCapacity);
    MyVector(size_t size, const T& defaultValue);

    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);

    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    ~MyVector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& back();
    const T& back() const;

    T* begin();
    const T* begin() const;

    T* end();
    const T* end() const;

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();

    void clear();
    T* getData();
    const T* getData() const;

    void reserve(size_t newCapacity);

private:
    T* data;
    size_t vecSize;
    size_t vecCapacity;

    //void resizeCapacity(size_t newCapacity);
};

#include "MyVector.inl"
