#include "circle.h"

Circle::Circle() {
    std::cout << "Specify the radius of your favorite circle:";
    radius = handlingDoubleInput();

    while(true) {
        if(radius > 0) {
            std::cout << "OK\n";
            break;
        }
        std::cout << "Error: this circle is impossible. Try again.\n";
        radius = handlingDoubleInput();
    }
}

void Circle::square() {
    std::cout << "Square:\t" 
              << std::fixed << std::setprecision(2) 
              << getPI() * radius * radius 
              << "\n";
}

Shape::BoundingBoxDimensions Circle::dimensions() {
    BoundingBoxDimensions dimension;
    dimension.height = dimension.width = 2 * radius;
    return dimension;
}

std::string Circle::type() {
    return "circle";
}