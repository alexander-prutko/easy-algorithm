#include <iostream>
//#include "data_structure.h"
//#include "iterator.h"
#include "array.h"

int main() {
  using namespace std;
  using namespace easy_algorithm;
  DataStructure* pA = DataStructure::createArray<int>(5);
  DataStructure* pA2 = DataStructure::createArray<int>(*pA);
  cout << *pA2;
  cin >> *pA;

//  ((easy_algorithm::Array<int>*)pA)->insert(1,0);
  pA->swap(*pA2);

  cin.get();

  return 0;
}