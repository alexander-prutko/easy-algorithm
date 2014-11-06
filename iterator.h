#ifndef EASY_ALGORITHM_ITERATOR_H
#define EASY_ALGORITHM_ITERATOR_H

#include <iosfwd>
#include <cstddef>

namespace easy_algorithm {

class Iterator {
public:
  friend std::ostream& operator << (std::ostream& os, const Iterator& iter);        // ����� �������� �������� � �����
  friend const std::istream& operator >> (const std::istream& is, Iterator& iter);  // ���� �������� �������� �� ������

  Iterator(const Iterator& iter);                               // ����������� �����������. ������� �������� ���������� iter
  virtual ~Iterator();                                          // ����������� ���������� ��������� ����������� �������� ��������
  
  Iterator& operator ++ ();                                     // ���������� ��������� ���������
  Iterator& operator -- ();                                     // ���������� ��������� ���������
  const Iterator& operator += (ptrdiff_t diff);                 // �������� ������� ��������� �� diff ������
  const Iterator& operator -= (ptrdiff_t diff);                 // �������� ������� ��������� �� diff �����
  const Iterator& operator = (const Iterator& iter);            // ������ �������� ���������� iter
  //Iterator& insert(Elem elem);                                  // �������� ������� � ������� ���������
                                                                // (���������� ������� ������������ ��������)
  void swap(Iterator& iter);                                    // �������� ��������, �� ������� ��������� 2 ���������
  Iterator& replace(Iterator& iter);                            // ����������� ��������, �� ������� ��������� �������� ������� iter
  Iterator& remove();                                           // ������� �������, �� ������� ��������� ��������
  const ptrdiff_t operator - (const Iterator& iter);            // ���������� ���������� ��������� ����� ����� �����������

  //Elem& operator * () const;                                    // ������������� ���������
  //Elem* operator -> () const;                                   // ����� ����� �������� _pElem
  //Elem* getPointer() const;                                     // ���������� ��������� �� ������� (_pElem)
  bool operator < (const Iterator& iter) const;                 // ��������� ��������, �� ������� ��������� 2 ���������

private:
  virtual std::ostream& vPrint(std::ostream& os, const Iterator& iter) = 0;         // ����� �������� �������� � �����
  virtual const std::istream& vInput(const std::istream& is, Iterator& ds) = 0;     // ���� �������� �������� �� ������

  virtual Iterator& vClone() = 0;                               // ���������� ������ �� ����� ��������� (��� ������������ �����������)

  virtual Iterator& vIncrease() = 0;                            // ������������� operator ++
  virtual Iterator& vDecrease() = 0;                            // ������������� operator --
  virtual const Iterator& vSeekIter(ptrdiff_t diff) = 0;        // ������������� operator +=, operator -=
  virtual const Iterator& vAssign(const Iterator& iter) = 0;    // ������������� =
  //virtual Iterator& vInsert(Elem elem) = 0;                     // ����������� ������� �������������
  virtual void vSwap(Iterator& iter) = 0;                       // �������� ���������� ������ (��� ��������� v)
  virtual Iterator& vReplace(Iterator& iter) = 0;               // ������������ ����������� ��������� ��������
  virtual Iterator& vRemove() = 0;
  virtual ptrdiff_t vDiff(const Iterator& iter) = 0;            // ������������� operator -
  
  //Elem* _pElem;
};

/*const Iterator operator + (const Iterator& iter, ptrdiff_t diff);     // ���������� �������� � �������� �� diff ������
const Iterator operator + (ptrdiff_t diff, const Iterator& iter);
const Iterator operator - (const Iterator& iter, ptrdiff_t diff);     // ���������� �������� � �������� �� diff ������
const Iterator operator ++ (Iterator& iter, int);                     // ����������� ��������� ���������
const Iterator operator -- (Iterator& iter, int);                     // ����������� ��������� ���������*/
}

#endif