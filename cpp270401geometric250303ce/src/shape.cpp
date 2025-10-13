#include "shape.h"

Shape::Shape() {}

Shape::~Shape() {}

void Shape::setXY() {
    std::cout << "Specify the coordinates of the center of the figure: X";
    int x = handlingIntInput();    
    this->x = x;
    std::cout << "      and Y";
    int y {handlingIntInput()};    
    this->y = y;
}

std::string Shape::getColor(const Color& color) {
    switch (color) {
        case Color::BLACK:
            return "black";
        case Color::RED:
            return "red";
        case Color::WHITE:
            return "white";
        case Color::GREEN:            
            return "green";        
        default:
            return "colorless";
    }
}

void Shape::printColor() {
    for(size_t i = static_cast<size_t>(Color::START) + 1; i < static_cast<size_t>(Color::END); i = i << 1) {
        Color clrTMP = static_cast<Color>(static_cast<size_t>(i));
        std::cout << "  * " << getColor(clrTMP) << "\n";
    }
}

void Shape::setColor() {
    std::cout << "Please select from the list provided:\n";
    printColor();
    std::cout << "color of the figure--> ";
    std::string clrTMP {correctCommandInput()};
    if(clrTMP == "red") {
        color = Color::RED;
    } else if(clrTMP == "white") {
        color = Color::WHITE;
    } else if(clrTMP == "black") {
        color = Color::BLACK;
    } else if(clrTMP == "green") {
        color = Color::GREEN;
    } 
}

std::string Shape::getFigure(const Figure& figre) {
    switch (figre) {
        case Figure::CIRCLE:
            return "circle";
        case Figure::RECTANGLE:
            return "rectangle";
        case Figure::SQUARE:
            return "square";
        case Figure::TRIANGLE:
            return "triangle";
        default:
            return "";
    }
}

void Shape::printArea(const double& areaFigure, const double& areaRectangle, const Figure& figure) {
    std::cout << " * Area of the " << getFigure(figure) << " = " << std::fixed << std::setprecision(2) << areaFigure 
              << ",\n * Area of the a rectangle that completely describes the " <<  getFigure(figure) << " = "
              << std:: fixed << std::setprecision(2) << areaRectangle
              << ",\n * Color of the circle = " << getColor(this->color)
              << "\n";
}

void Shape::setFigure() {}