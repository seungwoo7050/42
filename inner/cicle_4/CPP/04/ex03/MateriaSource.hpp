#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <string>
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
private:
  AMateria* templates[4];

public:
  MateriaSource();
  MateriaSource(const MateriaSource& copy);
  MateriaSource& operator=(const MateriaSource& ref);
  virtual ~MateriaSource();
  
  void learnMateria(AMateria* m);
  AMateria* createMateria(const std::string& type);
};

#endif