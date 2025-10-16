#pragma once
#include "shape.h"

class Rectangle : public Shape {
  protected:
    double side1;
    double side2;
  
  public:
    Rectangle();
    ~Rectangle() = default;

    void setRectangle();

    void square() override;
    Shape::BoundingBoxDimensions dimensions() override;
    std::string type() override;
};