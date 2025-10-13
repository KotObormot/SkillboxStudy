#include "ceo.h"

CEO::CEO() {
    std::cout << "Enter the name of CEO of the enterprise--> ";
    getline(std::cin, name);
}

void CEO::does(int& instructionFromCEO) {    
    std::cout << "Enter an integer that correspond to the CEO's instructions";
    instructionFromCEO = handlingIntInput();
}

void CEO::print() {
    std::cout << "CEO " << name << " (staffID " << getStaffID() << ") "
              << " manages the strategy. He determines the main vector of movement - the top-level tasks.\n";
}