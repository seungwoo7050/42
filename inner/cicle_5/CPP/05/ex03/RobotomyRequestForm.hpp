#ifndef __ROBOTOMYREQUESTFORM_HPP__
#define __ROBOTOMYREQUESTFORM_HPP__

#include <cstdlib>  // for rand(), srand()
#include <ctime>    // for time()
#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
private:
  std::string target;

public:
  // OCCF
  RobotomyRequestForm();
  RobotomyRequestForm(std::string target);
  RobotomyRequestForm(const RobotomyRequestForm& copy);
  RobotomyRequestForm& operator=(const RobotomyRequestForm& copy);
  ~RobotomyRequestForm();

  void execute(Bureaucrat const & bureaucrat) const;
};

#endif