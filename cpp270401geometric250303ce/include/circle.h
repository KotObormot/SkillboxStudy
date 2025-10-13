#pragma once
#include <cmath>
#include "shape.h"

class Circle: public Shape {  //круг
  public:
    double radius;
    Circle();
    ~Circle();

    void shapeArea() override;
};