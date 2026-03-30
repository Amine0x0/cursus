#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal() {
    type = "WrongCat";
    std::cout << "WrongCat is created!" << std::endl;
};

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other){
    std::cout << "WrongCat copy constructor called!" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other){
    if (this != &other){
       WrongAnimal::operator=(other);
    }
    return *this;
}

WrongCat::~WrongCat() {
    std::cout << "WrongCat is destroyed" << std::endl; 
}

void WrongCat::makeSound() const {
    std::cout << "Wrong Meow!" << std::endl;
}
