#ifndef EASY_ALGORITHM_LIST_H
#define EASY_ALGORITHM_LIST_H

#include <iosfwd>
#include <iostream>
#include <stdexcept>
#include "data_structure.h"

namespace easy_algorithm {

template <class Item>
class ListIterator;                              // Предварительное объявление класса

template <class Item>
class List : public DataStructure {              // Класс-массив
public:
  struct list {
    list(Item i = Item(), list* l = NULL) : item(i), next(l) {}
    Item item;
    list* next;
  };
  typedef list* link;

  friend class DataStructure;                     // DataStructure вызывает защищенный конструктор List

  virtual ~List();                                // Виртуальный деструктор позволяет полиморфное удаление объектов

  void insert(Item item, size_t index);           // Вставить элемент item в позицию index
  void insert(Item item);                         // Вставить элемент item в конец списка
  link operator [] (size_t index);                // Возвращает ссылку на элемент с индексом index
  link operator [] (size_t index) const;

  ListIterator<Item> begin() const;              // Возвращает итератор на начало списка
  ListIterator<Item> end() const;                // Возвращает итератор на конец списка (итератор указывает на элемент за последним элемента списка)

protected:
  link getPointer() const;                        // Возвращает указатель на список (pList)
  link getEnd() const;
  void setPointer(link s, link e);                // Устанавливает указатель на список (pList)
  List(size_t maxSize);                           // Конструкторы закрытые, объекты класса List создаются
  List(const DataStructure& olist);               // с помощью производящих функций класса DataStructure
  
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

