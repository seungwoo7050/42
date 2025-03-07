#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	FragTrap agu1("아구몬");
	FragTrap papi1("파피몬");
	FragTrap agu2(agu1);
	FragTrap papi2;
	papi2 = papi1;
	
	agu1.highFivesGuys();
	agu1.attack("파피몬");
	papi1.takeDamage(agu1.getAttackDamage());
	papi1.beRepaired(agu1.getAttackDamage());	
	
	return (0);
}