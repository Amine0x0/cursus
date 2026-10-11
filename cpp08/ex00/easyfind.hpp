#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <exception>


template <typename T>
typename T::iterator easyfind(T& param, int n);

template <typename T>
typename T::const_iterator	easyfind(T const &container, int value);

class NotFoundExcept : public std::exception{
    public:
        virtual const char* what() throw(){
            return "not found";
        };
};

#include "easyfind.tpp"
#endif