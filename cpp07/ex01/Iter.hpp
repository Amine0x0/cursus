#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <cstddef>

template <typename T, typename F>
void iter(T* array, size_t const size, F function) {
    for (size_t i = 0; i < size; ++i) {
        function(array[i]);
    }
}

#endif