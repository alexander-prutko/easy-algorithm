#include "data_structure.h"
#include <stdexcept>

namespace easy_algorithm {

bool DataStructure::checkIndex(size_t index) {
  return !(index >= _size || index < 0);
}

DataStructure::DataStructure(size_t maxSize)
  : _size(0), _maxSize(maxSize) {}

DataStructure::DataStructure(const DataStructure& ds)
  : _size(ds.size()), _maxSize(ds.maxSize()) {
//  *this = ds.vClone();
}

/*DataStructure::DataStructure(const Iterator& beg, const Iterator& end)
  : _size(0), _maxSize(end-beg) {
  for(Iterator iter = beg; beg != end; ++iter)
    insert(*iter);
}*/

size_t DataStructure::size() const {
  return _size;
}

size_t DataStructure::maxSize() const {
  return _maxSize;
}

bool DataStructure::empty() const {
  return _size == 0 ? true : false;
}

std::ostream& operator << (std::ostream& os, const DataStructure& ds) {
  return ds.vPrint(os, ds);
}

const std::istream& operator >> (const std::istream& is, DataStructure& ds) {
  return ds.vInput(is, ds);
}

/*void DataStructure::insert(Elem elem, size_t index = _size - 1) {
  if(_size == _maxSize)
    throw std::length_error(LengthError);
  if(index > _size || index < 0)
    throw std::out_of_range(IndexError);
  vInsert(elem, index);
  ++_size;
}*/


void DataStructure::swap(size_t index1, size_t index2) {
  if(!checkIndex(index1) || !checkIndex(index2))
    throw std::out_of_range(IndexError);
  if(index1 != index2)
    vSwap(index1, index2);
}

void DataStructure::swap(DataStructure& ds) {
  vSwap(ds);
}

void DataStructure::replace(size_t source, size_t dest) {
  if(!checkIndex(source) || !checkIndex(dest))
    throw std::out_of_range(IndexError);
  if(source != dest)
    vReplace(source, dest);
}


void DataStructure::remove(size_t index) {
  if(!checkIndex(index))
    throw std::out_of_range(IndexError);
  vRemove(index);
}

/*Iterator DataStructure::begin() const {
  return vBegin();
}*/

/*Iterator DataStructure::end() const {
  return vEnd();
}*/

/*Elem& DataStructure::operator [] (size_t index) {
  if(!checkIndex(index))
    throw std::out_of_range(IndexError);
  return vGet(index);
}*/

/*const Elem& DataStructure::operator [] (size_t index) const {
  if(!checkIndex(index))
    throw std::out_of_range(IndexError);
  return vGet(index);
}*/

const DataStructure& DataStructure::operator = (const DataStructure& ds) {
  vAssign(ds);
  return *this;
//  DataStructure temp(ds);
//  vSwap(temp);
}



}