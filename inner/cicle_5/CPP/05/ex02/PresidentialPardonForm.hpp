#ifndef __PRESIDENTIALPARDONFORM_HPP__
#define __PRESIDENTIALPARDONFORM_HPP__

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
private:
  std::string target;

public:
  // OCCF
  PresidentialPardonForm();
  PresidentialPardonForm(std::string target);
  PresidentialPardonForm(const PresidentialPardonForm& copy);
  PresidentialPardonForm& operator=(const PresidentialPardonForm& copy);
  ~PresidentialPardonForm();

  void execute(Bureaucrat const & bureaucrat) const;
};

#endif