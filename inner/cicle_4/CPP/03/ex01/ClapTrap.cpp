#include "ClapTrap.hpp"

ClapTrap::ClapTrap() 
: name("unknown"), hit_point(10), energy_point(10), attack_damage(0) {
  std::cout << "ClapTrap " << name << " default constructor called !" << std::endl;
}
ClapTrap::ClapTrap(std::string _name)
: name(_name), hit_point(10), energy_point(10), attack_damage(0) {
  std::cout << "ClapTrap " << name << " constructor called !" << std::endl;
}
ClapTrap::ClapTrap(const ClapTrap& copy) {
  if (this != &copy) {
    name = copy.name;
    hit_point = copy.hit_point;
    energy_point = copy.energy_point;
    attack_damage = copy.attack_damage;
    std::cout << "ClapTrap " << name << " copy constructor called !" << std::endl;
  }
}
ClapTrap& ClapTrap::operator=(const ClapTrap& ref) {
  if (this != &ref) {
    name = ref.name;
    hit_point = ref.hit_point;
    energy_point = ref.energy_point;
    attack_damage = ref.attack_damage;
    std::cout << "ClapTrap " << name << " copy assignment operator called !" << std::endl;
  }
  return *this;
}
ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << name << " destructor called !" << std::endl;
}


void ClapTrap::attack(const std::string &target) {
  if (energy_point <= 0 || hit_point <= 0) {
    std::cout << "ClapTrap " << name << " is out of energy or hit point." << std::endl;
  } else {
    std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
  }
  energy_point -= 1;
}
void ClapTrap::takeDamage(unsigned int amount) {
  std::cout << "ClapTrap " << name << " takes " << amount << " damage !" << std::endl;
  hit_point -= amount;
}
void ClapTrap::beRepaired(unsigned int amount) {
  if (energy_point <= 0 || hit_point <= 0) {
    std::cout << "ClapTrap " << name << " is out of energy or hit point." << std::endl;
  } else {
    std::cout << "ClapTrap " << name << " repairs itself for " << amount << " point!" << std::endl;
  }
  energy_point -= 1;
  hit_point += amount;
}
unsigned int ClapTrap::getAttackDamage () const { return attack_damage; }