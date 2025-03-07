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

  bool  operator>(const Fixed& ref) const;
  bool  operator<(const Fixed& ref) const;
  bool  operator>=(const Fixed& ref) const;
  bool  operator<=(const Fixed& ref) const;
  bool  operator==(const Fixed& ref) const;
  bool  operator!=(const Fixed& ref) const;

  Fixed operator+(const Fixed& ref) const;
  Fixed operator-(const Fixed& ref) const;
  Fixed operator*(const Fixed& ref) const;
  Fixed operator/(const Fixed& ref) const;

  Fixed&  operator++(void);
  Fixed   operator++(int);
  Fixed&  operator--(void);
  Fixed   operator--(int);

  static        Fixed& min(Fixed &a, Fixed &b);
  static        Fixed& max(Fixed &a, Fixed &b);
  static const  Fixed& min(const Fixed &a, const Fixed &b);
  static const  Fixed& max(const Fixed &a, const Fixed &b);
};

std::ostream& operator<<(std::ostream& os, const Fixed& ref);

#endif