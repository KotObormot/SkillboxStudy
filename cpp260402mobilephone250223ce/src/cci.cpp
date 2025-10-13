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

std::string standardString(std::string& anyString) {
    std::string standardString {};    
    for(int i {0}; i < anyString.size(); ++i) {
        char symbol = anyString[i];
        if(std::isdigit(symbol)) {
            standardString += symbol;
        } else if(symbol >= 'A' && symbol <= 'Z'
                || symbol >= 'a' && symbol <= 'z') {
            standardString += std::tolower(symbol);
        }
    }    
    return standardString;
}