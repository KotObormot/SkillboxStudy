#pragma once
#include "common.h"
#include "store.h"

class Basket {
  private:
    Store store;
    std::map<std::string, int> basket;
  public:
    Basket() = default;
    ~Basket() = default;
    void add();
    void remove();
    void print();
    void printStore();
};