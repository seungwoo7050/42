#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>
#include <iostream>

class ICharacter;

class AMateria {
protected:
  std::string type;

public:
  AMateria();
  AMateria(const std::string& type);
  AMateria(const AMateria& copy);
  AMateria& operator=(const AMateria& ref);
  virtual ~AMateria();

  const std::string& getType() const;

  virtual AMateria* clone() const = 0;
  virtual void use(ICharacter& target);

};
//

#endif