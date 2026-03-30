#include "ClapTrap.hpp"

ClapTrap::ClapTrap(){
    name = "default";
    hitPoints = 10;
    energyPoints = 10;
    attackDamage = 0;

    std::cout << "ClapTrap default constructor called!" << std::endl;
}

ClapTrap::ClapTrap(std::string name){
    this->name = name;
    hitPoints = 10;
    energyPoints = 10;
    attackDamage = 0;

    std::cout << "Claptrap created under the name : [" << name << "]!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other){
    this->name = other.name;
    this->hitPoints = other.hitPoints;
    this->energyPoints = other.energyPoints;
    this->attackDamage = other.attackDamage;

    std::cout << "copy constructor called!" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other){
    if (this != &other){
        this->name = other.name;
        this->hitPoints = other.hitPoints;
        this->energyPoints = other.energyPoints;
        this->attackDamage = other.attackDamage;
    }
    std::cout << "assignement operator called!" << std::endl;
    return *this;
}

ClapTrap::~ClapTrap(){
    std::cout << "ClapTrap [" << name << "] is destroyed!" << std::endl;
}


void ClapTrap::attack(const std::string& target){
    if (hitPoints == 0){
        std::cout << name << " is dead and cannot attack!" << std::endl;
        return ;
    }
    if (energyPoints == 0){
        std::cout << name << " has no energy left to attack!" << std::endl;
        return ;
    }
    energyPoints--;
    std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount){
    if (hitPoints == 0){
        std::cout << name << " is already dead!" << std::endl;
        return ;
    }
    if (amount >= hitPoints){
        hitPoints = 0;
        std::cout << name << " takes " << amount << " damage and dies!" << std::endl;
    }
    else{
        hitPoints -= amount;
        std::cout << name << " takes " << amount << " damage! HP remaining: " << hitPoints << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount){
    if (hitPoints == 0){
        std::cout << name << " is dead and cannot be repaired!" << std::endl;
        return ;
    }
    if (energyPoints == 0){
        std::cout << name << " has no energy left to repair!" << std::endl;
        return ;
    }
    energyPoints--;
    hitPoints += amount;
    std::cout << name << " repairs itself for " << amount << " HP! HP is now: " << hitPoints << std::endl;
}