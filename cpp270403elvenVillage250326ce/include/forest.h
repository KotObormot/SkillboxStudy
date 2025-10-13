#pragma once
#include <vector>
#include <ctime>
#include "branch.h"

const unsigned NUMBER_OF_TREES(5);

class Forest {
  private:
    std::vector<std::vector<std::vector<Branch>>> trees;
  public:
    void createForest();
    void searchForElf(const std::string&);
    void print();
};