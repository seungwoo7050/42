#ifndef __BUREAUCRAT_HPP__
#define __BUREAUCRAT_HPP__

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat {
private:
  const std::string name;
  int               grade;


  // internal function
  void  checkGrade(int grade) const;

public:
  // OCCF
  Bureaucrat();
  Bureaucrat(std::string name, int grade);
  Bureaucrat(const Bureaucrat& copy);
  Bureaucrat& operator=(const Bureaucrat& ref);
  ~Bureaucrat();


  // required member function
  std::string getName() const;
  int         getGrade() const;

  void  incrementGrade();
  void  decrementGrade();


   // custom exception
  class GradeTooHighException : public std::exception {
    const char* what() const throw();
  };
  class GradeTooLowException : public std::exception {
    const char* what() const throw();
  };
};


// required function
std::ostream& operator<<(std::ostream& os, Bureaucrat& ref);

#endif