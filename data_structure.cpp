#include "data_structure.h"
#include <stdexcept>

namespace easy_algorithm {

const char* LengthError = "Unable to insert a new itement!";    // Сообщения при генерировании исключений
const char* IndexError = "Index is out of range!";

void DataStructure::checkIndex(size_t index) const {
  if((index >= _size || index < 0))
    throw std::out_of_range(IndexError);
}

DataStructure::DataStructure(size_t maxSize)
  : _size(0), _maxSize(maxSize), _cur1(0), _cur2(0) {}

DataStructure::DataStructure(const DataStructure& ds)
  : _size(ds.Size()), _maxSize(ds.maxSize()), _cur1(0), _cur2(0) {
}

DataStructure::~DataStructure() {}

size_t DataStructure::Size() const {
  return _size;
}

void DataStructure::setSize(size_t size) {
  _size = size;
}

size_t DataStructure::maxSize() const {
  return _maxSize;
}

void DataStructure::setMaxSize(size_t size) {
  _maxSize = size;
}

bool DataStructure::empty() const {
  return _size == 0 ? true : false;
}

std::ostream& operator << (std::ostream& os, const DataStructure& ds) {
  return ds.vPrint(os, ds);
}

std::istream& operator >> (std::istream& is, DataStructure& ds) {
  return ds.vInput(is, ds);
}

void DataStructure::swap(size_t index1, size_t index2) {
  checkIndex(index1);
  checkIndex(index2);
  if(index1 != index2) {
    setCur1(index1);
    setCur2(index2);
    vSwap();
  }
}

void DataStructure::swap(DataStructure& ds) {
  vSwap(ds);
}

void DataStructure::move(size_t source, size_t dest) {
  checkIndex(source);
  checkIndex(dest);
  if(source != dest) {
    setCur1(source);
    setCur2(dest);
    vMove();
  }
}


void DataStructure::remove(size_t index) {
  checkIndex(index);
  setCur1(index);
  vRemove();
}

const DataStructure& DataStructure::operator = (const DataStructure& ds) {
  vAssign(ds);
  return *this;
}

bool DataStructure::compare(size_t index1, size_t index2) const {
  checkIndex(index1);
  checkIndex(index2);
  setCur1(index1);
  setCur2(index2);
  return vCompare();
}

void DataStructure::setCur1(size_t index) const {
  checkIndex(index);
  vSetCur1(index);
  _cur1 = index;
}

void DataStructure::setCur2(size_t index) const {
  checkIndex(index);
  vSetCur2(index);
  _cur2 = index;
}

size_t DataStructure::getCur1() const {
  return _cur1;
}

size_t DataStructure::getCur2() const {
  return _cur2;
}

bool DataStructure::compare() const {
  if (_cur1 != _cur2)
    return vCompare();
  return false;
}

void DataStructure::swap() {
  if (_cur1 != _cur2)
    vSwap();
}

void DataStructure::move() {
  if (_cur1 != _cur2)
    vMove();
}

void DataStructure::remove() {
  vRemove();
}

}
