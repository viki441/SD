#include "MyVector.h"
#include <stdexcept>
#include <utility> // for std::move

/////////////////////////////////// CTORS ////////////////////////////

template<typename T>
MyVector<T>::MyVector()
    : _data(nullptr), _size(0), _capacity(0)
{
}

template<typename T>
MyVector<T>::MyVector(size_t initialCapacity)
    : _data(initialCapacity > 0 ? new T[initialCapacity] : nullptr),
    _size(0),
    _capacity(initialCapacity)
{
    // No exception needed for 0 capacity
}

template<typename T>
MyVector<T>::MyVector(size_t size, const T& defaultValue)
    : _data(size > 0 ? new T[size] : nullptr),
    _size(size),
    _capacity(size)
{
    for (size_t i = 0; i < _size; i++)
        _data[i] = defaultValue;
}

/////////////////////////////////// DTOR ////////////////////////////

template<typename T>
MyVector<T>::~MyVector()
{
    delete[] _data;
}

/////////////////////////////////// COPY ////////////////////////////

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
    : _data(other._capacity > 0 ? new T[other._capacity] : nullptr),
    _size(other._size),
    _capacity(other._capacity)
{
    for (size_t i = 0; i < _size; i++)
        _data[i] = other._data[i];
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if (this != &other) {
        delete[] _data;
        _data = other._capacity > 0 ? new T[other._capacity] : nullptr;
        _size = other._size;
        _capacity = other._capacity;
        for (size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }
    return *this;
}

/////////////////////////////////// MOVE ////////////////////////////

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : _data(other._data),
    _size(other._size),
    _capacity(other._capacity)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept
{
    if (this != &other) {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

/////////////////////////////////// ACCESS ////////////////////////////

template<typename T>
T& MyVector<T>::operator[](size_t index)
{
    if (index >= _size)
        throw std::out_of_range("Index out of range");
    return _data[index];
}

template<typename T>
const T& MyVector<T>::operator[](size_t index) const
{
    if (index >= _size)
        throw std::out_of_range("Index out of range");
    return _data[index];
}

template<typename T>
T& MyVector<T>::back()
{
    if (empty())
        throw std::out_of_range("Vector is empty");
    return _data[_size - 1];
}

template<typename T>
const T& MyVector<T>::back() const
{
    if (empty())
        throw std::out_of_range("Vector is empty");
    return _data[_size - 1];
}

template<typename T>
T* MyVector<T>::begin() { return _data; }

template<typename T>
const T* MyVector<T>::begin() const { return _data; }

template<typename T>
T* MyVector<T>::end() { return _data + _size; }

template<typename T>
const T* MyVector<T>::end() const { return _data + _size; }

/////////////////////////////////// CAPACITY ////////////////////////////

template<typename T>
size_t MyVector<T>::size() const { return _size; }

template<typename T>
size_t MyVector<T>::capacity() const { return _capacity; }

template<typename T>
bool MyVector<T>::empty() const { return _size == 0; }

template<typename T>
void MyVector<T>::reserve(size_t newCapacity)
{
    if (newCapacity <= _capacity)
        return;

    T* new_data = new T[newCapacity];
    for (size_t i = 0; i < _size; ++i)
        new_data[i] = std::move(_data[i]);

    delete[] _data;
    _data = new_data;
    _capacity = newCapacity;
}

/////////////////////////////////// MODIFIERS ////////////////////////////

template<typename T>
void MyVector<T>::push_back(const T& value)
{
    if (_size == _capacity)
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    _data[_size++] = value;
}

template<typename T>
void MyVector<T>::push_back(T&& value)
{
    if (_size == _capacity)
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    _data[_size++] = std::move(value);
}

template<typename T>
void MyVector<T>::pop_back()
{
    if (empty())
        throw std::out_of_range("Vector is empty");
    _size--;
}

template<typename T>
void MyVector<T>::clear()
{
    _size = 0;
}

template<typename T>
T* MyVector<T>::getData() { return _data; }

template<typename T>
const T* MyVector<T>::getData() const { return _data; }
