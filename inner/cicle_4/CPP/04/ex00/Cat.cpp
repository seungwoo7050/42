#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
  std::cout << "A Cat is born." << std::endl;
}
Cat::Cat(const Cat& copy) : Animal(copy) { 
  if (this != &copy) {
    std::cout << "A CopyCat is born." << std::endl;
  }  
}
Cat& Cat::operator=(const Cat& ref) { 
  if (this != &ref) {
    Animal::operator=(ref);
  }
  return *this;
}
Cat::~Cat() {
  std::cout << "A Cat is dead." << std::endl;
}

void  Cat::makeSound() const {
  std::cout << "Meow !!" << std::endl;
}