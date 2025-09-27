#pragma once
#include "common.h"

class Laguna {
  private:
    std::vector<size_t> laguna;

  public:
    Laguna();
    ~Laguna() = default;

    void fishing();
    void print();
};