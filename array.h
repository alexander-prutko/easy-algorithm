#ifndef EASY_ALGORITHM_ARRAY_H
#define EASY_ALGORITHM_ARRAY_H

#include <iosfwd>
#include <stdexcept>
#include <iostream>
#include "data_structure.h"

namespace easy_algorithm {

template <class Item>
class ArrayIterator;                              // Предварительное объявление класса

template <class Item>
class Array : public DataStructure {              // Класс-массив
public:
  friend class DataStructure;                     // DataStructure вызывает защищенный конструктор Array

  virtual ~Array();                               // Виртуальный деструктор позволяет полиморфное удаление объектов

  void insert(Item item, size_t index);           // Вставить элемент item в позицию index
  void insert(Item item);                         // Вставить элемент item в конец массива
  Item& operator [] (size_t index);               // Возвращает ссылку на элемент с индексом index
  const Item& operator [] (size_t index) const;

  ArrayIterator<Item> begin() const;              // Возвращает итератор на начало массива
  ArrayIterator<Item> end() const;                // Возвращает итератор на конец массива (итератор указывает на элемент за последним элемента массива)

protected:
  Item* getPointer() const;                       // Возвращает указатель на массив (pArray)
  void setPointer(Item*);                         // Устанавливает указатель на массив (pArray)
  Array(size_t maxSize);                          // Конструкторы закрытые, объекты класса Array создаются
  Array(const DataStructure& array);              // с помощью производящих функций класса DataStructure
  
private:
  std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const;    // Вывод структуры данных в поток
  std::istream& vInput(std::istream& is, DataStructure& ds);    // Ввод структуры данных из потока

  void vSwap(DataStructure& ds);                            // Переопределение чисто виртуальных функций DataStructure
  const DataStructure& vAssign(const DataStructure& ds);
  void vSwap();
  void vReplace();
  void vRemove();
  void vSetCur1(size_t index) const;
  void vSetCur2(size_t index) const;
  bool vCompare();

