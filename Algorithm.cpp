#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "array.h"
#include "sort_algorithm.h"
#include "sort.h"
#include "array_iterator.h"
#include "vector_adapter.h"
#include "list.h"
#include "list_iterator.h"
#include "dllist.h"
#include "dllist_iterator.h"

int main() {
  using namespace std;
  using namespace easy_algorithm;

 /* ListIterator<int> lll;

  srand((unsigned)time(NULL));

  // Создание массива
  DataStructure* pA = DataStructure::createArray<int>(10);
  Array<int>* pa = dynamic_cast<Array<int>*>(pA);

  // Вставки 6 произвольных элементов в массив
  for(size_t i = 0; i < 6; ++i)
    pa->insert(rand());

  // Создаем копию текущего массива
  DataStructure* pA2 = DataStructure::createArray<int>(*pA);
  // Вывод копии массива
  cout << "Array copy:" << endl << *pA;

  cout << "Insert 3 elements (type 3 integers) at the end of the array:" << endl;
  // Ввод еще 3 элементов из потока ввода
  for(int i = 0; i < 3; ++i)
    cin >> *pA;

  // Вставка элемента в 4-ю позицию
  cout << "Insert 1 element at 4th position (type 1 integer):" << endl;
  {
    int temp;
    cin >> temp;
    pa->insert(temp, 4);
  }

  // Создание итераторов
  ArrayIterator<int> iter(pa->begin());
  ArrayIterator<int> iter2(pa->end());
  cout << "Enter integer value for the first element:" << endl;
  // Значение, вводимое с клавиатуры, присваивается элементу, на который указывает итератор (первый элемент)
  cin >> iter;
  // Смещаем итераторы
  ++iter;
  --iter2;
  cout << "The second element is " << iter << endl;
  cout << "The third element is " << (*pa)[2] << endl;
  cout << "The last element is " << iter2 << endl;
  // Вывод всего массива
  cout << "The whole array:" << endl << *pA;
  cout << "Size: " << pA->Size() << endl << "Maximal size: " << pA->maxSize() << endl;

  // Обмен первого и последнего элементов массива
  cout << "Swap the first and the last element" << endl;
  pA->swap(0,9);
  // Перемещение 3-го элемента на 8-ю позицию
  cout << "Replace the third element to the 8th position" << endl;
  pA->replace(2,7);
  // Удаление 6-го элемента
  cout << "Remove the 6th element" << endl;
  pA->remove(5);
  cout << "The array is empty: " << boolalpha << pA->empty() << endl;
  cout << "The 3rd element is less than the 5th element: " << boolalpha << pA->compare(2, 4) << endl;
  cout << "The whole array:" << endl << *pA;

  // Второй массив становится идентичным первому
  *pA2 = *pA;
  cout << "The whole 2nd array after copy:" << endl << *pA;

  // Сортировка массива
  // Создание объекта, реализующего метод сортировки выбором
  SelectionSort* ss = new SelectionSort;
  // Объект, подсчитывающий время выполнения операций
  TimeObserver* to = new TimeObserver;

  // Объект-фасад
  Sort s(pA, ss, to);
  // Выполнение сортировки
  s.sort();

  iter = pa->begin();
  iter2 = pa->end();
  int cnt = 0;
  cout << "Sorted array:" << endl;
  // Вывод массива с помощью итераторов
  for (ArrayIterator<int> i = iter; i != iter2; ++i, ++cnt) {
    cout << cnt << " " << i << endl;
  }
  cout << "Total comparison time (ms): " << s.getComparisonTime() << endl;
  cout << "Total assignment time (ms): " << s.getAssignmentTime() << endl;
  cout << "Total search time (ms): " << s.getSearchTime() << endl;
  cout << "Comparison, assignment and search time (ms): " <<  s.getComparisonTime() + s.getAssignmentTime() + s.getSearchTime() << endl;
  cout << "Total time (ms): " << s.getTotalTime() << endl;

  // Создание вектора с элементами {5,4,3,2,1}
  vector<int> intVec(5);
  cout << "Creation of vector:" << endl;
  for (int i = 0; i < 5; ++i) {
    intVec[i] = 5 - i;
    cout << intVec[i] << endl;
  }

  // Создание адаптера для вектора
  DataStructure* pVA = DataStructure::createVectorAdapter<int>(intVec);
  s.resetTimeObserver();
  s.setDataStructure(pVA);
  // Сортировка вектора
  s.sort();

  VectorAdapter<int>* pva = dynamic_cast<VectorAdapter<int>*>(pVA);
  ArrayIterator<int> ib = (pva->begin());
  ArrayIterator<int> ie = (pva->end());
  cnt = 0;
  cout << "Sorted vector:" << endl;
  for (ArrayIterator<int> i = ib; i != ie; ++i, ++cnt) {
    cout << cnt << " " << (*i) << endl;
  }
  cout << "Total comparison time (ms): " << s.getComparisonTime() << endl;
  cout << "Total assignment time (ms): " << s.getAssignmentTime() << endl;
  cout << "Total search time (ms): " << s.getSearchTime() << endl;
  cout << "Comparison, assignment and search time (ms): " <<  s.getComparisonTime() + s.getAssignmentTime() + s.getSearchTime() << endl;
  cout << "Total time (ms): " << s.getTotalTime() << endl;

  // Создание структуры данных из 1000 элементов
  DataStructure* pA3 = DataStructure::createArray<int>(1000);
  Array<int>* pa3 = dynamic_cast<Array<int>*>(pA3);

  // Вставки 1000 произвольных элементов в массив
  for(size_t i = 0; i < 1000; ++i)
    pa3->insert(rand());

  s.resetTimeObserver();
  s.setDataStructure(pA3);
  s.sort();
  cout << endl << "Sorting array of 1000 elements" << endl;
  cout << "Total comparison time (ms): " << s.getComparisonTime() << endl;
  cout << "Total assignment time (ms): " << s.getAssignmentTime() << endl;
  cout << "Total search time (ms): " << s.getSearchTime() << endl;
  cout << "Comparison, assignment and search time (ms): " <<  s.getComparisonTime() + s.getAssignmentTime() + s.getSearchTime() << endl;
  cout << "Total time (ms): " << s.getTotalTime() << endl;
  
  cin.get();
  cin.get();

  delete ss;
  delete to;
  delete pA;
  delete pA2;
  delete pA3;
  delete pVA;*/
/*
  // Создание массива
  DataStructure* pL = DataStructure::createList<int>(10);
  List<int>* pl = dynamic_cast<List<int>*>(pL);

  //(*pl)[0]->item=(*pl)[1]->item;
  pl->insert(51);
  pl->insert(42);
  pl->insert(33);
  pl->insert(24,2);
  pL->swap(2,3);
  cout << pL->compare(2,3) << " " << (*pl)[2]->next->item << " " << (*pl)[3]->next->item << endl;
  pL->swap(3,0);
  pL->replace(1,3);
  pL->remove(2);
  cout << *pL << endl;
  cin >> *pL;
  cout << endl << *pL;

  DataStructure* pL2 = DataStructure::createList<int>(10);

  *pL2 = *pL;
  cout << endl << *pL2;

  int cnt = 0;
  //++lib;
  // Сортировка массива
  // Создание объекта, реализующего метод сортировки выбором
  SelectionSort* ss = new SelectionSort;
  // Объект, подсчитывающий время выполнения операций
  TimeObserver* to = new TimeObserver;

  // Объект-фасад
  Sort s(pL, ss, to);
  // Выполнение сортировки
  s.sort();
  ListIterator<int> lib = (pl->begin());
  ListIterator<int> lie = (pl->end());
  for (ListIterator<int> i = lib; i != lie; ++i, ++cnt) {
    cout << cnt << " " << (*i) << endl;
  }

  delete pL;
  delete pL2;*/

  DataStructure* pDL = DataStructure::createDLList<int>(10);
  DLList<int>* pdl = dynamic_cast<DLList<int>*>(pDL);

  //(*pl)[0]->item=(*pl)[1]->item;
  pdl->insert(51);
  pdl->insert(42);
  pdl->insert(33);
  pdl->insert(24, 2);
  pDL->swap(2, 3);
  pDL->swap(3, 0);
  pDL->replace(3, 1);
  //pDL->remove(2);
  cout << pDL->compare(2, 3) << " " << (*pdl)[2]->next->item << " " << (*pdl)[3]->next->item << endl;
  //pL->swap(2,3);
  pDL->replace(1, 3);
  pDL->remove(2);
  cout << *pDL << endl;
  cin >> *pDL;
  cout << endl << *pDL;

  int cnt = 0;

  DLListIterator<int> dlib = --(pdl->begin());
  DLListIterator<int> dlie = (pdl->end());
  for (Iterator<int>* i = &(--dlie); *i != dlib; --(*i), ++cnt) {
    cout << cnt << " " << (*i) << endl;
  }

  return 0;
}
