#pragma once
#include "common.h"

class Toy {
  public:
    Toy() = default;
    Toy(const std::string&);
    ~Toy();
    std::string getNmae();

  private:
    std::string name;
};