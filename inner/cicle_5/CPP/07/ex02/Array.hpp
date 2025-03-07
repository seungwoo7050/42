#ifndef ARRAY_HPP
#define ARRAY_HPP

template<typename T>
class Array {
private:
  T* array;
  size_t array_size;

public:
  Array() : array(new T[0]), array_size(0) {}
  Array(size_t size) : array(new T[size]), array_size(size) {
    for (size_t i = 0; i < array_size; i++) {
        array[i] = 0;
    }
  }
  Array(const Array& copy) : array(new T[copy.array_size]), array_size(copy.array_size) {
    for (size_t i = 0; i < array_size; i++) {
      array[i] = copy.array[i];
    }
  }
  Array& operator=(const Array& ref) {
    if (this != &ref && array_size == ref.array_size) {
      delete[] array;
      array_size = ref.array_size;
      array = new T[array_size];
      for (size_t i = 0; i < array_size; i++) {
        array[i] = ref.array[i];
      }
    } else {
      throw std::exception();
    }
    return *this;
  }
  ~Array() {
    delete[] array;
  }

  T& operator[](const size_t idx) const {
    if (idx >= array_size)
      throw std::exception();
    return array[idx];
  }
  const size_t& size() const { return array_size; }
};

#endif