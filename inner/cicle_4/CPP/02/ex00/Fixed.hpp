#ifndef __FIXED_HPP__
#define __FIXED_HPP__

#include <iostream>

class Fixed {
private:
  int               fixed_point_value;
  static const int  fractional_bits = 8;

public:
  Fixed();
  Fixed(const Fixed& copy);
  Fixed& operator=(const Fixed& ref);
  ~Fixed();

  int   getRawBits( void ) const;
  void  setRawBits( int const raw );
};

#endif