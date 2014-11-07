#ifndef EASY_ALGORITHM_DATA_STRUCTURE_H
#define EASY_ALGORITHM_DATA_STRUCTURE_H

#include <iosfwd>

namespace easy_algorithm {

template <class Item>
class Array;

class DataStructure {
public:
  friend std::ostream& operator << (std::ostream& os, const DataStructure& ds);         // Вывод структуры данных в поток
  friend const std::istream& operator >> (const std::istream& is, DataStructure& ds);   // Ввод структуры данных из потока

  template <class Item>
  static DataStructure* createArray(size_t maxSize);    // Производящие функции Array
  template <class Item>
  static DataStructure* createArray(const DataStructure& array);
  
  virtual ~DataStructure();                             // Виртуальный деструктор позволяет полиморфное удаление объектов

  void swap(size_t index1, size_t index2);              // Поменять местами 2 элемента с индексами index1 и index2
  void swap(DataStructure& ds);                         // Поменять структуры данных
  void replace(size_t source, size_t dest);             // Переставить элемент с индексом source в позицию dest
  void remove(size_t index);                            // Удалить элемент с индексом index
  bool compare(size_t index1, size_t index2);           // Возвращает true, если элемент 1 меньше элемента 2
  const DataStructure& operator = (const DataStructure& ds);    // Делает содержание структуры данных идентичной ds
  
  size_t Size() const;                                  // Возвращает количество элементов
  size_t maxSize() const;                               // Возвращает максимальный размер структуры данных
  bool empty() const;                                   // Возвращает true, если елементов нет

  void swap();
  void replace();
  void remove();
  void setCur1(size_t index);
  void setCur2(size_t index);
  size_t getCur1();
  size_t getCur2();
  bool compare();

protected:
  explicit DataStructure(size_t maxSize);                 // Конструктор, задающий максимальный размер структуры данных
                                                          // (не позволяет неявного преобразования)
  DataStructure(const DataStructure& ds);                 // Конструктор копирования
  
  void checkIndex(size_t index);                          // Проверка индекса
  void setSize(size_t size);                              // Устанавливает количество элементов
  void setMaxSize(size_t size);                           // Устанавливает максимальный размер структуры данных

private:
  virtual std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const = 0;    // Вывод структуры данных в поток
  virtual const std::istream& vInput(const std::istream& is, DataStructure& ds) = 0;    // Ввод структуры данных из потока

private:
  virtual void vSwap(DataStructure& ds) = 0;
  virtual const DataStructure& vAssign(const DataStructure& ds) = 0;    // Соответствует operator =             

  virtual void vSwap() = 0;
  virtual void vReplace() = 0;
  virtual void vRemove() = 0;
  virtual void vSetCur1(size_t index) = 0;
  virtual void vSetCur2(size_t index) = 0;
  virtual bool vCompare() = 0;
  
  size_t _size;
  size_t _maxSize;
  size_t _cur1, _cur2;
};

template <class Item>
DataStructure* DataStructure::createArray(size_t maxSize) {
  return new Array<Item>(maxSize);
}

template <class Item>
DataStructure* DataStructure::createArray(const DataStructure& array) {
  return new Array<Item>(array);
}

}

#endif
