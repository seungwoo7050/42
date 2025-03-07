#include "HumanB.hpp"

HumanB::HumanB(std::string _name) : name(_name) {
  weapon = NULL;
}

void  HumanB::attack() {
  if (this->weapon == NULL) {
    std::cout << name << " does not have a weapon." << std::endl;
  } else {
    std::cout << name << " attacks with their " << weapon->getType() << std::endl;
  }
}
void  HumanB::setWeapon(Weapon& ref) {
  weapon = &ref;
}