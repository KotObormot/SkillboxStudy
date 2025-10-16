#include "common.h"
#include "dog.h"
#include "toy.h"

#define DEBUG true

int main() {
    std::cout << "Hello!\n";

    auto sharik {std::make_shared<Dog>("Sharik")};
    auto zhuchka {std::make_shared<Dog>("Zhuchka")};
    auto rex {std::make_shared<Dog>("Rex")};

    auto ball {std::make_shared<Toy>("Ball")};
    auto bone {std::make_shared<Toy>("Bone")};

    std::cout << "\n=========================\n";

    sharik->getToy(ball);

    std::cout << "\n***************************\n";
    zhuchka->getToy(bone);

    std::cout << "\n****************************\n";
    sharik->getToy(bone);

    std::cout << "\n***************************\n";
    zhuchka->getToy(bone);

    std::cout << "\n***************************\n";
    rex->getToy(ball);

    std::cout << "\n***************************\n";
    sharik->dropToy();

    std::cout << "\n***************************\n";
    rex->dropToy();

    std::cout << "\n***************************\n";
    sharik->dropToy();
    rex->getToy(ball);

    std::cout << "\n=========================\n";
    return 0;
}