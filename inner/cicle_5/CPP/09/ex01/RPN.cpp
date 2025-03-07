#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN&) { }
RPN& RPN::operator=(const RPN&) { 
  return *this;
}
RPN::~RPN() {}

RPN::RPN(const std::string& input) {
  std::istringstream iss(input);
  std::stack<int> stack;
  std::string token;

  while(iss >> token) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      if (stack.size() < 2)
        throw std::invalid_argument("Error");

      int b = stack.top();
      stack.pop();
      int a = stack.top();
      stack.pop();

      if (token == "+") stack.push(a + b);
      else if (token == "-") stack.push(a - b);
      else if (token == "*") stack.push(a * b);
      else if (token == "/") stack.push(a / b);
    } else if (token >= "0" && token <= "9") {
      std::istringstream number_stream(token);
      int number;
      number_stream >> number;
      stack.push (number);
    } else {
      throw std::invalid_argument("Error");
    }
  }
  if (stack.size() != 1)
    throw std::invalid_argument("Error");
  std::cout << stack.top() << std::endl;
}