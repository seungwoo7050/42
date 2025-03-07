#include "RobotomyRequestForm.hpp"

// OCCF
RobotomyRequestForm::RobotomyRequestForm()
  : AForm("robotomy", 72, 45), target("noTarget") {
  std::cout << "Default constructor set Robotomy target: `noTarget`" << std::endl;
}
RobotomyRequestForm::RobotomyRequestForm(std::string target)
  : AForm("robotomy", 72, 45), target(target) { }
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
  : AForm(copy), target(copy.target) {}
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& ref) {
  if (this != &ref) {
    AForm::operator=(ref);
    target = ref.target;
  }
  return *this;
}
RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const & bureaucrat) const {
  checkExecutable(bureaucrat);
  std::cout << "Whirring....." << std::endl;
  srand(static_cast<unsigned int>(time(0)));
  if (rand() % 2) {
    std::cout << target << " has been successfully robotomized." << std::endl;
  } else {
    std::cout << target << " failed to robotomized." << std::endl;
  }
}