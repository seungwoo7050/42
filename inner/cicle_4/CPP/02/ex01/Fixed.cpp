#include "Fixed.hpp"

Fixed::Fixed() : fixed_point_value(0) { std::cout << "Default constructor called" << std::endl; }
Fixed::Fixed(const int n) : fixed_point_value(n << fractional_bits) { std::cout << "Int constructor called" << std::endl; }
Fixed::Fixed(const float n) : fixed_point_value(roundf(n * (1 << fractional_bits))) { std::cout << "Float constructor called" << std::endl; }
Fixed::Fixed(const Fixed& copy) {
  if (this != &copy) {
    std::cout << "Copy constructor called" << std::endl;
    *this = copy;
  }  
}
Fixed& Fixed::operator=(const Fixed& ref) {
  if (this != &ref) {
    std::cout << "Copy assignment operator called" << std::endl;
    fixed_point_value = ref.fixed_point_value;
  }  
  return *this;
}
Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }


int Fixed::getRawBits(void)const { 
  std::cout << "getRawBits member function called" << std::endl;
  return fixed_point_value; 
}
void Fixed::setRawBits(int const raw) { fixed_point_value = raw; }
float Fixed::toFloat() const { return (static_cast<float>(fixed_point_value) / (1 << fractional_bits )); }
int   Fixed::toInt()const { return (fixed_point_value >> fractional_bits); }

std::ostream& operator<<(std::ostream& os, const Fixed& ref) {
  os << ref.toFloat();
  return os;
}

// float는 비트 연산이 불가하다
// roundf = 버림 > 반올림
// 