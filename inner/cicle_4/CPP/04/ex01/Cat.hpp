#ifndef __CAT_HPP__
#define __CAT_HPP__

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
private:
  Brain*  brain;

public:
  Cat();
  Cat(const Cat& copy);
  Cat& operator=(const Cat& ref);
  ~Cat();

  void makeSound() const;
};

#endif