#ifndef EASY_ALGORITHM_ARRAY_H
#define EASY_ALGORITHM_ARRAY_H

#include <iosfwd>
#include "data_structure.h"

namespace easy_algorithm {

template <class Item>
class Array : public DataStructure {
public:
  friend class DataStructure;

  virtual ~Array();

  void insert(Item item, size_t index);           // Вставить элемент item в позицию index
  void insert(Item item);
  Item& operator [] (size_t index);               // Возвращает ссылку на элемент с индексом index
  const Item& operator [] (size_t index) const;

protected:      // protected?
  Item* getPointer() const;
  void setPointer(Item*);
  
private:
  Array(size_t maxSize);                                    // Конструкторы закрытые, объекты класса Array создаются
  Array(const DataStructure& array);                        // с помощью производящих функций класса DataStructure

  std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const;
  const std::istream& vInput(const std::istream& is, DataStructure& ds);
  void vSwap(DataStructure& ds);
  const DataStructure& vAssign(const DataStructure& ds);

  void vSwap();
  void vReplace();
  void vRemove();
  void vSetCur1(size_t index);
  void vSetCur2(size_t index);
  bool vCompare();

  Item* pArray;
  Item *_pCur1, *_pCur2;
};

template <class Item>
Array<Item>::Array(size_t maxSize) : DataStructure(maxSize) {
  pArray = new Item[maxSize];
  _pCur1 = _pCur2 = pArray;
}

template <class Item>
Array<Item>::Array(const DataStructure& array) : DataStructure(array) {
  pArray = new Item[array.maxSize()]; 
  for (size_t i = 0; i < array.Size(); ++i) {
    pArray[i] = ((Array<Item>*)(&array))->pArray[i];  // Преобразование к Array<Item>*, т.к. этот конструктор вызовется точно для Array
  }
  _pCur1 = _pCur2 = pArray;
}

template <class Item>
std::ostream& Array<Item>::vPrint(std::ostream& os, const DataStructure& ds) const {
  return os; // Заглушка
}

template <class Item>
const std::istream& Array<Item>::vInput(const std::istream& is, DataStructure& ds) {
  return is; // Заглушка
}

template <class Item>
void Array<Item>::insert(Item item) {
  size_t size = Size();
  if(size == maxSize())
    throw std::length_error("Unable to insert a new itement!");
  insert(item, Size());
}

template <class Item>
void Array<Item>::insert(Item item, size_t index) {
  size_t size = Size();
  if(size >= maxSize())
    throw std::length_error("Unable to insert a new itement!");
  if (index > size || index < 0)
    throw std::out_of_range("Index is out of range!");
  if(index == size)
    pArray[index] = item;
  else {
    for(size_t i = size - 1; i >= index; --i)
      pArray[i + 1] = pArray[i];
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
void Array<Item>::vSwap(DataStructure& ds) {
  Item* temp = pArray;
  pArray = ((Array<int>*)(&ds))->getPointer();    // Преобразование к Array<Item>*, т.к. vSwap вызовется точно для Array
  ((Array<int>*)(&ds))->setPointer(temp);

  size_t tmp = maxSize();
  setMaxSize(ds.maxSize());
  ((Array<int>*)(&ds))->setMaxSize(tmp);

  tmp = Size();
  setSize(ds.Size());
  ((Array<int>*)(&ds))->setSize(tmp);

  if (Size()) {
    setCur1(0);
    setCur2(0);
  }
  if (tmp) {
    ((Array<int>*)(&ds))->setCur1(0);
    ((Array<int>*)(&ds))->setCur2(0);
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
const DataStructure& Array<Item>::vAssign(const DataStructure& ds) {
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
void Array<Item>::vSetCur1(size_t index) {
  _pCur1 = &pArray[index];
}

template <class Item>
void Array<Item>::vSetCur2(size_t index) {
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
      pArray[i] = pArray[i + 1];
    pArray[cur2] = temp;
  }
  else {
    Item temp = pArray[cur1];
    for (size_t i = cur1; i > cur2; --i)
      pArray[i] = pArray[i - 1];
    pArray[cur2] = temp;
  }
}

template <class Item>
void Array<Item>::vRemove() {
  size_t size = Size();
  size_t index = getCur1();
  if (index < size - 1) {
    for (size_t i = index; i < size - 1; ++i)
      pArray[i] = pArray[i + 1];
  }
  setSize(size - 1);
}

}

#endif
