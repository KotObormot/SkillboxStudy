#include "rectangle.h"

Rectangle::Rectangle() {
    std::cout << "Specify the sides of the rectangle:";
    side1 = handlingDoubleInput();
    side2 = handlingDoubleInput();
    
    while(true) {
        if((side1 > 0) && (side2 > 0)) {
            std::cout << "OK.\n";
            break;
        } else {
            std::cout << "Error: the rectangle is impossible. Try again.\n";
            side1 = handlingDoubleInput();
            side2 = handlingDoubleInput();
        }
    }
}

void Rectangle::square() {
    std::cout << "Square:\t" 
              << std::fixed << std::setprecision(2) 
              << side1 * side2 
              << "\n";
}

Shape::BoundingBoxDimensions Rectangle::dimensions() {
    BoundingBoxDimensions dimension;
    dimension.height = side1;
    dimension.width = side2;
    return dimension;
}

std::string Rectangle::type() {
    return "rectangle";
}