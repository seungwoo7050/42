#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& literal) {
  if (isParticular(literal)) return ;
  if (isInt(literal)) return ;
  if (isFloat(literal)) return ;
  if (isDouble(literal)) return ;  
  if (isChar(literal)) return ;
  
  printImpossible();
}

// quarter function
bool ScalarConverter::isInt(const std::string& literal) {
  char *end;
  errno = 0;

  long int_val = std::strtol(literal.c_str(), &end, 10);
  if (*end == '\0' && errno == 0 && int_val >= std::numeric_limits<int>::min() && int_val <= std::numeric_limits<int>::max()) {
    printResults(static_cast<int>(int_val), static_cast<float>(int_val), static_cast<double>(int_val));
    return true;
  }
  return false;
}
bool ScalarConverter::isFloat(const std::string& literal) {
  char *end;
  errno = 0;

  float float_val = std::strtof(literal.c_str(), &end);
  if (*end == 'f' && *(end + 1) == '\0' && errno == 0) {
    printResults(static_cast<int>(float_val), static_cast<float>(float_val), static_cast<double>(float_val));
    return true;
  }
  return false;
}
bool ScalarConverter::isDouble(const std::string& literal) {
  char *end;
  errno = 0;

  double double_val = std::strtod(literal.c_str(), &end);
  if (*end == '\0' && errno == 0) {
    printResults(static_cast<int>(double_val), static_cast<float>(double_val), static_cast<double>(double_val));
    return true;
  }
  return false;
}
bool ScalarConverter::isChar(const std::string& literal) {
  if (literal.length() == 1 && isprint(literal[0]) && !isdigit(literal[0])) {
    char char_val = literal[0];
    printResults(static_cast<int>(char_val), static_cast<float>(char_val), static_cast<double>(char_val));
    return true;
  }
  return false;
}
bool ScalarConverter::isParticular(const std::string& literal) {
  if (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
  literal == "-inf" || literal == "+inf" || literal == "nan") {
    printParticular(literal);
    return true;
  }
  return false;
}

// print function
void ScalarConverter::printResults(int int_val, float float_val, double double_val) {
  std::cout << "char: " << (isprint(int_val) ? "'" + std::string(1, static_cast<char>(int_val)) + "'" : "Non displayable") << std::endl;
  std::cout << "int: " << int_val << std::endl;
  if (int_val == 0) {
    std::cout << "float: 0.0f" << std::endl;
    std::cout << "double: 0.0" << std::endl;

  } else {
    std::cout << "float: " << float_val << "f" << std::endl;
    std::cout << "double: " << double_val << std::endl;
  }
}
void ScalarConverter::printParticular(const std::string& literal) {
  std::string float_literal = (literal == "-inf" || literal == "+inf" || literal == "nan") ? literal + "f" : literal;
  std::string double_literal = (literal == "-inf" || literal == "+inf" || literal == "nan") ? literal : literal.substr(0, literal.size() - 1);
 
  std::cout << "char: impossible" << std::endl;
  std::cout << "int: impossible" << std::endl;
  std::cout << "float: " << float_literal << std::endl;
  std::cout << "double: " << double_literal << std::endl;
}
void ScalarConverter::printImpossible() {
  std::cout << "char: impossible" << std::endl;
  std::cout << "int: impossible" << std::endl;
  std::cout << "float: impossible" << std::endl;
  std::cout << "double: impossible" << std::endl;
}