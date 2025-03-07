#ifndef __SEDIFL_HPP__
#define __SEDIFL_HPP__

#include <fstream>
#include <string>
#include <iostream>

class SedIFL {
private:
  std::string filename;

public:
  SedIFL(std::string _filename);
  
  int replace(std::string origin, std::string replace);
};

#endif