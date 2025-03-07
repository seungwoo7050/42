#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

#define N 4

int main()
{
  const Animal* j = new Dog();
  const Animal* i = new Cat();
  delete j;//should not create a leak
  delete i;
  
  Animal  *animals[N];
  int     idx;

  for (idx = 0; idx < N; idx++) {
    if (idx >= N / 2) 
      animals[idx] = new Cat();
    else
      animals[idx] = new Dog();
  }
  for (idx = 0; idx < N; idx++)
    delete animals[idx];

  Cat A;
  Cat B(A);

  // Animal *A = new Dog();
  // A->makeSound();
  // delete A;
  // A = new Cat();
  // A->makeSound();
  // delete A;
  // A = new Animal();


  return 0;
}