#ifndef EASY_ALGORITHM_DATA_STRUCTURE_H
#define EASY_ALGORITHM_DATA_STRUCTURE_H

#include <iosfwd>
//#include "iterator.h"
//class Iterator;
template <class Item>
class Array;

namespace easy_algorithm {

class DataStructure {
public:
  friend std::ostream& operator << (std::ostream& os, const DataStructure& ds);         // ����� ��������� ������ � �����
  friend const std::istream& operator >> (const std::istream& is, DataStructure& ds);   // ���� ��������� ������ �� ������

  template <class Item>
  static DataStructure* createArray(size_t maxSize);
  template <class Item>
  static DataStructure* createArray(const DataStructure& array);
  
  virtual ~DataStructure(){}                              // ����������� ���������� ��������� ����������� �������� ��������

  //void insert(Elem elem, size_t index = _size - 1);     // �������� ������� elem � ������� index
  void swap(size_t index1, size_t index2);              // �������� ������� 2 �������� � ��������� index1 � index2
  void swap(DataStructure& ds);                         // �������� ��������� ������
  void replace(size_t source, size_t dest);             // ����������� ������� � �������� source � ������� dest
  void remove(size_t index);                // ������� ������� � �������� index
  //Iterator begin() const;                               // ���������� �������� �� ������ ��������� ������
  //Iterator end() const;                                 // ���������� �������� �� ����� ��������� ������
  //Elem& operator [] (size_t index);                     // ���������� ������ �� ������� � �������� index
  //const Elem& operator [] (size_t index) const;
  const DataStructure& operator = (const DataStructure& ds);    // ������ ���������� ��������� ������ ���������� ds
  
  size_t size() const;                            // ���������� ���������� ���������
  size_t maxSize() const;                         // ���������� ������������ ������ ��������� ������
  bool empty() const;                             // ���������� true, ���� ��������� ���
protected:
  const char* LengthError = "Unable to insert a new element!";
  const char* IndexError = "Index is out of range!";
  explicit DataStructure(size_t maxSize);                 // �����������, �������� ������������ ������ ��������� ������
                                                          // (�� ��������� �������� ��������������)
  DataStructure(const DataStructure& ds);                 // ����������� �����������
  //DataStructure(const Iterator& beg, const Iterator& end);            // �����������, ���������������� � ������� ����������

  bool checkIndex(size_t index);                  // �������� �������
private:
  virtual std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const = 0;          // ����� ��������� ������ � �����
  virtual const std::istream& vInput(const std::istream& is, DataStructure& ds) = 0;    // ���� ��������� ������ �� ������

public:
  /////virtual DataStructure& vClone() const = 0;                            // ���������� ������ �� ����� ��������� ������
private:                                                                        // (��� ������������ �����������)

  //virtual void vInsert(Elem elem, size_t index) = 0;                  // ����������� ������� �������������
  virtual void vSwap(size_t index1, size_t index2) = 0;                 // �������� ���������� ������ (��� ��������� v)
  virtual void vSwap(DataStructure& ds) = 0;                            // ������������ ����������� ��������� ��������
  virtual void vReplace(size_t source, size_t dest) = 0;                
  virtual void vRemove(size_t index) = 0;
  //virtual Iterator vBegin() const = 0;
  //virtual Iterator vEnd() const = 0;
  //virtual Elem& vGet(size_t index) = 0;                                 // ������������� operator []
  //virtual const Elem& vGet(size_t index) const = 0;
  virtual const DataStructure& vAssign(const DataStructure& ds) = 0;    // ������������� operator =
  
  

  size_t _size;
  size_t _maxSize;
};

template <class Item>
static DataStructure* DataStructure::createArray(size_t maxSize) {
  return new Array<Item>(5);
}

template <class Item>
static DataStructure* DataStructure::createArray(const DataStructure& array) {
  return new Array<Item>(array);
}

}

#endif