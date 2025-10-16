#pragma once
#include "common.h"
#include "movie.h"

class Movies {
  private:
    std::map<std::string, Movie> movieCollection;

  public:
    Movies() = default;
    ~Movies() = default;
    void print();
    void read();
    void search(const std::string&);
};