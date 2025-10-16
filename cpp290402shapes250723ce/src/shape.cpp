#include "shape.h"

void Shape::printParams(Shape* shape) {
    std::cout << "Type:\t" << shape->type() << "\n";
    shape->square();
    std::cout << "Bounding rectangle dimensions:"
              << "\n" << " * Width:\t" << shape->dimensions().width
              << "\n" << " * Height:\t" << shape->dimensions().height
              << "\n";  
}