#include "Fixed.hpp"

Fixed::Fixed(){
    value = 0;
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n){
    std::cout << "Int constructor called" << std::endl;
    value = n << FractBits;
}

Fixed::Fixed(const float f){
    std::cout << "Float constructor called" << std::endl;
    value = roundf(f * (1 << FractBits));
}

Fixed::Fixed(const Fixed& other){
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed& Fixed::operator=(const Fixed& other){
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->value = other.getRawBits();
    return *this;
}

Fixed::~Fixed(){
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
    return value;
}

void Fixed::setRawBits(int const raw){
    value = raw;
}

float Fixed::toFloat(void) const {
    return (float)value / (1 << FractBits);
}

int Fixed::toInt(void) const {
    return value >> FractBits;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed){
    os << fixed.toFloat();
    return os;
}