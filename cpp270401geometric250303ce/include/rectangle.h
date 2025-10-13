#pragma once
#include <cmath>
#include "shape.h"

class Rectangle: public Shape {  //круг
  public:
    double height;
    double width;
    Rectangle();
    ~Rectangle();

    virtual void shapeArea() override;
};