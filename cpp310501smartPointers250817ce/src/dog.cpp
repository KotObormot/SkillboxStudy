#include "dog.h"

Dog::Dog(std::string name) : name(name) {}

Dog::~Dog() {
    std::cout << name << " has played enough and is sleeping.\n";
}

std::string Dog::getName() {
    return name;
}

void Dog::print() {
    std::cout << name  << "\t" << this
              << "\ttoy: " << toy.lock()
              << "\n";
}

void Dog::getToy(std::shared_ptr<Toy> toy) {
    std::cout << "Does the dog " << name << " want a toy " 
              << "\t" << toy->getNmae()
              << "?\n";

    if(toy->getDog()) {
        if(toy->getDog().get() == this) {
            // Если у собаки уже есть эта игрушка, необходимо вывести в консоль фразу I already have this toy.
            std::cout << name << " already has this toy " << toy->getNmae() << "\n";
        } else {
            // Если в данный момент игрушка находится у другой собаки, нужно вывести в консоль фразу Another dog is playing with this toy.
            std::cout << "Another dog, " << toy->getDog()->getName() << ", is playing with this toy " << toy->getNmae() << "\n";
        }
    } else {
        // Если игрушка свободна, собака подбирает её.
        this->toy = toy;

        auto sharedDog {shared_from_this()};
        toy->setDog(sharedDog);

        std::cout << name << " picks up " 
                << "\t" << std::shared_ptr<Toy>(this->toy)->getNmae()
                << "\n";
    }
}

void Dog::dropToy() {
    if(toy.lock()) {
        std::cout << name << " throws " << std::shared_ptr<Toy>(toy)->getNmae() << " on floor.\n";
        
        toy.lock()->droped();
        toy.reset();
    } else {
        std::cout << name << " has nothing to drop.\n";
    }
}