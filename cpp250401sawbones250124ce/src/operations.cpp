#include <iostream>
#include "operations.h"

void scalpel(One_coordinate& coordinate_start, One_coordinate& coordinate_finish) {
    std::cout << " Make a cut from point: ";
    coordinate_start.input_coordinates(coordinate_start);
    std::cout << " to point: ";
    coordinate_finish.input_coordinates(coordinate_finish);
    std::cout << "The cut is successful.\n";
}

bool suture(One_coordinate& coordinate_start, One_coordinate& coordinate_finish, const One_coordinate& coordinates_scalpel_start, const One_coordinate& coordinates_scalpel_finish) {
    bool isSutureApplied {false};
    std::cout << "We put a seam from point: ";
    coordinate_start.input_coordinates(coordinate_start);
    std::cout << " to point: ";
    coordinate_finish.input_coordinates(coordinate_finish);
    if(coordinate_start.x == coordinates_scalpel_start.x 
            && coordinate_start.y == coordinates_scalpel_start.y 
            && coordinate_finish.x == coordinates_scalpel_finish.x
            && coordinate_finish.y == coordinates_scalpel_finish.y) {
        std::cout << "The suture is successful.\n";
        isSutureApplied = true;
    } else {
        std::cout << "The suture is not applied.\n";        
    }
    return isSutureApplied;
}

void hemostat(One_coordinate& coordinate) {
    std::cout << "Hemostat!\nPoint the point: ";
    coordinate.input_coordinates(coordinate);
    std::cout << "Hemostatic clamp successfully applied.\n";
}

void tweezers(One_coordinate& coordinate) {
    std::cout << "Tweezers!\nPoint the point: ";
    coordinate.input_coordinates(coordinate);
    std::cout << "Tweezers successfully applied.\n";
}

