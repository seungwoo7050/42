#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	ScavTrap agu1("아구몬");
	ScavTrap papi1("파피몬");
	ScavTrap agu2(agu1);
	ScavTrap papi2;
	papi2 = papi1;
	
	agu1.guardGate();
	agu1.attack("파피몬");
	papi1.takeDamage(agu1.getAttackDamage());
	papi1.beRepaired(agu1.getAttackDamage());
	
	return (0);
}