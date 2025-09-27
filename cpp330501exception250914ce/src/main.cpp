#include "common.h"
#include "store.h"
#include "basket.h"

int main() {
    std::cout << "Hello\n";
    std::cout << "\n--------------------------------\n";

    Basket basket;
    std::cout << "Enter ADD or REMOVE or EXIT for exit--> ";
    std::string command(correctCommandInput());
    while(true) {
        if(command == "close" || command == "exit") {
            break;
        } else if(command == "add") {
            basket.add();
        } else if(command == "remove") {
            basket.remove();
        } else if(command == "print") {
            basket.print();
            basket.printStore();
        }
        std::cout << "Enter ADD or REMOVE or EXIT for exit--> ";
        command = correctCommandInput();
    }
}
