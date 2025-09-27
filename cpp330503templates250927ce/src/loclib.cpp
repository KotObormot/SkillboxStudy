#include "loclib.h"

int randomNumber(int min, int max) {
    return (std::rand() % (max - min + 1)) + min;
}

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

std::string correctCommandInput(const std::string& cmd) {
    std::string command {};
    while(true) {
        std::cin.clear();
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int i = 0; i < command.size(); ++i) {
            command[i] = std::tolower(command[i]);
        }
        if(command == cmd) {
            return command;
        } else {
            std::cout << "Error. Please use '" << cmd << "'.\n";
        }
    }
}

std::string normString(const std::string& badString) {
    std::string normString{};
        for(size_t i(0); i < badString.size(); ++i) {
            normString += std::tolower(badString[i]);
        }
    return normString;
}

const double getPI() {
    return std::atan(1.0) * 4;
    // return acos(-1.0);
}

const double getE() {
    return std::exp(1.0);
}