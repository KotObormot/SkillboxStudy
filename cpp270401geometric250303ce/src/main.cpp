#include <iostream>
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"

int main() {    
    std::cout << "Hello\n";
    std::string command {};
    bool isGameOver {false};
    while(!isGameOver) {
        std::cout << "user@computer:~$ ";
        std::string command {correctCommandInput()};
        while(command != "circle"
                && command != "square"
                && command != "triangle"
                && command != "rectangle"
                && command != "close") {
            std::cout << "Try again--> ";
            command = correctCommandInput();
        }

        if(command == "circle") {
            Circle circle;
            circle.shapeArea();
        } else if(command == "close") {
            std::cout << "Mischief managed.\n";
            isGameOver = true;
        } else if(command == "rectangle") {
            Rectangle rectangle;
            rectangle.shapeArea();
        } else if(command == "square") {
            Square square;
            square.shapeArea();
        } else if(command == "triangle") {
            Triangle triangle;
            triangle.shapeArea();
        }
    }
    return 0;

}