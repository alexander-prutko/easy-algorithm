#ifndef EASY_ALGORITHM_LIST_ITERATOR_H
#define EASY_ALGORITHM_LIST_ITERATOR_H

#include <iosfwd>
#include <stdexcept>
#include "iterator.h"
#include "list.h"

namespace easy_algorithm {

template <class Item>
class ListIterator : public Iterator<Item> {                               // Класс - итератор для массивов
public:
  typedef typename List<Item>::link link;
  ListIterator(const Iterator<Item>& iter);                                // Конструктор копирования. Создает итератор идентичный iter
  ListIterator(link item);                                                // Конструктор с параметром, на какой элемент указывать
  virtual ~ListIterator();                                                 // Виртуальный деструктор позволяет полиморфное удаление объектов
  ListIterator();                                                          // Конструктор по умолчанию
  link getNode() const;
  void setNode(link node);

private:
  virtual std::ostream& vPrint(std::ostream& os, const Iterator<Item>& iter) const;               // Вывод значения элемента в поток
  virtual std::istream& vInput(std::istream& is, Iterator<Item>& ds);     // Ввод значения элемента из потока

  virtual Iterator<Item>& vIncrease();                                  // Соответствует operator ++
  virtual Iterator<Item>& vDecrease();                                  // Соответствует operator --
  virtual const Iterator<Item>& vSeekIter(ptrdiff_t diff);              // Соответствует operator +=, operator -=
  virtual const Iterator<Item>& vAssign(const Iterator<Item>& iter);    // Соответствует = iter
  virtual Iterator<Item>& vInsert(const Item& item);                    // Соответствует = item
  virtual void vSwap(Iterator<Item>& iter);                             // Соответствует swap
  virtual ptrdiff_t vDiff(const Iterator<Item>& iter);                  // Соответствует operator -

protected:
  using Iterator<Item>::_pItem;                                         // Указатель на элемент, на который ссылается итератор
  link _pNode;
};

template <class Item>
ListIterator<Item>::ListIterator() : Iterator<Item>(), _pNode(0) {}

template <class Item>
ListIterator<Item>::~ListIterator() {}

template <class Item>
ListIterator<Item>::ListIterator(link item) : Iterator<Item>(), _pNode(item) {
  _pItem = &(item->item);
}

template <class Item>
ListIterator<Item>::ListIterator(const Iterator<Item>& iter) : Iterator<Item>(iter), _pNode(iter.getNode()) {}

template <class Item>
std::ostream& ListIterator<Item>::vPrint(std::ostream& os, const Iterator<Item>& iter) const {
  os << *iter;                                                          // Вывод элемента, на который указывает итератор
  return os;
}

template <class Item>
typename List<Item>::link ListIterator<Item>::getNode() const {
  return _pNode;
}

template <class Item>
void ListIterator<Item>::setNode(link node) {
  _pNode = node;
}

template <class Item>
std::istream& ListIterator<Item>::vInput(std::istream& is, Iterator<Item>& iter) {
  Item temp;
  is >> temp;
  if(!(is.rdstate() & std::ios::failbit))
    iter = temp;                                                        // Присваивание элементу, на который указывает итератор, значения из входного потока
  return is;
}

template <class Item>
Iterator<Item>& ListIterator<Item>::vIncrease() {
  _pNode = _pNode->next;
  _pItem = &(_pNode->item);
  //++_pItem;
  return *this;
}

template <class Item>
Iterator<Item>& ListIterator<Item>::vDecrease() {
  throw std::exception();
  //--_pItem;
  return *this;
}

template <class Item>
const Iterator<Item>& ListIterator<Item>::vSeekIter(ptrdiff_t diff) {
  for(ptrdiff_t i = 0; i < diff; ++i)
    _pNode = _pNode->next;
  _pItem = &(_pNode->item);
  //_pItem += diff;
  return *this;
}

template <class Item>
const Iterator<Item>& ListIterator<Item>::vAssign(const Iterator<Item>& iter) {
  const ListIterator<Item>* pIter = dynamic_cast<const ListIterator<Item>*>(&iter);
  _pNode = pIter->getNode();
  _pItem = pIter->getPointer();
  return *this;
}

template <class Item>
Iterator<Item>& ListIterator<Item>::vInsert(const Item& item) {
  *_pItem = item;
  return *this;
}

template <class Item>
void ListIterator<Item>::vSwap(Iterator<Item>& iter) { //??? переделать
  Item* temp = _pItem;
  _pItem = iter.getPointer();
  iter.setPointer(temp);

  ListIterator<Item>* pIter = dynamic_cast<ListIterator<Item>*>(&iter);
  link ltemp = _pNode;
  _pNode = pIter->getNode();
  pIter->setNode(ltemp);
}

template <class Item>
ptrdiff_t ListIterator<Item>::vDiff(const Iterator<Item>& iter) {
  ptrdiff_t cnt = 0;
  link first = dynamic_cast<const ListIterator<Item>*>(&iter)->getNode();
  if (first != _pNode)
    while (first != _pNode) {
      first = first->next;
      ++cnt;
    }
  return cnt;
}

}

#endif
