#ifndef EASY_ALGORITHM_DLLIST_H
#define EASY_ALGORITHM_DLLIST_H

#include <iosfwd>
#include <iostream>
#include <stdexcept>
#include <math.h>
#include "data_structure.h"

namespace easy_algorithm {

  template <class Item>
  class DLListIterator;                              // Предварительное объявление класса

  template <class Item>
  class DLList : public DataStructure {              // Класс-двуссвязный список
  public:
    struct dllist {                                  // Структура - реализация узлов списка
      dllist(Item i = Item(), dllist* n = NULL, dllist* p = NULL) : item(i), next(n), prev(p) {}
      Item item;                                     // Элемент списка
      dllist *next, *prev;                           // Указатели на следующий и предыдущий узлы списка
    };
    typedef dllist* dllink;

    friend class DataStructure;                     // DataStructure вызывает защищенный конструктор DLList

    virtual ~DLList();                              // Виртуальный деструктор позволяет полиморфное удаление объектов

    void insert(Item item, size_t index);           // Вставить элемент item в позицию index
    void insert(Item item);                         // Вставить элемент item в конец списка
    dllink operator [] (size_t index);              // Возвращает узел с индексом index
    dllink operator [] (size_t index) const;

    DLListIterator<Item> begin() const;              // Возвращает итератор на начало списка
    DLListIterator<Item> end() const;                // Возвращает итератор на конец списка (итератор указывает на узел за последним элементом списка)

  protected:
    dllink getPointer() const;                        // Возвращает указатель на список (pDLList)
    dllink getEnd() const;                            // Возвращает указатель на конец списка (pEnd)
    void setPointer(dllink s, dllink e);              // Устанавливает указатель на список и на конец списка (pDLList, pEnd)
    DLList(size_t maxSize);                           // Конструкторы закрытые, объекты класса DLList создаются
    DLList(const DataStructure& odllist);             // с помощью производящих функций класса DataStructure

  private:
    std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const;    // Вывод структуры данных в поток
    std::istream& vInput(std::istream& is, DataStructure& ds);    // Ввод структуры данных из потока

    void vSwap(DataStructure& ds);                                // Переопределение чисто виртуальных функций DataStructure
    const DataStructure& vAssign(const DataStructure& ds);
    void vSwap();
    void vMove();
    void vRemove();
    void vSetCur1(size_t index) const;
    void vSetCur2(size_t index) const;
    bool vCompare() const;

    dllink pDLList;                                           // Указатель на список
    dllink pEnd;                                              // Указатель на конец списка
    mutable dllink _pCur1, _pCur2;                            // Указатели на узлы списка, на которые указывают курсоры _cur1 и _cur2
  };

  template <class Item>
  DLListIterator<Item> DLList<Item>::begin() const {          // Возвращает итератор на начало списка
    return DLListIterator<Item>(pDLList->next);
  }

  template <class Item>
  DLListIterator<Item> DLList<Item>::end() const {            // Возвращает итератор на конец списка
    return DLListIterator<Item>(pEnd);                        // В качестве параметра - указатель на узел после последнего узла (конец списка)
  }

  template <class Item>
  DLList<Item>::DLList(size_t maxSize) : DataStructure(maxSize), _pCur1(0), _pCur2(0) {
    pDLList = new dllist();
    pEnd = new dllist();
    pDLList->next = pEnd;
    pDLList->prev = NULL;
    pEnd->next = NULL;
    pEnd->prev = pDLList;
    _pCur1 = _pCur2 = pDLList;
  }

  template <class Item>
  DLList<Item>::DLList(const DataStructure& odllist) : DataStructure(odllist), _pCur1(0), _pCur2(0) {
    pDLList = new dllist();
    pEnd = new dllist();
    pDLList->next = pEnd;
    pDLList->prev = NULL;
    pEnd->next = NULL;
    pEnd->prev = pDLList;
    _pCur1 = _pCur2 = pDLList;
    setSize(0);

    const DLList<Item>* pL = (dynamic_cast<const DLList<Item>*>(&odllist));          // Преобразование к DLList<Item>*, т.к. vPrint вызовется точно для DLList
    dllink pLink = pL->pDLList->next;
    for (size_t i = 0; i < odllist.Size(); ++i) {
      insert(pLink->item);                                                           // Вставка новых элементов из odllist
      pLink = pLink->next;
    }
  }

