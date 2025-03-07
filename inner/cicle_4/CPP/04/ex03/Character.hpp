#ifndef CHARCTER_HPP
#define CHARCTER_HPP

#include "ICharacter.hpp"

class Character : public ICharacter {
private:
  std::string name;
  AMateria* inventory[4];

public:
  Character();
  Character(const std::string& name);
  Character(const Character& copy);
  Character& operator=(const Character& ref);
  virtual ~Character();

  const std::string& getName() const;
  void equip(AMateria* m);
  void unequip(int idx);
  void use(int idx, ICharacter& target);  
};

#endif