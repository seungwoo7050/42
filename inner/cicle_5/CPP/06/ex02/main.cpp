#include "Utils.hpp"

int main() {
  Base* base = generate();
  
  std::cout << "Identify by pointer: ";
  identify(base);
  
  std::cout << "Identify by reference: ";
  identify(*base);

  return 0;
}