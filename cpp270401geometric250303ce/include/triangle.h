#pragma once
#include <iostream>
#include <cmath>
#include "shape.h"

class Triangle: public Shape {  //круг
  public:
    double edgeTriangle;
    Triangle();
    ~Triangle();

    void shapeArea() override;
};