#ifndef EASY_ALGORITHM_SORT_H
#define EASY_ALGORITHM_SORT_H

#include "data_structure.h"
#include "sort_algorithm.h"

namespace easy_algorithm {
  
class Sort {
public:
  Sort(DataStructure* ds, SortAlgorithm* sa);
  void sort();

private:
  DataStructure* _pDS;
  SortAlgorithm* _pSA;
};

}

#endif
