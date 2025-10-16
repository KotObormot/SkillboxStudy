#include "common.h"
#include "loclib.h"
#include "shape.h"
#include "trianlge.h"
#include "circle.h"
#include "rectangle.h"

int main() {
    std::cout << "Hello!\n"
              << "Please enter the shape type or 'close' to exit:"
              << "\n";
    std::string command {};

    while(true) {
        std::cout << "user@computer:~$ ";
        std::string command {correctCommandInput()};
        if(command == "close") {
            std::cout << "Mischief managed.\n";
            break;
        }
        while(command != "circle"
                && command != "triangle"
                && command != "rectangle"
                && command != "close") {
            std::cout << "Try again--> ";
            command = correctCommandInput();
        }

        if(command == "circle") {
            Circle circle;
            Shape::printParams(&circle);
        } else if(command == "rectangle") {
            Rectangle rectangle;
            Shape::printParams(&rectangle);
        } else if(command == "triangle") {
            Triangle triangle;
            Shape::printParams(&triangle);
        }
    }
    return 0;
}