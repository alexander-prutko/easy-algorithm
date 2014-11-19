#ifndef EASY_ALGORITHM_DLLIST_ITERATOR_H
#define EASY_ALGORITHM_DLLIST_ITERATOR_H

#include <iosfwd>
#include <stdexcept>
#include "iterator.h"
#include "dllist.h"

namespace easy_algorithm {

  template <class Item>
  class DLListIterator : public Iterator<Item> {                               // Класс - итератор для массивов
  public:
    typedef typename DLList<Item>::dllink dllink;
    DLListIterator(const Iterator<Item>& iter);                                // Конструктор копирования. Создает итератор идентичный iter
    DLListIterator(dllink item);                                                // Конструктор с параметром, на какой элемент указывать
    virtual ~DLListIterator();                                                 // Виртуальный деструктор позволяет полиморфное удаление объектов
    DLListIterator();                                                          // Конструктор по умолчанию
    dllink getNode() const;
    void setNode(dllink node);

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
    dllink _pNode;
  };

  template <class Item>
  DLListIterator<Item>::DLListIterator() : Iterator<Item>(), _pNode(0) {}

  template <class Item>
  DLListIterator<Item>::~DLListIterator() {}

  template <class Item>
  DLListIterator<Item>::DLListIterator(dllink item) : Iterator<Item>(), _pNode(item) {
    _pItem = &(item->item);
  }

  template <class Item>
  DLListIterator<Item>::DLListIterator(const Iterator<Item>& iter) : Iterator<Item>(iter), _pNode(dynamic_cast<const DLListIterator<Item>*>(&iter)->getNode()) {}

  template <class Item>
  std::ostream& DLListIterator<Item>::vPrint(std::ostream& os, const Iterator<Item>& iter) const {
    os << *iter;                                                          // Вывод элемента, на который указывает итератор
    return os;
  }

  template <class Item>
  typename DLList<Item>::dllink DLListIterator<Item>::getNode() const {
    return _pNode;
  }

  template <class Item>
  void DLListIterator<Item>::setNode(dllink node) {
    _pNode = node;
  }

  template <class Item>
  std::istream& DLListIterator<Item>::vInput(std::istream& is, Iterator<Item>& iter) {
    Item temp;
    is >> temp;
    if (!(is.rdstate() & std::ios::failbit))
      iter = temp;                                                        // Присваивание элементу, на который указывает итератор, значения из входного потока
    return is;
  }

  template <class Item>
  Iterator<Item>& DLListIterator<Item>::vIncrease() {
    _pNode = _pNode->next;
    _pItem = &(_pNode->item);
    //++_pItem;
    return *this;
  }

  template <class Item>
  Iterator<Item>& DLListIterator<Item>::vDecrease() {
    _pNode = _pNode->prev;
    _pItem = &(_pNode->item);
    //--_pItem;
    return *this;
  }

  template <class Item>
  const Iterator<Item>& DLListIterator<Item>::vSeekIter(ptrdiff_t diff) {
    if (diff > 0)
      for (ptrdiff_t i = 0; i < diff; ++i)
        _pNode = _pNode->next;
    if (diff < 0)
      for (ptrdiff_t i = 0; i < -diff; ++i)
        _pNode = _pNode->prev;
    _pItem = &(_pNode->item);
    //_pItem += diff;
    return *this;
  }

  template <class Item>
  const Iterator<Item>& DLListIterator<Item>::vAssign(const Iterator<Item>& iter) {
    const DLListIterator<Item>* pIter = dynamic_cast<const DLListIterator<Item>*>(&iter);
    _pNode = pIter->getNode();
    _pItem = pIter->getPointer();
    return *this;
  }

  template <class Item>
  Iterator<Item>& DLListIterator<Item>::vInsert(const Item& item) {
    *_pItem = item;
    return *this;
  }

  template <class Item>
  void DLListIterator<Item>::vSwap(Iterator<Item>& iter) { //??? переделать
    Item* temp = _pItem;
    _pItem = iter.getPointer();
    iter.setPointer(temp);

    DLListIterator<Item>* pIter = dynamic_cast<DLListIterator<Item>*>(&iter);
    dllink ltemp = _pNode;
    _pNode = pIter->getNode();
    pIter->setNode(ltemp);
  }

  template <class Item>
  ptrdiff_t DLListIterator<Item>::vDiff(const Iterator<Item>& iter) {
    ptrdiff_t cnt = 0;
    dllink first = dynamic_cast<const DLListIterator<Item>*>(&iter)->getNode();
    if (first != _pNode)
    while (first != _pNode) {
      first = first->next;
      ++cnt;
    }
    return cnt;
  }

}

#endif
