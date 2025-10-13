#pragma once

#include <string>
#include "cci.h"
#include "timer.h"

class Address {
  private:
    std::string phone {};
    std::string name {};
  public:
    Address(std::string phone, std::string name);
    Address(const Address& addrss);
    Address();
    ~Address();
    Address addAddress(std::string&);
    Address addAddress();
    void printAddress();
    void standardFields(std::string& searchString);
    void callAddress();
    void smsAddress();
    void setPhone(std::string phone);
    void setName(std::string name);
    std::string getPhone();
    std::string getName();    
};