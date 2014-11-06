#ifndef EASY_ALGORITHM_ITERATOR_H
#define EASY_ALGORITHM_ITERATOR_H

#include <iosfwd>
#include <cstddef>

namespace easy_algorithm {

class Iterator {
public:
  friend std::ostream& operator << (std::ostream& os, const Iterator& iter);        // Вывод значения элемента в поток
  friend const std::istream& operator >> (const std::istream& is, Iterator& iter);  // Ввод значения элемента из потока

  Iterator(const Iterator& iter);                               // Конструктор копирования. Создает итератор идентичный iter
  virtual ~Iterator();                                          // Виртуальный деструктор позволяет полиморфное удаление объектов
  
  Iterator& operator ++ ();                                     // Префиксный инкремент итератора
  Iterator& operator -- ();                                     // Префиксный декремент итератора
  const Iterator& operator += (ptrdiff_t diff);                 // Изменить позицию итератора на diff вперед
  const Iterator& operator -= (ptrdiff_t diff);                 // Изменить позицию итератора на diff назад
  const Iterator& operator = (const Iterator& iter);            // Делает итератор идентичным iter
  //Iterator& insert(Elem elem);                                  // Вставить элемент в позицию итератора
                                                                // (возвращает позицию вставленного элемента)
  void swap(Iterator& iter);                                    // Поменять значения, на которые указывают 2 итератора
  Iterator& replace(Iterator& iter);                            // Переместить значение, на которое указывает итератов позицию iter
  Iterator& remove();                                           // Удалить элемент, на который указывает итератор
  const ptrdiff_t operator - (const Iterator& iter);            // Возвращает количество элементов между двумя итераторами

  //Elem& operator * () const;                                    // Разыменование итератора
  //Elem* operator -> () const;                                   // Выбор члена элемента _pElem
  //Elem* getPointer() const;                                     // Возвращает указатель на элемент (_pElem)
  bool operator < (const Iterator& iter) const;                 // Сравнение значений, на которые указывают 2 итератора

private:
  virtual std::ostream& vPrint(std::ostream& os, const Iterator& iter) = 0;         // Вывод значения элемента в поток
  virtual const std::istream& vInput(const std::istream& is, Iterator& ds) = 0;     // Ввод значения элемента из потока

  virtual Iterator& vClone() = 0;                               // Возвращает ссылку на копию итератора (для конструктора копирования)

  virtual Iterator& vIncrease() = 0;                            // Соответствует operator ++
  virtual Iterator& vDecrease() = 0;                            // Соответствует operator --
  virtual const Iterator& vSeekIter(ptrdiff_t diff) = 0;        // Соответствует operator +=, operator -=
  virtual const Iterator& vAssign(const Iterator& iter) = 0;    // Соответствует =
  //virtual Iterator& vInsert(Elem elem) = 0;                     // Виртуальные функции соответствуют
  virtual void vSwap(Iterator& iter) = 0;                       // функциям интерфейса класса (без приставки v)
  virtual Iterator& vReplace(Iterator& iter) = 0;               // Обеспечивают полиморфное поведение объектов
  virtual Iterator& vRemove() = 0;
  virtual ptrdiff_t vDiff(const Iterator& iter) = 0;            // Соответствует operator -
  
  //Elem* _pElem;
};

/*const Iterator operator + (const Iterator& iter, ptrdiff_t diff);     // Возвращает итератор с позицией на diff больше
const Iterator operator + (ptrdiff_t diff, const Iterator& iter);
const Iterator operator - (const Iterator& iter, ptrdiff_t diff);     // Возвращает итератор с позицией на diff меньше
const Iterator operator ++ (Iterator& iter, int);                     // Постфиксный инкремент итератора
const Iterator operator -- (Iterator& iter, int);                     // Постфиксный декремент итератора*/
}

#endif