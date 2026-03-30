#include "Cat.hpp"

Cat::Cat() : AAnimal() {
	brain = new Brain();
	type = "Cat";
	std::cout << "Cat is created!" << std::endl;
}

Cat::Cat(const Cat& other) : AAnimal(other) {
	std::cout << "Cat copy constructor called!" << std::endl;
	brain = new Brain(*other.brain);
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "Cat assignment operator called!" << std::endl;
	if (this != &other) {
		AAnimal::operator=(other);
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
