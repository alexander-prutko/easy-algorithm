#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "array.h"
#include "sort_algorithm.h"
#include "sort.h"
#include "array_iterator.h"
#include "vector_adapter.h"

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

  //cin.get();

  //for (size_t i = 0; i < pa->Size(); ++i)
  //  cout << (*pa)[i] << " ";

  //cin.get();

  ArrayIterator<int> ib = (pa->begin());
  ArrayIterator<int> ie = (pa->end());
  int cnt = 0;
  for (ArrayIterator<int> i = ib; i != ie; ++i, ++cnt) {
    cout << cnt << " " << (*i) << endl;
  }
  //Iterator<int>* ai = new ArrayIterator<int>;
  //cin>>(*ai);

  vector<int> vv(5);
  for (int i = 0; i < 5; ++i)
    vv[i] = 5 - i;

  DataStructure* pVA = DataStructure::createVectorAdapter<int>(vv);
  Sort s2(pVA, ss, to);
  s2.sort();

  VectorAdapter<int>* pva = dynamic_cast<VectorAdapter<int>*>(pVA);
  ArrayIterator<int> ib2 = (pva->begin());
  ArrayIterator<int> ie2 = (pva->end());
  cnt = 0;
  for (ArrayIterator<int> i = ib2; i != ie2; ++i, ++cnt) {
    cout << cnt << " " << (*i) << endl;
  }
  
  cin.get();

  //ai->operator++();

  return 0;
}
