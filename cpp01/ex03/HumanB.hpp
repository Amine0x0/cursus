#ifndef HUMAN_B_HPP
#define HUMAN_B_HPP

#include "Weapon.hpp"
#include <string>
#include <iostream>

class HumanB {
    private:
        std::string name;
        Weapon *weapon;
    public:
        HumanB(std::string name);
        ~HumanB();
        void setWeapon(Weapon &weapon);
        void attack() const;
};

#endif