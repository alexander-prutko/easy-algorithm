#ifndef EASY_ALGORITHM_VECTOR_ADAPTER_H
#define EASY_ALGORITHM_VECTOR_ADAPTER_H

#include <vector>
#include <stdexcept>
#include "data_structure.h"

namespace easy_algorithm {

template <class Item>
class Array;                                                                // Предварительное объявление класса

template <class Item>
class VectorAdapter : public Array<Item> {                                  // Класс-адаптер для работы с vector
public:
  friend class DataStructure;                                               // DataStructure вызывает защищенный конструктор VectorAdapter

  virtual ~VectorAdapter();                                                 // Виртуальный деструктор позволяет полиморфное удаление объектов
  
protected:
  VectorAdapter(std::vector<Item>& array);                                  // В качестве параметра конструктора - существующий vector
  using DataStructure::setSize;
  using DataStructure::setCur1;
  using DataStructure::setCur2;
  using Array<Item>::setPointer;

private:
  void vSwap(DataStructure& ds) { throw std::exception(); }                 // Нельзя обменивать вектор с другими структурами данных
  void vRemove() { throw std::exception(); }                                // Нельзя удалять элементы из вектора (нельзя именять размер)
  void insert(Item item, size_t index);                                     // Запрещаем вставку новых элементов в вектор (нельзя именять размер)
  void insert(Item item);

  std::vector<Item>* pVector;                                               // Указатель на vector
};

template <class Item>
VectorAdapter<Item>::VectorAdapter(std::vector<Item>& array) : Array<Item>(array.size()) {
  setSize(array.size());
  setPointer(&(array[0]));
  setCur1(0);
  setCur2(0);
}

template <class Item>
VectorAdapter<Item>::~VectorAdapter() {}

}

#endif
