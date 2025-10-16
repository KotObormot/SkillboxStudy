#pragma once
#include "shape.h"

class Triangle : public Shape {  //
  private:
    double sideA;
    double sideB;
    double sideC;

  public:    
    Triangle();
    ~Triangle() = default;

    void square() override;
    BoundingBoxDimensions dimensions() override;
    std::string type() override;
};