#include "Bureaucrat.hpp"

// internal function
void  Bureaucrat::checkGrade(int grade) const {
  if (grade < 1)
    throw GradeTooHighException();
  else if (grade > 150)
    throw GradeTooLowException();
}


// OCCF
Bureaucrat::Bureaucrat()
  : name("Bureaucrat"), grade(75) {
  std::cout << "Default constructor set Bureaucrat name: `Bureaucrat`, grade: `75`" << std::endl;
}
Bureaucrat::Bureaucrat(std::string name, int grade)
  : name(name), grade(grade) {
  checkGrade(grade);
}
Bureaucrat::Bureaucrat(const Bureaucrat& copy)
  : name(copy.name), grade(copy.grade) {
  checkGrade(grade);
}
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& ref) {
  if (this != &ref) {
    grade = ref.grade;
    checkGrade(grade);
  }
  return *this;
}
Bureaucrat::~Bureaucrat() {}


// required member function
std::string Bureaucrat::getName() const { return name; }
int         Bureaucrat::getGrade() const { return grade; }

void  Bureaucrat::incrementGrade() {
  checkGrade(grade - 1);
  grade--;
}
void  Bureaucrat::decrementGrade() {
  checkGrade(grade + 1);
  grade++;
}
void Bureaucrat::signForm(AForm& form) {
  if (form.getIsSigned() == false) {
    try {
      form.beSigned(*this);
      std::cout << name << " signed " << form.getName() << std::endl;
    } catch (std::exception& e) {
      std::cout << name << " couldn't sign " << form.getName() << " because ";
      std::cout << e.what() << std::endl;
    }
  } else {
    std::cout << name << " can't sign this " << form.getName() << " because It's already done." << std::endl;
  }   
}
void Bureaucrat::executeForm(const AForm& form) const {
  try {
    form.execute(*this);
    std::cout << name << " executed " << form.getName() << std::endl;
  } catch (std::exception& e) {
    std::cout << name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
  }
}


// custom exception
const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return "Exception occurred: Bureaucrat::GradeTooLowException";
}
const char* Bureaucrat::GradeTooHighException::what() const throw() {
  return "Exception occurred: Bureaucrat::GradeTooHighException";
}


// required function
std::ostream& operator<<(std::ostream& os, Bureaucrat& ref) {
  os << ref.getName() << ", bureaucrat grade " << ref.getGrade() << ".";
  return os;
}