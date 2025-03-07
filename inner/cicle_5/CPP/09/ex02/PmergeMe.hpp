#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <iostream>

class PmergeMe {
private:
  PmergeMe(const PmergeMe&);
  PmergeMe& operator=(const PmergeMe&);

  // vector    
  std::vector<std::pair<int, int> > createPairsVector(const std::vector<int>& arr);
  void sortEachPair(std::vector<std::pair<int, int> >& pairs);
  void quickSortMainChain(std::vector<int>& main_chain, int low, int high);
  int partition(std::vector<int>& arr, int low, int high);
  std::vector<int> buildJacobInsertionSequenceVector(int n);
  void binaryInsert(std::vector<int>& arr, int val);
  int binarySearchInsertPosition(std::vector<int>& arr, int val);

  // deque
  std::deque<std::pair<int, int> > createPairsDeque(const std::deque<int>& arr);
  void sortEachPair(std::deque<std::pair<int, int> >& pairs);
  void quickSortMainChain(std::deque<int>& main_chain, int low, int high);
  int partition(std::deque<int>& arr, int low, int high);
  std::deque<int> buildJacobInsertionSequenceDeque(int n);
  void binaryInsert(std::deque<int>& arr, int val);
  int binarySearchInsertPosition(std::deque<int>& arr, int val);
  
  

public:
  PmergeMe();
  ~PmergeMe();

  void mergeInsertSort(std::vector<int>& arr);
  void mergeInsertSort(std::deque<int>& arr);
};

#endif // PMERGEME_HPP
