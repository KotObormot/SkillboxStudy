#include "branch.h"

void Branch::setName() {
    std::cout << "What is the elf's name?--> ";
    getline(std::cin, name);
}

std::string Branch::getName() {
    std::string nameTMP {};
    for(size_t i(0); i < name.size(); ++i) {
        nameTMP += std::tolower(name[i]);
    }
    if(nameTMP != "none") {
        return name; 
    } else {
        return "The house is not inhabited.";
    }
}

std::string Branch::getLowerName() {
    std::string nameTMP;
    for(size_t i(0); i < name.size(); ++i) {
        nameTMP += std::tolower(name[i]);
    }
    return nameTMP;
}