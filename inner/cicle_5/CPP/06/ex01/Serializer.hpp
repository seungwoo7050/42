#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstring> // std::memcpy
#include "Data.hpp"

typedef unsigned long uintptr_t;

class Serializer {
public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);

private:
    Serializer();
    Serializer(Serializer& copy);
    Serializer& operator=(Serializer& ref);
    ~Serializer();
};

#endif
