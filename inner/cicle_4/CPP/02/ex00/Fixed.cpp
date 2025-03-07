#include "Fixed.hpp"

Fixed::Fixed() : fixed_point_value(0) { std::cout << "Default constructor called" << std::endl; }
Fixed::Fixed(const Fixed& copy) {
  if (this != &copy) {
    std::cout << "Copy constructor called" << std::endl;
    fixed_point_value = copy.getRawBits();
  }  
}
Fixed& Fixed::operator=(const Fixed& ref) {
  if (this != &ref) {
    std::cout << "Copy assignment operator called" << std::endl;
    fixed_point_value = ref.getRawBits();
  }  
  return *this;
}
Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }


int Fixed::getRawBits(void)const { 
  std::cout << "getRawBits member function called" << std::endl;
  return fixed_point_value; 
}
void Fixed::setRawBits(int const raw) { fixed_point_value = raw; }