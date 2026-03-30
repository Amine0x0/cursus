#ifndef HUMAN_A_HPP
#define HUMAN_A_HPP

#include "Weapon.hpp"
#include <string>
#include <iostream>

class HumanA {
    private:
        std::string name;
        Weapon &weapon;
    public:
        HumanA(std::string name, Weapon &weapon);
        void attack() const;
};

#endif
