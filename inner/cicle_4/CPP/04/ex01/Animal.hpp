#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include <iostream>
#include <string>

class Animal {
protected:
  std::string type;
  
public:
  Animal();
  Animal(std::string type);
  Animal(const Animal& copy);
  Animal& operator=(const Animal& ref);
  virtual ~Animal();
  
  std::string   getType() const;
  virtual void  makeSound() const;
};

#endif