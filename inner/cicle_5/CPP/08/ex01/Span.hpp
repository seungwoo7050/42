#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>     // std::vector
#include <algorithm>  // std::find, std::min_element, std::max_element
#include <iterator>   // std::iterator_traits
#include <exception>  // std::exception
#include <cmath>      // std::abs
#include <limits>     // std::numeric_limits
#include <iostream>

class Span {
private:
  std::vector<int> numbers;
  unsigned int max_size;

public:
  Span(const unsigned int &N);
  Span(const Span& copy);
  Span& operator=(const Span& ref);
  ~Span();

  void addNumber(int number);

  template <typename Iterator>
  void addNumbers(Iterator begin, Iterator end) {
    for (Iterator it = begin; it != end; it++) {
      addNumber(*it);
    }
  }

  unsigned int shortestSpan() const;
  unsigned int longestSpan() const;
};

#endif