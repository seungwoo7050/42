#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void iter(T* array, size_t length, void (*func)(T&)) {
  for (size_t i = 0; i < length; ++i) {
    func(array[i]);
  }
}

template <typename T>
void print(T& element) {
  std::cout << element << " ";
}

template <typename T>
void increment(T& element) {
  element += 1;
}

template <typename T>
void doubleValue(T& element) {
  element *= 2;
}

template <typename T>
void square(T& element) {
  element *= element;
}

#endif