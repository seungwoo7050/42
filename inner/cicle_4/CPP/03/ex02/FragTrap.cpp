#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
  std::cout << "FragTrap " << name << " default constructor called !" << std::endl;
  hit_point = 100;
  energy_point = 100;
  attack_damage = 30;
}
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
  std::cout << "FragTrap " << name << " constructor called !" << std::endl;
  hit_point = 100;
  energy_point = 100;
  attack_damage = 30;
}
FragTrap::FragTrap(const FragTrap& copy) : ClapTrap(copy) {
  std::cout << "FragTrap " << name << " copy constructor called !" << std::endl;
}
FragTrap& FragTrap::operator=(const FragTrap& ref) {
  ClapTrap::operator=(ref);
  return *this;
}
FragTrap::~FragTrap() {
  std::cout << "FragTrap " << name << " destructor called !" << std::endl;
}

void FragTrap::highFivesGuys() {
  if (energy_point <= 0 || hit_point <= 0) {
    std::cout << "FragTrap " << name << " is out of energy or hit point." << std::endl;
  } else {
    std::cout << "FragTrap " << name << " asks for a high five." << std::endl;
  }
}