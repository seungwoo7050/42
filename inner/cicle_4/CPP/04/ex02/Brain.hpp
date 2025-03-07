#ifndef __BRAIN_HPP__
#define __BRAIN_HPP__

#include <string>
#include <iostream>

class Brain {
private:
  std::string ideas[100];

public:
  Brain();
  Brain(const Brain& copy);
  Brain& operator=(const Brain& ref);
  ~Brain();
};

#endif