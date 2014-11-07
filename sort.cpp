#include "sort.h"

namespace easy_algorithm {

Sort::Sort(DataStructure* ds, SortAlgorithm* sa) : _pDS(ds), _pSA(sa) {}

void Sort::sort() {
  _pSA->sort(_pDS);
}

}
