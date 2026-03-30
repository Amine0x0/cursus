#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

void    sep(){
    std::cout << "----- ----- -----" << std::endl;
}

int main()
{
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();
    delete j;
    delete i;
    sep();
    AAnimal* animals[10];
    for (int k = 0; k < 10; k++) {
        if (k < 5) {
            animals[k] = new Dog();
        } else {
            animals[k] = new Cat();
        }
    }
    sep();
    for (int k = 0; k < 10; k++) {
        animals[k]->makeSound();
    }
    for (int k = 0; k < 10; k++) {
        delete animals[k];
    }
    sep();
    Dog dog1;
    {
        Dog dog2 = dog1;
    }
    sep();
    Cat cat1;
    {
        Cat cat2 = cat1;
    }
    sep();
    Dog dog3;
    dog3 = dog1;
    sep();
    // AAnimal Test;
    return 0;
}