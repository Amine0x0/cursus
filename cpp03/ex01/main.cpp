#include "ScavTrap.hpp"

int main()
{
    ScavTrap Bot1("Bot1");
    Bot1.attack("Enemy");
    Bot1.takeDamage(30);
    Bot1.beRepaired(10);
    Bot1.guardGate();
    return 0;
}
