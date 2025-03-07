#ifndef __FIXED_HPP__
#define __FIXED_HPP__

#include <iostream>
#include <cmath>

class Fixed {
private:
  int               fixed_point_value;
  static const int  fractional_bits = 8;

public:
  Fixed();
  Fixed(const int n);
  Fixed(const float n);
  Fixed(const Fixed& copy);
  Fixed& operator=(const Fixed& ref);
  ~Fixed();

  int   getRawBits( void ) const;
  void  setRawBits( int const raw );
  float toFloat( void ) const;
  int   toInt( void ) const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& ref);

#endif