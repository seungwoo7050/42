#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
private:
  const std::string name;
  bool  is_signed;
  const int grade_required_to_sign;
  const int grade_required_to_exec;


  // internal function
  void checkGrade(int grade) const;

public:
  // OCCF
  Form();
  Form(std::string name, int grts, int grte);
  Form(const Form& copy);
  Form& operator=(const Form& ref);
  ~Form();


  // required member function
  std::string getName() const;
  bool        getIsSigned() const;
  int         getGradeRequiredToSign() const;
  int         getGradeRequiredToExec() const;

  void beSigned(const Bureaucrat& bureaucrat);


  // custom exception
  class GradeTooHighException : public std::exception {
    const char* what() const throw();
  };
  class GradeTooLowException : public std::exception {
    const char* what() const throw();
  };
};

// required function
std::ostream& operator<<(std::ostream& os, Form& ref);

#endif