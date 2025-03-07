#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
  std::cout << "A Dog is born." << std::endl;
  brain = new Brain();
}
Dog::Dog(const Dog& copy) : Animal(copy) { 
  if (this != &copy)
    brain = new Brain(*copy.brain);
}
Dog& Dog::operator=(const Dog& ref) { 
  if (this != &ref) {
    Animal::operator=(ref);
    delete brain;
    brain = new Brain(*ref.brain);
  }  
  return *this;
}
Dog::~Dog() {
  delete brain;
  std::cout << "A Dog is dead." << std::endl;
}

void  Dog::makeSound() const {
  std::cout << "Bark !!" << std::endl;
}