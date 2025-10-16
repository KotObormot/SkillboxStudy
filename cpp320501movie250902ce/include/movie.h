#pragma once
#include "common.h"

class Movie {
  private:
    std::string title;
    std::string country;
    int year;
    std::string studio;
    std::vector<std::string> writers;
    std::string director;
    std::string producer;
    std::string composer;
    std::map<std::string, std::string> cast;

  public:
    Movie() = default;
    ~Movie() = default;

//    void make();
    void make_tmp();
    void print();
    void write();
    void read();
};