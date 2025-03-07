#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
  std::cout << "A WrongCat is born." << std::endl;
}
WrongCat::WrongCat(const WrongCat& copy) : WrongAnimal(copy) { }
WrongCat& WrongCat::operator=(const WrongCat& ref) { 
  WrongAnimal::operator=(ref);
  return *this;
}
WrongCat::~WrongCat() {
  std::cout << "A WrongCat is dead." << std::endl;
}

void  WrongCat::makeSound() const {
  std::cout << "Meow !!" << std::endl;
}