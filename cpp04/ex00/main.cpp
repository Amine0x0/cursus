#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"


void    sep(){
    std::cout << "----- ----- -----" << std::endl;
}

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    sep();
    i->makeSound();
    j->makeSound();
    meta->makeSound();
    sep();
    const WrongAnimal* meta2 = new WrongAnimal();
    const WrongAnimal* Wcat = new WrongCat();
    std::cout << Wcat->getType() << std::endl;
    Wcat->makeSound();
    sep();
    delete i;
    delete j;
    delete meta;
    delete meta2;
    delete Wcat;
    return 0;
}