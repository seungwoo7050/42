#include "PresidentialPardonForm.hpp"


PresidentialPardonForm::PresidentialPardonForm()
  : AForm("Presidential", 25, 5), target("noTarget") {
  std::cout << "Default constructor set Presidential target: `noTarget`" << std::endl;
}
PresidentialPardonForm::PresidentialPardonForm(std::string target)
  : AForm("Presidential", 25, 5), target(target) {}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& copy)
  : AForm(copy), target(copy.target) {}
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& ref) {
  if (this != &ref) {
    AForm::operator=(ref);
    target = ref.target;
  }
  return *this;
}
PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::execute(Bureaucrat const & bureaucrat) const {
  checkExecutable(bureaucrat);
  std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}