#ifndef EASY_ALGORITHM_SORT_H
#define EASY_ALGORITHM_SORT_H

#include "sort_algorithm.h"

namespace easy_algorithm {

class DataStructure;      // Предварительное объявление класса

class Sort {              // Класс-интерфейс для сортировки структур данных и подсчета времени выполнения операций
public:
  Sort(DataStructure* ds, SortAlgorithm* sa, TimeObserver* to);
  void sort();            // Выполнить сортировку структуры данных ds с помощью алгоритма sa. to будет собирать сведения о времени процесса сортировки

private:
  DataStructure* _pDS;
  SortAlgorithm* _pSA;
  TimeObserver* _pTO;
};

}

#endif
