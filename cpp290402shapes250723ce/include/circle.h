#pragma once
#include "shape.h"

class Circle : public Shape {
  protected:
    double radius;
  public:
    Circle();
    ~Circle() = default;

    void square() override;
    Shape::BoundingBoxDimensions dimensions() override;
    std::string type() override;
};
