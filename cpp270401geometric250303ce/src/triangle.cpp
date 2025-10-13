#include "triangle.h"

Triangle::Triangle() {}

Triangle::~Triangle() {}

void Triangle::shapeArea() {
    this->setXY();
    this->setColor();
    std::cout << "Specify the edge of the equilateral triangle";
    this->edgeTriangle = handlingDouleInput();
    double areaTriangle {this->edgeTriangle * this->edgeTriangle * std::sqrt(3) / 4};
    double areaRectangle {this->edgeTriangle * this->edgeTriangle};
    printArea(areaTriangle, areaRectangle, Figure::TRIANGLE);
}