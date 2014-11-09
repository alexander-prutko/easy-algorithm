#ifndef EASY_ALGORITHM_VECTOR_ADAPTER_H
#define EASY_ALGORITHM_VECTOR_ADAPTER_H

#include <iosfwd>
#include <stdexcept>
#include <vector>
#include "data_structure.h"
#include "array_iterator.h"

namespace easy_algorithm {

template <class Item>
class VectorAdapter : public DataStructure {
public:
  friend class DataStructure;

  virtual ~VectorAdapter();

  void insert(Item item, size_t index);           // Вставить элемент item в позицию index
  void insert(Item item);
  Item& operator [] (size_t index);               // Возвращает ссылку на элемент с индексом index
  const Item& operator [] (size_t index) const;

  ArrayIterator<Item> begin() const;
  ArrayIterator<Item> end() const;

protected:      // protected?
  Item* getPointer() const;
  void setPointer(Item*);
  
private:
  VectorAdapter(std::vector<Item>& array);                        

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

  std::vector<Item>* pVector;
  Item* pArray;
  Item *_pCur1, *_pCur2;
};

template <class Item>
ArrayIterator<Item> VectorAdapter<Item>::begin() const {
  return ArrayIterator<Item>(pArray);
}

template <class Item>
ArrayIterator<Item> VectorAdapter<Item>::end() const {
  return ArrayIterator<Item>(&(pArray[Size()]));
}

template <class Item>
VectorAdapter<Item>::VectorAdapter(std::vector<Item>& array) : DataStructure(array.size()) {
  setSize(array.size());
  pArray = &(array[0]); 
  _pCur1 = _pCur2 = pArray;
}

template <class Item>
std::ostream& VectorAdapter<Item>::vPrint(std::ostream& os, const DataStructure& ds) const {
  return os; // Заглушка
}

template <class Item>
const std::istream& VectorAdapter<Item>::vInput(const std::istream& is, DataStructure& ds) {
  return is; // Заглушка
}

template <class Item>
void VectorAdapter<Item>::insert(Item item) {
  size_t size = Size();
  if(size == maxSize())
    throw std::length_error("Unable to insert a new itement!");
  insert(item, Size());
}

template <class Item>
void VectorAdapter<Item>::insert(Item item, size_t index) {
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
Item* VectorAdapter<Item>::getPointer() const {
  return pArray;
}

template <class Item>
void VectorAdapter<Item>::setPointer(Item* p) {
  pArray = p;
}

template <class Item>
void VectorAdapter<Item>::vSwap(DataStructure& ds) {
  Item* temp = pArray;
  VectorAdapter<Item>* ptrArray = dynamic_cast<VectorAdapter<Item>*>(&ds);

  pArray = ptrArray->getPointer();    // Преобразование к VectorAdapter<Item>*, т.к. vSwap вызовется точно для VectorAdapter
  ptrArray->setPointer(temp);

  size_t tmp = maxSize();
  setMaxSize(ds.maxSize());
  ptrArray->setMaxSize(tmp);

  tmp = Size();
  setSize(ds.Size());
  ptrArray->setSize(tmp);

  if (Size()) {
    setCur1(0);
    setCur2(0);
  }
  if (tmp) {
    ptrArray->setCur1(0);
    ptrArray->setCur2(0);
  }
}

template <class Item>
Item& VectorAdapter<Item>::operator [] (size_t index) {
  checkIndex(index);
  return pArray[index];
}

template <class Item>
const Item& VectorAdapter<Item>::operator [] (size_t index) const {
  checkIndex(index);
  return pArray[index];
}

template <class Item>
const DataStructure& VectorAdapter<Item>::vAssign(const DataStructure& ds) {
  DataStructure* temp = DataStructure::createArray<Item>(ds);
  swap(*temp);
  delete temp;
  return *this; 
}

template <class Item>
VectorAdapter<Item>::~VectorAdapter() {
  delete [] (pArray);
}

template <class Item>
void VectorAdapter<Item>::vSetCur1(size_t index) {
  _pCur1 = &pArray[index];
}

template <class Item>
void VectorAdapter<Item>::vSetCur2(size_t index) {
  _pCur2 = &pArray[index];
}

template <class Item>
bool VectorAdapter<Item>::vCompare() {
  return *_pCur1 < *_pCur2;
}

template <class Item>
void VectorAdapter<Item>::vSwap() {
  std::swap(*_pCur1, *_pCur2);
}

template <class Item>
void VectorAdapter<Item>::vReplace() {
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
void VectorAdapter<Item>::vRemove() {
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
