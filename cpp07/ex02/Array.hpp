#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <iostream>

template <typename T>
class Array {
private:
    T* _data;
    unsigned int _size;

public:
    Array();
    Array(unsigned int n);
    
    ~Array();
    
    Array(const Array& other);

    Array& operator=(const Array& other);

    T& operator[](unsigned int i);

    const T& operator[](unsigned int i) const;

    unsigned int size() const;
};

#include "Array.tpp"
#endif