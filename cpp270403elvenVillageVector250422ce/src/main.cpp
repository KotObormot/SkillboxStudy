#include "branch.h"
#include "forest.h"

int main() {
    std::srand(std::time(nullptr));
    std::cout << "Hello!\n";

    Forest forest;
    forest.create();
    
    std::cout << "\n======================\n";

    while (true) {
        std::string elfToFind;
        std::cout << "Search or EXIT to exit--> ";
        getline(std::cin, elfToFind);

        if(getLowerName(elfToFind) == "exit") {
            break;
        } else if(getLowerName(elfToFind) == "print") {
            forest.print();
        } else {
            forest.findNeighbors(elfToFind);
        }
    }

    return 0;
}
