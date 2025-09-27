#pragma once
#include "common.h"

class Store {
  private:
    std::map<std::string, int> store;

  public:
    Store();
    ~Store();
    
    void print();
    std::map<std::string, int>::iterator checkProduct(std::string&);
    void checkNumber(std::map<std::string, int>::iterator, int);
};
