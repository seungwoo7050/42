#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
  std::cout << "A Cat is born." << std::endl;
  brain = new Brain();
}
Cat::Cat(const Cat& copy) : Animal(copy) { 
  if (this != &copy)
    brain = new Brain(*copy.brain);
}
Cat& Cat::operator=(const Cat& ref) { 
  if (this != &ref) {
    Animal::operator=(ref);
    delete brain;
    brain = new Brain(*ref.brain);
  }
  return *this;  
}
Cat::~Cat() {
  delete brain;
  std::cout << "A Cat is dead." << std::endl;
}

void  Cat::makeSound() const {
  std::cout << "Meow !!" << std::endl;
}