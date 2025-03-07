#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
  std::cout << "ScavTrap " << name << " default constructor called !" << std::endl;
  hit_point = 100;
  energy_point = 50;
  attack_damage = 20;
}
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
  std::cout << "ScavTrap " << name << " constructor called !" << std::endl;
  hit_point = 100;
  energy_point = 50;
  attack_damage = 20;
}
ScavTrap::ScavTrap(const ScavTrap& copy) : ClapTrap(copy) {
  std::cout << "ScavTrap " << name << " copy constructor called !" << std::endl;
}
ScavTrap& ScavTrap::operator=(const ScavTrap& ref) {
  ClapTrap::operator=(ref);
  return *this;
}
ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap " << name << " destructor called !" << std::endl;
}


void ScavTrap::attack(const std::string &target) {
  if (energy_point <= 0 || hit_point <= 0) {
    std::cout << "ScavTrap " << name << " is out of energy or hit point." << std::endl;
  } else {
    std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
  }
  energy_point -= 1;
}
void ScavTrap::guardGate() {
  if (energy_point <= 0 || hit_point <= 0) {
    std::cout << "ScavTrap " << name << " is out of energy or hit point." << std::endl;
  } else {
    std::cout << "ScavTrap " << name << " is now in Gate keeper mode." << std::endl;
  }
}