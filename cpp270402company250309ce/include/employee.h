#pragma once
#include <staff.h>

class Employee: public Staff {
  private:
    bool busy;
    int task;
  public:
    Employee();
    void does(int&) override;
    bool getBusy();
    void print() override;
};