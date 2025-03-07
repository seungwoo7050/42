#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
  std::cout << "A Dog is born." << std::endl;
}
Dog::Dog(const Dog& copy) : Animal(copy) {
  if (this != &copy) {
    std::cout << "A CopyDog is born." << std::endl;
  }
}
Dog& Dog::operator=(const Dog& ref) { 
  if (this != &ref) {
    Animal::operator=(ref);
  } 
  return *this; 
}
Dog::~Dog() {
  std::cout << "A Dog is dead." << std::endl;
}

void  Dog::makeSound() const {
  std::cout << "Bark !!" << std::endl;
}