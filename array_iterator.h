#ifndef EASY_ALGORITHM_ARRAY_ITERATOR_H
#define EASY_ALGORITHM_ARRAY_ITERATOR_H

#include <iosfwd>
#include <stdexcept>
#include "iterator.h"

namespace easy_algorithm {

template <class Item>
class ArrayIterator : public Iterator<Item> {
public:
  ArrayIterator(const Iterator<Item>& iter);                                // Конструктор копирования. Создает итератор идентичный iter
  virtual ~ArrayIterator() {}                                               // Виртуальный деструктор позволяет полиморфное удаление объектов
  ArrayIterator() : Iterator<Item>() {} /******/
private:
  virtual std::ostream& vPrint(std::ostream& os, Iterator<Item>& iter);         // Вывод значения элемента в поток
  virtual const std::istream& vInput(const std::istream& is, Iterator<Item>& ds);     // Ввод значения элемента из потока

  //virtual Iterator& vClone() = 0;                               // Возвращает ссылку на копию итератора (для конструктора копирования)

  virtual Iterator<Item>& vIncrease();                            // Соответствует operator ++
  virtual Iterator<Item>& vDecrease();                            // Соответствует operator --
  virtual const Iterator<Item>& vSeekIter(ptrdiff_t diff);        // Соответствует operator +=, operator -=
  virtual const Iterator<Item>& vAssign(const Iterator<Item>& iter);    // Соответствует =
  virtual Iterator<Item>& vInsert(const Item& item);              // Виртуальные функции соответствуют
  virtual void vSwap(Iterator<Item>& iter);                       // функциям интерфейса класса (без приставки v)
//  virtual Iterator<Item>& vReplace(Iterator& iter);             // Обеспечивают полиморфное поведение объектов
//  virtual Iterator<Item>& vRemove();
  virtual ptrdiff_t vDiff(const Iterator<Item>& iter);            // Соответствует operator -

protected:
  using Iterator<Item>::_pItem;

};

template <class Item>
std::ostream& ArrayIterator<Item>::vPrint(std::ostream& os, Iterator<Item>& iter) {
  return os; // Заглушка
}

template <class Item>
const std::istream& ArrayIterator<Item>::vInput(const std::istream& is, Iterator<Item>& iter) {
  return is; // Заглушка
}

template <class Item>
Iterator<Item>& ArrayIterator<Item>::vIncrease() {
  if (!_pItem)
    throw std::exception();
  ++_pItem;
  return *this;
}

template <class Item>
Iterator<Item>& ArrayIterator<Item>::vDecrease() {
  if (!_pItem)
    throw std::exception();
  --_pItem;
  return *this;
}

template <class Item>
const Iterator<Item>& ArrayIterator<Item>::vSeekIter(ptrdiff_t diff) {
  if (!_pItem)
    throw std::exception();
  _pItem += diff;
  return *this;
}

template <class Item>
const Iterator<Item>& ArrayIterator<Item>::vAssign(const Iterator<Item>& iter) {
  _pItem = iter.getPointer();
  return *this;
}

template <class Item>
Iterator<Item>& ArrayIterator<Item>::vInsert(const Item& item) {
  *_pItem = item;
  return *this;
}

template <class Item>
void ArrayIterator<Item>::vSwap(Iterator<Item>& iter) {
  std::swap(*_pItem, *(iter.getPointer()));
}

template <class Item>
ptrdiff_t ArrayIterator<Item>::vDiff(const Iterator<Item>& iter) {
  return (_pItem - iter.getPointer()) / sizeof(Item);
}

}

#endif
