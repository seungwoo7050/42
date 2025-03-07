#ifndef EASHFIND_HPP
#define EASHFIND_HPP

#include <iterator>
#include <algorithm>
#include <exception>

template <typename T>
typename T::iterator easyfind(T& container, const int& value) {
  typename T::iterator it = std::find(container.begin(), container.end(), value);

  if (it == container.end()) {
    throw std::out_of_range("Value not found in container.");
  }

  return it;
}

#endif