#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "array.h"
#include "sort_algorithm.h"
#include "sort.h"

int main() {
  using namespace std;
  using namespace easy_algorithm;
  DataStructure* pA = DataStructure::createArray<int>(10);

  Array<int>* pa = dynamic_cast<Array<int>*>(pA);

  srand((unsigned)time(NULL));

  for(size_t i = 0; i < 10; ++i)
    pa->insert(rand());

  SelectionSort* ss = new SelectionSort;

  for (size_t i = 0; i < pa->Size(); ++i)
    cout<<(*pa)[i]<<" ";
  cout << endl;

  Sort s(pA,ss);
  s.sort();

  cin.get();

  for (size_t i = 0; i < pa->Size(); ++i)
    cout << (*pa)[i] << " ";

  cin.get();

  return 0;
}
