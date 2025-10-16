#pragma once
#include "common.h"
#include "loclib.h"
#include "talent.h"

class Dog {
  private:
    std::string name;
    std::vector<Talent*> talents;

  public:
    Dog() = default;
    ~Dog() = default;
    Dog(std::string);
    std::string getName();
    void setTalent(Talent*);
    void show_talents();
};