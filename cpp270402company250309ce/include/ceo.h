#pragma once
#include "staff.h"

class CEO: public Staff {
  public:
    CEO();
    void print() override;
    void does(int&) override;
};