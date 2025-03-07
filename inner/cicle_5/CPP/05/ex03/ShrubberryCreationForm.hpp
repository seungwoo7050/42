#ifndef __SHRUBBERRYCREATIONFORM_HPP__
#define __SHRUBBERRYCREATIONFORM_HPP__

#include <fstream>
#include "AForm.hpp"

class ShrubberryCreationForm : public AForm {
private:
  std::string target;
  static const std::string ascii_tree;

public:
  // OCCF
  ShrubberryCreationForm();
  ShrubberryCreationForm(std::string target);
  ShrubberryCreationForm(const ShrubberryCreationForm& copy);
  ShrubberryCreationForm& operator=(const ShrubberryCreationForm& copy);
  ~ShrubberryCreationForm();
  
  void execute(Bureaucrat const & bureaucrat) const;
};

#endif