  link pList;                                           // Указатель на список
  link pEnd;
  mutable link _pCur1, _pCur2;                          // Указатели на элементы списка, на которые указывают курсоры _cur1 и _cur2
};

template <class Item>
ListIterator<Item> List<Item>::begin() const {//?
  return ListIterator<Item>(pList->next);
}

template <class Item>
ListIterator<Item> List<Item>::end() const {//?
  return ListIterator<Item>(pEnd);                            // В качестве параметра - ссылка на элемент после последнего элемента
}

template <class Item>
List<Item>::List(size_t maxSize) : DataStructure(maxSize), _pCur1(0), _pCur2(0) { //готово
  pList = new list();
  pEnd = new list();
  pList->next = pEnd;
  pEnd->next = NULL;
  _pCur1 = _pCur2 = pList;
}

template <class Item>
List<Item>::List(const DataStructure& olist) : DataStructure(olist), _pCur1(0), _pCur2(0) {  //готово
  pList = new list();
  pEnd = new list();
  pList->next = pEnd;
  pEnd->next = NULL;
  _pCur1 = _pCur2 = pList;
  setSize(0);

  const List<Item>* pL = (dynamic_cast<const List<Item>*>(&olist));          // Преобразование к List<Item>*, т.к. vPrint вызовется точно для List
  link pLink = pL->pList;
  for(size_t i = 0; i < olist.Size(); ++i) {
    insert(pLink->next->item);
    pLink = pLink->next;
  }
}

template <class Item>
std::ostream& List<Item>::vPrint(std::ostream& os, const DataStructure& ds) const { //готово
  const List<Item>* pL = (dynamic_cast<const List<Item>*>(&ds));          // Преобразование к List<Item>*, т.к. vPrint вызовется точно для List
  link pLink = pL->pList;
  for(size_t i = 0; i < ds.Size(); ++i) {
    os << pLink->next->item << std::endl;                                 // Вывод i-того элемента
    pLink = pLink->next;
  }
  return os;
}

template <class Item>
std::istream& List<Item>::vInput(std::istream& is, DataStructure& ds) { //готово
  List<Item>* pL = (dynamic_cast<List<Item>*>(&ds));                      // Преобразование к List<Item>*, т.к. vInput вызовется точно для List
  Item temp;
  if(ds.Size() < ds.maxSize()) {                                          // Если структура данных заполнена, вводимое значение игнорируется
    is >> temp;
    if(!(is.rdstate() & std::ios::failbit))
      pL->insert(temp);                                                   // Вставка элемента в конец структуры данных
  }
  return is;
}

template <class Item>
void List<Item>::insert(Item item) { //готово
  size_t size = Size();
  if(size == maxSize())
    throw std::length_error("Unable to insert a new itement!");
  insert(item, size);                                                     // Вставка в конец списка
}

template <class Item>
void List<Item>::insert(Item item, size_t index) { //готово
  size_t size = Size();
  if (index)
    setCur1(index - 1);
  //setSize(size + 1);
  if(size >= maxSize())
    throw std::length_error("Unable to insert a new itement!");
  if (index > size || index < 0)
    throw std::out_of_range("Index is out of range!");
  if (index == 0) {
    if (size == 0)
      pList->next = new list(item, pEnd);
    else
      pList->next = new list(item, (*this)[index]->next);
  } else
  if (index == size) {
    //pList[index] = item;                                                    // Вставка в конец списка
    (*this)[index - 1]->next->next = new list(item, pEnd);
  } else {
    (*this)[index - 1]->next->next = new list(item, (*this)[index]->next);
    /*for(size_t i = size - 1; i >= index; --i)
      pList[i + 1] = pList[i];                                                // Сдвиг части списка, начиная с места вставки, вправо
    pList[index] = item;*/
  }
  setSize(size + 1);
}

template <class Item>
typename List<Item>::link List<Item>::getPointer() const { //готово?
  return pList;
}

template <class Item>
typename List<Item>::link List<Item>::getEnd() const { //готово?
  return pEnd;
}

template <class Item>
void List<Item>::setPointer(link s, link e) { //готово?
  pList = s;
  pEnd = e;
}

template <class Item>
void List<Item>::vSwap(DataStructure& ds) {                                // Обмен внутреннего содержания списков
  List<Item>* ptrList = dynamic_cast<List<Item>*>(&ds);                    // Преобразование к List<Item>*, т.к. vSwap вызовется точно для List
  
  link tempList = pList;
  link tempEnd = pEnd;
  pList = ptrList->getPointer();
  pEnd = ptrList->getEnd();
  ptrList->setPointer(tempList, tempEnd);

  size_t tmp = maxSize();
  setMaxSize(ds.maxSize());
  ptrList->setMaxSize(tmp);

  tmp = Size();
  setSize(ds.Size());
  ptrList->setSize(tmp);

  if (!empty()) {                                                           // Иначе setCur1, setCur1 генерируют исключение
    setCur1(0);
    setCur2(0);
  }
  if (tmp) {
    ptrList->setCur1(0);
    ptrList->setCur2(0);
  }
}

template <class Item>
typename List<Item>::link List<Item>::operator [] (size_t index) { //готово
  checkIndex(index);
  size_t c1 = getCur1();
  size_t c2 = getCur2();
  link pL = pList;
  if (index < c1 && index < c2) {
    for (size_t i = 0; i < index; ++i)
      pL = pL->next;
    //pL = pL->next;
  } else
  if (c1 <= index && (c2 <= c1 || (c1 < c2 && c2 > index))) {
    pL = _pCur1;
    for (size_t i = c1; i < index; ++i)
      pL = pL->next;
    //pL = pL->next;
  } else
  if (c2 <= index && (c1 <= c2 || (c2 < c1 && c1 > index))) {
    pL = _pCur2;
    for (size_t i = c2; i < index; ++i)
      pL = pL->next;
    //pL = pL->next;
  }
  //setCur1(index);
  //_pCur1 = pL;
  return pL; //возвращаем ссылку на временный объект или нет?
}

template <class Item>
typename List<Item>::link List<Item>::operator [] (size_t index) const { //готово
  checkIndex(index);
  size_t c1 = getCur1();
  size_t c2 = getCur2();
  link pL = pList;
  if (index < c1 && index < c2) {
    for (size_t i = 0; i < index; ++i)
      pL = pL->next;
    //pL = pL->next;
  }
  else
  if (c1 <= index && (c2 <= c1 || (c1 < c2 && c2 > index))) {
    pL = _pCur1;
    for (size_t i = c1; i < index; ++i)
      pL = pL->next;
    //pL = pL->next;
  }
  else
  if (c2 <= index && (c1 <= c2 || (c2 < c1 && c1 > index))) {
    pL = _pCur2;
    for (size_t i = c2; i < index; ++i)
      pL = pL->next;
    //pL = pL->next;
  }
  //setCur1(index);
  //_pCur1 = pL;
  return pL; //возвращаем ссылку на временный объект или нет?
}

template <class Item>
const DataStructure& List<Item>::vAssign(const DataStructure& ds) {    // Идиома создания временного объекта и обмена
  DataStructure* temp = DataStructure::createList<Item>(ds); //заглушка (но вроде должна норм работать)
  swap(*temp);
  delete temp;
  return *this; 
}

template <class Item>
List<Item>::~List() { //готово
  link temp = pList;
  while(temp != pEnd) {
    temp = pList->next;
    delete(pList);
    pList = temp;
  }
  delete(pList);
}

template <class Item>
void List<Item>::vSetCur1(size_t index) const { //готово
  _pCur1 = (operator[](index));
}

template <class Item>
void List<Item>::vSetCur2(size_t index) const { //готово
  _pCur2 = (operator[](index)); 
}

template <class Item>
bool List<Item>::vCompare() { //готово
  return _pCur1->next->item < _pCur2->next->item;
}

template <class Item>
void List<Item>::vSwap() { //готово
  std::swap(_pCur1->next, _pCur2->next);
  std::swap(_pCur1->next->next, _pCur2->next->next);
  setCur1(0);
  setCur2(0);
}

template <class Item>
void List<Item>::vReplace() { //готово
  link temp = _pCur1->next;
  _pCur1->next = _pCur1->next->next;
  if(getCur1() > getCur1()) {
    temp->next = _pCur2->next;
    _pCur2->next = temp;
  } else {
    temp->next = _pCur2->next->next;
    _pCur2->next->next = temp;
  }
  setCur1(0);
  setCur2(0);
}

template <class Item>
void List<Item>::vRemove() { //готово
  size_t size = Size();
  link temp = _pCur1->next;
  _pCur1->next = _pCur1->next->next;
  delete(temp);
  setCur1(0);
  setSize(size - 1);
}

}

#endif
