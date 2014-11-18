#include "sort.h"

namespace easy_algorithm {

Sort::Sort(DataStructure* ds, SortAlgorithm* sa, TimeObserver* to) : _pDS(ds), _pSA(sa), _pTO(to) {}

void Sort::sort() {
  _pSA->sort(_pDS, _pTO);
}

void Sort::setTimeObserver(TimeObserver* pTO) {
  if(!pTO)
    throw std::exception();
  _pTO = pTO;
  _pTO->reset();
}

void Sort::setDataStructure(DataStructure* pDS) {
  if(!pDS)
    throw std::exception();
  _pDS = pDS;
}

void Sort::setSortAlgorithm(SortAlgorithm* pSA) {
  if(!pSA)
    throw std::exception();
  _pSA = pSA;
}

void Sort::resetTimeObserver() {
  _pTO->reset();
}

double Sort::getComparisonTime() {
  return _pTO->getComparisonTime();
}

double Sort::getAssignmentTime() {
  return _pTO->getAssignmentTime();
}

double Sort::getTotalTime() {
  return _pTO->getTotalTime();
}

double Sort::getSearchTime() {
  return _pTO->getSearchTime();
}

}
