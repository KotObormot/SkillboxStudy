#pragma once
#include "common.h"
#include "toy.h"

class Shared_ptr_toy {
  private:
    Toy* ptr = nullptr;
    size_t* counter = nullptr ;

  public:
    Shared_ptr_toy();
    
    Shared_ptr_toy(Toy*);

    Shared_ptr_toy(const std::string&);

    Shared_ptr_toy(const Shared_ptr_toy& other);

    // Assignment operator
    Shared_ptr_toy& operator=(const Shared_ptr_toy& other) /*const*/;

    Toy* get() const;

    void reset();

    size_t use_count() const;

    std::string getToyName();

    ~Shared_ptr_toy();
};

Shared_ptr_toy make_shared_toy(const std::string&);