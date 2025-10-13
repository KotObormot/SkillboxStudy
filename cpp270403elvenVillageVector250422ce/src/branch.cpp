#include "branch.h"

Branch::Branch(Branch* parent, const std::string& name): parent(parent), children(0), elfName(name) {}
    
Branch::~Branch() {
    for(size_t i(0); i < children.size(); ++i) {
        delete children[i];
        children[i] = nullptr;
    }
}

void Branch::addChild(Branch* child) {
    children.push_back(child);
}

std::string Branch::getElfName() {
    std::string nameTMP{};
    for (size_t i(0); i < elfName.size(); ++i)  {
        nameTMP += std::tolower(elfName[i]);
    }
    if (nameTMP != "none") {
        return elfName;
    } else {
        return "The house is not inhabited.";
    }
}

void Branch::print() {
    std::cout << "\t" << getElfName();
}

size_t randomNumber(size_t min, size_t max) {
    return (std::rand() % (max - min + 1)) + min;
}

std::string getLowerName(const std::string& name) {
    std::string nameTMP;
    for(size_t i(0); i < name.size(); ++i) {
        nameTMP += std::tolower(name[i]);
    }
    return nameTMP;
}