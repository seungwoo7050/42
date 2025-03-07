#ifndef __HUMANB_HPP__
#define __HUMANB_HPP__

#include "Weapon.hpp"
#include <iostream>

class HumanB {
private:
  std::string name;
  Weapon      *weapon;

public:
  HumanB(std::string _name);
  
  void  setWeapon(Weapon &ref);
  void  attack();

};

#endif