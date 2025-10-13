#include "forest.h"

int main() {
    std::cout << "Hello!\n";
    std::cout << "\n";

    Forest forest;
    forest.createForest();
    
    while(true) {        
        std::cout << "Search or EXIT to exit--> ";
        std::string elfToFind;
        getline(std::cin, elfToFind);
        
        if(elfToFind == "EXIT" || elfToFind == "Exit" || elfToFind == "exit") {
            break;
        } else if(elfToFind == "print") {
            forest.print();
        } else {
            forest.searchForElf(elfToFind);
        }
        
    }
    return 0;
    
}