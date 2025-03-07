#include "Weapon.hpp"

Weapon::Weapon(std::string _type) : type(_type) {}

std::string&  Weapon::getType(void) { return type; }
void          Weapon::setType(std::string type) { this->type = type; }