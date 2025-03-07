#include "Bureaucrat.hpp"
#include "Form.hpp"


int main(void) {

  std::cout << std::endl << std::endl;
  
  // TEST Case 1
  std::cout << "Test1: Insertion overload" << std::endl;
  Form test1("Insertion", 42, 42);
  std::cout << test1 << std::endl;


  // TEST Case 2
  std::cout << std::endl << std::endl;
  std::cout << "Test2: An out of range sign grade, 0" << std::endl;
  try {
    Form test2("Sign Grade: 0", 0, 42);
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }


  // TEST Case 3
  std::cout << std::endl << std::endl;
  std::cout << "Test3: An out of range sign grade, 151" << std::endl;
  try {
    Form test3("Sign Grade: 151", 151, 42);
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  

  // TEST Case 4
  std::cout << std::endl << std::endl;
  std::cout << "Test4: An out of range exec grade, 0" << std::endl;
  try {
    Form test4("Exec Grade: 0", 42, 0);
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }


  // TEST Case 5
  std::cout << std::endl << std::endl;
  std::cout << "Test5: An out of range exec grade, 151" << std::endl;
  try {
    Form test5("Exec Grade: 151", 42, 151);
    return 0;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }


  // TEST Case 6
  std::cout << std::endl << std::endl;
  std::cout << "Test6: Sign successfully" << std::endl;
  Bureaucrat test6("Grade: 1", 1);
  Form test7("Form(42)", 42, 42);
  test6.signForm(test7);


  // TEST Case 7
  std::cout << std::endl << std::endl;
  std::cout << "Test7: Be already signed" << std::endl;
  test6.signForm(test7);


  // TEST Case 8
  std::cout << std::endl << std::endl;
  std::cout << "Test8: Too low grade to sign" << std::endl;
  try {
    Form test8("Form(42)", 42, 42);
    Bureaucrat test6("Grade: 43", 43);
    test6.signForm(test8);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  
  std::cout << std::endl << std::endl;
  std::cout << "Test COMPLETE !!" << std::endl;

  return 0;
}