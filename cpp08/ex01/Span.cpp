#include "Span.hpp"

Span::Span() : _maxSize(0) {}

Span::~Span() {}

Span::Span(const Span& other) {
    _maxSize = other._maxSize;
    _numbers = other._numbers;
}

Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::Span(unsigned int N) : _maxSize(N) {}

void Span::addNumber(unsigned int N) {
    if (_numbers.size() >= _maxSize)
        throw std::out_of_range("full Span");
    _numbers.push_back(N);
}

unsigned int Span::shortestSpan() {
    if (_numbers.size() < 2)
        throw std::logic_error("can't find a span for less than 2 elements");

    std::vector<unsigned int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    unsigned int min_span = sorted[1] - sorted[0];
    for (size_t i = 1; i < sorted.size() - 1; ++i) {
        unsigned int diff = sorted[i + 1] - sorted[i];
        if (diff < min_span) {
            min_span = diff;
        }
    }
    return min_span;
}

unsigned int Span::longestSpan() {
    if (_numbers.size() < 2)
        throw std::logic_error("can't find a span for less than 2 elements");

    std::vector<unsigned int>::iterator min_it = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<unsigned int>::iterator max_it = std::max_element(_numbers.begin(), _numbers.end());

    return *max_it - *min_it;
}