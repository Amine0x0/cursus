#include "Zombie.hpp"

Zombie::Zombie() : name("") {}

Zombie::Zombie(std::string name) : name(name) {}

Zombie::~Zombie() {
    std::cout << name << " is now destroyed." << std::endl;
}

void    Zombie::announce(){
    if (!(name.empty()))
        std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
    return ;
}

void    Zombie::setName(std::string newName){
    name = newName;
}