#include "toy.h"

Toy::Toy(const std::string& name) : name(name) {}

std::string Toy::getNmae() {
    return name;
}

Toy::~Toy() {
    std::cout << "Toy " << name << " was dropped." << "\n";
}