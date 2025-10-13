#include <iostream>
#include "monitor.h"
#include "window.h"
#include "cci.h"

const int MONITOR_WIDTH {80};
const int MONITOR_HEIGHT {50};

#define DEBUG true

int main () {
    std::cout << "Hello\n";
    std::string command {};
    bool isGameOver {false};
    Monitor console(MONITOR_WIDTH, MONITOR_HEIGHT);
        
    while(!isGameOver) {
        std::cout << "user@computer:~$ ";
        std::string command {correctCommandInput()};
        while(command != "display" 
                && command != "resize"
                && command != "move"
                && command != "close") {
            std::cout << "Try again--> ";
            command = correctCommandInput();
        }

        if(command == "display") {
            console.display();
        } else if(command == "close") {
            isGameOver = true;
        } else if(command == "move") {
            console.move();
        } else if(command == "resize") {
            console.resize();
        }
    }
    return 0;
}