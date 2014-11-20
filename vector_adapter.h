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
  using Array<Item>::setMaxSize;
  using Array<Item>::setSize;
  using Array<Item>::setCur1;
  using Array<Item>::setCur2;
  using Array<Item>::setPointer;
  using Array<Item>::getPointer;

private:
  void vSwap(DataStructure&) { throw std::exception(); }                    // Нельзя обменивать вектор с другими структурами данных
  void vRemove() { throw std::exception(); }                                // Нельзя удалять элементы из вектора (нельзя именять размер)
  void insert(Item item, size_t index);                                     // Запрещаем вставку новых элементов в вектор (нельзя именять размер)
  void insert(Item item);

  Item* temp;                                                               // Указатель на элемент вектора
};

template <class Item>
VectorAdapter<Item>::VectorAdapter(std::vector<Item>& array) : Array<Item>(0) {
  temp = getPointer();        // Необходимо запомнить указатель pArray на пустой массив, созданный конструктором Array,
  setSize(array.size());      // чтобы потом деструкт Array его удалил, т.к. здесь мы для pArray назначим указатель на вектор
  setMaxSize(array.size());
  setPointer(&(array[0]));    // Назначаем pArray на массив вектора, чтобы работать с ним
  setCur1(0);
  setCur2(0);
}

template <class Item>
VectorAdapter<Item>::~VectorAdapter() {
  setPointer(temp);           // Восстанавливаем pArray на пустой массив, созданный конструктором Array, чтобы деструктор Array его удалил
}

}

#endif
