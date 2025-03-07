#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberryCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"


int main(void) {

  Bureaucrat a("a", 1);
  Bureaucrat z("z", 150);

  std::cout << std::endl << std::endl;
  std::cout << "*** Test ShrubberyCreationForm ***" << std::endl << std::endl;
  AForm* s1 = new ShrubberryCreationForm("shrubbery1");
  AForm* s2 = new ShrubberryCreationForm("shrubbery2");
  std::cout << "case1: Not signed, enough grade" << std::endl;
  a.executeForm(*s1);

  std::cout << std::endl;
  std::cout << "case2: Be signed, enough grade" << std::endl;
  a.signForm(*s1);
  a.executeForm(*s1);
  
  std::cout << std::endl;
  std::cout << "case3: Not signed, not enough grade" << std::endl;
  z.executeForm(*s2);
  
  std::cout << std::endl;
  std::cout << "case4: Be signed, not enough grade" << std::endl;
  a.signForm(*s2);
  z.executeForm(*s2);

  delete s1;
  delete s2;

  std::cout << std::endl << std::endl;
  std::cout << "*** Test RobotomyRequestForm ***" << std::endl << std::endl;
  s1 = new RobotomyRequestForm("robotomy1");
  s2 = new RobotomyRequestForm("robotomy2");
  std::cout << "case1: Not signed, enough grade" << std::endl;
  a.executeForm(*s1);

  std::cout << std::endl;
  std::cout << "case2: Be signed, enough grade" << std::endl;
  a.signForm(*s1);
  a.executeForm(*s1);
  
  std::cout << std::endl;
  std::cout << "case3: Not signed, not enough grade" << std::endl;
  z.executeForm(*s2);
  
  std::cout << std::endl;
  std::cout << "case4: Be signed, not enough grade" << std::endl;
  a.signForm(*s2);
  z.executeForm(*s2);

  delete s1;
  delete s2;

  std::cout << std::endl << std::endl;
  std::cout << "*** Test PresidentialPardonForm ***" << std::endl << std::endl;
  s1 = new PresidentialPardonForm("presiden1");
  s2 = new PresidentialPardonForm("presiden2");
  std::cout << "case1: Not signed, enough grade" << std::endl;
  a.executeForm(*s1);

  std::cout << std::endl;
  std::cout << "case2: Be signed, enough grade" << std::endl;
  a.signForm(*s1);
  a.executeForm(*s1);
  
  std::cout << std::endl;
  std::cout << "case3: Not signed, not enough grade" << std::endl;
  z.executeForm(*s2);
  
  std::cout << std::endl;
  std::cout << "case4: Be signed, not enough grade" << std::endl;
  a.signForm(*s2);
  z.executeForm(*s2);

  
  std::cout << std::endl << std::endl;
  std::cout << "Test COMPLETE !!" << std::endl;

  return 0;
}