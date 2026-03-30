#include "Dog.hpp"

Dog::Dog() : AAnimal() {
	brain = new Brain();
	type = "Dog";
	std::cout << "Dog is created!" << std::endl;
}

Dog::Dog(const Dog& other) : AAnimal(other) {
	std::cout << "Dog copy constructor called!" << std::endl;
	brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog assignment operator called!" << std::endl;
	if (this != &other) {
		AAnimal::operator=(other);
		*brain = *other.brain;
	}
	return *this;
}

Dog::~Dog() {
	delete brain;
	std::cout << "Dog is destroyed!" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Woof!" << std::endl;
}
