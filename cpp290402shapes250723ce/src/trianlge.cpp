#include "trianlge.h"

Triangle::Triangle() {
    std::cout << "Specify the sides of the triangle:";
    sideA = handlingDoubleInput();
    sideB = handlingDoubleInput();
    sideC = handlingDoubleInput();
    
    while(true) {
        if((sideA > 0)
                && (sideB > 0)
                && (sideC > 0)
                && (sideA + sideB > sideC)
                && (sideA + sideC > sideB)
                && (sideB + sideC > sideA)) {
            std::cout << "OK\n";
            break;
        } else {
            std::cout << "Error: triangle is impossible. Try again.\n";
            sideA = handlingDoubleInput();
            sideB = handlingDoubleInput();
            sideC = handlingDoubleInput();
        }
    }
}

void Triangle::square() {
    double semiperimeter((sideA + sideB + sideC) / 2);
    double square(std::sqrt(semiperimeter                         // sqrt(p * (p - a) * (p - b) * (p - c))
                            * (semiperimeter - sideA)
                            * (semiperimeter - sideB)
                            * (semiperimeter - sideC)));
    std::cout << "Square:\t" << std::fixed << std::setprecision(2) << square << "\n";    
}

Shape::BoundingBoxDimensions Triangle::dimensions() {
    double semiperimeter((sideA + sideB + sideC) / 2);
    double sideMax((std::max(std::max(sideA, sideB), sideC)));
    BoundingBoxDimensions dimensions;
    dimensions.height = (2 / sideMax) * std::sqrt(semiperimeter                         // 
                                      * (semiperimeter - sideA)
                                      * (semiperimeter - sideB)
                                      * (semiperimeter - sideC));
    dimensions.width = sideMax;
    return dimensions;
}

std::string Triangle::type() {
    return "triangle";
}