#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <ctime>

#include "PmergeMe.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << "<integers>" << std::endl;
    return 1;
  }

  std::vector<int> vec;
  std::deque<int> deq;

  for (int i = 1; i < argc; i++) {
    std::istringstream iss(argv[i]);
    int num;
    if (!(iss >> num) || num < 1) {
      std::cout << "Error: Invalid input => " << argv[i] << std::endl;
      return 1;
    }
    vec.push_back(num);
    deq.push_back(num);
  }

  PmergeMe pmergeme;

  std::cout << "Befor: ";
  for (int i = 1; i < argc; i++) {
    std::cout << argv[i] << " ";
  }
  std::cout << std::endl;

  clock_t start = clock();
  pmergeme.mergeInsertSort(vec);
  clock_t end = clock();
  double duration_vector = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

  start = clock();
  pmergeme.mergeInsertSort(deq);
  end = clock();
  double duration_deque = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

  std::cout << "After: ";
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Time to process a range of " << (argc - 1) << " elements with std::vector : " << duration_vector << " us" << std::endl;
  std::cout << "Time to process a range of " << (argc - 1) << " elements with std::deque  : " << duration_deque << " us" << std::endl;

  return 0;  
}
