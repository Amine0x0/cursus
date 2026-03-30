#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap(){
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;

    std::cout << "FragTrap default constructor called!" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name){
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;

    std::cout << "FragTrap created under the name : [" << name << "]!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other){
    std::cout << "FragTrap copy constructor called!" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other){
    if (this != &other){
        ClapTrap::operator=(other);
    }
    std::cout << "FragTrap assignement operator called!" << std::endl;
    return *this;
}

FragTrap::~FragTrap(){
    std::cout << "FragTrap [" << name << "] is destroyed!" << std::endl;
}

void FragTrap::attack(const std::string& target){
    if (hitPoints == 0){
        std::cout << name << " is dead and cannot attack!" << std::endl;
        return ;
    }
    if (energyPoints == 0){
        std::cout << name << " has no energy left to attack!" << std::endl;
        return ;
    }
    energyPoints--;
    std::cout << "FragTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void){
    std::cout << "FragTrap " << name << " requests a high five!" << std::endl;
}
