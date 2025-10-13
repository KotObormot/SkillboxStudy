#include <iostream>
#include "square.h"

Square::Square() {}

Square::~Square() {}

void Square::shapeArea() {
    this->setXY();
    this->setColor();
    std::cout << "Specify the side of the square";
    this->height = handlingDouleInput();
    double areaSquare {this->height * this->height};
    printArea(areaSquare, areaSquare, Figure::SQUARE);
}