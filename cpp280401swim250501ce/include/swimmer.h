#pragma once
#include "constant_variables.h"

class Swimmer {
  private:
    double velocity;    // meters per second
    double distance;    // swimmer has swum at any given moment
    double timeTaken;   // swim completion time
    bool isFinish;      // did the swimmer finish?
    std::string name;   // name

  public:
    Swimmer();
    ~Swimmer() = default;
    std::string getName();
    double getVelocity();
    double getDistance();
    bool getIsFinish();
    double getTimeTaken();
    void timeLine();
};
