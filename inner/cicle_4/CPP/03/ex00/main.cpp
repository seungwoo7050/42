#include "ClapTrap.hpp"

int main()
{
	ClapTrap agu1("아구몬");
	ClapTrap papi1("파피몬");
	ClapTrap agu2(agu1);
	ClapTrap papi2;
	papi2 = papi1;
	
	agu1.attack("파피몬");
	papi1.takeDamage(agu1.getAttackDamage());
	papi1.beRepaired(1);	
	
	return (0);
}