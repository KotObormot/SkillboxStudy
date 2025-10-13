#include <iostream>
#include "coordinate.h"
#include "double_input.h"

#define PRINT_RESULT false

void One_coordinate::input_coordinates(One_coordinate& coordinate) {
    std::cout << "specify X";
    coordinate.x = handling_invalid_input();
    std::cout << " and now Y";
    coordinate.y = handling_invalid_input();
    #if PRINT_RESULT
    std::cout << std::fixed
              << coordinate.x << " "
              << coordinate.y << "\n";
    #endif
}
