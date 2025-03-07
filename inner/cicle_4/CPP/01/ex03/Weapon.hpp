#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

#include <string>

class Weapon {
private:
  std::string type;

public:
  Weapon(std::string _type);

  std::string&  getType(void);
  void          setType(std::string type);
};

#endif