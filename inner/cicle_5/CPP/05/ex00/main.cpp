#include "Bureaucrat.hpp"

int main(void) {

  std::cout << std::endl << std::endl;

  // TEST Case 1
  std::cout << "Test1: Insertion overload" << std::endl;
  Bureaucrat test1("Insertion", 42);
  std::cout << test1 << std::endl;


  // TEST Case 2
  std::cout << std::endl << std::endl;
  std::cout << "Test2: An out of range grade, 0" << std::endl;
  try {
    Bureaucrat test2("Grade: 0", 0);
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  

  // TEST Case 3
  std::cout << std::endl << std::endl;
  std::cout << "Test3: An out of range grade, 151" << std::endl;
  try {
    Bureaucrat test3("Grade: 151", 151);
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }


  // TEST Case 4
  std::cout << std::endl << std::endl;
  std::cout << "Test4: Invalid increase" << std::endl;
  try {
    Bureaucrat test4("Grade: 1", 1);
    test4.incrementGrade();
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }


  // TEST Case 5
  std::cout << std::endl << std::endl;
  std::cout << "Test5: Invalid decrease" << std::endl;
  try {
    Bureaucrat test5("Grade: 150", 150);
    test5.decrementGrade();
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << std::endl << std::endl;
  std::cout << "Test COMPLETE !!" << std::endl;

  return 0;
}