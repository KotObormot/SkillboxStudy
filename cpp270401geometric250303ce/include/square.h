#pragma once
#include <cmath>
#include "rectangle.h"

class Square: public Rectangle {  //
  public:
    Square();
    ~Square();

    void shapeArea() override;
};