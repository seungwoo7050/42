#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
  std::cout << "A WrongAnimal is born." << std::endl;
}
WrongAnimal::WrongAnimal(std::string type) : type(type) {
  std::cout << "A WrongAnimal is born." << std::endl;
}
WrongAnimal::WrongAnimal(const WrongAnimal& copy) {
  if (this != &copy) {
    type = copy.type;
  }
}
WrongAnimal& WrongAnimal::operator=(const WrongAnimal& ref) {
   if (this != &ref) {
    type = ref.type;
  }
  return *this;
}
WrongAnimal::~WrongAnimal() {
  std::cout << "A WrongAnimal is dead." << std::endl;
}

std::string WrongAnimal::getType() const { return type; }
void WrongAnimal::makeSound() const {
  std::cout << "I can't cry." <<std::endl;
}