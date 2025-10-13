#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

const size_t NUMBER_OF_TREES(5);   // 5 trees
const size_t NUMBER_OF_LARGE_BRANCHES_MAX(5); // 3-5 main large branches.
const size_t NUMBER_OF_LARGE_BRANCHES_MIN(3);
const size_t NUMBER_OF_MIDDLE_BRANCHES_MAX(3); // 2-3 medium branches.
const size_t NUMBER_OF_MIDDLE_BRANCHES_MIN(2);

class Branch {
  public:
    Branch* parent;
    std::vector<Branch*> children;
    std::string elfName;

    Branch(Branch*, const std::string&);
    
    ~Branch();

    std::string getElfName();

    void addChild(Branch*);

    void print();
};

std::string getLowerName(const std::string&);
size_t randomNumber(size_t, size_t);