#include "Cat.hpp"

Cat::Cat() : Animal() {
	brain = new Brain();
	type = "Cat";
	std::cout << "Cat is created!" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
	std::cout << "Cat copy constructor called!" << std::endl;
	brain = new Brain(*other.brain);
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "Cat assignment operator called!" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		*brain = *other.brain;
	}
	return *this;
}

Cat::~Cat() {
	delete brain;
	std::cout << "Cat is destroyed!" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Meow!" << std::endl;
}