  template <class Item>
  std::ostream& DLList<Item>::vPrint(std::ostream& os, const DataStructure& ds) const {
    const DLList<Item>* pL = (dynamic_cast<const DLList<Item>*>(&ds));          // Преобразование к DLList<Item>*, т.к. vPrint вызовется точно для DLList
    dllink pLink = pL->pDLList->next;
    for (size_t i = 0; i < ds.Size(); ++i) {
      os << pLink->item << std::endl;                                           // Вывод i-того элемента
      pLink = pLink->next;
    }
    return os;
  }

  template <class Item>
  std::istream& DLList<Item>::vInput(std::istream& is, DataStructure& ds) {
    DLList<Item>* pL = (dynamic_cast<DLList<Item>*>(&ds));                   // Преобразование к DLList<Item>*, т.к. vInput вызовется точно для DLList
    Item temp;
    if (ds.Size() < ds.maxSize()) {                                          // Если структура данных заполнена, вводимое значение игнорируется
      is >> temp;
      if (!(is.rdstate() & std::ios::failbit))
        pL->insert(temp);                                                    // Вставка элемента в конец структуры данных
    }
    return is;
  }

  template <class Item>
  void DLList<Item>::insert(Item item) {
    size_t size = Size();
    if (size == maxSize())
      throw std::length_error("Unable to insert a new itement!");
    insert(item, size);                                                      // Вставка в конец списка
  }

