#include "Form.hpp"

// internal function
void Form::checkGrade(int grade) const {
  if (grade < 1)
    throw GradeTooHighException();
  else if (grade > 150)
    throw GradeTooLowException();
}


// OCCF
Form::Form()
  : name("Form"), is_signed(false), grade_required_to_sign(75), grade_required_to_exec(75) {
    std::cout << "Default constructor set Form name: `Form`" << std::endl;
    std::cout << "Grade required to sign & execute: `75`" << std::endl;
  }
Form::Form(std::string name, int grts, int grte)
  : name(name), is_signed(false), grade_required_to_sign(grts), grade_required_to_exec(grte) {
  checkGrade(grade_required_to_sign);
  checkGrade(grade_required_to_exec);
}
Form::Form(const Form& copy) 
  : name(copy.name), is_signed(copy.is_signed), grade_required_to_sign(copy.grade_required_to_sign), grade_required_to_exec(copy.grade_required_to_exec) {
  checkGrade(grade_required_to_sign);
  checkGrade(grade_required_to_exec);
}
Form& Form::operator=(const Form& ref) {
  if (this != &ref) {
    is_signed = ref.is_signed;
  }
  return *this;
}
Form::~Form() {}


// required member function
std::string Form::getName() const { return name; }
bool Form::getIsSigned() const { return is_signed; }
int Form::getGradeRequiredToSign() const { return grade_required_to_sign; }
int Form::getGradeRequiredToExec() const { return grade_required_to_exec; }

void Form::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > grade_required_to_sign)
    throw GradeTooLowException();
  else {
    if (is_signed == false)
      is_signed = true;
  }
}

// custom exception
const char* Form::GradeTooHighException::what() const throw() {
  return "Exception occurred: Form::GradeTooHighException";
}
const char* Form::GradeTooLowException::what() const throw() {
  return "Exception occurred: Form::GradeTooLowException";
}


// required function
std::ostream& operator<<(std::ostream& os, Form& ref) {
  os << ref.getName() << " is ";
  if (ref.getIsSigned() == true) {
    os << "sigend." << std::endl;
  } else  {
    os << "not sigend." << std::endl;
  }

  os << "You need " << ref.getGradeRequiredToSign()
  << " grade to sign this form." << std::endl 
  << "And you need "
  << ref.getGradeRequiredToExec() << "grade to execute this form.";

  return os;
}

