#pragma once
#include <stdexcept>
//#include "BinaryTree.h"
#include <utility> 

template<typename T>
class MyVector
{
public:
    // constructors
    MyVector();
    MyVector(size_t initialCapacity);

    //for dfs
    MyVector(size_t size, const T& defaultValue);

    // copy 
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);

    // move
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    // destructor
    ~MyVector();

    // capacity
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    // element access
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& back();
    const T& back() const;
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;



    // modifiers
    void push_back(const T& value);
    void push_back(T&& value);

    void pop_back();
    void clear();

    ///////////////////////////////////////////////////////////////

    T* getData();
    const T* getData() const;


    ////////////////////////////////RESERVE
    void reserve(size_t newCapacity);

private:
    T* _data;
    size_t _size;
    size_t _capacity;

    void resizeCapacity(size_t newCapacity);
};

#include "MyVector.inl"