#include "sort_algorithm.h"

namespace easy_algorithm {

void SortAlgorithm::sort(DataStructure* pDS, TimeObserver* pTO) {
  vSort(pDS, pTO);
}

void SelectionSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  size_t s = pDS->Size();
  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

  bool cmp;
  for (size_t i = 0; i < s - 1; ++i) {                // Алгоритм сортировки выбором
    //pDS->setCur2(i);
    size_t min = i;
    for (size_t j = i; j < s; ++j) {
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur1(j);
      }
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur2(min);
      }
      {
      Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
      cmp = pDS->compare();
      }
      if (cmp) // a[j] < a[min]
        min = j;
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur1(i);
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur2(min);
    }
    {
    Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
    pDS->swap();// exch(a[i], a[min]);
    }

    }                 // Остановка счетчика, передача значения классу TimeObserver
  }
}

}
