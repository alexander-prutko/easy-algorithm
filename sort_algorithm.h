#ifndef EASY_ALGORITHM_SORT_ALGORITHM_H
#define EASY_ALGORITHM_SORT_ALGORITHM_H

#include <time.h>
#include <Windows.h>
#include "data_structure.h"

namespace easy_algorithm {

class TimeObserver {                // Класс принимает время выполнения операции и увеличивает счетчик
public:
  TimeObserver() { reset(); }
  void update1(double ms) { t1 += ms; ++n1; }
  void update2(double ms) { t2 += ms; ++n2; }
  void update3(double ms) { t3 += ms; ++n3; }
  void reset(){
    t1 = t2 = t3 = n1 = n2 = n3 = 0;
  }

private:
  double t1, t2, t3;
  unsigned int n1, n2, n3;
};

class SortAlgorithm {                                             // Базовый класс алгоритмов сортировки
public:
  void sort(DataStructure* pDS, TimeObserver* pTO);

protected:
  class Timer {                                                   // Вложенный класс для подсчета времени выполнения операций
  public:
    Timer(TimeObserver* pTO, int t) : type(t), _pTO(pTO) { QueryPerformanceCounter((LARGE_INTEGER*)&t1); }  // Конструктор инициализирует счетчик (t - тип)
    virtual ~Timer() {                                            // Деструктор передат подсчитанное время классу TimeObserver
      QueryPerformanceCounter((LARGE_INTEGER*)&t2);
      QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
      switch (type) {
        case 0:
          _pTO->update1((t2 - t1) / freq);
          break;
        case 1:
          _pTO->update2((t2 - t1) / freq);
          break;
        case 2:
          _pTO->update3((t2 - t1) / freq);
          break;
        default:;
      }
    }

  private:
    int type;                   // Тип счетчика
    TimeObserver* _pTO;         // Класс подсчета времени выполнения операций
    double t1, t2, freq;        // Переменные для подсчета времени выполнения операций
  };

private:
  virtual void vSort(DataStructure* pDS, TimeObserver* pTO) = 0;  // Виртуальная функция, соответствующая sort
};

class SelectionSort : public SortAlgorithm {                      // Класс, реализующий сортировку выбором
public:

private:
  void vSort(DataStructure* pDS, TimeObserver* pTO);
};

}

#endif
