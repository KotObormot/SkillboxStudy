#include <iostream>
#include <string>
#include <limits> // для std::numeric_limits
#include "cci.h"

std::string correctCommandInput() {
    std::string command {};
    std::cin.clear();
    std::cin >> command;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i = 0; i < command.size(); ++i) {
        command[i] = std::tolower(command[i]);
    }
    return command;
}