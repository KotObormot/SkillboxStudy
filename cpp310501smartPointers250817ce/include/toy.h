#pragma once
#include "common.h"
#include "dog.h"

class Toy {
  public:
    Toy() = default;
    Toy(const std::string&);
    ~Toy();
    std::string getNmae();
    std::shared_ptr<Dog> getDog();
    void setDog(std::shared_ptr<Dog>);
    void droped();
    void print();

  private:
    std::string name;
    std::weak_ptr<Dog> playingDog;
};