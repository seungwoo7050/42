#ifndef __DOG_HPP__
#define __DOG_HPP__

#include "Animal.hpp"

class Dog : public Animal {
public:
  Dog();
  Dog(const Dog& copy);
  Dog& operator=(const Dog& ref);
  ~Dog();

  void makeSound() const;
};

#endif