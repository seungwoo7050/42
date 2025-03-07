#ifndef __HUMANA_HPP__
#define __HUMANA_HPP__

#include "Weapon.hpp"
#include <iostream>

class HumanA {
private:
  std::string name;
  Weapon&     weapon;

public:
  HumanA(std::string _name, Weapon& _weapon);
  void  attack();

};

#endif