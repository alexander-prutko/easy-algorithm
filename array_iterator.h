#ifndef EASY_ALGORITHM_ARRAY_ITERATOR_H
#define EASY_ALGORITHM_ARRAY_ITERATOR_H

#include <iosfwd>
#include "iterator.h"

namespace easy_algorithm {

template <class Item>
class ArrayIterator : public Iterator<Item> {                               // Класс - итератор для массивов
public:
  ArrayIterator(const Iterator<Item>& iter);                                // Конструктор копирования. Создает итератор идентичный iter
  ArrayIterator(Item* item);                                                // Конструктор с параметром, на какой элемент указывать
  virtual ~ArrayIterator();                                                 // Виртуальный деструктор позволяет полиморфное удаление объектов
  ArrayIterator();                                                          // Конструктор по умолчанию

private:
  virtual std::ostream& vPrint(std::ostream& os, Iterator<Item>& iter);               // Вывод значения элемента в поток
  virtual const std::istream& vInput(const std::istream& is, Iterator<Item>& ds);     // Ввод значения элемента из потока

  virtual Iterator<Item>& vIncrease();                                  // Соответствует operator ++
  virtual Iterator<Item>& vDecrease();                                  // Соответствует operator --
  virtual const Iterator<Item>& vSeekIter(ptrdiff_t diff);              // Соответствует operator +=, operator -=
  virtual const Iterator<Item>& vAssign(const Iterator<Item>& iter);    // Соответствует = iter
  virtual Iterator<Item>& vInsert(const Item& item);                    // Соответствует = item
  virtual void vSwap(Iterator<Item>& iter);                             // Соответствует swap
  virtual ptrdiff_t vDiff(const Iterator<Item>& iter);                  // Соответствует operator -

protected:
  using Iterator<Item>::_pItem;                                         // Указатель на элемент, на который ссылается итератор
};

template <class Item>
ArrayIterator<Item>::ArrayIterator() : Iterator<Item>() {}

template <class Item>
ArrayIterator<Item>::~ArrayIterator() {}

template <class Item>
ArrayIterator<Item>::ArrayIterator(Item* item) : Iterator<Item>() {
  _pItem = item;
}

template <class Item>
ArrayIterator<Item>::ArrayIterator(const Iterator<Item>& iter) : Iterator<Item>(iter) {}

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
  ++_pItem;
  return *this;
}

template <class Item>
Iterator<Item>& ArrayIterator<Item>::vDecrease() {
  --_pItem;
  return *this;
}

template <class Item>
const Iterator<Item>& ArrayIterator<Item>::vSeekIter(ptrdiff_t diff) {
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
