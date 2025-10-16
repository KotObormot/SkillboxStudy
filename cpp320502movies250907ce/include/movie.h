#pragma once
#include "common.h"

struct Movie {
    std::string country;
    int year;
    std::string studio;
    std::vector<std::string> writers;
    std::string director;
    std::string producer;
    std::string composer;
    std::map<std::string, std::string> cast;

    Movie() = default;
    ~Movie() = default;
    void print();
};
