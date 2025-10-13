#include <iostream>
#include "rectangle.h"

Rectangle::Rectangle() {}

Rectangle::~Rectangle() {}

void Rectangle::shapeArea() {
    this->setXY();
    this->setColor();
    std::cout << "Specify the sides of the rectangle: height";
    this->height = handlingDouleInput();    
    std::cout << "      and width";
    this->width = handlingDouleInput();
    double areaFigure {this->width * this->height};
    printArea(areaFigure, areaFigure, Figure::RECTANGLE);
}