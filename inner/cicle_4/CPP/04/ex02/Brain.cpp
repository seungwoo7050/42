#include "Brain.hpp"

Brain::Brain() {
  ideas[0] = "I know how to think.";
  std::cout << ideas[0] << std::endl;
}
Brain::Brain(const Brain& copy) {
  if (this != &copy) {
    for (int i = 0; i < 100; i++) {
      ideas[i] = copy.ideas[i];
    }
  }
  std::cout << ideas[0] << std::endl << "and ";
  std::cout << "I know how to copy." << std::endl;
}
Brain& Brain::operator=(const Brain& ref) {
  if (this != &ref) {
    for (int i = 0; i < 100; i++) {
      ideas[i] = ref.ideas[i];
    }
  }
  return *this;
}
Brain::~Brain() {
  std::cout << "I don't want to die" << std::endl;
}