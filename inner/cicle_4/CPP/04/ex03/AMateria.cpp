#include "AMateria.hpp"

AMateria::AMateria() : type("unknown") {}
AMateria::AMateria(const std::string& type) : type(type) {}
AMateria::AMateria(const AMateria& copy) 
: type(copy.type) { }
AMateria& AMateria::operator=(const AMateria& ref) {
  if (this != &ref) {
    type = ref.type;
  }
  return *this;
}
AMateria::~AMateria() {}

const std::string& AMateria::getType() const {
  return type;
}
void AMateria::use(ICharacter& target) {
  (void)target;
}
