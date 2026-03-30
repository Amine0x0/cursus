#include "ClapTrap.hpp"

int main()
{
    ClapTrap Bot1("Bot1");
    Bot1.attack("Enemy");
    Bot1.takeDamage(5);
    Bot1.beRepaired(3);
    return 0;
}
