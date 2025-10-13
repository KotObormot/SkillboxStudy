#include <iostream>
#include "circle.h"

Circle::Circle() {}

Circle::~Circle() {}

void Circle::shapeArea() {
    this->setXY();
    this->setColor();
    std::cout << "Specify radius of the circle";
    this->radius = handlingDouleInput();
    double areaCircle {atan(1) * 4 * this->radius};
    double areaRectangle {4.00f * this->radius * this->radius};
    printArea(areaCircle, areaRectangle, Figure::CIRCLE);
}