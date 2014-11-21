#ifndef EASY_ALGORITHM_POD_H
#define EASY_ALGORITHM_POD_H

#include <string>

namespace easy_algorithm {

std::string randomString() {            // Генерирует String из случайной последовательности [0-9]
  std::string ret(100, '\0');
  for(int i = 0; i < 100; ++i)
    ret[i] = '0' + rand() % 10;
  return ret;
}

void delay() {
  for(int i = 0; i<100;++i) 
    i=i;
}

struct PODss {                          // Структура с маленьким ключом и маленьким значением
  PODss() : key(rand()) {}
  int key;
  char value[1];
  bool operator < (PODss& p) { return key < p.key; }
  friend std::ostream& operator << (std::ostream& os, const PODss& pod) {
    os << pod.key;
    return os;
  }
  friend std::istream& operator >> (std::istream& is, PODss& pod) {
    int temp;
    is >> temp;
    if(!(is.rdstate() & std::ios::failbit))
      pod.key = temp;
    return is;
  }
};

struct PODsb {                          // Структура с маленьким ключом и большим значением
  PODsb() : key(rand()) {}
  int key;
  char value[10240];
  bool operator < (PODsb& p) { return key < p.key; }
  friend std::ostream& operator << (std::ostream& os, const PODsb& pod) {
    os << pod.key;
    return os;
  }
  friend std::istream& operator >> (std::istream& is, PODsb& pod) {
    int temp;
    is >> temp;
    if(!(is.rdstate() & std::ios::failbit))
      pod.key = temp;
    return is;
  }
};

struct PODbs {                          // Структура с большим ключом и маленьким значением
  PODbs() : key(randomString()) {}
  std::string key;
  char value[1];
  bool operator < (PODbs& p) {
    //delay();
    return key < p.key; 
  }
  friend std::ostream& operator << (std::ostream& os, const PODbs& pod) {
    os << pod.key;
    return os;
  }
  friend std::istream& operator >> (std::istream& is, PODbs& pod) {
    std::string temp;
    is >> temp;
    if(!(is.rdstate() & std::ios::failbit))
      pod.key = temp;
    return is;
  }
};

struct PODbb {                          // Структура с большим ключом и большим значением
  PODbb() : key(randomString()) {}
  std::string key;
  char value[10240];
  bool operator < (PODbb& p) {
    //delay();
    return key < p.key; 
  }
  friend std::ostream& operator << (std::ostream& os, const PODbb& pod) {
    os << pod.key;
    return os;
  }
  friend std::istream& operator >> (std::istream& is, PODbb& pod) {
    std::string temp;
    is >> temp;
    if(!(is.rdstate() & std::ios::failbit))
      pod.key = temp;
    return is;
  }
};

}

#endif