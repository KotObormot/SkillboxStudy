#pragma once
#include <iostream>
#include <string>

class Branch {
  private:
    std::string name {"Some Elf"};
  public:
    void setName();
    std::string getName();
    std::string getLowerName();
};