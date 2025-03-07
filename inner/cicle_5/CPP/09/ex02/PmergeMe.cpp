#include "PmergeMe.hpp"

// PmergeMe OCCF
PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe&) {}
PmergeMe& PmergeMe::operator=(const PmergeMe&) {
  return *this;
}
PmergeMe::~PmergeMe() {}

// vector
void PmergeMe::mergeInsertSort(std::vector<int>& arr) {
  if (arr.size() < 2)
    return ;

  std::vector<std::pair<int ,int> > pairs = createPairsVector(arr);
  sortEachPair(pairs);

  std::vector<int> main_chain;
  std::vector<int> pend_chain;
  for (size_t i = 0; i < pairs.size(); i++) {
    main_chain.push_back(pairs[i].second);
  }
  int straggler = -1;
  if (arr.size() % 2 == 1) {
    straggler = arr.back();
  }

  quickSortMainChain(main_chain, 0, main_chain.size() - 1);

  for (size_t i = 0; i < main_chain.size(); ++i) {
    for (size_t j = 0; j < pairs.size(); ++j) {
      if (main_chain[i] == pairs[j].second) {
        pend_chain.push_back(pairs[j].first);
        break;
      }
    }
  }
  
  std::vector<int> insertionSequence = buildJacobInsertionSequenceVector(pend_chain.size());

  for (size_t i = 0; i < insertionSequence.size(); i++) {
    binaryInsert(main_chain, pend_chain[insertionSequence[i] - 1]);
  }
  if (straggler != -1) {
    binaryInsert(main_chain, straggler);
  }
  arr = main_chain;
}
std::vector<std::pair<int, int> > PmergeMe::createPairsVector(const std::vector<int>& arr) {
  std::vector<std::pair<int, int> > pairs;
  for (size_t i = 0; i + 1 < arr.size(); i += 2) {
    pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
  }
  return pairs; 
}
void PmergeMe::sortEachPair(std::vector<std::pair<int, int> >& pairs) {
  for (size_t i = 0; i < pairs.size(); i++) {
    if (pairs[i].first > pairs[i].second) {
      std::swap(pairs[i].first, pairs[i]. second);
    }
  }
}
void PmergeMe::quickSortMainChain(std::vector<int>& main_chain, int low, int high) {
  if (low < high) {
    int pivot_index = partition(main_chain, low, high);
    quickSortMainChain(main_chain, low, pivot_index - 1);
    quickSortMainChain(main_chain, pivot_index + 1, high);
  }
}
int PmergeMe::partition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);

  return i + 1;
}
std::vector<int> PmergeMe::buildJacobInsertionSequenceVector(int n) {
  std::vector<int> jacobsthal;
  jacobsthal.push_back(1);
  jacobsthal.push_back(3);

  for (int i = 1; jacobsthal[i] < n; i++) {
    int cur = jacobsthal[i] + 2 * jacobsthal[i - 1];
    jacobsthal.push_back(cur);
  }

  std::vector<int> sequence;
  sequence.push_back(1);
  for (size_t i = 1; i < jacobsthal.size(); i++) {
    for (int j = 0; jacobsthal[i] - j > jacobsthal[i - 1]; j++) {
      if (jacobsthal[i] - j <= n) {
        sequence.push_back(jacobsthal[i] - j);
      }
    }    
  }
  return sequence;
}
void PmergeMe::binaryInsert(std::vector<int>& arr, int val) {
  int pos = binarySearchInsertPosition(arr, val);
  arr.insert(arr.begin() + pos, val);
}
int PmergeMe::binarySearchInsertPosition(std::vector<int>& arr, int val) {
  int left = 0;
  int right = arr.size();

  while (left < right) {
    int mid = (left + right) / 2;
    if (arr[mid] < val) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}


// deque
void PmergeMe::mergeInsertSort(std::deque<int>& arr) {
  if (arr.size() < 2)
    return ;

  std::deque<std::pair<int ,int> > pairs = createPairsDeque(arr);
  sortEachPair(pairs);

  std::deque<int> main_chain;
  std::deque<int> pend_chain;
  for (size_t i = 0; i < pairs.size(); i++) {
    main_chain.push_back(pairs[i].second);
  }
  int straggler = -1;
  if (arr.size() % 2 == 1) {
    straggler = arr.back();
  }    

  quickSortMainChain(main_chain, 0, main_chain.size() - 1);

  for (size_t i = 0; i < main_chain.size(); ++i) {
    for (size_t j = 0; j < pairs.size(); ++j) {
      if (main_chain[i] == pairs[j].second) {
        pend_chain.push_back(pairs[j].first);
        break;
      }
    }
  }
  
  std::deque<int> insertionSequence = buildJacobInsertionSequenceDeque(pend_chain.size());

  for (size_t i = 0; i < insertionSequence.size(); i++) {
    binaryInsert(main_chain, pend_chain[insertionSequence[i] - 1]);
  }
  if (straggler != -1) {
    binaryInsert(main_chain, straggler);
  }
  arr = main_chain;
}
std::deque<std::pair<int, int> > PmergeMe::createPairsDeque(const std::deque<int>& arr) {
  std::deque<std::pair<int, int> > pairs;
  for (size_t i = 0; i + 1 < arr.size(); i += 2) {
    pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
  }
  return pairs; 
}
void PmergeMe::sortEachPair(std::deque<std::pair<int, int> >& pairs) {
  for (size_t i = 0; i < pairs.size(); i++) {
    if (pairs[i].first > pairs[i].second) {
      std::swap(pairs[i].first, pairs[i]. second);
    }
  }
}
void PmergeMe::quickSortMainChain(std::deque<int>& main_chain, int low, int high) {
  if (low < high) {
    int pivot_index = partition(main_chain, low, high);
    quickSortMainChain(main_chain, low, pivot_index - 1);
    quickSortMainChain(main_chain, pivot_index + 1, high);
  }
}
int PmergeMe::partition(std::deque<int>& arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);

  return i + 1;
}
std::deque<int> PmergeMe::buildJacobInsertionSequenceDeque(int n) {
  std::deque<int> jacobsthal;
  jacobsthal.push_back(1);
  jacobsthal.push_back(3);

  for (int i = 1; jacobsthal[i] < n; i++) {
    int cur = jacobsthal[i] + 2 * jacobsthal[i - 1];
    jacobsthal.push_back(cur);
  }

  std::deque<int> sequence;
  sequence.push_back(1);
  for (size_t i = 1; i < jacobsthal.size(); i++) {
    for (int j = 0; jacobsthal[i] - j > jacobsthal[i - 1]; j++) {
      if (jacobsthal[i] - j <= n) {
        sequence.push_back(jacobsthal[i] - j);
      }
    }    
  }
  return sequence;
}
void PmergeMe::binaryInsert(std::deque<int>& arr, int val) {
  int pos = binarySearchInsertPosition(arr, val);
  arr.insert(arr.begin() + pos, val);
}
int PmergeMe::binarySearchInsertPosition(std::deque<int>& arr, int val) {
  int left = 0;
  int right = arr.size();

  while (left < right) {
    int mid = (left + right) / 2;
    if (arr[mid] < val) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}