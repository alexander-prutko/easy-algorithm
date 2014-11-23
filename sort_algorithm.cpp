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

  for (size_t i = s - 1; i > 0; i--) {                // Алгоритм сортировки вставками
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
    pDS->move();
    }
  }

  }
}

void BubbleSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  size_t s = pDS->Size();
  bool cmp;
  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

  for (size_t i = 0; i < s - 1; i++)                  // Алгоритм сортировки пузырьком
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

  for (h = 0; h <= (s - 1) / 9; h = 3 * h + 1);       // Алгоритм сортировки Шелла
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
      pDS->move();
      }
    }

  }
}

void QuickSort::vSort(DataStructure* pDS, TimeObserver* pTO) {
  {
  Timer t(pTO, 2);  // Запуск счетчика (2 тип) - Полное время

  quicksort(pDS, 0, pDS->Size() - 1, pTO);

  }
}

void QuickSort::quicksort(DataStructure* pDS, size_t l, size_t r, TimeObserver* pTO) {
  if (r <= l) return;
	size_t i = partition(pDS, l, r, pTO);
  if(i == 0)
    return;
  else
	  quicksort(pDS, l, i - 1, pTO);
  if(i == pDS->Size() - 1)
    return;
  else
	  quicksort(pDS, i + 1, r, pTO);
}

size_t QuickSort::partition(DataStructure* pDS, size_t l, size_t r, TimeObserver* pTO) {
  bool cmp;
  size_t i = l - 1, j = r;
	//Item v = a[r];
	for (;;) {
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur1(++i);
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur2(r);
    }
    {
    Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
    cmp = pDS->compare();
    }
		while (cmp/*a[++i] < v*/) {
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur1(++i);
      }
      {
      Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
      cmp = pDS->compare();
      }
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur1(r);
    }
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur2(--j);
    }
    {
    Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
    cmp = pDS->compare();
    }
		while (cmp/*v < a[--j]*/) {
			if (j == i)
				break;
      {
      Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
      pDS->setCur2(--j);
      }
      {
      Timer t(pTO, 0);  // Запуск счетчика (0 тип) - Время сравнения
      cmp = pDS->compare();
      }
    }
		if (i >= j)
			break;
		//exch(a[i], a[j]);
    {
    Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
    pDS->setCur1(i);
    }
    //pDS->setCur2(j);//?
    {
    Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
    pDS->swap();
    }
	}
	//exch(a[i], a[r]);
  {
  Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
  pDS->setCur1(i);
  }
  {
  Timer t(pTO, 3);  // Запуск счетчика (3 тип) - Время поиска элемента
  pDS->setCur2(r);
  }
  {
  Timer t(pTO, 1);  // Запуск счетчика (1 тип) - Время присваивания
  pDS->swap();
  }
	return i;
}

}