  Item* pArray;                                   // Указатель на массив
  Item *_pCur1, *_pCur2;                          // Указатели на элементы массива, на которые указывают курсоры _cur1 и _cur2
};

template <class Item>
ArrayIterator<Item> Array<Item>::begin() const {
  return ArrayIterator<Item>(pArray);
}

template <class Item>
ArrayIterator<Item> Array<Item>::end() const {
  return ArrayIterator<Item>(&(pArray[Size()]));                            // В качестве параметра - ссылка на элемент после последнего элемента
}

template <class Item>
Array<Item>::Array(size_t maxSize) : DataStructure(maxSize) {
  pArray = new Item[maxSize];
  _pCur1 = _pCur2 = pArray;
}

template <class Item>
Array<Item>::Array(const DataStructure& array) : DataStructure(array) {
  pArray = new Item[array.maxSize()]; 
  const Array<Item>* ptrArray = dynamic_cast<const Array<Item>*>(&array);   // Преобразование к Array<Item>*, т.к. этот конструктор вызовется точно для Array
  for (size_t i = 0; i < array.Size(); ++i) {
    pArray[i] = ptrArray->pArray[i];                                        // Копирование содержимого массива
  }
  _pCur1 = _pCur2 = pArray;
}

template <class Item>
std::ostream& Array<Item>::vPrint(std::ostream& os, const DataStructure& ds) const {
  const Array<Item>* pA = (dynamic_cast<const Array<Item>*>(&ds));        // Преобразование к Array<Item>*, т.к. vPrint вызовется точно для Array
  for(size_t i = 0; i < ds.Size(); ++i)
    os << pA->operator [](i) << std::endl;                                // Вывод i-того элемента
  return os;
}

template <class Item>
std::istream& Array<Item>::vInput(std::istream& is, DataStructure& ds) {
  Array<Item>* pA = (dynamic_cast<Array<Item>*>(&ds));                    // Преобразование к Array<Item>*, т.к. vInput вызовется точно для Array
  Item temp;
  if(ds.Size() < ds.maxSize()) {                                          // Если структура данных заполнена, вводимое значение игнорируется
    is >> temp;
    if(!(is.rdstate() & std::ios::failbit))
      pA->insert(temp);                                                   // Вставка элемента в конец структуры данных
  }
  return is;
}

template <class Item>
void Array<Item>::insert(Item item) {
  size_t size = Size();
  if(size == maxSize())
    throw std::length_error("Unable to insert a new itement!");
  insert(item, size);                                                     // Вставка в конец массива
}

template <class Item>
void Array<Item>::insert(Item item, size_t index) {
  size_t size = Size();
  if(size >= maxSize())
    throw std::length_error("Unable to insert a new itement!");
  if (index > size || index < 0)
    throw std::out_of_range("Index is out of range!");
  if(index == size)
    pArray[index] = item;                                                   // Вставка в конец массива
  else {
    for(size_t i = size - 1; i >= index; --i)
      pArray[i + 1] = pArray[i];                                            // Сдвиг части массива, начиная с места вставки, вправо
    pArray[index] = item;
  }
  setSize(size + 1);
}

template <class Item>
Item* Array<Item>::getPointer() const {
  return pArray;
}

template <class Item>
void Array<Item>::setPointer(Item* p) {
  pArray = p;
}

template <class Item>
void Array<Item>::vSwap(DataStructure& ds) {                                // Обмен внутреннего содержания массивов
  Item* temp = pArray;
  Array<Item>* ptrArray = dynamic_cast<Array<Item>*>(&ds);                  // Преобразование к Array<Item>*, т.к. vSwap вызовется точно для Array

  pArray = ptrArray->getPointer();
  ptrArray->setPointer(temp);

  size_t tmp = maxSize();
  setMaxSize(ds.maxSize());
  ptrArray->setMaxSize(tmp);

  tmp = Size();
  setSize(ds.Size());
  ptrArray->setSize(tmp);

  if (!empty()) {                                                           // Иначе setCur1, setCur1 генерируют исключение
    setCur1(0);
    setCur2(0);
  }
  if (tmp) {
    ptrArray->setCur1(0);
    ptrArray->setCur2(0);
  }
}

template <class Item>
Item& Array<Item>::operator [] (size_t index) {
  checkIndex(index);
  return pArray[index];
}

template <class Item>
const Item& Array<Item>::operator [] (size_t index) const {
  checkIndex(index);
  return pArray[index];
}

template <class Item>
const DataStructure& Array<Item>::vAssign(const DataStructure& ds) {    // Идиома создания временного объекта и обмена
  DataStructure* temp = DataStructure::createArray<Item>(ds);
  swap(*temp);
  delete temp;
  return *this; 
}

template <class Item>
Array<Item>::~Array() {
  delete [] (pArray);
}

template <class Item>
void Array<Item>::vSetCur1(size_t index) const {
  _pCur1 = &pArray[index];
}

template <class Item>
void Array<Item>::vSetCur2(size_t index) const {
  _pCur2 = &pArray[index];
}

template <class Item>
bool Array<Item>::vCompare() {
  return *_pCur1 < *_pCur2;
}

template <class Item>
void Array<Item>::vSwap() {
  std::swap(*_pCur1, *_pCur2);
}

template <class Item>
void Array<Item>::vReplace() {
  size_t cur1 = getCur1();
  size_t cur2 = getCur2();
  if (cur1 < cur2) {
    Item temp = pArray[cur1];
    for (size_t i = cur1; i < cur2; ++i)
      pArray[i] = pArray[i + 1];                                            // Сдвиг части массива между cur1 и cur2 влево
    pArray[cur2] = temp;
  }
  else {
    Item temp = pArray[cur1];
    for (size_t i = cur1; i > cur2; --i)
      pArray[i] = pArray[i - 1];                                            // Сдвиг части массива между cur1 и cur2 вправо
    pArray[cur2] = temp;
  }
}

template <class Item>
void Array<Item>::vRemove() {
  size_t size = Size();
  size_t index = getCur1();
  if (index < size - 1) {                                                   // Если элемент последний - ничего не сдвигаем
    for (size_t i = index; i < size - 1; ++i)
      pArray[i] = pArray[i + 1];                                            // Иначе сдвигаем часть массива после удаленного элемента влево
  }
  setSize(size - 1);
}

}

#endif
