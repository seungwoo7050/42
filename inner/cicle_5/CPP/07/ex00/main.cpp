#include <iostream>
#include <string>
#include "whatever.hpp"

int main(void) {
  int a = 42;
  int b = 24;

  std::cout << std::endl << std::endl;
  std::cout << "*** Test: Int ***" << std::endl;
  std::cout << "a: " << a << ", b: " << b << std::endl << std::endl;
  ::swap(a, b);
  std::cout << "* After the swap" << std::endl;
  std::cout << "a: " << a << ", b: " << b << std::endl ;
  std::cout << "max(a, b): " << ::max(a, b) << std::endl;
  std::cout << "min(a, b): " << ::min(a, b) << std::endl;

  std::string c = "42";
  std::string d = "world";

  std::cout << std::endl << std::endl;
  std::cout << "*** Test: String ***" << std::endl;
  std::cout << "c: " << c << ", d: " << d << std::endl << std::endl;
  ::swap(c, d);
  std::cout << "* After the swap" << std::endl;
  std::cout << "c: " << c << ", d: " << d << std::endl;
  std::cout << "max(c, d): " << ::max(c, d) << std::endl;
  std::cout << "min(c, d): " << ::min(c, d) << std::endl;

  return 0;
}