#ifndef __ZOMBIE_HPP__
#define __ZOMBIE_HPP__

#include <iostream>
#include <string>

class Zombie {
private:
  std::string name;

public:
  Zombie( std::string _name );
  ~Zombie();
  void  announce(void);
};

Zombie* newZombie( std::string name );
void    randomChump( std::string name );

#endif