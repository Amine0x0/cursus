#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap(){
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;

    std::cout << "ScavTrap default constructor called!" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name){
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;

    std::cout << "ScavTrap created under the name : [" << name << "]!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other){
    std::cout << "ScavTrap copy constructor called!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other){
    if (this != &other){
        ClapTrap::operator=(other);
    }
    std::cout << "ScavTrap assignement operator called!" << std::endl;
    return *this;
}

ScavTrap::~ScavTrap(){
    std::cout << "ScavTrap [" << name << "] is destroyed!" << std::endl;
}

void ScavTrap::attack(const std::string& target){
    if (hitPoints == 0){
        std::cout << "ScavTrap " << name << " is dead and cannot attack!" << std::endl;
        return ;
    }
    if (energyPoints == 0){
        std::cout << "ScavTrap " << name << " has no energy left to attack!" << std::endl;
        return ;
    }
    energyPoints--;
    std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate(){
    std::cout << "ScavTrap " << name << " is now in Gate keeper mode!" << std::endl;
}
