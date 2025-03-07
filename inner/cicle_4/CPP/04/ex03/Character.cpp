#include "Character.hpp"

Character::Character() 
: name("unknown") {
  for (int i = 0; i < 4; i++) {
    inventory[i] = NULL;
  }
}
Character::Character(const std::string& name) 
: name(name) {
  for (int i = 0; i < 4; i++) {
    inventory[i] = NULL;
  }
}
Character::Character(const Character& copy)
: name(copy.name) {
  for (int i = 0; i < 4; i++) {
     if (copy.inventory[i])
      inventory[i] = copy.inventory[i]->clone();
    else
      inventory[i] = NULL;
  }
}
Character& Character::operator=(const Character& ref) {
  if (this != &ref) {
    name = ref.name;
    for (int i = 0; i < 4; i++) {
      if (inventory[i])
        delete inventory[i];
      if (ref.inventory[i])
        inventory[i] = ref.inventory[i]->clone();
      else
        inventory[i] = NULL;
    }
  }
  return *this;
}
Character::~Character() {
  for (int i = 0; i < 4; i++) {
    if (inventory[i])
      delete inventory[i];
  }
}

const std::string& Character::getName() const { return name; }

void Character::equip(AMateria* m) {
  for (int i = 0; i < 4; i++) {
    if (!inventory[i]) {
      inventory[i] = m;
      break;
    }
  }
}
void Character::unequip(int idx) {
  if (idx >= 0 && idx < 4) {
    inventory[idx] = NULL;
  }
}
void Character::use(int idx, ICharacter& target) {
  if (idx >= 0 && idx < 4 && inventory[idx])
    inventory[idx]->use(target);    
}