#include "toy.h"

Toy::Toy(const std::string& name) : name(name) {}

std::string Toy::getNmae() {
    return name;
}

std::shared_ptr<Dog> Toy::getDog() {
    auto sharedDog = playingDog.lock();
    return sharedDog;
}

void Toy::setDog(std::shared_ptr<Dog> dog) {
    playingDog = dog;
}

void Toy::droped() {
    playingDog.reset();
}

void Toy::print() {
    std::cout << name << ": " << this
              << "\tdog: " << playingDog.lock()
              << "\n"; 
}

Toy::~Toy() {
    std::cout << name << " is put away in the box." << "\n";
}