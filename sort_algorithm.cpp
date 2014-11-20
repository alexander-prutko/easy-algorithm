#include "sort_algorithm.h"

namespace easy_algorithm {

void SortAlgorithm::sort(DataStructure* pDS, TimeObserver* pTO) {
  vSort(pDS, pTO);
}

void SelectionSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  size_t s = pDS->Size();
  bool cmp;
  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

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

void InsertionSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  size_t s = pDS->Size();
  bool cmp;
  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

  for (size_t i = s - 1; i > 0; i--) {
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur1(i);
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur2(i-1);
    }
    {
    Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
    cmp = pDS->compare();
    }
    if (cmp) {
      {
      Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
      pDS->swap();
      }
    }
  }
  for (size_t i = 2; i <= s - 1; i++) {
    int j = i;
    //int v = a[i];
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur1(i);
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur2(j - 1);
    }
    {
    Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
    cmp = pDS->compare();
    }
    while (cmp/*v*//*a[i] < a[j - l]*/) {
      //a[j] = a[j - l];
      j--;
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur2(j - 1);
      }
      {
      Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
      cmp = pDS->compare();
      }
    }
    //a[j] = v;
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur2(j);
    }
    {
    Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
    pDS->replace();
    }
  }

  }
}

void BubbleSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  size_t s = pDS->Size();
  bool cmp;
  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

  for (size_t i = 0; i < s - 1; i++)
    for (size_t j = s - 1; j > i; j--) {
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur1(j);
      }
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur2(j - 1);
      }
      {
      Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
      cmp = pDS->compare();
      }
      if (cmp/*a[j] < a[j - 1]*/) {
        {
        Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
        pDS->swap();
        }
        //exch(a[j - l], a[j]);
      }
    }

  }
}

void ShellSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  size_t s = pDS->Size();
  bool cmp;
  size_t h;

  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

  for (h = 0; h <= (s - 1) / 9; h = 3 * h + 1);
  for (; h > 0; h /= 3)
    for (size_t i = h; i <= s - 1; i++) {
      size_t j = i;
      //int v = a[i];
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur1(i);
      }
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur2(j - h);
      }
      {
      Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
      cmp = pDS->compare();
      }
      while (j >= h && cmp/*v < a[j - h]*/) {
        //a[j] = a[j - h];
        j -= h;
        if (j >= h) {
          {
          Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
          pDS->setCur2(j - h);
          }
          {
          Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
          cmp = pDS->compare();
          }
        }
      }
      //a[j] = v;
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur2(j);
      }
      {
      Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
      pDS->replace();
      }
    }

  }
}

}
