#ifndef __AFORM_HPP__
#define __AFORM_HPP__

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
private:
  const std::string name;
  bool  is_signed;
  const int grade_required_to_sign;
  const int grade_required_to_exec;


  // internal function
  void checkGrade(int grade) const;

protected:  
  // OCCF
  AForm();
  AForm(std::string name, int grts, int grte);
  AForm(const AForm& copy);
  AForm& operator=(const AForm& ref);

public:
  // OCCF
  virtual ~AForm();


  // required member function
  std::string getName() const;
  bool getIsSigned() const;
  int getGradeRequiredToSign() const;
  int getGradeRequiredToExec() const;

  void beSigned(Bureaucrat& bureaucrat);
  
  virtual void execute(Bureaucrat const & executor) const = 0;


  // utility function
  void checkExecutable(const Bureaucrat& Bureaucrat) const;


  // custom exception
  class GradeTooHighException : public std::exception {
    const char* what() const throw();
  };
  class GradeTooLowException : public std::exception {
    const char* what() const throw();
  };
  class NotYetSignedException : public std::exception {
    const char* what() const throw();
  };
};

// required function
std::ostream& operator<<(std::ostream& os, AForm& ref);

#endif