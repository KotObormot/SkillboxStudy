#pragma once
#include "common.h"
#include "toy.h"

class Dog : public std::enable_shared_from_this<Dog> {
  private:
    std::string name;
    std::weak_ptr<Toy> toy;

  public:
    Dog() = default;
    ~Dog();
    Dog(std::string);
    std::string getName();
    void print();
    void getToy(std::shared_ptr<Toy>);
    void dropToy();
};