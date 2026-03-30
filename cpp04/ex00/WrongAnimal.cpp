#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal"){
    std::cout << "WrongAnimal is created!" << std::endl;
};

WrongAnimal::WrongAnimal(const WrongAnimal& other){
    std::cout << "WrongAnimal copy constructor called!" << std::endl;
    this->type = other.type;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other){
    if (this != &other){
        this->type = other.type;
    }
    return *this;
}

WrongAnimal::~WrongAnimal() {
    std::cout << "WrongAnimal is destroyed" << std::endl; 
}

void WrongAnimal::makeSound() const {
    std::cout << "wrong animal sound..." << std::endl;
}

std::string WrongAnimal::getType() const {
    return this->type;
}
