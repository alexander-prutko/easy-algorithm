#ifndef EASY_ALGORITHM_DATA_STRUCTURE_H
#define EASY_ALGORITHM_DATA_STRUCTURE_H

#include <iosfwd>
//#include "iterator.h"
//class Iterator;
template <class Item>
class Array;

namespace easy_algorithm {

class DataStructure {
public:
  friend std::ostream& operator << (std::ostream& os, const DataStructure& ds);         // Вывод структуры данных в поток
  friend const std::istream& operator >> (const std::istream& is, DataStructure& ds);   // Ввод структуры данных из потока

  template <class Item>
  static DataStructure* createArray(size_t maxSize);
  template <class Item>
  static DataStructure* createArray(const DataStructure& array);
  
  virtual ~DataStructure(){}                              // Виртуальный деструктор позволяет полиморфное удаление объектов

  //void insert(Elem elem, size_t index = _size - 1);     // Вставить элемент elem в позицию index
  void swap(size_t index1, size_t index2);              // Поменять местами 2 элемента с индексами index1 и index2
  void swap(DataStructure& ds);                         // Поменять структуры данных
  void replace(size_t source, size_t dest);             // Переставить элемент с индексом source в позицию dest
  void remove(size_t index);                // Удалить элемент с индексом index
  //Iterator begin() const;                               // Возвращает итератор на начало структуры данных
  //Iterator end() const;                                 // Возвращает итератор на конец структуры данных
  //Elem& operator [] (size_t index);                     // Возвращает ссылку на элемент с индексом index
  //const Elem& operator [] (size_t index) const;
  const DataStructure& operator = (const DataStructure& ds);    // Делает содержание структуры данных идентичной ds
  
  size_t size() const;                            // Возвращает количество элементов
  size_t maxSize() const;                         // Возвращает максимальный размер структуры данных
  bool empty() const;                             // Возвращает true, если елементов нет
protected:
  const char* LengthError = "Unable to insert a new element!";
  const char* IndexError = "Index is out of range!";
  explicit DataStructure(size_t maxSize);                 // Конструктор, задающий максимальный размер структуры данных
                                                          // (не позволяет неявного преобразования)
  DataStructure(const DataStructure& ds);                 // Конструктор копирования
  //DataStructure(const Iterator& beg, const Iterator& end);            // Конструктор, инициализирующий с помощью итераторов

  bool checkIndex(size_t index);                  // Проверка индекса
private:
  virtual std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const = 0;          // Вывод структуры данных в поток
  virtual const std::istream& vInput(const std::istream& is, DataStructure& ds) = 0;    // Ввод структуры данных из потока

public:
  /////virtual DataStructure& vClone() const = 0;                            // Возвращает ссылку на копию структуры данных
private:                                                                        // (для конструктора копирования)

  //virtual void vInsert(Elem elem, size_t index) = 0;                  // Виртуальные функции соответствуют
  virtual void vSwap(size_t index1, size_t index2) = 0;                 // функциям интерфейса класса (без приставки v)
  virtual void vSwap(DataStructure& ds) = 0;                            // Обеспечивают полиморфное поведение объектов
  virtual void vReplace(size_t source, size_t dest) = 0;                
  virtual void vRemove(size_t index) = 0;
  //virtual Iterator vBegin() const = 0;
  //virtual Iterator vEnd() const = 0;
  //virtual Elem& vGet(size_t index) = 0;                                 // Соответствует operator []
  //virtual const Elem& vGet(size_t index) const = 0;
  virtual const DataStructure& vAssign(const DataStructure& ds) = 0;    // Соответствует operator =
  
  

  size_t _size;
  size_t _maxSize;
};

template <class Item>
static DataStructure* DataStructure::createArray(size_t maxSize) {
  return new Array<Item>(5);
}

template <class Item>
static DataStructure* DataStructure::createArray(const DataStructure& array) {
  return new Array<Item>(array);
}

}

#endif