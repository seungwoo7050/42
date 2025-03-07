#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <sstream>
#include <stack>
#include <exception>
#include <iostream>

class RPN {
private:
  RPN(const RPN&);
  RPN& operator=(const RPN&);  

public:
  RPN();
  RPN(const std::string& input);
  ~RPN();
};

#endif