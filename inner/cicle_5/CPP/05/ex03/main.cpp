#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include "ShrubberryCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"


int main(void) {

  Bureaucrat a("a", 1);
  Bureaucrat z("z", 150);

  AForm* s1  = NULL;
  AForm* s2  = NULL;
  AForm* s3  = NULL;

  Intern i;

  std::cout << std::endl << std::endl;
  std::cout << "*** Test Intern's ShrubberyCreationForm ***" << std::endl << std::endl;
  s1 = i.makeForm("shrubbery creation", "shrubbery1");
  s2 = i.makeForm("shrubbery creation", "shrubbery2");
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
  std::cout << "*** Test Intern's RobotomyRequestForm ***" << std::endl << std::endl;
  s1 = i.makeForm("robotomy request", "robotomy1");
  s2 = i.makeForm("robotomy request", "robotomy2");
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
  std::cout << "*** Test Intern's PresidentialPardonForm ***" << std::endl << std::endl;
  s1 = i.makeForm("presidential pardon", "presiden1");
  s2 = i.makeForm("presidential pardon", "presiden2");
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
  std::cout << "*** Test Intern's Exception ***" << std::endl << std::endl;

  try {
    s1 = i.makeForm("shrubbery creation", "wrong1");
    s2 = i.makeForm("robotomy request", "wrong2");
    s3 = i.makeForm("presidential ardon", "wrong3");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  
  if (s1)
    delete s1;
  if (s2)
    delete s2;
  if (s3)
    delete s3;
  
  
  std::cout << std::endl << std::endl;
  std::cout << "Test COMPLETE !!" << std::endl;

  return 0;
}