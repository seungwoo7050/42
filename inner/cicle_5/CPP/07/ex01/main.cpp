#include <iostream>
#include "iter.hpp"

int main() {
  int int_array[] = {1,2,3,4,5};
  size_t int_array_length = sizeof(int_array) / sizeof(int_array[0]);

  std::cout << "*** int Array ***" << std::endl;
  std::cout << "Original array: ";
  iter(int_array, int_array_length, print);
  std::cout << std::endl;

  std::cout << "Doubled array: ";
  iter(int_array, int_array_length, doubleValue);
  iter(int_array, int_array_length, print);
  std::cout << std::endl;

  std::cout << "Incremented array: ";
  iter(int_array, int_array_length, increment);
  iter(int_array, int_array_length, print);
  std::cout << std::endl;

  std::cout << "Squared array: ";
  iter(int_array, int_array_length, square);
  iter(int_array, int_array_length, print);
  std::cout << std::endl;

  std::string str_array[] = { "A", "B", "C", "D", "E" };
  size_t str_array_length = sizeof(str_array) / sizeof(str_array[0]);

  std::cout << "*** std::string Array ***" << std::endl;
  std::cout << "Original array: ";
  iter(str_array, str_array_length, print);
  std::cout << std::endl;

  return 0;
}