#include "MyVector.h"

template<typename T>
MyVector<T>::MyVector()
    : data(nullptr), vecSize(0), vecCapacity(0)
{}

template<typename T>
MyVector<T>::MyVector(size_t initialCapacity)
    : data(initialCapacity > 0 ? new T[initialCapacity] : nullptr),
    vecSize(0),
    vecCapacity(initialCapacity)
{}

template<typename T>
MyVector<T>::MyVector(size_t size, const T& defaultValue)
    : data(size > 0 ? new T[size] : nullptr),
    vecSize(size),
    vecCapacity(size)
{
    for (size_t i = 0; i < vecSize; i++)
        data[i] = defaultValue;
}

template<typename T>
MyVector<T>::~MyVector()
{
    delete[] data;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
    : data(other.vecCapacity > 0 ? new T[other.vecCapacity] : nullptr),
    vecSize(other.vecSize),
    vecCapacity(other.vecCapacity)
{
    for (size_t i = 0; i < vecSize; i++)
        data[i] = other.data[i];
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if (this != &other)
    {
        delete[] data;
        data = other.vecCapacity > 0 ? new T[other.vecCapacity] : nullptr;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;
        for (size_t i = 0; i < vecSize; i++)
            data[i] = other.data[i];
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : data(other.data),
    vecSize(other.vecSize),
    vecCapacity(other.vecCapacity)
{
    other.data = nullptr;
    other.vecSize = 0;
    other.vecCapacity = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;
        other.data = nullptr;
        other.vecSize = 0;
        other.vecCapacity = 0;
    }
    return *this;
}



template<typename T>
T& MyVector<T>::operator[](size_t index)
{
    if (index >= vecSize)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template<typename T>
const T& MyVector<T>::operator[](size_t index) const
{
    if (index >= vecSize)
        throw std::out_of_range("Index out of range");
    return data[index];
}



template<typename T>
T& MyVector<T>::back()
{
    if (empty())
        throw std::out_of_range("Vector is empty");
    return data[vecSize - 1];
}

template<typename T>
const T& MyVector<T>::back() const
{
    if (empty())
        throw std::out_of_range("Vector is empty");
    return data[vecSize - 1];
}



template<typename T>
T* MyVector<T>::begin()
{ 
    return data; 
}

template<typename T>
const T* MyVector<T>::begin() const 
{ 
    return data; 
}



template<typename T>
T* MyVector<T>::end() 
{
    return data + vecSize; 
}

template<typename T>
const T* MyVector<T>::end() const 
{ 
    return data + vecSize; 
}




template<typename T>
size_t MyVector<T>::size() const 
{ 
    return vecSize; 
}

template<typename T>
size_t MyVector<T>::capacity() const 
{ 
    return vecCapacity; 
}

template<typename T>
bool MyVector<T>::empty() const 
{ 
    return vecSize == 0; 
}


template<typename T>
void MyVector<T>::reserve(size_t newCapacity)
{
    if (newCapacity <= vecCapacity) 
        return;

    T* newData = new T[newCapacity];
    for (size_t i = 0; i < vecSize; ++i)
        newData[i] = std::move(data[i]);

    delete[] data;
    data = newData;
    vecCapacity = newCapacity;
}



template<typename T>
void MyVector<T>::push_back(const T& value)
{
    if (vecSize == vecCapacity)
        reserve(vecCapacity == 0 ? 1 : vecCapacity * 2);
    data[vecSize++] = value;
}

template<typename T>
void MyVector<T>::push_back(T&& value)
{
    if (vecSize == vecCapacity)
        reserve(vecCapacity == 0 ? 1 : vecCapacity * 2);
    data[vecSize++] = std::move(value);
}




template<typename T>
void MyVector<T>::pop_back()
{
    if (empty())
        throw std::out_of_range("Vector is empty");
    vecSize--;
}



template<typename T>
void MyVector<T>::clear() 
{
    vecSize = 0; 
}

template<typename T>
T* MyVector<T>::getData() 
{ 
    return data; 
}

template<typename T>
const T* MyVector<T>::getData() const 
{
    return data; 
}
