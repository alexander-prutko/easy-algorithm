#include "sort_algorithm.h"

namespace easy_algorithm {

void SortAlgorithm::sort(DataStructure* pDS) {
  vSort(pDS);
}


void SelectionSort::vSort(DataStructure* pDS) {
  size_t s = pDS->Size();

  for (size_t i = 0; i < s - 1; ++i) {
    //pDS->setCur2(i);
    size_t min = i;
    for (size_t j = i; j < s; ++j) {
      pDS->setCur1(j);
      pDS->setCur2(min);
      if (pDS->compare()/*a[j] < a[min]*/)
        min = j;
    }
    pDS->setCur1(i);
    pDS->setCur2(min);
    pDS->swap();// exch(a[i], a[min]);
  }
}

}
