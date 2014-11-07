#include "sort.h"

namespace easy_algorithm {

Sort::Sort(DataStructure* ds, SortAlgorithm* sa, TimeObserver* to) : _pDS(ds), _pSA(sa), _pTO(to) {}

void Sort::sort() {
  _pSA->sort(_pDS, _pTO);
}

}
