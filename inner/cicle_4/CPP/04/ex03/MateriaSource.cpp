#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
  for (int i = 0; i < 4; i++) {
    templates[i] = NULL;
  }
}
MateriaSource::MateriaSource(const MateriaSource& copy) {
  for (int i = 0; i < 4; i++) {
    if (copy.templates[i])
      templates[i] = copy.templates[i]->clone();
    else
      templates[i] = NULL;
  }
}
MateriaSource& MateriaSource::operator=(const MateriaSource& ref) {
  if (this != &ref) {
    for (int i = 0; i < 4; i++) {
      if (templates[i])
        delete templates[i];
      if (ref.templates[i])
        templates[i] = ref.templates[i]->clone();
      else
        templates[i] = NULL;
    }
  }
  return *this;
}
MateriaSource::~MateriaSource() {
  for (int i = 0; i < 4; i++) {
    if (templates[i])
      delete templates[i];
  }
}
void MateriaSource::learnMateria(AMateria* m) {
  for (int i = 0; i < 4; i++) {
    if (!templates[i]) {
      templates[i] = m;
      break;
    }
  }
}
AMateria* MateriaSource::createMateria(const std::string& type) {
  for (int i = 0; i < 4; i++) {
    if (templates[i] && templates[i]->getType() == type)
      return templates[i]->clone();
  }
  return NULL;
}
