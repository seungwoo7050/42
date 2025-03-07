#ifndef __FRAG_TRAP_HPP__
#define __FRAG_TRAP_HPP__

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
  FragTrap();
  FragTrap(std::string name);
  FragTrap(const FragTrap& copy);
  FragTrap& operator=(const FragTrap& ref);
  ~FragTrap();

  void highFivesGuys(void);
};

#endif