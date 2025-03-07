#include "ShrubberryCreationForm.hpp"

const std::string ShrubberryCreationForm::ascii_tree =
  " 42  /\\\n"
  "    /42\\\n"
  "   / 42 \\\n"
  "  /__42__\\\n"
  "     ||\n";


// OCCF
ShrubberryCreationForm::ShrubberryCreationForm()
  : AForm("shrubbery", 145, 137), target("noTarget") {
  std::cout << "Default constructor set Shrubbery target: `noTarget`" << std::endl;
}
ShrubberryCreationForm::ShrubberryCreationForm(std::string target)
  : AForm("shrubbery", 145, 137), target(target) {}
ShrubberryCreationForm::ShrubberryCreationForm(const ShrubberryCreationForm& copy)
  : AForm(copy), target(copy.target) {}
ShrubberryCreationForm& ShrubberryCreationForm::operator=(const ShrubberryCreationForm& ref) {
  if (this != &ref) {
    AForm::operator=(ref);
    target = ref.target;
  }
  return *this;
}
ShrubberryCreationForm::~ShrubberryCreationForm() {}

void ShrubberryCreationForm::execute(Bureaucrat const & bureaucrat) const {
  checkExecutable(bureaucrat);
  std::ofstream write_file((target + "shrubbery").c_str(), std::ios::out | std::ios::app);
  if (!write_file.is_open()) {
    throw std::runtime_error("Failed to open file at ShrubberryCreationForm.");
  }
  write_file << ascii_tree;
  write_file.close();
}