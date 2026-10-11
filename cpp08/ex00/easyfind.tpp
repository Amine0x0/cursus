#ifndef EASYFIND_TPP
#define EASYFIND_TPP

#include <algorithm>
#include <vector>

template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw NotFoundExcept();
    }
    return it;
}

template <typename T>
typename T::const_iterator easyfind(T const &container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw NotFoundExcept();
    }
    return it;
}

#endif