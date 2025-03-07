#include "Intern.hpp"

// OCCF
Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern& ref) {
  if (this != &ref) {
    (*this) = ref;
  }
  return *this;
}
Intern::~Intern() {}

// required member function
AForm* Intern::makeForm(std::string name, std::string target) {
  AForm* by_intern = NULL;

  if (name == "shrubbery creation") {
    by_intern = new ShrubberryCreationForm(target);
  } else if (name == "robotomy request") {
    by_intern = new RobotomyRequestForm(target);
  } else if (name == "presidential pardon") {
    by_intern = new PresidentialPardonForm(target);
  } else {
    throw DoesNotExistException();
  }

  std::cout << "Intern creates " << name << std::endl;

  return by_intern;
}

// custom exception
const char* Intern::DoesNotExistException::what() const throw() {
  return "Exception occurred: Intern::DoesNotExistException";
}