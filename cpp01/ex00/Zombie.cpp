#include "Zombie.hpp"

Zombie::Zombie(std::string name) : name(name) {}

Zombie::~Zombie() {
    std::cout << name << " is now destroyed." << std::endl;
}

void    Zombie::announce(){
    if (!(name.empty()))
        std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}