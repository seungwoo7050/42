#include "Utils.hpp"

Base* generate(void) {
  unsigned int random;

  std::ifstream random_file("/dev/random");
  if (!random_file.is_open()) {
    std::srand(static_cast<unsigned int>(std::time(0)));
    random = std::rand() % 3;
  } else {
    random_file.read(reinterpret_cast<char*>(&random), sizeof(unsigned int));
    random_file.close();
    random %= 3;
  }
  switch(random) {
    case 0: return new A();
    case 1: return new B();
    case 2: return new C();
  }
  return NULL;
}

void identify(Base* p) {
  if (dynamic_cast<A*>(p))
   std::cout << "A" << std::endl;
  else if (dynamic_cast<B*>(p))
   std::cout << "B" << std::endl;
  else if (dynamic_cast<C*>(p))
   std::cout << "C" << std::endl;
  else
    std::cout << "Unknown" << std::endl;
}

void identify(Base& p) {
  try {
    (void)dynamic_cast<A&>(p);
    std::cout << "A" << std::endl;
  } catch (const std::exception& e) {}

  try {
    (void)dynamic_cast<B&>(p);
    std::cout << "B" << std::endl;
  } catch (const std::exception& e) {}
  
  try {
    (void)dynamic_cast<C&>(p);
    std::cout << "C" << std::endl;
  } catch (const std::exception& e) {}

}