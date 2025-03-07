#include "Harl.hpp"
#include <cstdio>

int main() {
  std::string input;
  Harl        harl;

  while (true) {
    std::cout << "Enter a level: ";
    std::getline(std::cin, input);
    if (!input.compare("EXIT")) {
      return 0;
    }      
    if (std::cin.eof()) {
      clearerr(stdin);
      std::cin.clear();
      std::cout << std::endl;
    } else {
      harl.complain(input);
    }
  }
  return (0);
}