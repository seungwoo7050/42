#ifndef __INTERN_HPP__
#define __INTERN_HPP__

#include <exception>

#include "AForm.hpp"
#include "ShrubberryCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
public:
  // OCCF
  Intern();
  Intern(const Intern&);
  Intern& operator=(const Intern& ref);
  ~Intern();

  // required member function
  AForm* makeForm(std::string name, std::string target);

  // custom exception
  class DoesNotExistException : public std::exception {
    const char* what() const throw();
  };
};

#endif