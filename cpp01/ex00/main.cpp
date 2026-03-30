#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main() {
    std::cout << "announcing from stack..." << std::endl;
    randomChump("Bruh");
    
    std::cout << "annoucing from heap" << std::endl;
    Zombie *z = new Zombie("bruhhhh");

    z->announce();
    delete z;
    return (0);
}