#include "Animal.hpp"

Animal::Animal() : type("Animal"){
    std::cout << "Animal is created!" << std::endl;
};

Animal::Animal(const Animal& other){
    std::cout << "Animal copy constructor called!" << std::endl;
    this->type = other.type;
}

Animal& Animal::operator=(const Animal& other){
    if (this != &other){
        this->type = other.type;
    }
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal is destroyed" << std::endl; 
}

void Animal::makeSound() const {
    std::cout << "generic animal sound..." << std::endl;
}

std::string Animal::getType() const {
    return this->type;
}