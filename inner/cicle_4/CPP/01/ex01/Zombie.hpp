#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__

#include <iostream>
#include <string>

class Zombie {
private:
  std::string name;

public:
  Zombie();
  Zombie( std::string _name );
  ~Zombie();

  void  announce(void);
  void  setName(std::string name);
};

Zombie* zombieHorde(int N, std::string name);

#endif