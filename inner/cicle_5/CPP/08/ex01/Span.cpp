#include "Span.hpp"

Span::Span(const unsigned int &N) : max_size(N) { }
Span::Span(const Span& copy) : numbers(copy.numbers), max_size(copy.max_size) { }
Span& Span::operator=(const Span& ref) {
  if (this != &ref) {
    numbers = ref.numbers;
    max_size = ref.max_size;
  }
  return *this;
}
Span::~Span() { }

void Span::addNumber(int number) {
  if (numbers.size() >= max_size)
    throw std::out_of_range("Span is Full.");
  numbers.push_back(number);
}

unsigned int Span::shortestSpan() const {
  if (numbers.size() < 2)
    throw std::runtime_error("Not enough numbers.");

  std::vector<int> sorted(numbers);
  std::sort(sorted.begin(), sorted.end());
  unsigned int min_span = std::numeric_limits<int>::max() - std::numeric_limits<int>::min();
  for (std::size_t i = 0; i < sorted.size() - 1; i++) {
    unsigned int span = sorted[i + 1] - sorted[i];
    if (span < min_span)
      min_span = span;
  }
  return min_span;
}

unsigned int Span::longestSpan() const {
  if (numbers.size() < 2)
    throw std::runtime_error("Not enough numbers.");
  int min_element = *std::min_element(numbers.begin(), numbers.end());
  int max_element = *std::max_element(numbers.begin(), numbers.end());

  return max_element - min_element;
}
