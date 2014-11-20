#ifndef EASY_ALGORITHM_SORT_ALGORITHM_H
#define EASY_ALGORITHM_SORT_ALGORITHM_H

#include <time.h>
#include <Windows.h>
#include "data_structure.h"

namespace easy_algorithm {

class TimeObserver {                // Класс принимает время выполнения операции и увеличивает счетчик
public:
  TimeObserver() { reset(); }
  void updateComparisonTime(double ms)  {
    t1 += ms; ++n1; }   // Обновление времен выполнения операций
  void updateAssignmentTime(double ms)  {
    t2 += ms; ++n2; }
  void updateTotalTime(double ms)       {
    t3 += ms; ++n3; }
  void updateSearchTime(double ms)      {
    t4 += ms; ++n4; }

  double getComparisonTime()  { return t1; }    // Получение времен выполнения операций
  double getAssignmentTime()  { return t2; }
  double getTotalTime()       { return t3; }
  double getSearchTime()      { return t4; }
  
  void reset(){
    t1 = t2 = t3 = t4 = n1 = n2 = n3 = n4 = 0;
  }

private:
  double t1, t2, t3, t4;
  unsigned int n1, n2, n3, n4;
};

class SortAlgorithm {                                             // Базовый класс алгоритмов сортировки
public:
  void sort(DataStructure* pDS, TimeObserver* pTO);
  virtual ~SortAlgorithm() {}

protected:
  class Timer {                                                   // Вложенный класс для подсчета времени выполнения операций
  public:
    Timer(TimeObserver* pTO, int t) : type(t), _pTO(pTO) { QueryPerformanceCounter((LARGE_INTEGER*)&t1); }  // Конструктор инициализирует счетчик (t - тип)
    virtual ~Timer() {                                            // Деструктор передат подсчитанное время классу TimeObserver
      QueryPerformanceCounter((LARGE_INTEGER*)&t2);
      QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
      switch (type) {
        case 0:
          _pTO->updateComparisonTime((t2 - t1) / freq);
          break;
        case 1:
          _pTO->updateAssignmentTime((t2 - t1) / freq);
          break;
        case 2:
          _pTO->updateTotalTime((t2 - t1) / freq);
          break;
      case 3:
          _pTO->updateSearchTime((t2 - t1) / freq);
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
  virtual ~SelectionSort() {}

private:
  void vSort(DataStructure* pDS, TimeObserver* pTO);
};

class InsertionSort : public SortAlgorithm {                      // Класс, реализующий сортировку вставками
public:
  virtual ~InsertionSort() {}

private:
  void vSort(DataStructure* pDS, TimeObserver* pTO);
};

class BubbleSort : public SortAlgorithm {                      // Класс, реализующий сортировку пузырьком
public:
  virtual ~BubbleSort() {}

private:
  void vSort(DataStructure* pDS, TimeObserver* pTO);
};

class ShellSort : public SortAlgorithm {                      // Класс, реализующий сортировку Шелла
public:
  virtual ~ShellSort() {}

private:
  void vSort(DataStructure* pDS, TimeObserver* pTO);
};

}

#endif
