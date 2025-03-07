#include "Animal.hpp"

Animal::Animal() {
  std::cout << "An Animal is born." << std::endl;
}
Animal::Animal(std::string type) : type(type) {
  std::cout << "Animal is born." << std::endl;
}
Animal::Animal(const Animal& copy) {
  if (this != &copy) {
    type = copy.type;
  }
  std::cout << "A CopyAnimal is born." << std::endl;
}
Animal& Animal::operator=(const Animal& ref) {
   if (this != &ref) {
    type = ref.type;
  }
  return *this;
}
Animal::~Animal() {
  std::cout << "An Animal is dead." << std::endl;
}

std::string Animal::getType() const { return type; }
void Animal::makeSound() const {
  std::cout << "I can't cry." <<std::endl;
}