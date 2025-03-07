#ifndef __SCAV_TRAP_HPP__
#define __SCAV_TRAP_HPP__

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public: 
  ScavTrap();
  ScavTrap(std::string name);
  ~ScavTrap();
  ScavTrap(const ScavTrap& copy);
  ScavTrap& operator=(const ScavTrap& ref);

  void  attack(const std::string& target);
  void  guardGate();
};

#endif