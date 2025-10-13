#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <limits> // для std::numeric_limits
#include <fstream>
#include "Address.h"
#include "cci.h"

class Phone {
  private:
    std::map<std::string, Address> phoneBook;
    void addAddressInBook(std::string&);
    std::vector<std::map<std::string, Address>::iterator> findPhone(std::string& phoneLooking);
    std::vector<std::map<std::string, Address>::iterator> findName(std::string& nameLooking);
  public:
    void saveBook();
    bool loadBook();
    void addAddressInBook();
    void show ();
    void call();
    void sms();
};
