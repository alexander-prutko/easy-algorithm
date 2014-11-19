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
  class DLList : public DataStructure {              // Класс-массив
  public:
    struct dllist {
      dllist(Item i = Item(), dllist* n = NULL, dllist* p = NULL) : item(i), next(n), prev(p) {}
      Item item;
      dllist *next, *prev;
    };
    typedef dllist* dllink;

    friend class DataStructure;                     // DataStructure вызывает защищенный конструктор DLList

    virtual ~DLList();                                // Виртуальный деструктор позволяет полиморфное удаление объектов

    void insert(Item item, size_t index);           // Вставить элемент item в позицию index
    void insert(Item item);                         // Вставить элемент item в конец списка
    dllink operator [] (size_t index);                // Возвращает ссылку на элемент с индексом index
    dllink operator [] (size_t index) const;

    DLListIterator<Item> begin() const;              // Возвращает итератор на начало списка
    DLListIterator<Item> end() const;                // Возвращает итератор на конец списка (итератор указывает на элемент за последним элемента списка)

  protected:
    dllink getPointer() const;                        // Возвращает указатель на список (pDLList)
    dllink getEnd() const;
    void setPointer(dllink s, dllink e);                // Устанавливает указатель на список (pDLList)
    DLList(size_t maxSize);                           // Конструкторы закрытые, объекты класса DLList создаются
    DLList(const DataStructure& odllist);               // с помощью производящих функций класса DataStructure

  private:
    std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const;    // Вывод структуры данных в поток
    std::istream& vInput(std::istream& is, DataStructure& ds);    // Ввод структуры данных из потока

    void vSwap(DataStructure& ds);                                // Переопределение чисто виртуальных функций DataStructure
    const DataStructure& vAssign(const DataStructure& ds);
    void vSwap();
    void vReplace();
    void vRemove();
    void vSetCur1(size_t index) const;
    void vSetCur2(size_t index) const;
    bool vCompare();

    dllink pDLList;                                           // Указатель на список
    dllink pEnd;
    mutable dllink _pCur1, _pCur2;                          // Указатели на элементы списка, на которые указывают курсоры _cur1 и _cur2
  };

  template <class Item>
  DLListIterator<Item> DLList<Item>::begin() const {//?
    return DLListIterator<Item>(pDLList->next);
  }

  template <class Item>
  DLListIterator<Item> DLList<Item>::end() const {//?
    return DLListIterator<Item>(pEnd);                            // В качестве параметра - ссылка на элемент после последнего элемента
  }

  template <class Item>
  DLList<Item>::DLList(size_t maxSize) : DataStructure(maxSize), _pCur1(0), _pCur2(0) { //заглушка
    pDLList = new dllist();
    pEnd = new dllist();
    pDLList->next = pEnd;
    pDLList->prev = NULL;
    pEnd->next = NULL;
    pEnd->prev = pDLList;
    _pCur1 = _pCur2 = pDLList;
  }

  template <class Item>
  DLList<Item>::DLList(const DataStructure& odllist) : DataStructure(odllist), _pCur1(0), _pCur2(0) {  //заглушка
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
      insert(pLink->item);
      pLink = pLink->next;
    }
  }

  template <class Item>
  std::ostream& DLList<Item>::vPrint(std::ostream& os, const DataStructure& ds) const { //заглушка
    const DLList<Item>* pL = (dynamic_cast<const DLList<Item>*>(&ds));          // Преобразование к DLList<Item>*, т.к. vPrint вызовется точно для DLList
    dllink pLink = pL->pDLList;
    for (size_t i = 0; i < ds.Size(); ++i) {
      os << pLink->next->item << std::endl;                                 // Вывод i-того элемента
      pLink = pLink->next;
    }
    return os;
  }

  template <class Item>
  std::istream& DLList<Item>::vInput(std::istream& is, DataStructure& ds) { //заглушка
    DLList<Item>* pL = (dynamic_cast<DLList<Item>*>(&ds));                      // Преобразование к DLList<Item>*, т.к. vInput вызовется точно для DLList
    Item temp;
    if (ds.Size() < ds.maxSize()) {                                          // Если структура данных заполнена, вводимое значение игнорируется
      is >> temp;
      if (!(is.rdstate() & std::ios::failbit))
        pL->insert(temp);                                                   // Вставка элемента в конец структуры данных
    }
    return is;
  }

  template <class Item>
  void DLList<Item>::insert(Item item) { //заглушка
    size_t size = Size();
    if (size == maxSize())
      throw std::length_error("Unable to insert a new itement!");
    insert(item, size);                                                     // Вставка в конец списка
  }

  template <class Item>
  void DLList<Item>::insert(Item item, size_t index) { //заглушка
    size_t size = Size();
    if (index) {
      setCur1(index - 1);
      setCur2(index - 1);
    }
    //setSize(size + 1);
    if (size >= maxSize())
      throw std::length_error("Unable to insert a new itement!");
    if (index > size || index < 0)
      throw std::out_of_range("Index is out of range!");
    if (index == 0) {
      if (size == 0) {
        pDLList->next = new dllist(item, pEnd, pDLList);
        pEnd->prev = pDLList->next;
      } else {
        pDLList->next = new dllist(item, (*this)[index]->next, pDLList);
        pDLList->next->next->prev = pDLList->next;
      }
    } else
    if (index == size) {
      //pDLList[index] = item;                                                    // Вставка в конец списка
      dllink temp = (*this)[index - 1];
      temp->next = new dllist(item, pEnd, temp);
      pEnd->prev = temp->next;
    }
    else {
      dllink temp = (*this)[index - 1];
      dllink temp2 = (*this)[index];
      temp->next = new dllist(item, temp2, temp);
      temp2->prev = temp->next;
      /*for(size_t i = size - 1; i >= index; --i)
      pDLList[i + 1] = pDLList[i];                                                // Сдвиг части списка, начиная с места вставки, вправо
      pDLList[index] = item;*/
    }
    setSize(size + 1);
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::getPointer() const { //заглушка?
    return pDLList;
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::getEnd() const { //заглушка?
    return pEnd;
  }

  template <class Item>
  void DLList<Item>::setPointer(dllink s, dllink e) { //заглушка?
    pDLList = s;
    pEnd = e;
  }

  template <class Item>
  void DLList<Item>::vSwap(DataStructure& ds) {                                // Обмен внутреннего содержания списков
    DLList<Item>* ptrDLList = dynamic_cast<DLList<Item>*>(&ds);                    // Преобразование к DLList<Item>*, т.к. vSwap вызовется точно для DLList

    dllink tempDLList = pDLList;
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

    if (!empty()) {                                                           // Иначе setCur1, setCur1 генерируют исключение
      setCur1(0);
      setCur2(0);
    }
    if (tmp) {
      ptrDLList->setCur1(0);
      ptrDLList->setCur2(0);
    }
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::operator [] (size_t index) { //заглушка
    checkIndex(index);
    dllink pL;
    size_t c1 = getCur1();
    size_t c2 = getCur2();
    size_t c;
    if (abs(int(index - c1)) < abs(int(index - c2))) {
      c = c1;
      pL = _pCur1;
    } else {
      c = c2;
      pL = _pCur2;
    }
    if (c < index) {
      for (size_t i = c; i < index; ++i)
        pL = pL->next;
    } else {
      for (size_t i = c; i > index; --i)
        pL = pL->prev;
    }
    return pL; //возвращаем ссылку на временный объект или нет?
  }

  template <class Item>
  typename DLList<Item>::dllink DLList<Item>::operator [] (size_t index) const { //заглушка
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
    return pL; //возвращаем ссылку на временный объект или нет?
  }

  template <class Item>
  const DataStructure& DLList<Item>::vAssign(const DataStructure& ds) {    // Идиома создания временного объекта и обмена
    DataStructure* temp = DataStructure::createDLList<Item>(ds); //заглушка (но вроде должна норм работать)
    swap(*temp);
    delete temp;
    return *this;
  }

  template <class Item>
  DLList<Item>::~DLList() { //заглушка
    dllink temp = pDLList;
    while (temp != pEnd) {
      temp = pDLList->next;
      delete(pDLList);
      pDLList = temp;
    }
    delete(pDLList);
  }

  template <class Item>
  void DLList<Item>::vSetCur1(size_t index) const { //заглушка
    if (index == 0)
      _pCur1 = pDLList->next;
    else
      _pCur1 = (operator[](index));
  }

  template <class Item>
  void DLList<Item>::vSetCur2(size_t index) const { //заглушка
    if (index == 0)
      _pCur2 = pDLList->next;
    else
      _pCur2 = (operator[](index));
  }

  template <class Item>
  bool DLList<Item>::vCompare() { //заглушка
    return _pCur1->item < _pCur2->item;
  }

  template <class Item>
  void DLList<Item>::vSwap() { //заглушка
    size_t c1 = getCur1();
    size_t c2 = getCur2();
    if (c1 == c2 - 1) {
      _pCur1->next = _pCur2->next;
      _pCur2->prev = _pCur1->prev;
      _pCur1->prev->next = _pCur2;
      _pCur2->next->prev = _pCur1;
      _pCur1->prev = _pCur2;
      _pCur2->next = _pCur1;
    }
    else if (c2 == c1 - 1) {
      _pCur2->next = _pCur1->next;
      _pCur1->prev = _pCur2->prev;
      _pCur2->prev->next = _pCur1;
      _pCur1->next->prev = _pCur2;
      _pCur2->prev = _pCur1;
      _pCur1->next = _pCur2;
    }
    else {
      std::swap(_pCur1->prev->next, _pCur2->prev->next);
      std::swap(_pCur1->next->prev, _pCur2->next->prev);
      std::swap(_pCur1->next, _pCur2->next);
      std::swap(_pCur1->prev, _pCur2->prev);
    }
    setCur1(0);
    setCur2(0);
  }

  template <class Item>
  void DLList<Item>::vReplace() { //заглушка
    _pCur1->prev->next = _pCur1->next;
    _pCur1->next->prev = _pCur1->prev;

    _pCur1->prev = _pCur2->prev;
    _pCur2->prev->next = _pCur1;
    _pCur2->prev = _pCur1;
    _pCur1->next = _pCur2;

    setCur1(0);
    setCur2(0);
  }

  template <class Item>
  void DLList<Item>::vRemove() { //заглушка
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
