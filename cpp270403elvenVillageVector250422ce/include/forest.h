#pragma once
#include "branch.h"

class Forest {
  private:
    Branch* root;
  public:
    Forest();
    ~Forest();

    void create();

    void search(const std::string&, Branch*, bool&, std::vector<std::string>&);

    void findNeighbors(const std::string& name);

    void print();
};

