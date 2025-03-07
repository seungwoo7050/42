#ifndef __SCALARCONVERTER_HPP__
#define __SCALARCONVERTER_HPP__

#include <string>     // std::string
#include <iostream>   // std::cout, std::endl;
#include <limits>     // std::numeric_limits
#include <cerrno>     // errno
#include <cctype>     // isprint, isdigit
#include <cstdlib>    // std::strtol, std::strtof, std::strtod



class ScalarConverter {
private:
  // TODO: This class must not be instanciable by user.
  // OCCF
  ScalarConverter();
  ScalarConverter(ScalarConverter&);
  ScalarConverter& operator=(ScalarConverter&);
  ~ScalarConverter();

  // quarter function
  static bool isInt(const std::string& literal);
  static bool isFloat(const std::string& literal);
  static bool isDouble(const std::string& literal);
  static bool isChar(const std::string& literal);
  static bool isParticular(const std::string& literal);

  // print function
  static void printResults(int, float, double);
  static void printParticular(const std::string&);
  static void printImpossible();
  
public:
  // required member function
  static void convert(const std::string& literal);
};

// required function

#endif