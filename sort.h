#ifndef EASY_ALGORITHM_SORT_H
#define EASY_ALGORITHM_SORT_H

#include "sort_algorithm.h"

namespace easy_algorithm {

class DataStructure;      // Предварительное объявление класса

class Sort {              // Класс-интерфейс для сортировки структур данных и подсчета времени выполнения операций
public:
  Sort(DataStructure* ds, SortAlgorithm* sa, TimeObserver* to);
  void sort();            // Выполнить сортировку структуры данных ds с помощью алгоритма sa. to будет собирать сведения о времени процесса сортировки
  void setTimeObserver(TimeObserver* pTO);
  void setDataStructure(DataStructure* pDS);
  void setSortAlgorithm(SortAlgorithm* pSA);
  void resetTimeObserver();

  double getComparisonTime();   // Получение времен выполнения операций
  double getAssignmentTime();
  double getTotalTime();
  double getSearchTime();

private:
  DataStructure* _pDS;
  SortAlgorithm* _pSA;
  TimeObserver* _pTO;
};

struct SortTime {
  double total, comp, assign, search;
  SortTime(double t, double c, double a, double s) : total(t), comp(c), assign(a), search(s) {}
};

}

#endif
