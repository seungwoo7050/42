#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <cstdlib>  //std::rand, std::srand
#include <ctime>    // std::time
#include <iostream>
#include <fstream>  // ifstream
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif