#include "Animal.hpp"

AAnimal::AAnimal() : type("AAnimal"){
	std::cout << "AAnimal is created!" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other){
	std::cout << "AAnimal copy constructor called!" << std::endl;
	this->type = other.type;
}

AAnimal& AAnimal::operator=(const AAnimal& other){
	if (this != &other){
		this->type = other.type;
	}
	return *this;
}

AAnimal::~AAnimal() {
	std::cout << "AAnimal is destroyed!" << std::endl;
}

std::string AAnimal::getType() const {
	return this->type;
}