  template <class Item>
  void DLList<Item>::insert(Item item, size_t index) {
    size_t size = Size();
    if (index) {
      setCur1(index - 1);
      setCur2(index - 1);
    }
    if (size >= maxSize())
      throw std::length_error("Unable to insert a new itement!");
    if (index > size || index < 0)
      throw std::out_of_range("Index is out of range!");
    if (index == 0) {                                                        // Если вставка в начало
      if (size == 0) {                                                       // Если список пуст
        pDLList->next = new dllist(item, pEnd, pDLList);
        pEnd->prev = pDLList->next;
      } else {                                                               // не пуст
        pDLList->next = new dllist(item, (*this)[index]->next, pDLList);
        pDLList->next->next->prev = pDLList->next;
      }
    } else
    if (index == size) {                                                     // Если вставка в конец
      //pDLList[index] = item;                                               // Вставка в конец списка
      dllink temp = (*this)[index - 1];
      temp->next = new dllist(item, pEnd, temp);
      pEnd->prev = temp->next;
    }
    else {                                                                   // Вставка в середину
      dllink temp = (*this)[index - 1];
      dllink temp2 = (*this)[index];
      temp->next = new dllist(item, temp2, temp);
      temp2->prev = temp->next;
    }
    setSize(size + 1);
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::getPointer() const {
    return pDLList;
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::getEnd() const {
    return pEnd;
  }

  template <class Item>
  void DLList<Item>::setPointer(dllink s, dllink e) {
    pDLList = s;
    pEnd = e;
  }

  template <class Item>
  void DLList<Item>::vSwap(DataStructure& ds) {                                // Обмен внутреннего содержания списков
    DLList<Item>* ptrDLList = dynamic_cast<DLList<Item>*>(&ds);                // Преобразование к DLList<Item>*, т.к. vSwap вызовется точно для DLList

    dllink tempDLList = pDLList;                                               // Обмен внутренними данными
    dllink tempEnd = pEnd;
    pDLList = ptrDLList->getPointer();
    pEnd = ptrDLList->getEnd();
    ptrDLList->setPointer(tempDLList, tempEnd);

    size_t tmp = maxSize();
    setMaxSize(ds.maxSize());
    ptrDLList->setMaxSize(tmp);

    tmp = Size();
    setSize(ds.Size());
    ptrDLList->setSize(tmp);

    if (!empty()) {                                                            // Иначе setCur1, setCur1 генерируют исключение
      setCur1(0);
      setCur2(0);
    }
    if (tmp) {
      ptrDLList->setCur1(0);
      ptrDLList->setCur2(0);
    }
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::operator [] (size_t index) {
    checkIndex(index);
    dllink pL;
    size_t c1 = getCur1();
    size_t c2 = getCur2();
    size_t c;
    if (abs(int(index - c1)) < abs(int(index - c2))) {      // Находим ближайший к искомому узлу курсор
      c = c1;
      pL = _pCur1;
    } else {
      c = c2;
      pL = _pCur2;
    }
    if (c < index) {                                        // От курсора ищем искомый узел
      for (size_t i = c; i < index; ++i)
        pL = pL->next;
    } else {
      for (size_t i = c; i > index; --i)
        pL = pL->prev;
    }
    return pL;
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::operator [] (size_t index) const {
    checkIndex(index);
    dllink pL;
    size_t c1 = getCur1();
    size_t c2 = getCur2();
    size_t c;
    if (abs(int(index - c1)) < abs(int(index - c2))) {
      c = c1;
      pL = _pCur1;
    }
    else {
      c = c2;
      pL = _pCur2;
    }
    if (c < index) {
      for (size_t i = c; i < index; ++i)
        pL = pL->next;
    }
    else {
      for (size_t i = c; i > index; --i)
        pL = pL->prev;
    }
    return pL;
  }

  template <class Item>
  const DataStructure& DLList<Item>::vAssign(const DataStructure& ds) {    // Идиома создания временного объекта и обмена
    DataStructure* temp = DataStructure::createDLList<Item>(ds);
    swap(*temp);
    delete temp;
    return *this;
  }

  template <class Item>
  DLList<Item>::~DLList() {
    dllink temp = pDLList;
    while (temp != pEnd) {        // Последовательное удаление узлов, начиная с начала
      temp = pDLList->next;
      delete(pDLList);
      pDLList = temp;
    }
    delete(pDLList);
  }

  template <class Item>
  void DLList<Item>::vSetCur1(size_t index) const {
    if (index == 0)
      _pCur1 = pDLList->next;
    else
      _pCur1 = (operator[](index));
  }

  template <class Item>
  void DLList<Item>::vSetCur2(size_t index) const {
    if (index == 0)
      _pCur2 = pDLList->next;
    else
      _pCur2 = (operator[](index));
  }

  template <class Item>
  bool DLList<Item>::vCompare() const {
    return _pCur1->item < _pCur2->item;
  }

  template <class Item>
  void DLList<Item>::vSwap() {
    size_t c1 = getCur1();
    size_t c2 = getCur2();
    if (c1 == c2 - 1) {                         // Если узлы смежные (1 вариант)
      _pCur1->next = _pCur2->next;
      _pCur2->prev = _pCur1->prev;
      _pCur1->prev->next = _pCur2;
      _pCur2->next->prev = _pCur1;
      _pCur1->prev = _pCur2;
      _pCur2->next = _pCur1;
    }
    else if (c2 == c1 - 1) {                    // Если узлы смежные (2 вариант)
      _pCur2->next = _pCur1->next;
      _pCur1->prev = _pCur2->prev;
      _pCur2->prev->next = _pCur1;
      _pCur1->next->prev = _pCur2;
      _pCur2->prev = _pCur1;
      _pCur1->next = _pCur2;
    }
    else {                                      // Если узлы не смежные
      std::swap(_pCur1->prev->next, _pCur2->prev->next);
      std::swap(_pCur1->next->prev, _pCur2->next->prev);
      std::swap(_pCur1->next, _pCur2->next);
      std::swap(_pCur1->prev, _pCur2->prev);
    }
    setCur1(0);
    setCur2(0);
  }

  template <class Item>
  void DLList<Item>::vMove() {
    size_t c1 = getCur1();
    size_t c2 = getCur2();
    if (c2 < c1) {
      _pCur1->prev->next = _pCur1->next;
      _pCur1->next->prev = _pCur1->prev;

      _pCur1->prev = _pCur2->prev;
      _pCur2->prev->next = _pCur1;
      _pCur2->prev = _pCur1;
      _pCur1->next = _pCur2;
    }
    else {
      _pCur1->prev->next = _pCur1->next;
      _pCur1->next->prev = _pCur1->prev;

      _pCur1->prev = _pCur2;
      _pCur2->next->prev = _pCur1;
      _pCur1->next = _pCur2->next;
      _pCur2->next = _pCur1;
    }

    setCur1(0);
    setCur2(0);
  }

  template <class Item>
  void DLList<Item>::vRemove() {
    size_t size = Size();
    dllink temp = _pCur1;
    _pCur1->prev->next = _pCur1->next;
    _pCur1->next->prev = _pCur1->prev;
    delete(temp);
    setCur1(0);
    setSize(size - 1);
  }

}

#endif
