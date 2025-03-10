#include <iostream>
#include <exception>
#include "RPN.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <rpn expression>" << std::endl;
    return 1;
  }
  try {
    RPN rpn(argv[1]);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  return 0;
}