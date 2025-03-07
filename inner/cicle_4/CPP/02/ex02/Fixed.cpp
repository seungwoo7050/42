#include "Fixed.hpp"

Fixed::Fixed() : fixed_point_value(0) { }
Fixed::Fixed(const int n) : fixed_point_value(n << fractional_bits) { }
Fixed::Fixed(const float n) : fixed_point_value(roundf(n * (1 << fractional_bits))) { }
Fixed::Fixed(const Fixed& copy) {
  if (this != &copy) {
    *this = copy;
  }  
}
Fixed& Fixed::operator=(const Fixed& ref) {
  if (this != &ref) {
    fixed_point_value = ref.fixed_point_value;
  }  
  return *this;
}
Fixed::~Fixed() { }


int Fixed::getRawBits(void) const { 
  return fixed_point_value; 
}
void Fixed::setRawBits(int const raw) { fixed_point_value = raw; }
float Fixed::toFloat() const { return (static_cast<float>(fixed_point_value) / (1 << fractional_bits )); }
int   Fixed::toInt()const { return (fixed_point_value >> fractional_bits); }

bool  Fixed::operator>(const Fixed& ref) const {
  return fixed_point_value > ref.fixed_point_value; 
}
bool  Fixed::operator<(const Fixed& ref) const {
  return fixed_point_value < ref.fixed_point_value; 
}
bool  Fixed::operator>=(const Fixed& ref) const {
  return fixed_point_value >= ref.fixed_point_value; 
}
bool  Fixed::operator<=(const Fixed& ref) const {
  return fixed_point_value <= ref.fixed_point_value; 
}
bool  Fixed::operator==(const Fixed& ref) const {
  return fixed_point_value == ref.fixed_point_value; 
}
bool  Fixed::operator!=(const Fixed& ref) const {
  return fixed_point_value != ref.fixed_point_value; 
}

Fixed Fixed::operator+(const Fixed& ref) const {
  return Fixed(toFloat() + ref.toFloat());
}
Fixed Fixed::operator-(const Fixed& ref) const {
  return Fixed(toFloat() - ref.toFloat());
}
Fixed Fixed::operator*(const Fixed& ref) const {
  return Fixed(toFloat() * ref.toFloat());
}
Fixed Fixed::operator/(const Fixed& ref) const {
  return Fixed(toFloat() / ref.toFloat());
}

Fixed&  Fixed::operator++(void) {
  ++this->fixed_point_value;
  return *this;
}
Fixed   Fixed::operator++(int) {
  Fixed tmp(*this);
  tmp.fixed_point_value = this->fixed_point_value++;
  return tmp;
}
Fixed&  Fixed::operator--(void) {
  --this->fixed_point_value;
  return *this;
}
Fixed   Fixed::operator--(int) {
  Fixed tmp(*this);
  tmp.fixed_point_value = this->fixed_point_value--;
  return tmp;
}

Fixed& Fixed::min(Fixed &a, Fixed &b) {
  if (a < b)
    return a;
  else
    return b;
}
Fixed& Fixed::max(Fixed &a, Fixed &b) {
  if (a < b)
    return b;
  else
    return a;
}
const   Fixed& Fixed::min(const Fixed &a, const Fixed &b) {
  if (a < b)
    return a;
  else
    return b;
}
const   Fixed& Fixed::max(const Fixed &a, const Fixed &b) {
  if (a < b)
    return b;
  else
    return a;
}

std::ostream& operator<<(std::ostream& os, const Fixed& ref) {
  os << ref.toFloat();
  return os;
}