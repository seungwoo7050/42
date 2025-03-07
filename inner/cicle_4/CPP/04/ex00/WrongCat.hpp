#ifndef __WRONGCAT_HPP__
#define __WRONGCAT_HPP__

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
public:
  WrongCat();
  WrongCat(const WrongCat& copy);
  WrongCat& operator=(const WrongCat& ref);
  ~WrongCat();

  void makeSound() const;
};

#endif