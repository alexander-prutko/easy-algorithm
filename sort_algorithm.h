#ifndef EASY_ALGORITHM_SORT_ALGORITHM_H
#define EASY_ALGORITHM_SORT_ALGORITHM_H

#include "data_structure.h"

namespace easy_algorithm {

class SortAlgorithm {
public:
  void sort(DataStructure* pDS);

private:
  virtual void vSort(DataStructure* pDS) = 0;
};

class SelectionSort : public SortAlgorithm {
public:

private:
  void vSort(DataStructure* pDS);
};

}

#endif
