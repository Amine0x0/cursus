#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iterator>

class Span{
    private:
        unsigned int _maxSize;
        std::vector<unsigned int> _numbers;
    public:
        Span();
        ~Span();
        Span& operator=(const Span& other);
        Span(const Span& other);
        Span(unsigned int N);

        void addNumber(unsigned int N);

        unsigned int shortestSpan();
        unsigned int longestSpan();

    template <typename Iterator>
    void addNumbers(Iterator begin, Iterator end) {
        if (_numbers.size() + std::distance(begin, end) > _maxSize)
            throw std::out_of_range("full Span");
        _numbers.insert(_numbers.end(), begin, end);
    }
};

#endif