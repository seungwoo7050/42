#ifndef __CLAPTARP_HPP__
#define __CLAPTARP_HPP__

#include <string>
#include <iostream>

class ClapTrap {
private:
  std::string name;
  int         hit_point;
  int         energy_point;
  int         attack_damage;

public:
  ClapTrap();
  ClapTrap(std::string _name);
  ~ClapTrap();
  ClapTrap(const ClapTrap& copy);
  ClapTrap& operator=(const ClapTrap& ref);

  void          attack(const std::string& target);
  void          takeDamage(unsigned int amount);
  void          beRepaired(unsigned int amount);
  unsigned int  getAttackDamage() const;
};

#endif