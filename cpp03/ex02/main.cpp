#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    {
        FragTrap Bot1("Bot1");
        Bot1.attack("Enemy");
        Bot1.takeDamage(30);
        Bot1.beRepaired(10);
        Bot1.highFivesGuys();
    }
    std::cout << "-----" << std::endl;
    {
        ClapTrap clap("Clap1");
        ScavTrap scav("Scav1");
        FragTrap frag("Frag1");

        clap.attack("Target");
        scav.attack("Target");
        frag.attack("Target");
    }
    return 0;
}
