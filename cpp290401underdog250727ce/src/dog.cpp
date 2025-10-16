#include "dog.h"

Dog::Dog(std::string name) : name(name) {
    this->name = name;
}

std::string Dog::getName() {
    return name;
}

void Dog::setTalent(Talent* talent) {
    talents.emplace_back(talent);
}

void Dog::show_talents() {
    std::cout << "This is " << name << " and it has some talents:\n";
    
    for(auto talent : talents) {
        std::cout << "\tIt can \"" << talent->getTalent() << "\".\n";
    }
}