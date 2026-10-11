#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include "Span.hpp"

int main() {
    try {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        Span listSpan(4);
        std::list<unsigned int> lst;
        lst.push_back(100);
        lst.push_back(5);
        lst.push_back(42);
        lst.push_back(200);

        listSpan.addNumbers(lst.begin(), lst.end());

        std::cout << "Shortest Span: " << listSpan.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << listSpan.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        Span dequeSpan(3);
        std::deque<unsigned int> deq;
        deq.push_back(10);
        deq.push_back(20);
        deq.push_back(15);

        dequeSpan.addNumbers(deq.begin(), deq.end());

        std::cout << "Shortest Span: " << dequeSpan.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << dequeSpan.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        Span small(2);
        small.addNumber(42);
        small.shortestSpan();
    } catch (const std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
    }

    try  {
        Span full(1);
        full.addNumber(1);
        full.addNumber(2);
    } catch (const std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
    }

    return 0;
}