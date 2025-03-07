#include "AForm.hpp"

// internal function
void AForm::checkGrade(int grade) const {
  if (grade < 1)
    throw GradeTooHighException();
  else if (grade > 150)
    throw GradeTooLowException();
}


// OCCF
AForm::AForm()
  : name("AForm"), is_signed(false), grade_required_to_sign(75), grade_required_to_exec(75) {
    std::cout << "Default constructor set AForm name: `AForm`" << std::endl;
    std::cout << "Grade required to sign & execute: `75`" << std::endl;
  }
AForm::AForm(std::string name, int grts, int grte)
  : name(name), is_signed(false), grade_required_to_sign(grts), grade_required_to_exec(grte) {
  checkGrade(grade_required_to_sign);
  checkGrade(grade_required_to_exec);
}
AForm::AForm(const AForm& copy) 
  : name(copy.name), is_signed(copy.is_signed), grade_required_to_sign(copy.grade_required_to_sign), grade_required_to_exec(copy.grade_required_to_exec) {
  checkGrade(grade_required_to_sign);
  checkGrade(grade_required_to_exec);
}
AForm& AForm::operator=(const AForm& ref) {
  if (this != &ref) {
    is_signed = ref.is_signed;
  }
  return *this;
}
AForm::~AForm() {}


// required member function
std::string AForm::getName() const { return name; }
bool AForm::getIsSigned() const { return is_signed; }
int AForm::getGradeRequiredToSign() const { return grade_required_to_sign; }
int AForm::getGradeRequiredToExec() const { return grade_required_to_exec; }

void AForm::beSigned(Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > grade_required_to_sign)
    throw GradeTooLowException();
  else {
    if (is_signed == false)
      is_signed = true;
  }
}

// utility function
void AForm::checkExecutable(const Bureaucrat& bureaucrat) const {
  if (getIsSigned() == false) throw NotYetSignedException();
  if (getGradeRequiredToExec() < bureaucrat.getGrade()) throw GradeTooLowException();
}


// custom exception
const char* AForm::GradeTooHighException::what() const throw() {
  return "Exception occurred: AForm::GradeTooHighException";
}
const char* AForm::GradeTooLowException::what() const throw() {
  return "Exception occurred: AForm::GradeTooLowException";
}
const char* AForm::NotYetSignedException::what() const throw() {
  return "Exception occurred: AForm::NotYetSignedException";
}


// required function
std::ostream& operator<<(std::ostream& os, AForm& ref) {
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

