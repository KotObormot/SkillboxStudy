#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "cci.h"

#define DEBUG false

class Staff {  
  private:
    #if DEBUG
    static inline unsigned staffNumber {0};  //inline variables are only available with ‘-std=c++17’ or ‘-std=gnu++17’ [-Wc++17-extensions]
    #else
    static unsigned staffNumber;
    #endif
    unsigned staffID;
  protected:
    std::string name;
    Staff();
    virtual void does(int&) = 0;
    virtual void print() = 0;
  public:
    static unsigned getStaffNumber();
    std::string getName();
    unsigned getStaffID();
};