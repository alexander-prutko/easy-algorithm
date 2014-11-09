#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "array.h"
#include "sort_algorithm.h"
#include "sort.h"
#include "array_iterator.h"

int main() {
  using namespace std;
  using namespace easy_algorithm;

  DataStructure* pA = DataStructure::createArray<int>(100);
    Array<int>* pa = dynamic_cast<Array<int>*>(pA);

  srand((unsigned)time(NULL));

  for(size_t i = 0; i < 100; ++i)
    pa->insert(rand());

  SelectionSort* ss = new SelectionSort;
  TimeObserver* to = new TimeObserver;

//  for (size_t i = 0; i < pa->Size(); ++i)
//    cout<<(*pa)[i]<<" ";
//  cout << endl;

  Sort s(pA,ss,to);
  s.sort();

  cin.get();

  //for (size_t i = 0; i < pa->Size(); ++i)
  //  cout << (*pa)[i] << " ";

  cin.get();

  ArrayIterator<int>* ai = new ArrayIterator<int>;
  ai->operator++();

  return 0;
}
